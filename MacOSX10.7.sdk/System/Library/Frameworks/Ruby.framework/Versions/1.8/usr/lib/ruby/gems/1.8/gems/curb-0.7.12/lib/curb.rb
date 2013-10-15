require 'curb_core'

module Curl

  class Easy
    class << self
    
      # call-seq:
      #   Curl::Easy.download(url, filename = url.split(/\?/).first.split(/\//).last) { |curl| ... }
      #   
      # Stream the specified url (via perform) and save the data directly to the
      # supplied filename (defaults to the last component of the URL path, which will 
      # usually be the filename most simple urls).
      # 
      # If a block is supplied, it will be passed the curl instance prior to the
      # perform call.
      # 
      # *Note* that the semantics of the on_body handler are subtly changed when using
      # download, to account for the automatic routing of data to the specified file: The 
      # data string is passed to the handler *before* it is written
      # to the file, allowing the handler to perform mutative operations where 
      # necessary. As usual, the transfer will be aborted if the on_body handler
      # returns a size that differs from the data chunk size - in this case, the 
      # offending chunk will *not* be written to the file, the file will be closed,
      # and a Curl::Err::AbortedByCallbackError will be raised.
      def download(url, filename = url.split(/\?/).first.split(/\//).last, &blk)
        curl = Curl::Easy.new(url, &blk)
        
        output = if filename.is_a? IO
          filename.binmode if filename.respond_to?(:binmode)
          filename
        else
          File.open(filename, 'wb')
        end
        
        begin
          old_on_body = curl.on_body do |data|
            result = old_on_body ?  old_on_body.call(data) : data.length
            output << data if result == data.length
            result
          end
          curl.perform
        ensure
          output.close rescue IOError
        end
        
        return curl
      end
    end

    # Allow the incoming cert string to be file:password
    # but be careful to not use a colon from a windows file path
    # as the split point. Mimic what curl's main does
    alias_method :native_cert=, :cert=
    def cert=(cert_file)
      pos = cert_file.rindex(':')
      if pos && pos > 1
        self.native_cert= cert_file[0..pos-1]
        self.certpassword= cert_file[pos+1..-1]
      else
        self.native_cert= cert_file
      end
      self.cert
    end
  end

  class Multi
    class << self
      # call-seq:
      #   Curl::Multi.get('url1','url2','url3','url4','url5', :follow_location => true) do|easy|
      #     easy
      #   end
      # 
      # Blocking call to fetch multiple url's in parallel.
      def get(urls, easy_options={}, multi_options={}, &blk)
        url_confs = []
        urls.each do|url|
          url_confs << {:url => url, :method => :get}.merge(easy_options)
        end
        self.http(url_confs, multi_options) {|c,code,method| blk.call(c) }
      end

      # call-seq:
      #
      #   Curl::Multi.post([{:url => 'url1', :post_fields => {'field1' => 'value1', 'field2' => 'value2'}},
      #                     {:url => 'url2', :post_fields => {'field1' => 'value1', 'field2' => 'value2'}},
      #                     {:url => 'url3', :post_fields => {'field1' => 'value1', 'field2' => 'value2'}}],
      #                    { :follow_location => true, :multipart_form_post => true },
      #                    {:pipeline => true }) do|easy|
      #     easy_handle_on_request_complete
      #   end
      # 
      # Blocking call to POST multiple form's in parallel.
      # 
      # urls_with_config: is a hash of url's pointing to the postfields to send 
      # easy_options: are a set of common options to set on all easy handles
      # multi_options: options to set on the Curl::Multi handle
      #
      def post(urls_with_config, easy_options={}, multi_options={}, &blk)
        url_confs = []
        urls_with_config.each do|uconf|
          url_confs << uconf.merge(:method => :post).merge(easy_options)
        end
        self.http(url_confs, multi_options) {|c,code,method| blk.call(c) }
      end

      # call-seq:
      #
      #   Curl::Multi.put([{:url => 'url1', :put_data => "some message"},
      #                    {:url => 'url2', :put_data => IO.read('filepath')},
      #                    {:url => 'url3', :put_data => "maybe another string or socket?"],
      #                    {:follow_location => true},
      #                    {:pipeline => true }) do|easy|
      #     easy_handle_on_request_complete
      #   end
      # 
      # Blocking call to POST multiple form's in parallel.
      # 
      # urls_with_config: is a hash of url's pointing to the postfields to send 
      # easy_options: are a set of common options to set on all easy handles
      # multi_options: options to set on the Curl::Multi handle
      #
      def put(urls_with_config, easy_options={}, multi_options={}, &blk)
        url_confs = []
        urls_with_config.each do|uconf|
          url_confs << uconf.merge(:method => :put).merge(easy_options)
        end
        self.http(url_confs, multi_options) {|c,code,method| blk.call(c) }
      end


      # call-seq:
      #
      # Curl::Multi.http( [
      #   { :url => 'url1', :method => :post,
      #     :post_fields => {'field1' => 'value1', 'field2' => 'value2'} },
      #   { :url => 'url2', :method => :get,
      #     :follow_location => true, :max_redirects => 3 },
      #   { :url => 'url3', :method => :put, :put_data => File.open('file.txt','rb') },
      #   { :url => 'url4', :method => :head }
      # ], {:pipeline => true})
      #
      # Blocking call to issue multiple HTTP requests with varying verb's.
      #
      # urls_with_config: is a hash of url's pointing to the easy handle options as well as the special option :method, that can by one of [:get, :post, :put, :delete, :head], when no verb is provided e.g. :method => nil -> GET is used
      # multi_options: options for the multi handle 
      # blk: a callback, that yeilds when a handle is completed
      #
      def http(urls_with_config, multi_options={}, &blk)
        m = Curl::Multi.new
        # configure the multi handle
        multi_options.each { |k,v| m.send("#{k}=", v) }
        callbacks = [:on_progress,:on_debug,:on_failure,:on_success,:on_body,:on_header]

        urls_with_config.each do|conf|
          c = conf.dup # avoid being destructive to input
          url     = c.delete(:url)
          method  = c.delete(:method)
          headers = c.delete(:headers)

          easy    = Curl::Easy.new(url)

          # assign callbacks
          callbacks.each do |cb|
            cbproc = c.delete(cb)
            easy.send(cb,&cbproc) if cbproc
          end

          case method
          when :post
            fields = c.delete(:post_fields)
            # set the post post using the url fields
            easy.post_body = fields.map{|f,k| "#{easy.escape(f)}=#{easy.escape(k)}"}.join('&')
          when :put
            easy.put_data = c.delete(:put_data)
          when :head
            easy.head = true
          when :delete
            easy.delete = true
          when :get
          else
            # XXX: nil is treated like a GET
          end

          # headers is a special key
          headers.each {|k,v| easy.headers[k] = v } if headers
 
          #
          # use the remaining options as specific configuration to the easy handle
          # bad options should raise an undefined method error
          #
          c.each { |k,v| easy.send("#{k}=",v) }

          easy.on_complete {|curl,code| blk.call(curl,code,method) } if blk
          m.add(easy)
        end
        m.perform
      end

      # call-seq:
      #
      # Curl::Multi.download(['http://example.com/p/a/t/h/file1.txt','http://example.com/p/a/t/h/file2.txt']){|c|}
      #
      # will create 2 new files file1.txt and file2.txt
      # 
      # 2 files will be opened, and remain open until the call completes
      #
      # when using the :post or :put method, urls should be a hash, including the individual post fields per post
      #
      def download(urls,easy_options={},multi_options={},download_paths=nil,&blk)
        errors = []
        procs = []
        files = []
        urls_with_config = []
        url_to_download_paths = {}

        urls.each_with_index do|urlcfg,i|
          if urlcfg.is_a?(Hash)
            url = url[:url]
          else
            url = urlcfg
          end

          if download_paths and download_paths[i]
            download_path = download_paths[i]
          else
            download_path = File.basename(url)
          end

          file = lambda do|dp|
            file = File.open(dp,"wb")
            procs << (lambda {|data| file.write data; data.size })
            files << file
            file
          end.call(download_path)

          if urlcfg.is_a?(Hash)
            urls_with_config << urlcfg.merge({:on_body => procs.last}.merge(easy_options))
          else
            urls_with_config << {:url => url, :on_body => procs.last, :method => :get}.merge(easy_options)
          end
          url_to_download_paths[url] = {:path => download_path, :file => file} # store for later
        end

        if blk
          # when injecting the block, ensure file is closed before yielding
          Curl::Multi.http(urls_with_config, multi_options) do |c,code,method|
            info = url_to_download_paths[c.url]
            begin
              file = info[:file]
              files.reject!{|f| f == file }
              file.close
            rescue => e
              errors << e
            end
            blk.call(c,info[:path])
          end
        else
          Curl::Multi.http(urls_with_config, multi_options)
        end

      ensure
        files.each {|f|
          begin
            f.close
          rescue => e
            errors << e
          end
        }
        raise errors unless errors.empty?
      end

    end
  end
end

require 'erb'


module Ferret::Browser
  class Delegator
    def initialize(reader, path)
      @reader, @path = reader, path
    end

    def run(env)
      controller, action, args = :home, :index, nil
      query_string = env['QUERY_STRING']||''
      params = parse_query_string(query_string)
      req_path = env['PATH_INFO'].gsub(/\/+/, '/')
      case req_path
      when '/'
        # nothing to do
      when /^\/?([-a-zA-Z]+)\/?$/
        controller = $1
      when /^\/?([-a-zA-Z]+)\/([-a-zA-Z]+)\/?(.*)?$/
        controller = $1
        action = $2
        args = $3
      else
        controller = :error
        args = req_path
      end
      controller_vars = {
        :params => params,
        :req_path => req_path,
        :query_string => query_string,
      }
      delegate(controller, action, args, controller_vars)
    end

    private

    def delegate(controller, action, args, controller_vars)
      begin
        controller = to_const(controller, 'Controller').
          new(@reader, @path, controller_vars)
        controller.send(action, args)
      rescue Exception => e
        puts e.to_s
        controller_vars[:params][:error] = e
        ErrorController.new(@reader, @path, controller_vars).index
      end
    end

    def to_const(str, suffix='')
      Ferret::Browser.const_get(str.to_s.split('-').
                                map {|w| w.capitalize}.join('') + suffix)
    end

    # from _why's camping
    def unescape_uri(s)
      s.tr('+', ' ').gsub(/%([\da-f]{2})/in){[$1].pack('H*')}
    end

    def parse_query_string(query_string, delim = '&;')
      m = proc {|_,o,n| o.update(n, &m) rescue ([*o] << n)}
      (query_string||'').split(/[#{delim}] */n).
        inject({}) { |hash, param| key, val = unescape_uri(param).split('=',2)
          hash.update(key.split(/[\]\[]+/).reverse.
            inject(val) { |x,i| Hash[i,x] }, &m)
        } 
    end
  end

  module ViewHelper
    # truncates the string at the first space after +len+ characters
    def truncate(str, len = 80)
      if str and str.length > len and (add = str[len..-1].index(' '))
        str = str[0, len + add] + '&#8230;'
      end
      str
    end

    def tick_or_cross(t)
      "<img src=\"/s/i/#{t ?'tick':'cross'}.png\" alt=\"#{t ?'yes':'no'}\"/>"
    end
  end

  class Controller
    include ViewHelper
    APP_DIR = File.expand_path(File.join(File.dirname(__FILE__), "browser/"))
    STATIC_DIR = File.expand_path(File.join(APP_DIR, "s/"))

    def initialize(reader, path, vars)
      @reader = reader
      @path = path
      vars.each_pair {|key, val| instance_eval("@#{key} = val")}
      @controller_path = pathify(self.class.to_s.gsub(/.*:/, ''))
    end

    def method_missing(meth_id, *args)
      render(:action => meth_id)
    end

    protected 

    def load_page(page)
      File.read(File.join(APP_DIR, page))
    end

    def render(options = {})
      options = {
        :controller => @controller_path,
        :action => :index,
        :status => 200,
        :content_type => 'text/html',
        :env => nil,
        :layout => 'views/layout.rhtml',
      }.update(options)

      path = "views/#{options[:controller]}/#{options[:action]}.rhtml"
      content = ERB.new(load_page(path)).result(lambda{})
      if options[:layout]
        content = ERB.new(load_page(options[:layout])).result(lambda{})
      end

      return options[:status], options[:content_type], content
    end

    # takes an optional block to set optional attributes in the links
    def paginate(idx, max, url, &b)
      return '' if max == 0
      url = url.gsub(%r{^/?(.*?)/?$}, '\1')
      b ||= lambda{}
      link = lambda {|*args|
        i, title, text = args
        "<a href=\"/#{url}/#{i}#{'?' + @query_string if @query_string}\" " +
         "#{'onclick="return false;"' if (i == idx)} " +
         "class=\"#{'disabled ' if (i == idx)}#{b.call(i)}\" " +
         "title=\"#{title||"Go to page #{i}"}\">#{text||i}</a>"
      }
      res = '<div class="nav">'
      if (idx > 0)
        res << link.call(idx - 1, "Go to previous page", "&#171; Previous")
      else
        res << "<a href=\"/#{url}/0\" onclick=\"return false;\" " +
                "class=\"disabled\" title=\"Disabled\">&#171; Previous</a>"
      end
      if idx < 10
        idx.times {|i| res << link.call(i)}
      else
        (0..2).each {|i| res << link.call(i)}
        res << '&nbsp;&#8230;&nbsp;'
        ((idx-4)...idx).each {|i| res << link.call(i)}
      end
      res << link.call(idx, 'Current Page')
      if idx > (max - 10)
        ((idx+1)...max).each {|i| res << link.call(i)}
      else
        ((idx+1)..(idx+4)).each {|i| res << link.call(i)}
        res << '&nbsp;&#8230;&nbsp;'
        ((max-3)...max).each {|i| res << link.call(i)}
      end
      if (idx < (max - 1))
        res << link.call(idx + 1, "Go to next page", "Next &#187;")
      else
        res << "<a href=\"/#{url}/#{max-1}\" onclick=\"return false;\" " +
                "class=\"disabled\" title=\"Disabled\"}\">Next &#187;</a>"
      end
      res << '</div>'
    end
    private

    def pathify(str)
      str.gsub(/Controller$/, '').gsub(/([a-z])([A-Z])/) {"#{$1}-#{$2}"}.downcase
    end
  end

  class ErrorController < Controller
    def index
      render(:status => 404)
    end
  end

  class HomeController < Controller
  end

  class DocumentController < Controller
    def list(page = 0)
      @page = (page||0).to_i
      @page_size = @params[:page_size]||10
      @first = @page * @page_size
      @last = [@reader.max_doc, (@page + 1) * @page_size].min
      render(:action => :list)
    end
    alias :index :list

    def show(doc_id)
      doc_id = @params['doc_id']||doc_id||'0'
      if doc_id !~ /^\d+$/
        raise ArgumentError.new("invalid document number '#{doc_id}'")
      end
      @doc_id = doc_id.to_i
      @doc = @reader[@doc_id].load unless @reader.deleted?(@doc_id)
      render(:action => :show)
    end

    private
    
    def choose_document(doc_id='')
      <<-EOF
<form action="" method="get" onsubmit="location.href='/document/show/' + document.getElementById('doc_id').value;return false;">
  <label for="doc_id">Go to document: 
    <input type="text" id="doc_id" name="doc_id" size="4" value="#{@doc_id}"/>
  </label>
</form>
      EOF
    end

    def paginate_docs
      paginate(@doc_id, @reader.max_doc, '/document/show/') {|i|
        'deleted' if @reader.deleted?(i)
      }
    end
  end

  class TermController < Controller
    def show(field)
      if field and field.length > 0
        @field = field.to_sym
        @terms = @reader.terms(@field).to_json(:fast)
      end
      render(:action => :index)
    end

    def termdocs(args)
      args = args.split('/')
      @field = args.shift.intern
      @term = args.join('/')
      render(:action => :termdocs,
             :content_type => 'text/plain',
             :layout => false)
    end
  end

  class TermVectorController < Controller
  end

  class HelpController < Controller
  end
end

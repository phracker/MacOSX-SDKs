#!/usr/bin/env ruby

require 'yaml'
require 'xmpp4r'
require 'xmpp4r/bytestreams'
require 'xmpp4r/roster'
require 'xmpp4r/version'

Jabber::debug = true

def human_readable(num)
  unit = ''
  units = %w(K M G T P E)
  while num > 10240 and units.size > 0
    num /= 1024
    unit = units.shift
  end
  "#{num} #{unit}B"
end

class Transfer
  attr_reader :peer, :filename, :bytes, :filesize

  def initialize(filetransfer, peer, filename, filesize, msgblock)
    @filetransfer = filetransfer
    @peer = peer
    @filename = filename
    @filesize = filesize
    @msgblock = msgblock

    @done = false
    @bytes = 0
    @stats = [0]
    @stats_lock = Mutex.new
    @stats_thread = Thread.new { stats_loop }


    @streamhost_cb = lambda { |streamhost,state,e|
      case state
        when :connecting
          say "Connecting to #{streamhost.jid} (#{streamhost.host}:#{streamhost.port})"
        when :success
          say "Successfully using #{streamhost.jid} (#{streamhost.host}:#{streamhost.port})"
        when :failure
          say "Error using #{streamhost.jid} (#{streamhost.host}:#{streamhost.port}): #{e}"
      end
    }
  end

  def done?
    @stats_thread.kill if @done
    @done
  end

  def stats_loop
    loop {
      sleep 1
      @stats_lock.synchronize {
        @stats.push @bytes
        @stats.shift if @stats.size > 5
      }
    }
  end

  def stats
    @stats_lock.synchronize {
      if @stats.first >= @stats.last
        0
      else
        (@stats.last - @stats.first) / (@stats.size - 1)
      end
    }
  end

  def say(text)
    @msgblock.call(text)
  end

  def transfer(from, to)
    while buf = from.read
      @bytes += to.write buf
    end
  end
end

class Upload < Transfer
  def initialize(filetransfer, iq, filename, filesize, can_range, msgblock)
    super(filetransfer, iq.from, filename, filesize, msgblock)

    if filename.size < 1
      say "What is this file for?"
      @done = true
      return
    end

    offset = nil
    if File::exist?(filename)
      if File::size(filename) < filesize and can_range
        @bytes = offset = File::size(filename)
        say "Will retrieve #{filename} starting at #{offset}"
      else
        say "#{filename} already exists"
        filetransfer.decline(iq)
        @done = true
        return
      end
    end

    Thread.new {
      begin
        stream = filetransfer.accept(iq, offset)
        if stream.kind_of?(Jabber::Bytestreams::SOCKS5Bytestreams)
          stream.connect_timeout = 5
          stream.add_streamhost_callback(nil, nil, &@streamhost_cb)
        end

        if stream.accept
          outfile = File.new(filename, (offset ? 'a' : 'w'))

          transfer(stream, outfile)

          outfile.close
          stream.close
          @done = true
        else
          say "Stream failed"
          @done = true
        end
      rescue
        puts $!.backtrace.first
        say "Error: #{$!}"
        @done = true
      end
    }
  end
end

class Download < Transfer
  def initialize(filetransfer, peer, filename, msgblock, socksconf)
    begin
      filesize = File.size(filename)
    rescue
      filesize = 0
    end

    super(filetransfer, peer, filename, filesize, msgblock)

    Thread.new {
      begin
        raise "No regular file" unless File.file?(filename)

        source = Jabber::FileTransfer::FileSource.new(filename)
        stream = filetransfer.offer(peer, source)
        unless stream
          raise "Well, you should accept what you request..."
          @done = true
        end

        if stream.kind_of?(Jabber::Bytestreams::SOCKS5Bytestreams)
          socksconf.call(stream)
          stream.add_streamhost_callback(nil, nil, &@streamhost_cb)
        end

        stream.open
        transfer(source, stream)
        stream.close
        @done = true
      rescue
        say "Error: #{$!}"
        @done = true
      end
    }
  end
end

class FileServe
  def initialize(conf)
    @uploads = 0
    @downloads = 0

    @transfers = []
    @transfers_lock = Mutex.new

    @client = Jabber::Client.new Jabber::JID.new(conf['jabber']['jid'])
    @client.connect
    @client.auth(conf['jabber']['password'])

    @ft = Jabber::FileTransfer::Helper.new(@client)
    Jabber::Version::SimpleResponder.new(@client,
                                       "XMPP4R FileServe example",
                                       Jabber::XMPP4R_VERSION,
                                       IO.popen('uname -sr').readlines.to_s.strip)
    register_handlers

    @directory = conf['directory']
    @directory.gsub!(/\/+$/, '')

    @socksserver = Jabber::Bytestreams::SOCKS5BytestreamsServer.new(conf['socks']['port'])

    conf['socks']['addresses'].each { |addr| @socksserver.add_address(addr) }

    @proxies = []
    conf['socks']['proxies'].collect { |jid|
      puts "Querying proxy #{jid}..."
      begin
        @proxies.push(Jabber::Bytestreams::SOCKS5Bytestreams::query_streamhost(@client, jid))
      rescue
        puts "Error: #{$!}"
      end
    }

    Thread.new { presence }
    Thread.new { cleaner }

    # Panic reboot ;-)
    @client.on_exception { initialize(conf) }
  end

  def presence
    rate_upload = 0
    rate_download = 0

    old_status = nil
    loop {
      # Update the @rate_* variables
      @transfers_lock.synchronize {
        @transfers.each { |t|
          if t.kind_of?(Upload) and t.stats > rate_upload
            rate_upload = t.stats
          elsif t.kind_of?(Download) and t.stats > rate_download
            rate_download = t.stats
          end
        }
      }
      status = "Attempted #{@downloads} downloads (max. #{human_readable rate_download}/s) and #{@uploads} uploads (max. #{human_readable rate_upload}/s)"

      @client.send(Jabber::Presence.new(:chat, status)) if status != old_status
      old_status = status

      sleep 1

    }
  end

  def register_handlers
    @client.add_message_callback { |msg|
      if msg.type == :chat and msg.body and msg.from != 'pentabarf@pentabarf.org/rails'
        puts "<#{msg.from}> #{msg.body.strip}"
        cmd, arg = msg.body.split(/ /, 2)

        command(msg.from, cmd, arg)
      end
    }

    @ft.add_incoming_callback { |iq,file|

      say = lambda { |text|
        say(iq.from, text)
      }

      puts "Incoming file transfer from #{iq.from}: #{file.fname} (#{file.size / 1024} KB)"
      filename = file.fname.split(/\//).last
      filename.gsub!(/^\.+/, '')

      puts "Range: #{file.range != nil}"
      transfer = Upload.new(@ft, iq, "#{@directory}/#{filename}", file.size, file.range != nil, say)
      @uploads += 1

      @transfers_lock.synchronize {
        @transfers.push(transfer)
      }

    }

    roster = Jabber::Roster::Helper.new(@client)

    roster.add_subscription_request_callback { |item,presence|
      roster.accept_subscription(presence.from)
    }

  end

  def command(from, cmd, arg)
    say = lambda { |text|
      say(from, text)
    }
    socksconf = lambda { |stream|
      stream.add_streamhost(@socksserver)
      @proxies.each { |sh|
        stream.add_streamhost(sh)
      }
    }

    case cmd
      when 'get'
        arg.gsub!(/\//, '')
        arg.gsub!(/^\.+/, '')
        transfer = Download.new(@ft, from, "#{@directory}/#{arg}", say, socksconf)
        @downloads += 1
        @transfers_lock.synchronize {
          @transfers.push(transfer)
        }
      when 'ls'
        text = ""
        Dir.foreach(@directory) { |file|
          next if file =~ /^\./
          path = "#{@directory}/#{file}"
          text += "#{file} (#{human_readable File.size(path)})\n" if File.file?(path)
        }
        say.call(text.strip)
      when 'stat'
        @transfers_lock.synchronize {
          text = "#{@transfers.size} transfers:\n"
          @transfers.each { |t|
            text += "#{t.filename} (#{t.peer}): #{(t.bytes * 100) / t.filesize}% (#{human_readable t.stats}/s)\n"
          }
        }
        say.call(text.strip)
      when 'help'
        say.call "Download a file: get <filename>\nList directory contents: ls\nLook who is currently wasting bandwidth: stat\nUpload a file, simply send this file"
      else
        say.call "Unknown command: #{cmd}, try help"
    end
  end

  def say(to, text)
    puts ">#{to}< #{text.strip}"
    @client.send(Jabber::Message.new(to, text).set_type(:chat))
  end

  def cleaner
    loop {

      @transfers_lock.synchronize {
        @transfers.delete_if { |t| t.done? }
      }

      sleep 1
    }
  end
end


FileServe.new(YAML::load(File.new('fileserve.conf')))
puts "Up and running!"
Thread.stop

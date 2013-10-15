#!/usr/bin/env ruby

require 'xmpp4r'
require 'xmpp4r/helpers/filetransfer'


if ARGV.size != 3
  puts "Usage: #{$0} <jid> <password> <incoming-directory>"
  exit
end


#Jabber::debug = true

cl = Jabber::Client.new(Jabber::JID.new(ARGV[0]))
puts "Connecting Jabber client..."
cl.connect
puts "Authenticating..."
cl.auth ARGV[1]

ft = Jabber::Helpers::FileTransfer.new(cl)
ft.add_incoming_callback { |iq,file|
  puts "Incoming file transfer from #{iq.from}: #{file.fname} (#{file.size / 1024} KB)"

  filename = "#{ARGV[2]}/#{file.fname.split(/\//).last}"
  offset = nil
  if File::exist?(filename)
    puts "#{filename} already exists"
    if File::size(filename) < file.size and file.range
      offset = File::size(filename)
      puts "Peer supports <range/>, will retrieve #{file.fname} starting at #{offset}"
    else
      puts "#{file.fname} is already fully retrieved, declining file-transfer"
      ft.decline(iq)
      next
    end
  end

  Thread.new {
    begin
      puts "Accepting #{file.fname}"
      stream = ft.accept(iq, offset)
      if stream.kind_of?(Jabber::Helpers::SOCKS5Bytestreams)
        stream.connect_timeout = 5
        stream.add_streamhost_callback { |streamhost,state,e|
          case state
            when :connecting
              puts "Connecting to #{streamhost.jid} (#{streamhost.host}:#{streamhost.port})"
            when :success
              puts "Successfully using #{streamhost.jid} (#{streamhost.host}:#{streamhost.port})"
            when :failure
              puts "Error using #{streamhost.jid} (#{streamhost.host}:#{streamhost.port}): #{e}"
          end
        }
      end

      puts "Waiting for stream configuration"
      if stream.accept
        puts "Stream established"
        outfile = File.new(filename, (offset ? 'a' : 'w'))
        while buf = stream.read
          outfile.write(buf)
          print '.'
          $stdout.flush
        end
        puts '!'
        outfile.close
        stream.close
      else
        puts "Stream failed"
      end
    rescue Exception => e
      puts "#{e.class}: #{e}\n#{e.backtrace.join("\n")}"
    end
  }
}

cl.send(Jabber::Presence.new(:chat, 'Send me files!'))

puts "Waiting."

Thread.stop

cl.close

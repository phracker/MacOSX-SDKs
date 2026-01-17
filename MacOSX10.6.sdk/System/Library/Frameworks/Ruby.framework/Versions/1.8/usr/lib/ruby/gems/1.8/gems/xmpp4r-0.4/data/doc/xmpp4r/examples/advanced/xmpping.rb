#!/usr/bin/env ruby
# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/


# This is PING for Jabber
#
# Please customize your ~/.xmppingrc


require 'xmpp4r'
require 'xmpp4r/httpbinding'
require 'xmpp4r/version/iq/version'
require 'xmpp4r/discovery/iq/discoinfo'
require 'optparse'
require 'yaml'
require 'thread'


##
# Options
##

interval = 5
jid = nil
conf_filename = "#{ENV['HOME']}/.xmppingrc"
accountname = 'default'

OptionParser.new { |opts|
  opts.banner = 'Usage: xmpping.rb [-d] [-a ACCOUNT] [-c FILENAME] [-i SECONDS] -t <JID>'
  opts.separator 'Ping a destination JID with various <iq/> stanzas'
  opts.on('-t', '--to JID', 'Destionation Jabber-ID') { |j| jid = Jabber::JID.new(j) }
  opts.on('-a', '--account ACCOUNT', 'Account tag to use (default: default)') { |a| accountname = a }
  opts.on('-c', '--config FILENAME', 'Configuration file (default: ~/.xmppingrc)') { |c| conf_filename = c }
  opts.on('-i', '--interval SECONDS', 'Wait SECONDS between each stanza (default: 5)') { |sec| interval = sec.to_i }
  opts.on('-d', '--debug', 'Enable XMPP4R debugging (print stanzas)') { Jabber::debug = true }
  opts.on_tail('-h', '--help', 'Show help') {
    puts opts
    exit
  }
  opts.parse!(ARGV)

  unless jid
    puts opts
    exit
  end
}


##
# Configuration
##

begin
  conf_file = File.new(conf_filename)
rescue Exception => e
  puts "Unable to open config file: #{e.to_s}"
  exit
end

conf = YAML::load(conf_file)
unless conf
  puts "#{conf_filename} is no valid YAML document"
  exit
end
account = conf[accountname]
unless account
  puts "Account #{accountname} not found in #{conf_filename}"
  exit
end

##
# Connection
##

if account['http bind']
  cl = Jabber::HTTPBinding::Client.new(Jabber::JID.new(account['jid']))
  cl.connect(account['http bind'])
else
  cl = Jabber::Client.new(Jabber::JID.new(account['jid']))
  cl.connect(account['host'], (account['port'] ? account['port'].to_i : 5222))
end
cl.auth(account['password'])

##
# Reply printer
##

def print_reply(iq, roundtrip)
  roundtrip_s = ((roundtrip * 100).round / 100.0).to_s + " sec"
  output = "Received a #{iq.query.namespace} #{iq.type} (id: #{iq.id}) from #{iq.from} (#{roundtrip_s}): "

  if iq.query.kind_of?(Jabber::Version::IqQueryVersion)
    output += "#{iq.query.iname}-#{iq.query.version} #{iq.query.os}"
  elsif iq.query.namespace == 'jabber:iq:time'
    output += "#{iq.query.first_element_text('display')} (#{iq.query.first_element_text('tz')})"
  elsif iq.query.kind_of?(Jabber::Discovery::IqQueryDiscoInfo)
    identity = iq.query.identity
    if identity
      output += "#{identity.iname} (#{identity.category} #{identity.type})"
    else
      output += "<identity/> missing"
    end
  else
    output += iq.query.to_s
  end

  puts output
end

##
# Main loop
##

  require 'mprofiler'
  MemoryProfiler.start(:string_debug=>true)

puts "XMPPING #{cl.jid} -> #{jid}"
query_methods = ['jabber:iq:version', 'jabber:iq:time', 'http://jabber.org/protocol/disco#info']
query_method = 0

loop {
  Thread.new {
    iq = Jabber::Iq.new_query(:get, jid)
    iq.query.add_namespace(query_methods[query_method])

    time1 = Time.new

    begin
      cl.send_with_id(iq) { |reply|
        print_reply(reply, Time.new - time1)
        true
      }
    rescue Jabber::ServerError => e
      puts "Error for #{iq.query.namespace} to #{iq.to}: #{e.error.to_s.inspect}"
    end
  }

  query_method += 1
  if query_method >= query_methods.size
    query_method = 0
  end

  sleep(interval)
}

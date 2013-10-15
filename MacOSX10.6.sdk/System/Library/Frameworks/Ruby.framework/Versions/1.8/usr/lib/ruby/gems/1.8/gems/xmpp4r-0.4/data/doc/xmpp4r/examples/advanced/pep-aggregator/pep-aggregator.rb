#!/usr/bin/env ruby

require 'xmpp4r/framework/bot'
require 'xmpp4r/pubsub'
require 'xmpp4r/vcard'
require 'ramaze'

if ARGV.size < 3
  puts "Usage: #{$0} <HTTP port> <JID> <Password> [Status message]"
  exit
end
HTTP_PORT = ARGV.shift.to_i
JID = ARGV.shift
PASSWORD = ARGV.shift
STATUS_MESSAGE = ARGV.shift

def xml_namespaces(filename, excludes=[])
  namespaces_recursive = nil
  namespaces_recursive = lambda { |element|
    namespaces = element.namespaces
    element.each_element { |child|
      namespaces.merge!(namespaces_recursive.call(child))
    }
    namespaces
  }

  root = REXML::Document.new(File.new(filename)).root
  all = namespaces_recursive.call(root)
  res = {}
  all.each { |prefix,uri|
    res[prefix] = uri unless excludes.include? prefix
  }
  res
end

Jabber::debug = true

class VcardCache < Jabber::Vcard::Helper
  attr_reader :vcards

  def initialize(stream)
    super
    @vcards = {}
  end

  def get(jid)
    unless @vcards[jid]
      begin
        @vcards[jid] = super
      rescue Jabber::ServerError
        @vcards[jid] = :error
      end
    end

    @vcards[jid]
  end

  def get_until(jid, timeout=10)
    begin
      Timeout::timeout(timeout) {
        get(jid)
      }
    rescue Timeout::Error
      @vcards[jid] = :timeout
    end

    @vcards[jid]
  end
end

MAX_ITEMS = 50
$jid_items = []

$bot = Jabber::Framework::Bot.new(JID, PASSWORD)
class << $bot
  def accept_subscription_from?(jid)
    roster.add(jid, nil, true)
    true
  end
end
$vcards = VcardCache.new($bot.stream)
xml_namespaces('index.xsl', %w(xmlns xsl pa j p)).each { |prefix,node|
        $bot.add_pep_notification(node) do |from,item|
          from.strip!
          item.add_namespace(Jabber::PubSub::NS_PUBSUB)
          item.attributes['node'] = node
          is_duplicate = false
          $jid_items.each { |jid1,item1|
            if jid1.to_s == from.to_s and node == item1.attributes['node']
              is_duplicate = (item.to_s == item1.to_s)
              break
            end
          }
          unless is_duplicate
            $jid_items.unshift([from, item])
            $jid_items = $jid_items[0..(MAX_ITEMS-1)]
          end
        end
      }

$bot.set_presence(nil, STATUS_MESSAGE || "Busy aggregating PEP events...")

class WebController < Ramaze::Controller
  map '/'
  template_root __DIR__
  engine :XSLT

  def index
    "<?xml version='1.0' encoding='UTF-8'?>" +
      "<items xmlns:jabber='jabber:client' jabber:to='#{Jabber::JID.new(JID).strip}'>" +
      $jid_items.collect do |jid,item_orig|
        item = item_orig.deep_clone
        item.attributes['jabber:from'] = jid.to_s
        vcard = $vcards.get_until(jid)
        if vcard.kind_of? Jabber::Vcard::IqVcard
          item.attributes['jabber:from-name'] = vcard['NICKNAME'] || vcard['FN'] || jid.node
          item.attributes['jabber:has-avatar'] = (vcard['PHOTO/TYPE'] and
                                                  vcard['PHOTO/BINVAL']) ? 'true' : 'false'
        else
          item.attributes['jabber:from-name'] = jid.node
          item.attributes['jabber:has-avatar'] = 'false'
        end
        item
      end.join +
      "</items>"
  end

  def avatar(jid)
    trait :engine => :None

    vcard = $vcards.get_until(jid)
    if vcard.kind_of? Jabber::Vcard::IqVcard
      if vcard['PHOTO/TYPE'] and vcard.photo_binval
        response['Content-Type'] = vcard['PHOTO/TYPE']
        response.body = vcard.photo_binval
      else
        response['Status'] = 404
      end
    else
        response['Status'] = 404
    end

    throw :respond
  end
end

Ramaze::start(:port => HTTP_PORT)

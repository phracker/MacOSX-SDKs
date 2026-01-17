# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'singleton'

module Jabber
  ##
  # The Jabber::IdGenerator class generates unique IDs for use
  # in XMMP stanzas. Jabber::IdGenerator includes the Singleton
  # Mixin, usage as following:
  #  Jabber::IdGenerator.generate_id
  #    => "23"
  class IdGenerator
    include Singleton

    def initialize
      @last_id = 0
    end

    ##
    # Generate an unique ID.
    #
    # This is kind of boring this way, as it just counts up
    # a number. Maybe something more random somewhen...
    def IdGenerator.generate_id
      IdGenerator.instance.generate_id
    end

    def generate_id
      @last_id += 1
      timefrac = Time.new.to_f.to_s.split(/\./, 2).last[-3..-1]

      "#{@last_id}#{timefrac}"
    end
  end
end

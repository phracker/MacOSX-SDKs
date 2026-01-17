# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

module Jabber
  module MUC
    ##
    # Don't use this. It is the base class (unifying shared
    # attributes) of XMUCUserItem and IqQueryMUCAdminItem
    class UserItem < XMPPElement
      def affiliation
        case attributes['affiliation']
          when 'admin' then :admin
          when 'member' then :member
          when 'none' then :none
          when 'outcast' then :outcast
          when 'owner' then :owner
          else nil
        end
      end

      def affiliation=(v)
        case v
          when :admin then attributes['affiliation'] = 'admin'
          when :member then attributes['affiliation'] = 'member'
          when :none then attributes['affiliation'] = 'none'
          when :outcast then attributes['affiliation'] = 'outcast'
          when :owner then attributes['affiliation'] = 'owner'
          else attributes['affiliation'] = nil
        end
      end

      def set_affiliation(v)
        self.affiliation = v
        self
      end

      def jid
        attributes['jid'].nil? ? nil : JID.new(attributes['jid'])
      end

      def jid=(j)
        attributes['jid'] = j.nil? ? nil : j.to_s
      end

      def set_jid(j)
        self.jid = j
        self
      end

      def nick
        attributes['nick']
      end

      def nick=(n)
        attributes['nick'] = n
      end

      def set_nick(n)
        self.nick = n
        self
      end

      def role
        case attributes['role']
          when 'moderator' then :moderator
          when 'none' then :none
          when 'participant' then :participant
          when 'visitor' then :visitor
          else nil
        end
      end

      def role=(r)
        case r
          when :moderator then attributes['role'] = 'moderator'
          when :none then attributes['role'] = 'none'
          when :participant then attributes['role'] = 'participant'
          when :visitor then attributes['role'] = 'visitor'
          else attributes['role'] = nil
        end
      end

      def set_role(r)
        self.role = r
        self
      end

      def reason
        text = nil
        each_element('reason') { |xe| text = xe.text }
        text
      end

      def reason=(s)
        delete_elements('reasion')
        add_element('reason').text = s
      end

      def set_reason(s)
        self.reason = s
        self
      end

      def continue
        c = nil
        each_element('continue') { |xe| c = xe }
        c.nil?
      end

      def continue=(c)
        delete_elements('continue')
        add_element('continue') if c
      end

      def set_continue(c)
        self.continue = c
        self
      end

      def actors
        a = []
        each_element('actor') { |xe|
          a.push(JID.new(xe.attributes['jid']))
        }
        a
      end

      def actors=(a)
        delete_elements('actor')
        a.each { |jid|
          e = add_element('actor')
          e.attributes['jid'] = jid.to_s
        }
      end

      def set_actors(a)
        self.actors = a
        self
      end
    end
  end
end

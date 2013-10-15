require 'net/ssh/errors'
require 'net/ssh/known-hosts'

module Net
  module SSH

    class HostKeyVerifier
      def verify(arguments)
        host = canonize(arguments[:peer])
        matches = Net::SSH::KnownHosts.search_for(host)

        # we've never seen this host before, so just automatically add the key.
        # not the most secure option (since the first hit might be the one that
        # is hacked), but since almost nobody actually compares the key
        # fingerprint, this is a reasonable compromise between usability and
        # security.
        if matches.empty?
          Net::SSH::KnownHosts.add(host, arguments[:key])
          return true
        end

        # If we found any matches, check to see that the key type and
        # blob also match.
        found = matches.any? do |key|
          key.ssh_type == arguments[:key].ssh_type &&
          key.to_blob  == arguments[:key].to_blob
        end

        # If a match was found, return true. Otherwise, raise an exception
        # indicating that the key was not recognized.
        found || process_cache_miss(host, arguments)
      end

      private

        def process_cache_miss(host, args)
          exception = HostKeyMismatch.new("fingerprint #{args[:fingerprint]} does not match for #{host.join(',')}")
          exception.data = args
          exception.callback = Proc.new { Net::SSH::KnownHosts.add(host, args[:key]) }
          raise exception
        end

        def canonize(peer)
          hosts = []
          hosts << Net::SSH::KnownHosts.canonize(peer[:host], peer[:port])
          hosts << Net::SSH::KnownHosts.canonize(peer[:ip], peer[:port])
          hosts.compact
        end
    end

  end
end
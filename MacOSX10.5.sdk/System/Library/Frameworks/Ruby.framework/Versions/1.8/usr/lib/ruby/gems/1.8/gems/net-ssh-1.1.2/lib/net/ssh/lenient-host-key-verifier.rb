require 'net/ssh/host-key-verifier'

module Net
  module SSH

    class LenientHostKeyVerifier < HostKeyVerifier
      def verify(arguments)
        return true if tunnelled?(arguments)
        super
      end

      private

        # A connection is potentially being tunnelled if the port is not 22,
        # and the ip refers to the localhost.
        def tunnelled?(args)
          return false if args[:peer][:port].to_i == 22
          
          ip = args[:peer][:ip]
          return ip == "127.0.0.1" || ip == "::1"
        end
    end

  end
end
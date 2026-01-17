module Net
  module SSH

    # The NullHostKeyVerifier simply allows every key it sees, without
    # bothering to verify. This mimics the pre-1.1 behavior of Net::SSH, but
    # is not very secure.
    class NullHostKeyVerifier
      def verify(arguments)
        true
      end
    end

  end
end
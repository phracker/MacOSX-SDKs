#--
# =============================================================================
# Copyright (c) 2004,2005 Jamis Buck (jamis@37signals.com)
# All rights reserved.
#
# This source file is distributed as part of the Net::SSH Secure Shell Client
# library for Ruby. This file (and the library as a whole) may be used only as
# allowed by either the BSD license, or the Ruby license (or, by association
# with the Ruby license, the GPL). See the "doc" subdirectory of the Net::SSH
# distribution for the texts of these licenses.
# -----------------------------------------------------------------------------
# net-ssh website : http://net-ssh.rubyforge.org
# project website: http://rubyforge.org/projects/net-ssh
# =============================================================================
#++

unless defined?( HAS_TERMIOS )
  begin
    require 'termios'
    HAS_TERMIOS = true
  rescue LoadError
    HAS_TERMIOS = false
  end
end

module Net
  module SSH
    module Util

      # A simple class for prompting a user for input.
      class Prompter

        # Displays the prompt and then waits for the user to enter a response.
        # If the 'termios' library is available, the user's input will not be
        # echoed to the terminal. The user's response will be returned, with
        # any trailing newline chomped.
        def password( prompt=nil )
          if $stdin.tty?
            echo false
            print prompt if prompt
          end

          $stdin.gets.chomp
        ensure
          if $stdin.tty?
            echo true
            puts
          end
        end

        if HAS_TERMIOS
          def echo( enable )
            term = Termios::getattr( $stdin )

            if enable
              term.c_lflag |= ( Termios::ECHO | Termios::ICANON )
            else
              term.c_lflag &= ~Termios::ECHO
            end

            Termios::setattr( $stdin, Termios::TCSANOW, term )
          end
        else
          def echo( enable )
          end
        end
        private :echo

      end

    end
  end
end

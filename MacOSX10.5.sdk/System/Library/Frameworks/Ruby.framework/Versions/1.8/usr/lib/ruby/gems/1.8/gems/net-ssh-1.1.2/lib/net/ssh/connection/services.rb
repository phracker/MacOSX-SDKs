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

module Net
  module SSH
    module Connection

      # Register the services that define the "connection" layer of the SSH
      # protocol.
      def register_services( container )

        # The :connection namespace contains all of the services in the
        # connection layer of the SSH protocol.
        container.namespace_define :connection do |ns|

          # The :channel namespace contains the channel-specific services.
          ns.namespace_define :channel do |ch|

            # The :open service provides a proc object that may be used to
            # request that a new channel be opened.
            ch.open do |c,p|
              require 'net/ssh/connection/channel'
              lambda do |type, data|
                Channel.open( c[:driver],
                              c[:log_for, p],
                              c[:transport][:buffers],
                              type, data )
              end
            end

            # The :create service provides a proc object that may be used to
            # create new channels, without sending a request to the server.
            ch.create do |c,p|
              require 'net/ssh/connection/channel'
              lambda do |type,rid,wsize,psize|
                Channel.create( c[:driver],
                                c[:log_for, p],
                                c[:transport][:buffers],
                                type, rid, wsize, psize )
              end
            end
          end

          # The :driver service manages the connection layer.
          ns.driver do |c,p|
            require 'net/ssh/connection/driver'
            Driver.new( c[:transport][:session],
                        c[:log_for, p],
                        c[:transport][:buffers],
                        :open => c[:channel][:open],
                        :create => c[:channel][:create] )
          end
        end
      end
      module_function :register_services

    end
  end
end

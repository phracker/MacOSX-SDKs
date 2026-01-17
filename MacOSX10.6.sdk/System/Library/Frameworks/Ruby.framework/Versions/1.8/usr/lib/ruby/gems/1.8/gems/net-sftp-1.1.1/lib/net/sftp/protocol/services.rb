#--
# =============================================================================
# Copyright (c) 2004, Jamis Buck (jamis@37signals.com)
# All rights reserved.
#
# This source file is distributed as part of the Net::SFTP Secure FTP Client
# library for Ruby. This file (and the library as a whole) may be used only as
# allowed by either the BSD license, or the Ruby license (or, by association
# with the Ruby license, the GPL). See the "doc" subdirectory of the Net::SFTP
# distribution for the texts of these licenses.
# -----------------------------------------------------------------------------
# net-sftp website: http://net-ssh.rubyforge.org/sftp
# project website : http://rubyforge.org/projects/net-ssh
# =============================================================================
#++

module Net ; module SFTP ; module Protocol

  def register_services( container )
    container.namespace_define :protocol do |ns|

      # The maximum version of the SFTP protocol supported by this
      # implementation. Clients may set this to a lower value to force the
      # usage of a specific SFTP version. It should _not_ be set higher than
      # the value that is given below.
      ns.version { 5 }

      # A proc object that, when invoked, returns a dispatcher object capable
      # of handling the requested protocol version.
      ns.dispatcher_factory do |c,|
        lambda do |version, extensions|
          version = "%02d" % version
          c.require "net/sftp/protocol/#{version}/services",
            "#{self}::V_#{version}"
          impl = c["v_#{version}".to_sym][:impl]
          impl.extensions = extensions
          impl
        end
      end

      # The driver service that manages the SFTP protocol-level communications
      ns.driver do |c,p|
        require 'net/sftp/protocol/driver'
        Driver.new( c[:connection][:driver],
                    c[:transport][:buffers],
                    c[:version],
                    c[:dispatcher_factory],
                    c[:log_for, p] )
      end

    end
  end
  module_function :register_services

end ; end ; end

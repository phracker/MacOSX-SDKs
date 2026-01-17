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

module Net ; module SFTP ; module Protocol ; module V_03

  def register_services( container )
    container.namespace_define :v_03 do |ns|

      ns.packet_assistant do |c,|
        require 'net/sftp/protocol/03/packet-assistant'
        PacketAssistant.new( c[:transport][:buffers],
                             c[:driver] )
      end

      ns.attr_factory do |c,|
        require 'net/sftp/protocol/01/attributes'
        V_01::Attributes.init( c[:transport][:buffers] )
      end

      ns.impl do |c,|
        require 'net/sftp/protocol/03/impl'
        Impl.new( c[:transport][:buffers],
                  c[:driver], c[:packet_assistant],
                  c[:attr_factory] )
      end

    end
  end
  module_function :register_services

end ; end ; end ; end

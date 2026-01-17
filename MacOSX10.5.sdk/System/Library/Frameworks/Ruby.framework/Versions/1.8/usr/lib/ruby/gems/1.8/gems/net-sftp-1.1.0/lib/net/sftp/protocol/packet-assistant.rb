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

  # This is the abstract base class for all packet assistant classes used by
  # the supported SFTP protocol versions.
  class PacketAssistant

    # A helper method for defining a new packet type. The +name+ is the name
    # of the packet (and of the corresponding method that is created), and the
    # arguments are symbols representing the types of each element in the
    # packet. The supported types are:
    #
    # * :long
    # * :int64
    # * :short
    # * :byte
    # * :string
    # * :attrs
    # * :write
    #
    # The :attrs and :write types both simply convert the argument to a string.
    #
    # The method that is created always supports an +id+ parameter in the
    # first position, which if null will default to the next available request
    # id. The method returns a tuple consisting of the request id, and a string
    # consisting of the arguments formatted according to the packet's
    # description.
    def self.packet( name, *args )
      body = ""
      args.each do |arg|
        body << "b.write"
        case arg
          when :long, :int64, :short, :byte
            body << "_#{arg} args.shift.to_i"
          when :string
            body << "_#{arg} args.shift.to_s"
          when :attrs, :write
            body << " args.shift.to_s"
        end
        body << "\n"
      end
      class_eval <<-EOF, __FILE__, __LINE__+1
        def #{name}( id, *args )
          b = buffers.writer
          id ||= driver.next_request_id
          b.write_long id
          #{body}
          [ id, b.to_s ]
        end
      EOF
    end

    # The buffer factory in use by this packet assistant, used to build the
    # packets.
    attr_reader :buffers

    # The protocol driver that will be used to obtain request ids.
    attr_reader :driver

    # Create a new PacketAssistant, which will use the given buffer factory and
    # SFTP protocol driver.
    def initialize( buffers, driver )
      @buffers = buffers
      @driver = driver
    end

  end

end ; end ; end

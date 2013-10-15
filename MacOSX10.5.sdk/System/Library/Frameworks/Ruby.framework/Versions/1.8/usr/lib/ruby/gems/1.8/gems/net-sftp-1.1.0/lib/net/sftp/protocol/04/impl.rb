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

require 'net/sftp/protocol/03/impl'

module Net ; module SFTP ; module Protocol ; module V_04

  # The implementation of the operations available to version 4 of the SFTP
  # protocol.
  class Impl < V_03::Impl
 
    # In version 4, stat accepts a flags parameter. If flags is +nil+, it
    # will default to returning all attributes. Otherwise, the flags parameter
    # should be a bitwise combination of the F_xxx constants of
    # Net::SFTP::Protocol::V_04::Attributes.
    def stat( id, filename, flags=nil )
      stat_raw id, filename, convert_flags( flags )
    end

    # In version 4, lstat accepts a flags parameter. If flags is +nil+, it
    # will default to returning all attributes. Otherwise, the flags parameter
    # should be a bitwise combination of the F_xxx constants of
    # Net::SFTP::Protocol::V_04::Attributes.
    def lstat( id, filename, flags=nil )
      lstat_raw id, filename, convert_flags( flags )
    end

    # In version 4, fstat accepts a flags parameter. If flags is +nil+, it
    # will default to returning all attributes. Otherwise, the flags parameter
    # should be a bitwise combination of the F_xxx constants of
    # Net::SFTP::Protocol::V_04::Attributes.
    def fstat( id, handle, flags=nil )
      fstat_raw id, handle, convert_flags( flags )
    end

    # In version 4, rename accepts a flags parameter. The valid flags are a
    # combination of the following:
    #
    # * FXP_RENAME_OVERWRITE (0x01)
    # * FXP_RENAME_ATOMIC (0x02)
    # * FXP_RENAME_NATIVE (0x04)
    #
    # Please refer to the SSH2 specification for the description of these flags.
    def rename( id, name, new_name, flags=0 )
      rename_raw id, name, new_name, flags
    end

    # A convenience method for converting the (stat) flags parameter into a
    # value acceptible to the SFTP protocol.
    def convert_flags( flags )
      return 0x800001FD if flags.nil?
      flags
    end
    private :convert_flags

    # Used internally to handle +name+ packets. The +on_name+ callback is
    # invoked, if registered, with the driver, id, and array of items. The v4
    # version of this method sets the 'longname' member of the Name object to
    # +nil+ (it is not used in this version).
    def do_name( channel, content )
      return unless has_on_name?
      id = content.read_long
      items = []
      content.read_long.times do
        items.push( Name.new( content.read_string, nil,
          @attr_factory.from_buffer( content ) ) )
      end
      call_on_name( driver, id, items )
    end

  end

end ; end ; end ; end

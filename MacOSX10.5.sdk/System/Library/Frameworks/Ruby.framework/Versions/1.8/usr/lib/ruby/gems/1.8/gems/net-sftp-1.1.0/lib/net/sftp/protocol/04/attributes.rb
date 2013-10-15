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

module Net ; module SFTP ; module Protocol ; module V_04

  # Version 4 of the SFTP protocol made some pretty significant alterations to
  # the File Attributes data type. This encapsulates those changes.
  class Attributes

    F_SIZE              = 0x00000001
    F_PERMISSIONS       = 0x00000004
    F_ACCESSTIME        = 0x00000008
    F_CREATETIME        = 0x00000010
    F_MODIFYTIME        = 0x00000020
    F_ACL               = 0x00000040
    F_OWNERGROUP        = 0x00000080
    F_SUBSECOND_TIMES   = 0x00000100
    F_EXTENDED          = 0x80000000
    
    attr_accessor :type
    attr_accessor :size
    attr_accessor :owner
    attr_accessor :group
    attr_accessor :permissions
    attr_accessor :atime
    attr_accessor :atime_nseconds
    attr_accessor :ctime
    attr_accessor :ctime_nseconds
    attr_accessor :mtime
    attr_accessor :mtime_nseconds
    attr_accessor :acl
    attr_accessor :extended

    ACL = Struct.new( :type, :flag, :mask, :who )

    # An initializer for specifying the buffer factory that should be used by
    # instances of this class.
    def self.init( buffers )
      @buffers = buffers
      self
    end

    # Return a reference to the buffer factory in use by this class.
    def self.buffers
      @buffers
    end

    # A convenience for obtaining a reference to the buffer factory used by
    # this instance's class.
    def buffers
      self.class.buffers
    end

    # Return an empty Attributes instance.
    def self.empty
      new
    end

    # Return an Attributes instance initialized from the given buffer.
    def self.from_buffer( buffer )
      flags = buffer.read_long

      type = buffer.read_byte
      size = buffer.read_int64 if ( flags & F_SIZE ) != 0
      owner = buffer.read_string if ( flags & F_OWNERGROUP ) != 0
      group = buffer.read_string if ( flags & F_OWNERGROUP ) != 0
      permissions = buffer.read_long if ( flags & F_PERMISSIONS ) != 0
      if ( flags & F_ACCESSTIME ) != 0
        atime = buffer.read_int64
        atime_nseconds = buffer.read_long if ( flags & F_SUBSECOND_TIMES ) != 0
      end
      if ( flags & F_CREATETIME ) != 0
        ctime = buffer.read_int64
        ctime_nseconds = buffer.read_long if ( flags & F_SUBSECOND_TIMES ) != 0
      end
      if ( flags & F_MODIFYTIME ) != 0
        mtime = buffer.read_int64
        mtime_nseconds = buffer.read_long if ( flags & F_SUBSECOND_TIMES ) != 0
      end
      if ( flags & F_ACL ) != 0
        acl_buf = buffers.reader( buffer.read_string )
        acl = []
        acl_buf.read_long.times do
          acl << ACL.new( acl_buf.read_long,
                          acl_buf.read_long,
                          acl_buf.read_long,
                          acl_buf.read_string )
        end
      end

      if ( flags & F_EXTENDED ) != 0
        extended = Hash.new
        buffer.read_long.times do
          extended[ buffer.read_string ] = buffer.read_string
        end
      end

      new( type, size, owner, group, permissions, atime, atime_nseconds,
        ctime, ctime_nseconds, mtime, mtime_nseconds, acl, extended )
    end

    # Create a new attributes object, initialized from the given hash. The
    # :uid and :gid attributes are treated specially; they are not actually
    # supported by this version of the protocol, but are instead converted
    # by this method to their corresponding names, and assigned (respectively)
    # to :owner and :group.
    def self.from_hash( hash )
      if hash.has_key?(:uid)
        require 'etc'
        hash[:owner] = Etc.getpwuid( hash[:uid] ).name
      end

      if hash.has_key?(:gid)
        require 'etc'
        hash[:group] = Etc.getgrgid( hash[:gid] ).name
      end

      new hash[:type] || T_REGULAR, hash[:size], hash[:owner], hash[:group],
        hash[:permissions], hash[:atime], hash[:atime_nseconds],
        hash[:ctime], hash[:ctime_nseconds], hash[:mtime],
        hash[:mtime_nseconds], hash[:acl], hash[:extended]
    end

    private_class_method :new

    T_REGULAR      = 1
    T_DIRECTORY    = 2
    T_SYMLINK      = 3
    T_SPECIAL      = 4
    T_UNKNOWN      = 5
    T_SOCKET       = 6
    T_CHAR_DEVICE  = 7
    T_BLOCK_DEVICE = 8
    T_FIFO         = 9

    # Create a new Attributes instance with the given values.
    def initialize( type=T_REGULAR, size=nil, owner=nil, group=nil,
      permissions=nil, atime=nil, atime_nseconds=nil, ctime=nil,
      ctime_nseconds=nil, mtime=nil, mtime_nseconds=nil, acl=nil,
      extended=nil )
    # begin
      @type = type
      @size = size
      @owner = owner
      @group = group
      @permissions = permissions
      @atime = atime
      @atime_nseconds = atime_nseconds
      @ctime = ctime
      @ctime_nseconds = ctime_nseconds
      @mtime = mtime
      @mtime_nseconds = mtime_nseconds
      @acl = acl
      @extended = extended
    end

    # Convert this object to a string, suitable for inclusion in an SFTP
    # packet (protocol version 4+).
    def to_s
      flags = 0

      flags |= F_SIZE if @size
      flags |= F_OWNERGROUP if @owner && @group
      flags |= F_PERMISSIONS if @permissions
      flags |= F_ACCESSTIME if @atime
      flags |= F_CREATETIME if @ctime
      flags |= F_MODIFYTIME if @mtime
      if @atime_nseconds && @ctime_nseconds && @mtime_nseconds
        flags |= F_SUBSECOND_TIMES
      end
      flags |= F_ACL if @acl
      flags |= F_EXTENDED if @extended

      buffer = buffers.writer
      buffer.write_long flags
      buffer.write_byte @type
      buffer.write_int64 @size if @size
      buffer.write_string @owner, @group if @owner && @group
      buffer.write_long @permissions if @permissions

      if @atime
        buffer.write_int64 @atime
        buffer.write_long @atime_nseconds if ( flags & F_SUBSECOND_TIMES != 0 )
      end
      if @ctime
        buffer.write_int64 @ctime
        buffer.write_long @ctime_nseconds if ( flags & F_SUBSECOND_TIMES != 0 )
      end
      if @mtime
        buffer.write_int64 @mtime
        buffer.write_long @mtime_nseconds if ( flags & F_SUBSECOND_TIMES != 0 )
      end

      if @acl
        acl_buf = buffers.writer
        acl_buf.write_long @acl.length
        @acl.each do |item|
          acl_buf.write_long item.type, item.flag, item.mask
          acl_buf.write_string item.who
        end
        buffer.write_string acl_buf.to_s
      end

      if @extended
        buffer.write_long @extended.length
        @extended.each { |k,v| buffer.write_string k, v }
      end

      buffer.to_s
    end

  end

end ; end ; end ; end

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

require 'net/sftp/errors'
require 'net/sftp/protocol/constants'

module Net ; module SFTP ; module Protocol ; module V_01

  # The implementing class for version 1 of the SFTP protocol. It
  # implements the various operations and callbacks available to this
  # level of the protocol. Other protocol versions will typically 
  # extend this class, adding (or modifying) methods as needed to bring
  # the implementation into sync with the needed version.
  class Impl
    include Constants

    Name = Struct.new( :filename, :longname, :attributes )

    # The protocol driver that drives this dispatcher.
    attr_reader :driver

    # The attribute-factory used by this dispatcher.
    attr_reader :attr_factory

    # The protocol extensions specified when the protocol version was
    # negotiated.
    attr_accessor :extensions

    # Create a new instance using the given protocol driver, packet
    # assistant, and attributes factory.
    def initialize( buffers, driver, assistant, attr_factory )
      @buffers = buffers
      @driver = driver
      @assistant = assistant
      @attr_factory = attr_factory
      @on_status = nil
      @on_handle = nil
      @on_data = nil
      @on_name = nil
      @on_attrs = nil
    end

    # A helper method for defining new operations supported by this
    # implementation. This will create one method for each named operation.
    # By default, the method simply formats the packet (using the packet
    # assistant), and then sends the data via the driver. It will then
    # return the request id used for this operation.
    def self.operation( *names )
      names.each do |name|
        const = "FXP_#{name.to_s.upcase}"
        class_eval <<-EOF, __FILE__, __LINE__+1
          def #{name}( id, *args )
            id, packet = @assistant.#{name}( id, *args )
            @driver.send_data #{const}, packet
            id
          end
        EOF
      end
    end

    # A helper method for registering new callbacks. Each callback will
    # cause three new methods to be created, <tt>on_<em>name</em></tt>,
    # <tt>has_on_<em>name</em>?</tt>, and <tt>call_on_<em>name</em></tt>.
    # The <tt>on_<em>name</em></tt> method may be used to register a block
    # for the corresponding callback.
    def self.callback( *names )
      names.each do |name|
        class_eval <<-EOF, __FILE__, __LINE__+1
          def on_#{name}( &block )
            @on_#{name} = block
          end

          def has_on_#{name}?
            not @on_#{name}.nil?
          end

          def call_on_#{name}( *args )
            return unless @on_#{name}
            @on_#{name}.call( *args )
          end

          public :on_#{name}
          protected :has_on_#{name}?, :call_on_#{name}
        EOF
      end
    end

    operation :open,
              :close,
              :read,
              :write,
              :opendir,
              :readdir,
              :remove,
              :stat,
              :lstat,
              :fstat,
              :setstat,
              :fsetstat,
              :mkdir,
              :rmdir,
              :realpath

    callback :status,
             :handle,
             :data,
             :name,
             :attrs

    alias :open_raw     :open
    alias :stat_raw     :stat
    alias :lstat_raw    :lstat
    alias :fstat_raw    :fstat

    alias :close_handle :close

    F_READ   = 0x00000001
    F_WRITE  = 0x00000002
    F_APPEND = 0x00000004
    F_CREAT  = 0x00000008
    F_TRUNC  = 0x00000010
    F_EXCL   = 0x00000020

    # The open operation is special, since it protects the caller from the
    # specific flags and options required by SFTP. Instead, the caller simply
    # specifies a combination of IO flags, and an appropriate posix mode, and
    # they are translated into the correct SFTP flags.
    def open( id, path, flags, mode=0660 )
      sftp_flags = case
        when ( flags & IO::WRONLY ) != 0 then F_WRITE
        when ( flags & IO::RDWR   ) != 0 then F_READ | F_WRITE
        when ( flags & IO::APPEND ) != 0 then F_APPEND
        else F_READ
      end

      sftp_flags |= F_CREAT if ( flags & IO::CREAT ) != 0
      sftp_flags |= F_TRUNC if ( flags & IO::TRUNC ) != 0
      sftp_flags |= F_EXCL  if ( flags & IO::EXCL  ) != 0

      attributes = @attr_factory.empty
      attributes.permissions = mode

      open_raw id, path, sftp_flags, attributes
    end

    # The stat operation is special, since later versions of the protocol add
    # support for 'flags'. These flags are ignored in this version, but the
    # parameter exists to allow a program written for one version of the
    # protocol to work with later versions.
    def stat( id, filename, flags=nil )
      stat_raw id, filename
    end

    # The lstat operation is special, since later versions of the protocol add
    # support for 'flags'. These flags are ignored in this version, but the
    # parameter exists to allow a program written for one version of the
    # protocol to work with later versions.
    def lstat( id, filename, flags=nil )
      lstat_raw id, filename
    end

    # The fstat operation is special, since later versions of the protocol add
    # support for 'flags'. These flags are ignored in this version, but the
    # parameter exists to allow a program written for one version of the
    # protocol to work with later versions.
    def fstat( id, handle, flags=nil )
      fstat_raw id, handle
    end

    # Dispatches the given packet type to the appropriate handler method.
    # If a new protocol version adds a new packet type, it should override
    # this method, performing its own checking first, followed by calling
    # +super+.
    def dispatch( channel, type, content )
      case type
        when FXP_STATUS then do_status( channel, content )
        when FXP_HANDLE then do_handle( channel, content )
        when FXP_DATA   then do_data( channel, content )
        when FXP_NAME   then do_name( channel, content )
        when FXP_ATTRS  then do_attrs( channel, content )
        else
          raise Net::SFTP::Exception,
            "unsupported SFTP packet type #{type} (#{content.to_s.inspect})"
      end
    end

    # Used internally to handle +status+ packets. The +on_status+ callback is
    # invoked, if registered, with the driver, id, and code.
    def do_status( channel, content )
      return unless has_on_status?
      id = content.read_long
      code = content.read_long
      call_on_status( driver, id, code, nil, nil )
    end

    # Used internally to handle +handle+ packets. The +on_handle+ callback is
    # invoked, if registered, with the driver, id, and handle.
    def do_handle( channel, content )
      return unless has_on_handle?
      id = content.read_long
      handle = content.read_string
      call_on_handle( driver, id, handle )
    end

    # Used internally to handle +data+ packets. The +on_data+ callback is
    # invoked, if registered, with the driver, id, and data (as a buffer).
    def do_data( channel, content )
      return unless has_on_data?
      id = content.read_long
      data = content.read_string
      call_on_data( driver, id, data )
    end

    # Used internally to handle +name+ packets. The +on_name+ callback is
    # invoked, if registered, with the driver, id, and array of items.
    def do_name( channel, content )
      return unless has_on_name?
      id = content.read_long
      items = []
      content.read_long.times do
        items.push( Name.new( content.read_string, content.read_string,
          @attr_factory.from_buffer( content ) ) )
      end
      call_on_name( driver, id, items )
    end

    # Used internally to handle +attrs+ packets. The +on_attrs+ callback is
    # invoked, if registered, with the driver, id, and attribute object.
    def do_attrs( channel, content )
      return unless has_on_attrs?
      id = content.read_long
      attrs = @attr_factory.from_buffer( content )
      call_on_attrs( driver, id, attrs )
    end

  end

end ; end ; end ; end

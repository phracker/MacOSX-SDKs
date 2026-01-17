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

require 'net/sftp/protocol/packet-assistant'

module Net ; module SFTP ; module Protocol ; module V_01

  # Defines the packets available to version 1 of the SFTP protocol, as well
  # as their formats. These packets are:
  #
  # * open( id, path, flags, attrs )
  # * close( id, handle )
  # * read( id, handle, offset, length )
  # * write( id, handle, offset, data )
  # * opendir( id, path )
  # * readdir( id, handle )
  # * remove( id, filename )
  # * stat( id, path )
  # * lstat( id, path )
  # * fstat( id, handle )
  # * setstat( id, path, attrs )
  # * fsetstat( id, handle, attrs )
  # * mkdir( id, path, attrs )
  # * rmdir( id, path )
  # * realpath( id, path )
  class PacketAssistant < Protocol::PacketAssistant

    packet :open,     :string, # path
                      :long,   # flags
                      :attrs   # file attributes

    packet :close,    :string  # handle

    packet :read,     :string, # handle
                      :int64,  # offset
                      :long    # length

    packet :write,    :string, # handle
                      :int64,  # offset
                      :string  # data

    packet :opendir,  :string  # path

    packet :readdir,  :string  # handle

    packet :remove,   :string  # filename

    packet :stat,     :string  # path

    packet :lstat,    :string  # path

    packet :fstat,    :string  # handle

    packet :setstat,  :string, # path
                      :attrs   # attributes to set

    packet :fsetstat, :string, # handle
                      :attrs   # attributes to set

    packet :mkdir,    :string, # path
                      :attrs   # directory attributes

    packet :rmdir,    :string  # path

    packet :realpath, :string  # path

  end

end ; end ; end ; end

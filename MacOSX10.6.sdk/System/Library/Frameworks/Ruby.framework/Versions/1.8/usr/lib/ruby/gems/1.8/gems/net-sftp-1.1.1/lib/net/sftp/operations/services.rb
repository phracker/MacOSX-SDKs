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

module Net ; module SFTP ; module Operations

  # Register all services that implement an SFTP operation.
  def register_services( container )
    container.namespace :operations
    container.operations.use :model => :prototype do |ns|
      [
        :open,
        [ :close_handle, :close ],
        :read, :write, :opendir, :readdir, :remove,
        :stat, :lstat, :fstat, :setstat, :fsetstat,
        :mkdir, :rmdir, :realpath, :rename
      ].each do |op|
        array = op.is_a?( Array )
        ns.register( array ? op.first : op ) do |c,p|
          require "net/sftp/operations/#{array ? op.last : op}"
          klass_name = ( array ? op.last : op ).to_s
          klass = const_get( klass_name[0,1].upcase + klass_name[1..-1] )
          klass.new c[:log_for, p], c[:session], c[:protocol][:driver]
        end
      end
    end
  end
  module_function :register_services

end ; end ; end

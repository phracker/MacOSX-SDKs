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

require 'net/ssh'
require 'net/sftp/session'

module Net ; module SFTP

  # A convenience method for starting a standalone SFTP session. It will
  # start up an SSH session using the given arguments (see the documentation
  # for Net::SSH::Session for details), and will then start a new SFTP session
  # with the SSH session. If a block is given, it will be passed to the SFTP
  # session.
  def start( *args, &block )
    session = Net::SSH.start( *args )
    Net::SFTP::Session.new( session, &block )
  ensure
    session.close if session && block_given?
  end
  module_function :start

end ; end

Net::SSH.register_service( :sftp ) do |c,p|
  Net::SFTP::Session.new( c[:session] )
end

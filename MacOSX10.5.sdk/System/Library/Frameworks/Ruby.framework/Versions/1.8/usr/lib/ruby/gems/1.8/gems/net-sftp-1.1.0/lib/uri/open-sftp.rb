# =======================================================================
# Net::SSH -- A Ruby module implementing the SSH2 client protocol
# Copyright (C) 2004 Jamis Buck (jamis@37signals.com)
# 
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
# 
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
# 
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
# =======================================================================

require 'open-uri'
require 'uri/sftp'
require 'net/sftp'

OpenURI::Options[ :chunk_size ] = true

module URI

  class SFTP
    def direct_open( buf, open_options )
      Net::SFTP.start( host, port, user, password, options ) do |sftp|
        if open_options[:content_length_proc]
          open_options[:content_length_proc].call( sftp.lstat( path ).size )
        end

        body = nil
        sftp.open_handle( path ) do |handle|
          body = sftp.read( handle,
                    :chunk_size => open_options[:chunk_size],
                    :progress_callback => open_options[:progress_proc] )
        end

        if body.nil?
          raise Net::SSH::SFTP::SFTPError, sftp.status[:message]
        end

        buf << body
        buf.io.rewind
      end
    end

    include OpenURI::OpenRead
  end

end

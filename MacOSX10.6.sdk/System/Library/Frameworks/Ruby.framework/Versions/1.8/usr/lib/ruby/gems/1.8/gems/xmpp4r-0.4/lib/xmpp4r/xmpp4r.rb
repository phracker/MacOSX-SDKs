# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

##
# The Jabber module is the root namespace of the library.
module Jabber
  # XMPP4R Version number.  This is the ONLY place where the version number
  # should be specified.  This constant is used to determine the version of
  # package tarballs and generated gems.
  XMPP4R_VERSION = '0.4'
end

require 'xmpp4r/client'
require 'xmpp4r/component'
require 'xmpp4r/debuglog'
require 'xmpp4r/errors'


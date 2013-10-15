# A workaround to make Rails 2.1 gem dependency easier on case-sensitive filesystems.
# Since the gem name is RedCloth and the file is redcloth.rb, config.gem 'RedCloth' doesn't
# work.  You'd have to use config.gem 'RedCloth', :lib => 'redcloth', and that's not 
# immediately obvious.  This file remedies that.
#
require File.join(File.dirname(__FILE__), '..', 'redcloth')
# If running on Windows, then add the current directory to the PATH
# for the current process so it can find the pre-built libxml2 and 
# iconv2 shared libraries (dlls).
if RUBY_PLATFORM.match(/mswin/i)
  ENV['PATH'] += ";#{File.dirname(__FILE__)}"
end

# Load the C-based binding.
require 'libxml_ruby'

# Load Ruby supporting code.
require 'libxml/error'
require 'libxml/parser'
require 'libxml/document'
require 'libxml/namespaces'
require 'libxml/namespace'
require 'libxml/node'
require 'libxml/ns'
require 'libxml/attributes'
require 'libxml/attr'
require 'libxml/attr_decl'
require 'libxml/tree'
require 'libxml/reader'
require 'libxml/html_parser'
require 'libxml/sax_parser'
require 'libxml/sax_callbacks'
require 'libxml/xpath_object'

# Deprecated
require 'libxml/properties'
$:.unshift(File.dirname(__FILE__))

# If this is a frozen gem in Rails 2.1 and RedCloth 3.x was already
# loaded by Rails' ActionView::Helpers::TextHelper, the user will get
# "redcloth_scan.bundle: Class is not a module (TypeError)"
# This hack is to work around that Rails loading problem.  The problem
# appears to be fixed in Edge Rails [51e4106].
Object.send(:remove_const, :RedCloth) if Object.const_defined?(:RedCloth) && RedCloth.is_a?(Class)

require 'redcloth_scan'
require 'redcloth/version'
require 'redcloth/textile_doc'
require 'redcloth/formatters/base'
require 'redcloth/formatters/html'
require 'redcloth/formatters/latex'

module RedCloth
  
  # A convenience method for creating a new TextileDoc. See
  # RedCloth::TextileDoc.
  def self.new( *args, &block )
    RedCloth::TextileDoc.new( *args, &block )
  end
  
  # Include extension modules (if any) in TextileDoc.
  def self.include(*args)
    RedCloth::TextileDoc.send(:include, *args)
  end
  
end

begin
  require 'erb'
  require 'redcloth/erb_extension'
  include ERB::Util
rescue LoadError
end
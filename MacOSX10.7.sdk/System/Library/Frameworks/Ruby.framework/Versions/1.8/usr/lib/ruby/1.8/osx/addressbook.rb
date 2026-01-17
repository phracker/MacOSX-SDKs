# Copyright (c) 2006-2008, The RubyCocoa Project.
# Copyright (c) 2001-2006, FUJIMOTO Hisakuni.
# All Rights Reserved.
#
# RubyCocoa is free software, covered under either the Ruby's license or the 
# LGPL. See the COPYRIGHT file for more information.

require 'osx/cocoa'

STDERR.puts "The osx/addressbook script has been deprecated, and its use is now discouraged. Please do `OSX.require_framework \"AddressBook\"` instead."
OSX.require_framework 'AddressBook'

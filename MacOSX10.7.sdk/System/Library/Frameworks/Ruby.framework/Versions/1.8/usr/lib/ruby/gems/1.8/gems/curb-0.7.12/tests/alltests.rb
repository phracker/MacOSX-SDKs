$: << $TESTDIR = File.expand_path(File.dirname(__FILE__))
require 'unittests'
Dir[File.join($TESTDIR, 'bug_*.rb')].each { |lib| require lib }

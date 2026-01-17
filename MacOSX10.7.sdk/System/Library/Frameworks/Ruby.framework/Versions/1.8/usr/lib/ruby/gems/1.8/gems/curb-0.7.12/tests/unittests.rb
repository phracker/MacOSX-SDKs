$: << $TESTDIR = File.expand_path(File.dirname(__FILE__))
Dir[File.join($TESTDIR, 'tc_*.rb')].each { |lib| require lib }

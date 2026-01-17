$: << $TESTDIR = File.expand_path(File.dirname(__FILE__))
puts "start"
begin
Dir[File.join($TESTDIR, 'bug_*.rb')].each { |lib| require lib }
rescue Object => e
  puts e.message
ensure
puts "done"
end

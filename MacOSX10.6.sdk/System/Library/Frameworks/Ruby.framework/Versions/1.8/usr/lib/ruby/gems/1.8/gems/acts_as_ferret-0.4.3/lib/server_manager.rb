################################################################################
require 'optparse'

################################################################################
$ferret_server_options = {
  'environment' => nil,
  'debug'       => nil,
}

################################################################################
OptionParser.new do |optparser|
  optparser.banner = "Usage: #{File.basename($0)} [options] {start|stop}"

  optparser.on('-h', '--help', "This message") do
    puts optparser
    exit
  end

  optparser.on('-e', '--environment=NAME', 'Set RAILS_ENV to the given string') do |e|
    $ferret_server_options['environment'] = e
  end

  optparser.on('--debug', 'Include full stack traces on exceptions') do
    $ferret_server_options['debug'] = true
  end

  $ferret_server_action = optparser.permute!(ARGV)
  (puts optparser; exit(1)) unless $ferret_server_action.size == 1

  $ferret_server_action = $ferret_server_action.first
  (puts optparser; exit(1)) unless %w(start stop).include?($ferret_server_action)
end

################################################################################
begin
  ENV['FERRET_USE_LOCAL_INDEX'] = 'true'
  ENV['RAILS_ENV'] = $ferret_server_options['environment']
  #require(File.join(File.dirname(__FILE__), '../../../../config/environment'))
  require(File.join(File.dirname(ENV['_']), '../config/environment'))
  require 'acts_as_ferret'
  ActsAsFerret::Remote::Server.new.send($ferret_server_action)
rescue Exception => e
  $stderr.puts(e.message)
  $stderr.puts(e.backtrace.join("\n")) if $ferret_server_options['debug']
  exit(1)
end

# acts_as_ferret install script
require 'fileutils'

def install(file)
  puts "Installing: #{file}"
  target = File.join(File.dirname(__FILE__), '..', '..', '..', file)
  if File.exists?(target)
    puts "target #{target} already exists, skipping"
  else
    FileUtils.cp File.join(File.dirname(__FILE__), file), target
  end
end

install File.join( 'script', 'ferret_start' )
install File.join( 'script', 'ferret_stop' )
install File.join( 'config', 'ferret_server.yml' )

puts IO.read(File.join(File.dirname(__FILE__), 'README'))


Dir.chdir File.dirname( __FILE__ )
$LOAD_PATH.unshift "#{File.dirname(__FILE__)}/../lib"
$LOAD_PATH.unshift "#{File.dirname(__FILE__)}/../ext/sqlite3_api"
p $LOAD_PATH

Dir["**/tc_*.rb"].each { |file| load file }

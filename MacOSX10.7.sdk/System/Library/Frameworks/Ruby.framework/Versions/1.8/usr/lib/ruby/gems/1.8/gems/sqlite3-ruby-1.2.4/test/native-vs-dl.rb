$:.unshift "../lib", "../ext/sqlite3_api"

require 'sqlite3'

require 'benchmark'

N = 1000

$VERBOSE=nil

puts "database creation..."
Benchmark.bm( 7 ) do |x|
  x.report('dl') do
    N.times do
      File.delete "test.db" rescue nil
      SQLite3::Database.open( "test.db", :driver => "DL" ).close
    end
  end
  x.report('native') do
    N.times do
      File.delete "test.db" rescue nil
      SQLite3::Database.open( "test.db", :driver => "Native" ).close
    end
  end
end
File.delete "test.db" rescue nil

SQLite3::Database.open( "test.db" ).close

puts
puts "database open..."
Benchmark.bm( 7 ) do |x|
  x.report('dl') do
    N.times do
      SQLite3::Database.open( "test.db", :driver => "DL" ).close
    end
  end
  x.report('native') do
    N.times do
      SQLite3::Database.open( "test.db", :driver => "Native" ).close
    end
  end
end
File.delete "test.db" rescue nil

dl = SQLite3::Database.open( "test-dl.db", :driver => "DL" )
native = SQLite3::Database.open( "test-native.db", :driver => "Native" )

dl.execute "create table foo (a,b)"
native.execute "create table foo (a,b)"

puts
puts "insertions"
Benchmark.bm( 7 ) do |x|
  x.report('dl') do
    dl.transaction do
      N.times do |i|
        dl.execute "insert into foo values (#{i}, #{i+1})"
      end
    end
  end
  x.report('native') do
    native.transaction do
      N.times do |i|
        native.execute "insert into foo values (#{i}, #{i+1})"
      end
    end
  end
end

puts
puts "insertions using prepared statement"
Benchmark.bm( 7 ) do |x|
  x.report('dl') do
    dl.transaction do
      dl.prepare "insert into foo values (?,?)" do |stmt|
        N.times { |i| stmt.execute i, i+1 }
      end
    end
  end
  x.report('native') do
    native.transaction do
      native.prepare( "insert into foo values (?,?)" ) do |stmt|
        N.times { |i| stmt.execute i, i+1 }
      end
    end
  end
end

dl.close
native.close
File.delete "test-dl.db" rescue nil
File.delete "test-native.db" rescue nil

dl = SQLite3::Database.open( "test-dl.db", :driver => "DL" )
native = SQLite3::Database.open( "test-native.db", :driver => "Native" )

dl.execute "create table foo (a,b)"
dl.execute "insert into foo values (1,2)"
dl.execute "insert into foo values (3,4)"
dl.execute "insert into foo values (5,6)"

native.execute "create table foo (a,b)"
native.execute "insert into foo values (1,2)"
native.execute "insert into foo values (3,4)"
native.execute "insert into foo values (5,6)"

puts
puts "queries"
Benchmark.bm( 7 ) do |x|
  x.report('dl') do
    N.times do
      dl.execute "select * from foo"
    end
  end
  x.report('native') do
    N.times do
      native.execute "select * from foo"
    end
  end
end

dl.close
native.close
File.delete "test-dl.db" rescue nil
File.delete "test-native.db" rescue nil

require 'benchmark'

N = 1000

$VERBOSE=nil

puts "file require"
Benchmark.bm( 7 ) do |x|
  x.report('sqlite') do
    N.times do
      $".delete_if { |i| i =~ /sqlite/ }
      require 'sqlite'
    end
  end
  x.report('sqlite3') do
    N.times do
      $".delete_if { |i| i =~ /sqlite3/ }
      require 'sqlite3'
    end
  end
end

puts
puts "database creation..."
Benchmark.bm( 7 ) do |x|
  x.report('sqlite') do
    N.times do
      File.delete "test.db" rescue nil
      SQLite::Database.open( "test.db" ).close
    end
  end
  x.report('sqlite3') do
    N.times do
      File.delete "test.db" rescue nil
      SQLite3::Database.open( "test.db" ).close
    end
  end
end
File.delete "test.db" rescue nil

SQLite::Database.open( "test.db" ).close
SQLite3::Database.open( "test3.db" ).close

puts
puts "database open..."
Benchmark.bm( 7 ) do |x|
  x.report('sqlite') do
    N.times do
      SQLite::Database.open( "test.db" ).close
    end
  end
  x.report('sqlite3') do
    N.times do
      SQLite3::Database.open( "test3.db" ).close
    end
  end
end
File.delete "test.db" rescue nil
File.delete "test3.db" rescue nil

db = SQLite::Database.open( "test.db" )
db3 = SQLite3::Database.open( "test3.db" )

db.execute "create table foo (a,b)"
db3.execute "create table foo (a,b)"

puts
puts "insertions"
Benchmark.bm( 7 ) do |x|
  x.report('sqlite') do
    db.transaction do
      N.times do |i|
        db.execute "insert into foo values (#{i}, #{i+1})"
      end
    end
  end
  x.report('sqlite3') do
    db3.transaction do
      N.times do |i|
        db3.execute "insert into foo values (#{i}, #{i+1})"
      end
    end
  end
end

puts
puts "insertions using prepared statement"
Benchmark.bm( 7 ) do |x|
  x.report('sqlite') do
    db.transaction do
      stmt = db.prepare "insert into foo values (?,?)"
      N.times { |i| stmt.execute i, i+1 }
    end
  end
  x.report('sqlite3') do
    db3.transaction do
      db3.prepare( "insert into foo values (?,?)" ) do |stmt|
        N.times { |i| stmt.execute i, i+1 }
      end
    end
  end
end

db.close
db3.close
File.delete "test.db" rescue nil
File.delete "test3.db" rescue nil

db = SQLite::Database.open( "test.db" )
db3 = SQLite3::Database.open( "test3.db" )

db.execute "create table foo (a,b)"
db.execute "insert into foo values (1,2)"
db.execute "insert into foo values (3,4)"
db.execute "insert into foo values (5,6)"

db3.execute "create table foo (a,b)"
db3.execute "insert into foo values (1,2)"
db3.execute "insert into foo values (3,4)"
db3.execute "insert into foo values (5,6)"

puts
puts "queries"
Benchmark.bm( 7 ) do |x|
  x.report('sqlite') do
    N.times do
      db.execute "select * from foo"
    end
  end
  x.report('sqlite3') do
    N.times do
      db3.execute "select * from foo"
    end
  end
end

db.close
db3.close
File.delete "test.db" rescue nil
File.delete "test3.db" rescue nil

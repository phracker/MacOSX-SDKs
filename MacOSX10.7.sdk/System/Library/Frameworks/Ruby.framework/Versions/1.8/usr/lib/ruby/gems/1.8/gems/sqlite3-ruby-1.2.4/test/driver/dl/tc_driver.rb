if (ENV["SQLITE3_DRIVERS"] || "Native").split(/,/).include?("DL")
  $:.unshift "../../../lib"

  require 'sqlite3/constants'
  require 'sqlite3/driver/dl/driver'
  require 'test/unit'

  class TC_DL_Driver < Test::Unit::TestCase

    def utf16ify( str )
      chars = str.split(//)
      chars.zip(["\0"] * chars.length).flatten.join
    end

    def setup
      @driver = SQLite3::Driver::DL::Driver.new
      @dbname = "test.db"
      @db = nil
    end

    def teardown
      @driver.close( @db ) rescue nil
      File.delete @dbname rescue nil
    end

    def test_open
      result, @db = @driver.open( @dbname )
      assert_equal SQLite3::Constants::ErrorCode::OK, result
      assert File.exist?( @dbname )
    end

    def test_open_utf16
      name = utf16ify( @dbname )
      result, @db = @driver.open( name, true )
      assert_equal SQLite3::Constants::ErrorCode::OK, result
      assert File.exist?( @dbname )
    end

    def test_errmsg
      result, @db = @driver.open( @dbname )
      msg = @driver.errmsg( @db )
      assert_equal msg, "not an error"
    end

    def test_errmsg16
      result, @db = @driver.open( @dbname )
      msg = @driver.errmsg( @db, true )
      assert_equal msg, utf16ify( "not an error" )
    end

    def test_prepare
      result, @db = @driver.open( @dbname )
      sql = "create table foo ( a, b )"
      result, handle, remainder = @driver.prepare( @db, sql )
      assert_equal SQLite3::Constants::ErrorCode::OK, result
      assert_equal "", remainder
      @driver.finalize( handle )
    end

    def test_prepare_error
      result, @db = @driver.open( @dbname )
      sql = "create tble foo ( a, b )"
      result, handle, remainder = @driver.prepare( @db, sql )
      assert_equal SQLite3::Constants::ErrorCode::ERROR, result
    end

    def test_prepare_remainder
      result, @db = @driver.open( @dbname )
      sql = "create table foo ( a, b ); select * from foo"
      result, handle, remainder = @driver.prepare( @db, sql )
      assert_equal SQLite3::Constants::ErrorCode::OK, result
      assert_equal " select * from foo", remainder
      @driver.finalize( handle )
    end

    def test_prepare16
      result, @db = @driver.open( @dbname )
      sql = utf16ify( "create table foo ( a, b )" )
      result, handle, remainder = @driver.prepare( @db, sql, true )
      assert_equal SQLite3::Constants::ErrorCode::OK, result
      assert_equal "", remainder
      @driver.finalize( handle )
    end

    def test_prepare16_remainder
      result, @db = @driver.open( @dbname )
      sql = utf16ify( "create table foo ( a, b ); select * from foo" )
      result, handle, remainder = @driver.prepare( @db, sql, true )
      assert_equal SQLite3::Constants::ErrorCode::OK, result
      assert_equal utf16ify( " select * from foo" ), remainder
      @driver.finalize( handle )
    end

    def test_complete
      assert @driver.complete?( "select * from foo;" )
    end

    def test_complete_fail
      assert !@driver.complete?( "select * from foo" )
    end

    def test_complete16
      assert @driver.complete?( utf16ify("select * from foo;"), true )
    end

    def create_foo
      result, @db = @driver.open( @dbname )
      sql = "create table foo ( a, b )"
      result, handle, = @driver.prepare( @db, sql )
      @driver.step( handle )
      @driver.finalize( handle )
    end

    def populate_foo
      create_foo
      sql = "insert into foo values ( 100, 200 )"
      result, handle, = @driver.prepare( @db, sql )
      @driver.step( handle )
      @driver.finalize( handle )
    end

    def test_step
      populate_foo
      sql = "select * from foo"
      result, handle, = @driver.prepare( @db, sql )
      result = @driver.step( handle )
      assert_equal SQLite3::Constants::ErrorCode::ROW, result
      result = @driver.step( handle )
      assert_equal SQLite3::Constants::ErrorCode::DONE, result
      @driver.finalize( handle )
    end

    def test_step_fail
      populate_foo
      sql = "select * from"
      result, handle, = @driver.prepare( @db, sql )
      result = @driver.step( handle )
      assert_equal SQLite3::Constants::ErrorCode::MISUSE, result
      @driver.finalize( handle )
    end

    def test_bind_blob
      create_foo
      sql = "insert into foo (b) values (?)"
      result, handle, = @driver.prepare( @db, sql )
      assert_equal SQLite3::Constants::ErrorCode::OK, result
      result = @driver.bind_blob( handle, 1, "a\0b\1c\2d\0e" )
      assert_equal SQLite3::Constants::ErrorCode::OK, result
      result = @driver.step( handle )
      assert_equal SQLite3::Constants::ErrorCode::DONE, result
      result = @driver.finalize( handle )
      assert_equal SQLite3::Constants::ErrorCode::OK, result
      sql = "select b from foo"
      result, handle, = @driver.prepare( @db, sql )
      assert_equal SQLite3::Constants::ErrorCode::OK, result
      result = @driver.step( handle )
      assert_equal SQLite3::Constants::ErrorCode::ROW, result
      assert_equal "a\0b\1c\2d\0e", @driver.column_blob( handle, 0 )
      result = @driver.finalize( handle )
      assert_equal SQLite3::Constants::ErrorCode::OK, result
    end

    def test_bind_double
      create_foo
      sql = "insert into foo (b) values (?)"
      result, handle, = @driver.prepare( @db, sql )
      assert_equal SQLite3::Constants::ErrorCode::OK, result
      result = @driver.bind_double( handle, 1, 3.14 )
      assert_equal SQLite3::Constants::ErrorCode::OK, result
      result = @driver.step( handle )
      assert_equal SQLite3::Constants::ErrorCode::DONE, result
      result = @driver.finalize( handle )
      assert_equal SQLite3::Constants::ErrorCode::OK, result
      sql = "select b from foo"
      result, handle, = @driver.prepare( @db, sql )
      assert_equal SQLite3::Constants::ErrorCode::OK, result
      result = @driver.step( handle )
      assert_equal SQLite3::Constants::ErrorCode::ROW, result
      assert_equal 3.14, @driver.column_double( handle, 0 )
      result = @driver.finalize( handle )
      assert_equal SQLite3::Constants::ErrorCode::OK, result
    end

    def test_bind_int
      create_foo
      sql = "insert into foo (b) values (?)"
      result, handle, = @driver.prepare( @db, sql )
      assert_equal SQLite3::Constants::ErrorCode::OK, result
      result = @driver.bind_int( handle, 1, 14 )
      assert_equal SQLite3::Constants::ErrorCode::OK, result
      result = @driver.step( handle )
      assert_equal SQLite3::Constants::ErrorCode::DONE, result
      result = @driver.finalize( handle )
      assert_equal SQLite3::Constants::ErrorCode::OK, result
      sql = "select b from foo"
      result, handle, = @driver.prepare( @db, sql )
      assert_equal SQLite3::Constants::ErrorCode::OK, result
      result = @driver.step( handle )
      assert_equal SQLite3::Constants::ErrorCode::ROW, result
      assert_equal 14, @driver.column_int( handle, 0 )
      result = @driver.finalize( handle )
      assert_equal SQLite3::Constants::ErrorCode::OK, result
    end

    def test_bind_null
      create_foo
      sql = "insert into foo (b) values (?)"
      result, handle, = @driver.prepare( @db, sql )
      assert_equal SQLite3::Constants::ErrorCode::OK, result
      result = @driver.bind_null( handle, 1 )
      assert_equal SQLite3::Constants::ErrorCode::OK, result
      result = @driver.step( handle )
      assert_equal SQLite3::Constants::ErrorCode::DONE, result
      result = @driver.finalize( handle )
      assert_equal SQLite3::Constants::ErrorCode::OK, result
      sql = "select b from foo"
      result, handle, = @driver.prepare( @db, sql )
      assert_equal SQLite3::Constants::ErrorCode::OK, result
      result = @driver.step( handle )
      assert_equal SQLite3::Constants::ErrorCode::ROW, result
      assert_equal SQLite3::Constants::ColumnType::NULL,
        @driver.column_type( handle, 0 )
      result = @driver.finalize( handle )
      assert_equal SQLite3::Constants::ErrorCode::OK, result
    end

    def test_bind_text
      create_foo
      sql = "insert into foo (b) values (?)"
      result, handle, = @driver.prepare( @db, sql )
      assert_equal SQLite3::Constants::ErrorCode::OK, result
      result = @driver.bind_text( handle, 1, "hello, world" )
      assert_equal SQLite3::Constants::ErrorCode::OK, result
      result = @driver.step( handle )
      assert_equal SQLite3::Constants::ErrorCode::DONE, result
      result = @driver.finalize( handle )
      assert_equal SQLite3::Constants::ErrorCode::OK, result
      sql = "select b from foo"
      result, handle, = @driver.prepare( @db, sql )
      assert_equal SQLite3::Constants::ErrorCode::OK, result
      result = @driver.step( handle )
      assert_equal SQLite3::Constants::ErrorCode::ROW, result
      assert_equal "hello, world", @driver.column_text( handle, 0 )
      result = @driver.finalize( handle )
      assert_equal SQLite3::Constants::ErrorCode::OK, result
    end

    def test_bind_text16
      create_foo
      sql = "insert into foo (b) values (?)"
      result, handle, = @driver.prepare( @db, sql )
      assert_equal SQLite3::Constants::ErrorCode::OK, result
      result = @driver.bind_text( handle, 1, utf16ify("hello, world"), true )
      assert_equal SQLite3::Constants::ErrorCode::OK, result
      result = @driver.step( handle )
      assert_equal SQLite3::Constants::ErrorCode::DONE, result
      result = @driver.finalize( handle )
      assert_equal SQLite3::Constants::ErrorCode::OK, result
      sql = "select b from foo"
      result, handle, = @driver.prepare( @db, sql )
      assert_equal SQLite3::Constants::ErrorCode::OK, result
      result = @driver.step( handle )
      assert_equal SQLite3::Constants::ErrorCode::ROW, result
      assert_equal "hello, world", @driver.column_text( handle, 0 )
      result = @driver.finalize( handle )
      assert_equal SQLite3::Constants::ErrorCode::OK, result
    end

    def test_bind_parameter_index
      create_foo
      sql = "insert into foo (b) values (:hello)"
      result, handle, = @driver.prepare( @db, sql )
      assert_equal SQLite3::Constants::ErrorCode::OK, result
      result = @driver.bind_parameter_index( handle, ":hello" )
      assert_equal 1, result
      result = @driver.bind_parameter_index( handle, ":foo" )
      assert_equal 0, result
      @driver.finalize( handle )
    end

    def test_bind_parameter_name
      create_foo
      sql = "insert into foo (a,b) values (?,:foo)"
      result, handle, = @driver.prepare( @db, sql )
      assert_equal SQLite3::Constants::ErrorCode::OK, result
      assert_nil nil, @driver.bind_parameter_name(handle,1)
      assert_equal ":foo", @driver.bind_parameter_name(handle,2)
      @driver.finalize( handle )
    end

  end
end
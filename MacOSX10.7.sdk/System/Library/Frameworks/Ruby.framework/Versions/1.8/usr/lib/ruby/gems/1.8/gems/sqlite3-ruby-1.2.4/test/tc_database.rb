$:.unshift "../lib"

require 'sqlite3/database'
require 'test/unit'

require 'mocks'

class TC_Database_Init < Test::Unit::TestCase
  def test_new
    # any_instance fails here...
    driver = Driver.new
    driver.expects(:open).once.with('foo.db', false).returns([0, 'cookie'])
    Driver.stubs(:new).returns(driver)
    db = SQLite3::Database.new( 'foo.db', :driver => Driver )
    assert !db.closed?
    assert !db.results_as_hash
    assert !db.type_translation
  end

  def test_open
    driver = Driver.new
    driver.expects(:open).once.with('foo.db', false).returns([0, 'cookie'])
    Driver.stubs(:new).returns(driver)
    db = SQLite3::Database.open( "foo.db", :driver => Driver )
    assert !db.closed?
    assert !db.results_as_hash
    assert !db.type_translation
  end
  
  def test_with_type_translation
    db = SQLite3::Database.open( "foo.db", :driver => Driver,
      :type_translation => true )
    assert db.type_translation
  end
  
  def test_with_results_as_hash
    db = SQLite3::Database.open( "foo.db", :driver => Driver,
      :results_as_hash => true )
    assert db.results_as_hash
  end
  
  def test_with_type_translation_and_results_as_hash
    db = SQLite3::Database.open( "foo.db", :driver => Driver,
      :results_as_hash => true,
      :type_translation => true )
    assert db.results_as_hash
    assert db.type_translation
  end
end

class TC_Database < Test::Unit::TestCase
  def setup
    @db = SQLite3::Database.open( "foo.db",
      :driver => Driver, :statement_factory => Statement )
  end

  def test_quote
    assert_equal "''one''two''three''", SQLite3::Database.quote(
      "'one'two'three'" )
  end

  def test_complete
    Driver.any_instance.expects(:complete?)
    @db.complete? "foo"
  end

  def test_errmsg
    Driver.any_instance.expects(:errmsg)
    @db.errmsg
  end

  def test_errcode
    Driver.any_instance.expects(:errcode)
    @db.errcode
  end

  def test_translator
    translator = @db.translator
    assert_instance_of SQLite3::Translator, translator
  end

  def test_close
    Driver.any_instance.expects(:close).returns(0)
    @db.close
    assert @db.closed?
    Driver.any_instance.expects(:close).never
    @db.close
  end

  def test_trace
    Driver.any_instance.expects(:trace).with('cookie', 15)
    @db.trace( 15 ) { "foo" }
    # assert_equal 1, driver.mock_blocks[:trace].length
  end

  def test_authorizer
    Driver.any_instance.expects(:set_authorizer).with('cookie', 15).returns(0)
    @db.authorizer( 15 ) { "foo" }
    # assert_equal 1, driver.mock_blocks[:set_authorizer].length
  end

  def test_prepare_no_block
    Statement.any_instance.expects(:close).never
    assert_nothing_raised { @db.prepare( "foo" ) }
  end

  def test_prepare_with_block
    called = false
    # any_instance fails here...
    statement = Statement.new('cookie', 'foo')
    statement.expects(:close).once
    Statement.stubs(:new).returns(statement)
    @db.prepare( "foo" ) { |stmt| called = true }
    assert called
  end

  def test_execute_no_block
    # any_instance fails here...
    statement = Statement.new('cookie', 'foo')
    statement.expects(:execute).with('bar', 'baz').returns(MockResultSet.new)
    Statement.stubs(:new).returns(statement)
    MockResultSet.any_instance.stubs(:inject).returns([['foo']])
    result = @db.execute( "foo", "bar", "baz" )
    assert_equal [["foo"]], result
  end

  def test_execute_with_block
    called = false
    # any_instance fails here...
    statement = Statement.new('cookie', 'foo')
    statement.expects(:execute).with('bar', 'baz').returns(MockResultSet.new)
    Statement.stubs(:new).returns(statement)
    @db.execute( "foo", "bar", "baz" ) do |row|
      called = true
      assert_equal ["foo"], row
    end

    assert called
  end

  def test_execute2_no_block
    # any_instance fails here...
    statement = Statement.new('cookie', 'foo')
    statement.expects(:execute).with('bar', 'baz').returns(MockResultSet.new)
    Statement.stubs(:new).returns(statement)
    MockResultSet.any_instance.stubs(:inject).returns([['name'], ['foo']])
    result = @db.execute2( "foo", "bar", "baz" )
    assert_equal [["name"],["foo"]], result
  end

  def test_execute2_with_block
    called = false
    parts = [ ["name"],["foo"] ]
    # any_instance fails here...
    statement = Statement.new('cookie', 'foo')
    statement.expects(:execute).with('bar', 'baz').returns(MockResultSet.new)
    Statement.stubs(:new).returns(statement)
    @db.execute2( "foo", "bar", "baz" ) do |row|
      called = true
      assert_equal parts.shift, row
    end

    assert called
  end

  def test_execute_batch
    # any_instance fails here...
    statement = Statement.new('cookie', 'foo')
    statement.expects(:execute).with('bar', 'baz').returns(MockResultSet.new)
    Statement.stubs(:new).returns(statement)
    @db.execute_batch( "foo", "bar", "baz" )
  end

  def test_get_first_row
    result = @db.get_first_row( "foo", "bar", "baz" )
    assert_equal ["foo"], result
  end

  def test_get_first_value
    result = @db.get_first_value( "foo", "bar", "baz" )
    assert_equal "foo", result
  end

  def test_changes
    Driver.any_instance.expects(:changes).returns(14)
    assert_equal 14, @db.changes
  end

  def test_total_changes
    Driver.any_instance.expects(:total_changes).returns(28)
    assert_equal 28, @db.total_changes
  end

  def test_interrupt
    Driver.any_instance.expects(:interrupt)
    @db.interrupt
  end
end

require 'rubygems'
gem 'mocha'

require 'mocha'

class Driver < Mocha::Mock
  def initialize
    super
    stubs( :open ).returns([0, 'cookie'])
    stubs( :close ).returns(0)
    stubs( :complete? ).returns(0)
    stubs( :errmsg ).returns('')
    stubs( :errcode ).returns(0)
    stubs( :trace ).returns(nil)
    stubs( :set_authorizer ).returns(0)
    stubs( :prepare ).returns([0, 'stmt', 'remainder'])
    stubs( :finalize ).returns(0)
    stubs( :changes ).returns(14)
    stubs( :total_changes ).returns(28)
    stubs( :interrupt ).returns(0)
  end
end

class MockResultSet < Mocha::Mock
  def initialize
    super
    stubs( :each ).yields(['foo'])
    stubs( :columns ).returns(['name'])
  end
end

class Statement < Mocha::Mock
  attr_reader :handle
  attr_reader :sql
  attr_reader :last_result

  def initialize( handle, sql )
    super()
    @handle = handle
    @sql = sql
    stubs( :close ).returns(0)
    stubs( :remainder ).returns('')
    stubs( :execute ).returns(MockResultSet.new)
  end
end

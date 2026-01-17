require 'sqlite3/constants'
require 'sqlite3/errors'
require 'sqlite3/pragmas'
require 'sqlite3/statement'
require 'sqlite3/translator'
require 'sqlite3/value'

module SQLite3

  # The Database class encapsulates a single connection to a SQLite3 database.
  # Its usage is very straightforward:
  #
  #   require 'sqlite3'
  #
  #   db = SQLite3::Database.new( "data.db" )
  #
  #   db.execute( "select * from table" ) do |row|
  #     p row
  #   end
  #
  #   db.close
  #
  # It wraps the lower-level methods provides by the selected driver, and
  # includes the Pragmas module for access to various pragma convenience
  # methods.
  #
  # The Database class provides type translation services as well, by which
  # the SQLite3 data types (which are all represented as strings) may be
  # converted into their corresponding types (as defined in the schemas
  # for their tables). This translation only occurs when querying data from
  # the database--insertions and updates are all still typeless.
  #
  # Furthermore, the Database class has been designed to work well with the
  # ArrayFields module from Ara Howard. If you require the ArrayFields
  # module before performing a query, and if you have not enabled results as
  # hashes, then the results will all be indexible by field name.
  class Database
    include Pragmas

    class <<self

      alias :open :new

      # Quotes the given string, making it safe to use in an SQL statement.
      # It replaces all instances of the single-quote character with two
      # single-quote characters. The modified string is returned.
      def quote( string )
        string.gsub( /'/, "''" )
      end

    end

    # The low-level opaque database handle that this object wraps.
    attr_reader :handle

    # A reference to the underlying SQLite3 driver used by this database.
    attr_reader :driver

    # A boolean that indicates whether rows in result sets should be returned
    # as hashes or not. By default, rows are returned as arrays.
    attr_accessor :results_as_hash

    # A boolean indicating whether or not type translation is enabled for this
    # database.
    attr_accessor :type_translation

    # Create a new Database object that opens the given file. If utf16
    # is +true+, the filename is interpreted as a UTF-16 encoded string.
    #
    # By default, the new database will return result rows as arrays
    # (#results_as_hash) and has type translation disabled (#type_translation=).
    def initialize( file_name, options={} )
      utf16 = options.fetch(:utf16, false)
      load_driver( options[:driver] )

      @statement_factory = options[:statement_factory] || Statement

      result, @handle = @driver.open( file_name, utf16 )
      Error.check( result, self, "could not open database" )

      @closed = false
      @results_as_hash = options.fetch(:results_as_hash,false)
      @type_translation = options.fetch(:type_translation,false)
      @translator = nil
      @transaction_active = false
    end

    # Return +true+ if the string is a valid (ie, parsable) SQL statement, and
    # +false+ otherwise. If +utf16+ is +true+, then the string is a UTF-16
    # character string.
    def complete?( string, utf16=false )
      @driver.complete?( string, utf16 )
    end

    # Return a string describing the last error to have occurred with this
    # database.
    def errmsg( utf16=false )
      @driver.errmsg( @handle, utf16 )
    end

    # Return an integer representing the last error to have occurred with this
    # database.
    def errcode
      @driver.errcode( @handle )
    end

    # Return the type translator employed by this database instance. Each
    # database instance has its own type translator; this allows for different
    # type handlers to be installed in each instance without affecting other
    # instances. Furthermore, the translators are instantiated lazily, so that
    # if a database does not use type translation, it will not be burdened by
    # the overhead of a useless type translator. (See the Translator class.)
    def translator
      @translator ||= Translator.new
    end

    # Closes this database.
    def close
      unless @closed
        result = @driver.close( @handle )
        Error.check( result, self )
      end
      @closed = true
    end

    # Returns +true+ if this database instance has been closed (see #close).
    def closed?
      @closed
    end

    # Installs (or removes) a block that will be invoked for every SQL
    # statement executed. The block receives a two parameters: the +data+
    # argument, and the SQL statement executed. If the block is +nil+,
    # any existing tracer will be uninstalled.
    def trace( data=nil, &block )
      @driver.trace( @handle, data, &block )
    end

    # Installs (or removes) a block that will be invoked for every access
    # to the database. If the block returns 0 (or +nil+), the statement
    # is allowed to proceed. Returning 1 causes an authorization error to
    # occur, and returning 2 causes the access to be silently denied.
    def authorizer( data=nil, &block )
      result = @driver.set_authorizer( @handle, data, &block )
      Error.check( result, self )
    end

    # Returns a Statement object representing the given SQL. This does not
    # execute the statement; it merely prepares the statement for execution.
    #
    # The Statement can then be executed using Statement#execute.
    #
    def prepare( sql )
      stmt = @statement_factory.new( self, sql )
      if block_given?
        begin
          yield stmt
        ensure
          stmt.close
        end
      else
        return stmt
      end
    end

    # Executes the given SQL statement. If additional parameters are given,
    # they are treated as bind variables, and are bound to the placeholders in
    # the query.
    #
    # Note that if any of the values passed to this are hashes, then the
    # key/value pairs are each bound separately, with the key being used as
    # the name of the placeholder to bind the value to.
    #
    # The block is optional. If given, it will be invoked for each row returned
    # by the query. Otherwise, any results are accumulated into an array and
    # returned wholesale.
    #
    # See also #execute2, #query, and #execute_batch for additional ways of
    # executing statements.
    def execute( sql, *bind_vars )
      prepare( sql ) do |stmt|
        result = stmt.execute( *bind_vars )
        if block_given?
          result.each { |row| yield row }
        else
          return result.inject( [] ) { |arr,row| arr << row; arr }
        end
      end
    end

    # Executes the given SQL statement, exactly as with #execute. However, the
    # first row returned (either via the block, or in the returned array) is
    # always the names of the columns. Subsequent rows correspond to the data
    # from the result set.
    #
    # Thus, even if the query itself returns no rows, this method will always
    # return at least one row--the names of the columns.
    #
    # See also #execute, #query, and #execute_batch for additional ways of
    # executing statements.
    def execute2( sql, *bind_vars )
      prepare( sql ) do |stmt|
        result = stmt.execute( *bind_vars )
        if block_given?
          yield result.columns
          result.each { |row| yield row }
        else
          return result.inject( [ result.columns ] ) { |arr,row|
            arr << row; arr }
        end
      end
    end

    # Executes all SQL statements in the given string. By contrast, the other
    # means of executing queries will only execute the first statement in the
    # string, ignoring all subsequent statements. This will execute each one
    # in turn. The same bind parameters, if given, will be applied to each
    # statement.
    #
    # This always returns +nil+, making it unsuitable for queries that return
    # rows.
    def execute_batch( sql, *bind_vars )
      sql = sql.strip
      until sql.empty? do
        prepare( sql ) do |stmt|
          stmt.execute( *bind_vars )
          sql = stmt.remainder.strip
        end
      end
      nil
    end

    # This is a convenience method for creating a statement, binding
    # paramters to it, and calling execute:
    #
    #   result = db.query( "select * from foo where a=?", 5 )
    #   # is the same as
    #   result = db.prepare( "select * from foo where a=?" ).execute( 5 )
    #
    # You must be sure to call +close+ on the ResultSet instance that is
    # returned, or you could have problems with locks on the table. If called
    # with a block, +close+ will be invoked implicitly when the block 
    # terminates.
    def query( sql, *bind_vars )
      result = prepare( sql ).execute( *bind_vars )
      if block_given?
        begin
          yield result
        ensure
          result.close
        end
      else
        return result
      end
    end

    # A convenience method for obtaining the first row of a result set, and
    # discarding all others. It is otherwise identical to #execute.
    #
    # See also #get_first_value.
    def get_first_row( sql, *bind_vars )
      execute( sql, *bind_vars ) { |row| return row }
      nil
    end

    # A convenience method for obtaining the first value of the first row of a
    # result set, and discarding all other values and rows. It is otherwise
    # identical to #execute.
    #
    # See also #get_first_row.
    def get_first_value( sql, *bind_vars )
      execute( sql, *bind_vars ) { |row| return row[0] }
      nil
    end

    # Obtains the unique row ID of the last row to be inserted by this Database
    # instance.
    def last_insert_row_id
      @driver.last_insert_rowid( @handle )
    end

    # Returns the number of changes made to this database instance by the last
    # operation performed. Note that a "delete from table" without a where
    # clause will not affect this value.
    def changes
      @driver.changes( @handle )
    end

    # Returns the total number of changes made to this database instance
    # since it was opened.
    def total_changes
      @driver.total_changes( @handle )
    end

    # Interrupts the currently executing operation, causing it to abort.
    def interrupt
      @driver.interrupt( @handle )
    end

    # Register a busy handler with this database instance. When a requested
    # resource is busy, this handler will be invoked. If the handler returns
    # +false+, the operation will be aborted; otherwise, the resource will
    # be requested again.
    #
    # The handler will be invoked with the name of the resource that was
    # busy, and the number of times it has been retried.
    #
    # See also the mutually exclusive #busy_timeout. 
    def busy_handler( data=nil, &block ) # :yields: data, retries
      result = @driver.busy_handler( @handle, data, &block )
      Error.check( result, self )
    end

    # Indicates that if a request for a resource terminates because that
    # resource is busy, SQLite should sleep and retry for up to the indicated
    # number of milliseconds. By default, SQLite does not retry
    # busy resources. To restore the default behavior, send 0 as the
    # +ms+ parameter.
    #
    # See also the mutually exclusive #busy_handler.
    def busy_timeout( ms )
      result = @driver.busy_timeout( @handle, ms )
      Error.check( result, self )
    end

    # Creates a new function for use in SQL statements. It will be added as
    # +name+, with the given +arity+. (For variable arity functions, use
    # -1 for the arity.)
    #
    # The block should accept at least one parameter--the FunctionProxy
    # instance that wraps this function invocation--and any other
    # arguments it needs (up to its arity).
    #
    # The block does not return a value directly. Instead, it will invoke
    # the FunctionProxy#set_result method on the +func+ parameter and
    # indicate the return value that way.
    #
    # Example:
    #
    #   db.create_function( "maim", 1 ) do |func, value|
    #     if value.nil?
    #       func.result = nil
    #     else
    #       func.result = value.split(//).sort.join
    #     end
    #   end
    #
    #   puts db.get_first_value( "select maim(name) from table" )
    def create_function( name, arity, text_rep=Constants::TextRep::ANY,
      &block ) # :yields: func, *args
    # begin
      callback = proc do |func,*args|
        begin
          block.call( FunctionProxy.new( @driver, func ),
            *args.map{|v| Value.new(self,v)} )
        rescue StandardError, Exception => e
          @driver.result_error( func,
            "#{e.message} (#{e.class})", -1 )
        end
      end

      result = @driver.create_function( @handle, name, arity, text_rep, nil,
        callback, nil, nil )
      Error.check( result, self )

      self
    end

    # Creates a new aggregate function for use in SQL statements. Aggregate
    # functions are functions that apply over every row in the result set,
    # instead of over just a single row. (A very common aggregate function
    # is the "count" function, for determining the number of rows that match
    # a query.)
    #
    # The new function will be added as +name+, with the given +arity+. (For
    # variable arity functions, use -1 for the arity.)
    #
    # The +step+ parameter must be a proc object that accepts as its first
    # parameter a FunctionProxy instance (representing the function
    # invocation), with any subsequent parameters (up to the function's arity).
    # The +step+ callback will be invoked once for each row of the result set.
    #
    # The +finalize+ parameter must be a +proc+ object that accepts only a
    # single parameter, the FunctionProxy instance representing the current
    # function invocation. It should invoke FunctionProxy#set_result to
    # store the result of the function.
    #
    # Example:
    #
    #   db.create_aggregate( "lengths", 1 ) do
    #     step do |func, value|
    #       func[ :total ] ||= 0
    #       func[ :total ] += ( value ? value.length : 0 )
    #     end
    #
    #     finalize do |func|
    #       func.set_result( func[ :total ] || 0 )
    #     end
    #   end
    #
    #   puts db.get_first_value( "select lengths(name) from table" )
    #
    # See also #create_aggregate_handler for a more object-oriented approach to
    # aggregate functions.
    def create_aggregate( name, arity, step=nil, finalize=nil,
      text_rep=Constants::TextRep::ANY, &block )
    # begin
      if block
        proxy = AggregateDefinitionProxy.new
        proxy.instance_eval(&block)
        step ||= proxy.step_callback
        finalize ||= proxy.finalize_callback
      end

      step_callback = proc do |func,*args|
        ctx = @driver.aggregate_context( func )
        unless ctx[:__error]
          begin
            step.call( FunctionProxy.new( @driver, func, ctx ),
              *args.map{|v| Value.new(self,v)} )
          rescue Exception => e
            ctx[:__error] = e
          end
        end
      end

      finalize_callback = proc do |func|
        ctx = @driver.aggregate_context( func )
        unless ctx[:__error]
          begin
            finalize.call( FunctionProxy.new( @driver, func, ctx ) )
          rescue Exception => e
            @driver.result_error( func,
              "#{e.message} (#{e.class})", -1 )
          end
        else
          e = ctx[:__error]
          @driver.result_error( func,
            "#{e.message} (#{e.class})", -1 )
        end
      end

      result = @driver.create_function( @handle, name, arity, text_rep, nil,
        nil, step_callback, finalize_callback )
      Error.check( result, self )

      self
    end

    # This is another approach to creating an aggregate function (see
    # #create_aggregate). Instead of explicitly specifying the name,
    # callbacks, arity, and type, you specify a factory object
    # (the "handler") that knows how to obtain all of that information. The
    # handler should respond to the following messages:
    #
    # +arity+:: corresponds to the +arity+ parameter of #create_aggregate. This
    #           message is optional, and if the handler does not respond to it,
    #           the function will have an arity of -1.
    # +name+:: this is the name of the function. The handler _must_ implement
    #          this message.
    # +new+:: this must be implemented by the handler. It should return a new
    #         instance of the object that will handle a specific invocation of
    #         the function.
    #
    # The handler instance (the object returned by the +new+ message, described
    # above), must respond to the following messages:
    #
    # +step+:: this is the method that will be called for each step of the
    #          aggregate function's evaluation. It should implement the same
    #          signature as the +step+ callback for #create_aggregate.
    # +finalize+:: this is the method that will be called to finalize the
    #              aggregate function's evaluation. It should implement the
    #              same signature as the +finalize+ callback for
    #              #create_aggregate.
    #
    # Example:
    #
    #   class LengthsAggregateHandler
    #     def self.arity; 1; end
    #
    #     def initialize
    #       @total = 0
    #     end
    #
    #     def step( ctx, name )
    #       @total += ( name ? name.length : 0 )
    #     end
    #
    #     def finalize( ctx )
    #       ctx.set_result( @total )
    #     end
    #   end
    #
    #   db.create_aggregate_handler( LengthsAggregateHandler )
    #   puts db.get_first_value( "select lengths(name) from A" )
    def create_aggregate_handler( handler )
      arity = -1
      text_rep = Constants::TextRep::ANY

      arity = handler.arity if handler.respond_to?(:arity)
      text_rep = handler.text_rep if handler.respond_to?(:text_rep)
      name = handler.name

      step = proc do |func,*args|
        ctx = @driver.aggregate_context( func )
        unless ctx[ :__error ]
          ctx[ :handler ] ||= handler.new
          begin
            ctx[ :handler ].step( FunctionProxy.new( @driver, func, ctx ),
              *args.map{|v| Value.new(self,v)} )
          rescue Exception, StandardError => e
            ctx[ :__error ] = e
          end
        end
      end

      finalize = proc do |func|
        ctx = @driver.aggregate_context( func )
        unless ctx[ :__error ]
          ctx[ :handler ] ||= handler.new
          begin
            ctx[ :handler ].finalize( FunctionProxy.new( @driver, func, ctx ) )
          rescue Exception => e
            ctx[ :__error ] = e
          end
        end

        if ctx[ :__error ]
          e = ctx[ :__error ]
          @driver.sqlite3_result_error( func, "#{e.message} (#{e.class})", -1 )
        end
      end

      result = @driver.create_function( @handle, name, arity, text_rep, nil,
        nil, step, finalize )
      Error.check( result, self )

      self
    end

    # Begins a new transaction. Note that nested transactions are not allowed
    # by SQLite, so attempting to nest a transaction will result in a runtime
    # exception.
    #
    # The +mode+ parameter may be either <tt>:deferred</tt> (the default),
    # <tt>:immediate</tt>, or <tt>:exclusive</tt>.
    #
    # If a block is given, the database instance is yielded to it, and the
    # transaction is committed when the block terminates. If the block
    # raises an exception, a rollback will be performed instead. Note that if
    # a block is given, #commit and #rollback should never be called
    # explicitly or you'll get an error when the block terminates.
    #
    # If a block is not given, it is the caller's responsibility to end the
    # transaction explicitly, either by calling #commit, or by calling
    # #rollback.
    def transaction( mode = :deferred )
      execute "begin #{mode.to_s} transaction"
      @transaction_active = true

      if block_given?
        abort = false
        begin
          yield self
        rescue ::Object
          abort = true
          raise
        ensure
          abort and rollback or commit
        end
      end

      true
    end

    # Commits the current transaction. If there is no current transaction,
    # this will cause an error to be raised. This returns +true+, in order
    # to allow it to be used in idioms like
    # <tt>abort? and rollback or commit</tt>.
    def commit
      execute "commit transaction"
      @transaction_active = false
      true
    end

    # Rolls the current transaction back. If there is no current transaction,
    # this will cause an error to be raised. This returns +true+, in order
    # to allow it to be used in idioms like
    # <tt>abort? and rollback or commit</tt>.
    def rollback
      execute "rollback transaction"
      @transaction_active = false
      true
    end

    # Returns +true+ if there is a transaction active, and +false+ otherwise.
    def transaction_active?
      @transaction_active
    end

    # Loads the corresponding driver, or if it is nil, attempts to locate a
    # suitable driver.
    def load_driver( driver )
      case driver
        when Class
          # do nothing--use what was given
        when Symbol, String
          require "sqlite3/driver/#{driver.to_s.downcase}/driver"
          driver = SQLite3::Driver.const_get( driver )::Driver
        else
          [ "Native", "DL" ].each do |d|
            begin
              require "sqlite3/driver/#{d.downcase}/driver"
              driver = SQLite3::Driver.const_get( d )::Driver
              break
            rescue SyntaxError
              raise
            rescue ScriptError, Exception, NameError
            end
          end
          raise "no driver for sqlite3 found" unless driver
      end

      @driver = driver.new
    end
    private :load_driver

    # A helper class for dealing with custom functions (see #create_function,
    # #create_aggregate, and #create_aggregate_handler). It encapsulates the
    # opaque function object that represents the current invocation. It also
    # provides more convenient access to the API functions that operate on
    # the function object.
    #
    # This class will almost _always_ be instantiated indirectly, by working
    # with the create methods mentioned above.
    class FunctionProxy

      # Create a new FunctionProxy that encapsulates the given +func+ object.
      # If context is non-nil, the functions context will be set to that. If
      # it is non-nil, it must quack like a Hash. If it is nil, then none of
      # the context functions will be available.
      def initialize( driver, func, context=nil )
        @driver = driver
        @func = func
        @context = context
      end

      # Calls #set_result to set the result of this function.
      def result=( result )
        set_result( result )
      end

      # Set the result of the function to the given value. The function will
      # then return this value.
      def set_result( result, utf16=false )
        @driver.result_text( @func, result, utf16 )
      end

      # Set the result of the function to the given error message.
      # The function will then return that error.
      def set_error( error )
        @driver.result_error( @func, error.to_s, -1 )
      end

      # (Only available to aggregate functions.) Returns the number of rows
      # that the aggregate has processed so far. This will include the current
      # row, and so will always return at least 1.
      def count
        ensure_aggregate!
        @driver.aggregate_count( @func )
      end

      # Returns the value with the given key from the context. This is only
      # available to aggregate functions.
      def []( key )
        ensure_aggregate!
        @context[ key ]
      end

      # Sets the value with the given key in the context. This is only
      # available to aggregate functions.
      def []=( key, value )
        ensure_aggregate!
        @context[ key ] = value
      end

      # A function for performing a sanity check, to ensure that the function
      # being invoked is an aggregate function. This is implied by the
      # existence of the context variable.
      def ensure_aggregate!
        unless @context
          raise MisuseException, "function is not an aggregate"
        end
      end
      private :ensure_aggregate!

    end

    # A proxy used for defining the callbacks to an aggregate function.
    class AggregateDefinitionProxy # :nodoc:
      attr_reader :step_callback, :finalize_callback

      def step( &block )
        @step_callback = block
      end

      def finalize( &block )
        @finalize_callback = block
      end
    end

  end

end


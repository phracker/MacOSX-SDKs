require 'sqlite3_api'

module SQLite3 ; module Driver ; module Native

  class Driver

    def initialize
      @callback_data = Hash.new
      @authorizer = Hash.new
      @busy_handler = Hash.new
      @trace = Hash.new
    end

    def complete?( sql, utf16=false )
      API.send( utf16 ? :sqlite3_complete16 : :sqlite3_complete, sql ) != 0
    end

    def busy_handler( db, data=nil, &block )
      if block
        cb = API::CallbackData.new
        cb.proc = block
        cb.data = data
        result = API.sqlite3_busy_handler( db, API::Sqlite3_ruby_busy_handler, cb )
        # Reference the Callback object so that 
        # it is not deleted by the GC
        @busy_handler[db] = cb
      else
        # Unreference the callback *after* having removed it
        # from sqlite
        result = API.sqlite3_busy_handler( db, nil, nil )
        @busy_handler.delete(db)
      end

      result
    end

    def set_authorizer( db, data=nil, &block )
      if block
        cb = API::CallbackData.new
        cb.proc = block
        cb.data = data
        result = API.sqlite3_set_authorizer( db, API::Sqlite3_ruby_authorizer, cb )
        @authorizer[db] = cb # see comments in busy_handler
      else
        result = API.sqlite3_set_authorizer( db, nil, nil )
        @authorizer.delete(db) # see comments in busy_handler
      end

      result
    end

    def trace( db, data=nil, &block )
      if block
        cb = API::CallbackData.new
        cb.proc = block
        cb.data = data
        result = API.sqlite3_trace( db, API::Sqlite3_ruby_trace, cb )
        @trace[db] = cb # see comments in busy_handler
      else
        result = API.sqlite3_trace( db, nil, nil )
        @trace.delete(db) # see comments in busy_handler
      end

      result
    end

    def open( filename, utf16=false )
      API.send( utf16 ? :sqlite3_open16 : :sqlite3_open, filename )
    end

    def errmsg( db, utf16=false )
      API.send( utf16 ? :sqlite3_errmsg16 : :sqlite3_errmsg, db )
    end

    def prepare( db, sql, utf16=false )
      API.send( ( utf16 ? :sqlite3_prepare16 : :sqlite3_prepare ),
        db, sql )
    end

    def bind_text( stmt, index, value, utf16=false )
      API.send( ( utf16 ? :sqlite3_bind_text16 : :sqlite3_bind_text ),
        stmt, index, value.to_s )
    end

    def column_name( stmt, index, utf16=false )
      API.send( ( utf16 ? :sqlite3_column_name16 : :sqlite3_column_name ),
        stmt, index )
    end

    def column_decltype( stmt, index, utf16=false )
      API.send(
        ( utf16 ? :sqlite3_column_decltype16 : :sqlite3_column_decltype ),
        stmt, index )
    end

    def column_text( stmt, index, utf16=false )
      API.send( ( utf16 ? :sqlite3_column_text16 : :sqlite3_column_text ),
        stmt, index )
    end

    def create_function( db, name, args, text, cookie, func, step, final )
      if func || ( step && final )
        cb = API::CallbackData.new
        cb.proc = cb.proc2 = nil
        cb.data = cookie
      end

      if func
        cb.proc = func

        func = API::Sqlite3_ruby_function_step
        step = final = nil
      elsif step && final
        cb.proc = step
        cb.proc2 = final

        func = nil
        step = API::Sqlite3_ruby_function_step
        final = API::Sqlite3_ruby_function_final
      end

      result = API.sqlite3_create_function( db, name, args, text, cb, func, step, final )

      # see comments in busy_handler
      if cb
        @callback_data[ name ] = cb
      else
        @callback_data.delete( name )
      end

      return result
    end

    def value_text( value, utf16=false )
      method = case utf16
        when nil, false then :sqlite3_value_text
        when :le then :sqlite3_value_text16le
        when :be then :sqlite3_value_text16be
        else :sqlite3_value_text16
      end

      API.send( method, value )
    end

    def result_text( context, result, utf16=false )
      method = case utf16
        when nil, false then :sqlite3_result_text
        when :le then :sqlite3_result_text16le
        when :be then :sqlite3_result_text16be
        else :sqlite3_result_text16
      end

      API.send( method, context, result.to_s )
    end

    def result_error( context, value, utf16=false )
      API.send( ( utf16 ? :sqlite3_result_error16 : :sqlite3_result_error ),
        context, value )
    end

    def self.api_delegate( name )
      eval "def #{name} (*args) API.sqlite3_#{name}( *args ) ; end"
    end

    api_delegate :libversion
    api_delegate :close
    api_delegate :last_insert_rowid
    api_delegate :changes
    api_delegate :total_changes
    api_delegate :interrupt
    api_delegate :busy_timeout
    api_delegate :errcode
    api_delegate :bind_blob
    api_delegate :bind_double
    api_delegate :bind_int
    api_delegate :bind_int64
    api_delegate :bind_null
    api_delegate :bind_parameter_count
    api_delegate :bind_parameter_name
    api_delegate :bind_parameter_index
    api_delegate :column_count
    api_delegate :step
    api_delegate :data_count
    api_delegate :column_blob
    api_delegate :column_bytes
    api_delegate :column_bytes16
    api_delegate :column_double
    api_delegate :column_int
    api_delegate :column_int64
    api_delegate :column_type
    api_delegate :finalize
    api_delegate :reset
    api_delegate :aggregate_count
    api_delegate :value_blob
    api_delegate :value_bytes
    api_delegate :value_bytes16
    api_delegate :value_double
    api_delegate :value_int
    api_delegate :value_int64
    api_delegate :value_type
    api_delegate :result_blob
    api_delegate :result_double
    api_delegate :result_int
    api_delegate :result_int64
    api_delegate :result_null
    api_delegate :result_value
    api_delegate :aggregate_context

  end

end ; end ; end

require 'sqlite3/constants'

module SQLite3

  class Exception < ::StandardError
    @code = 0

    # The numeric error code that this exception represents.
    def self.code
      @code
    end

    # A convenience for accessing the error code for this exception.
    def code
      self.class.code
    end
  end

  class SQLException < Exception; end
  class InternalException < Exception; end
  class PermissionException < Exception; end
  class AbortException < Exception; end
  class BusyException < Exception; end
  class LockedException < Exception; end
  class MemoryException < Exception; end
  class ReadOnlyException < Exception; end
  class InterruptException < Exception; end
  class IOException < Exception; end
  class CorruptException < Exception; end
  class NotFoundException < Exception; end
  class FullException < Exception; end
  class CantOpenException < Exception; end
  class ProtocolException < Exception; end
  class EmptyException < Exception; end
  class SchemaChangedException < Exception; end
  class TooBigException < Exception; end
  class ConstraintException < Exception; end
  class MismatchException < Exception; end
  class MisuseException < Exception; end
  class UnsupportedException < Exception; end
  class AuthorizationException < Exception; end
  class FormatException < Exception; end
  class RangeException < Exception; end
  class NotADatabaseException < Exception; end

  EXCEPTIONS = [
    nil,
    SQLException, InternalException, PermissionException,
    AbortException, BusyException, LockedException, MemoryException,
    ReadOnlyException, InterruptException, IOException, CorruptException,
    NotFoundException, FullException, CantOpenException, ProtocolException,
    EmptyException, SchemaChangedException, TooBigException,
    ConstraintException, MismatchException, MisuseException,
    UnsupportedException, AuthorizationException, FormatException,
    RangeException, NotADatabaseException
  ].each_with_index { |e,i| e.instance_variable_set( :@code, i ) if e }

  module Error
    def check( result, db=nil, msg=nil )
      unless result == Constants::ErrorCode::OK
        msg = ( msg ? msg + ": " : "" ) + db.errmsg if db
        raise(( EXCEPTIONS[result] || SQLite3::Exception ), msg)
      end
    end
    module_function :check
  end

end

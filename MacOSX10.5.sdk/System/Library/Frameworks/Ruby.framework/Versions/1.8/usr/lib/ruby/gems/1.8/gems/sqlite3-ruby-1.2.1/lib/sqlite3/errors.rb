#--
# =============================================================================
# Copyright (c) 2004, Jamis Buck (jgb3@email.byu.edu)
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
# 
#     * Redistributions of source code must retain the above copyright notice,
#       this list of conditions and the following disclaimer.
# 
#     * Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in the
#       documentation and/or other materials provided with the distribution.
# 
#     * The names of its contributors may not be used to endorse or promote
#       products derived from this software without specific prior written
#       permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# =============================================================================
#++

require 'sqlite3/constants'

module SQLite3

  class Exception < ::Exception
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

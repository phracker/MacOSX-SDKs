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

module SQLite3 ; module Constants

  module TextRep
    UTF8    = 1
    UTF16LE = 2
    UTF16BE = 3
    UTF16   = 4
    ANY     = 5
  end

  module ColumnType
    INTEGER = 1
    FLOAT   = 2
    TEXT    = 3
    BLOB    = 4
    NULL    = 5
  end

  module ErrorCode
    OK         =  0   # Successful result
    ERROR      =  1   # SQL error or missing database
    INTERNAL   =  2   # An internal logic error in SQLite
    PERM       =  3   # Access permission denied
    ABORT      =  4   # Callback routine requested an abort
    BUSY       =  5   # The database file is locked
    LOCKED     =  6   # A table in the database is locked
    NOMEM      =  7   # A malloc() failed
    READONLY   =  8   # Attempt to write a readonly database
    INTERRUPT  =  9   # Operation terminated by sqlite_interrupt()
    IOERR      = 10   # Some kind of disk I/O error occurred
    CORRUPT    = 11   # The database disk image is malformed
    NOTFOUND   = 12   # (Internal Only) Table or record not found
    FULL       = 13   # Insertion failed because database is full
    CANTOPEN   = 14   # Unable to open the database file
    PROTOCOL   = 15   # Database lock protocol error
    EMPTY      = 16   # (Internal Only) Database table is empty
    SCHEMA     = 17   # The database schema changed
    TOOBIG     = 18   # Too much data for one row of a table
    CONSTRAINT = 19   # Abort due to contraint violation
    MISMATCH   = 20   # Data type mismatch
    MISUSE     = 21   # Library used incorrectly
    NOLFS      = 22   # Uses OS features not supported on host
    AUTH       = 23   # Authorization denied

    ROW        = 100  # sqlite_step() has another row ready
    DONE       = 101  # sqlite_step() has finished executing
  end

end ; end

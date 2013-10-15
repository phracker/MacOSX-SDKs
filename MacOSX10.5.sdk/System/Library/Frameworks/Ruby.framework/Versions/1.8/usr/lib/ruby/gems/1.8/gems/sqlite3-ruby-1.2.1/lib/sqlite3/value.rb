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

  class Value
    attr_reader :handle

    def initialize( db, handle )
      @driver = db.driver
      @handle = handle
    end

    def null?
      type == :null
    end

    def to_blob
      @driver.value_blob( @handle )
    end

    def length( utf16=false )
      if utf16
        @driver.value_bytes16( @handle )
      else
        @driver.value_bytes( @handle )
      end
    end

    def to_f
      @driver.value_double( @handle )
    end

    def to_i
      @driver.value_int( @handle )
    end

    def to_int64
      @driver.value_int64( @handle )
    end

    def to_s( utf16=false )
      @driver.value_text( @handle, utf16 )
    end

    def type
      case @driver.value_type( @handle )
        when Constants::ColumnType::INTEGER then :int
        when Constants::ColumnType::FLOAT   then :float
        when Constants::ColumnType::TEXT    then :text
        when Constants::ColumnType::BLOB    then :blob
        when Constants::ColumnType::NULL    then :null
      end
    end
    
  end

end

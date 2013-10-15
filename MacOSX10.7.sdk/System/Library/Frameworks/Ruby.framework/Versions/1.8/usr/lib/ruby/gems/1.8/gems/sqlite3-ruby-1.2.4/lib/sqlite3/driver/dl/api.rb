require 'dl/import'

module SQLite3 ; module Driver; module DL;

  module API
    extend ::DL::Importable

    library_name = case RUBY_PLATFORM.downcase
      when /darwin/
        "libsqlite3.dylib"
      when /linux/, /freebsd|netbsd|openbsd|dragonfly/, /solaris/
        "libsqlite3.so"
      when /win32/
        "sqlite3.dll"
      else
        abort <<-EOF
== * UNSUPPORTED PLATFORM ======================================================
The platform '#{RUBY_PLATFORM}' is unsupported. Please help the author by
editing the following file to allow your sqlite3 library to be found, and
submitting a patch to jamis_buck@byu.edu. Thanks!

#{__FILE__}
=========================================================================== * ==
        EOF
    end

    if defined? SQLITE3_LIB_PATH
      library_name = File.join( SQLITE3_LIB_PATH, library_name )
    end

    dlload library_name

    typealias "db",      "void*"
    typealias "stmt",    "void*"
    typealias "value",   "void*"
    typealias "context", "void*"

    # until Ruby/DL supports 64-bit ints, we'll just treat them as 32-bit ints
    typealias "int64", "unsigned long"

    extern "const char *sqlite3_libversion()"

    extern "int sqlite3_open(const char*,db*)"
    extern "int sqlite3_open16(const void*,db*)"
    extern "int sqlite3_close(db)"
    extern "const char* sqlite3_errmsg(db)"
    extern "void* sqlite3_errmsg16(db)"
    extern "int sqlite3_errcode(db)"

    extern "int sqlite3_prepare(db,const char*,int,stmt*,const char**)"
    extern "int sqlite3_prepare16(db,const void*,int,stmt*,const void**)"
    extern "int sqlite3_finalize(stmt)"
    extern "int sqlite3_reset(stmt)"
    extern "int sqlite3_step(stmt)"

    extern "int64 sqlite3_last_insert_rowid(db)"
    extern "int sqlite3_changes(db)"
    extern "int sqlite3_total_changes(db)"
    extern "void sqlite3_interrupt(db)"
    extern "ibool sqlite3_complete(const char*)"
    extern "ibool sqlite3_complete16(const void*)"

    extern "int sqlite3_busy_handler(db,void*,void*)"
    extern "int sqlite3_busy_timeout(db,int)"

    extern "int sqlite3_set_authorizer(db,void*,void*)"
    extern "void* sqlite3_trace(db,void*,void*)"

    extern "int sqlite3_bind_blob(stmt,int,const void*,int,void*)"
    extern "int sqlite3_bind_double(stmt,int,double)"
    extern "int sqlite3_bind_int(stmt,int,int)"
    extern "int sqlite3_bind_int64(stmt,int,int64)"
    extern "int sqlite3_bind_null(stmt,int)"
    extern "int sqlite3_bind_text(stmt,int,const char*,int,void*)"
    extern "int sqlite3_bind_text16(stmt,int,const void*,int,void*)"
    #extern "int sqlite3_bind_value(stmt,int,value)"

    extern "int sqlite3_bind_parameter_count(stmt)"
    extern "const char* sqlite3_bind_parameter_name(stmt,int)"
    extern "int sqlite3_bind_parameter_index(stmt,const char*)"

    extern "int sqlite3_column_count(stmt)"
    extern "int sqlite3_data_count(stmt)"

    extern "const void *sqlite3_column_blob(stmt,int)"
    extern "int sqlite3_column_bytes(stmt,int)"
    extern "int sqlite3_column_bytes16(stmt,int)"
    extern "const char *sqlite3_column_decltype(stmt,int)"
    extern "void *sqlite3_column_decltype16(stmt,int)"
    extern "double sqlite3_column_double(stmt,int)"
    extern "int sqlite3_column_int(stmt,int)"
    extern "int64 sqlite3_column_int64(stmt,int)"
    extern "const char *sqlite3_column_name(stmt,int)"
    extern "const void *sqlite3_column_name16(stmt,int)"
    extern "const char *sqlite3_column_text(stmt,int)"
    extern "const void *sqlite3_column_text16(stmt,int)"
    extern "int sqlite3_column_type(stmt,int)"

    extern "int sqlite3_create_function(db,const char*,int,int,void*,void*,void*,void*)"
    extern "int sqlite3_create_function16(db,const void*,int,int,void*,void*,void*,void*)"
    extern "int sqlite3_aggregate_count(context)"

    extern "const void *sqlite3_value_blob(value)"
    extern "int sqlite3_value_bytes(value)"
    extern "int sqlite3_value_bytes16(value)"
    extern "double sqlite3_value_double(value)"
    extern "int sqlite3_value_int(value)"
    extern "int64 sqlite3_value_int64(value)"
    extern "const char* sqlite3_value_text(value)"
    extern "const void* sqlite3_value_text16(value)"
    extern "const void* sqlite3_value_text16le(value)"
    extern "const void* sqlite3_value_text16be(value)"
    extern "int sqlite3_value_type(value)"

    extern "void *sqlite3_aggregate_context(context,int)"
    extern "void *sqlite3_user_data(context)"
    extern "void *sqlite3_get_auxdata(context,int)"
    extern "void sqlite3_set_auxdata(context,int,void*,void*)"

    extern "void sqlite3_result_blob(context,const void*,int,void*)"
    extern "void sqlite3_result_double(context,double)"
    extern "void sqlite3_result_error(context,const char*,int)"
    extern "void sqlite3_result_error16(context,const void*,int)"
    extern "void sqlite3_result_int(context,int)"
    extern "void sqlite3_result_int64(context,int64)"
    extern "void sqlite3_result_null(context)"
    extern "void sqlite3_result_text(context,const char*,int,void*)"
    extern "void sqlite3_result_text16(context,const void*,int,void*)"
    extern "void sqlite3_result_text16le(context,const void*,int,void*)"
    extern "void sqlite3_result_text16be(context,const void*,int,void*)"
    extern "void sqlite3_result_value(context,value)"

    extern "int sqlite3_create_collation(db,const char*,int,void*,void*)"
    extern "int sqlite3_create_collation16(db,const char*,int,void*,void*)"
    extern "int sqlite3_collation_needed(db,void*,void*)"
    extern "int sqlite3_collation_needed16(db,void*,void*)"

    # ==== CRYPTO (NOT IN PUBLIC RELEASE) ====
    if defined?( CRYPTO_API ) && CRYPTO_API
      extern "int sqlite3_key(db,void*,int)"
      extern "int sqlite3_rekey(db,void*,int)"
    end

    # ==== EXPERIMENTAL ====
    if defined?( EXPERIMENTAL_API ) && EXPERIMENTAL_API
      extern "int sqlite3_progress_handler(db,int,void*,void*)"
      extern "int sqlite3_commit_hook(db,void*,void*)"
    end

  end

end ; end ; end

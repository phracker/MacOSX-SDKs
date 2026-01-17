require 'mkmf'

SWIG_WRAP = "sqlite3_api_wrap.c"

dir_config( "sqlite3", "/usr/local" )

have_library( "rt", "fdatasync" )

if have_header( "sqlite3.h" ) && have_library( "sqlite3", "sqlite3_open" )
  if !File.exists?( SWIG_WRAP ) || with_config( "swig", false )
    puts "creating #{SWIG_WRAP}"
    system "swig -ruby sqlite3_api.i" or raise "could not build wrapper via swig (perhaps swig is not installed?)"
  end

  create_makefile( "sqlite3_api" )
end

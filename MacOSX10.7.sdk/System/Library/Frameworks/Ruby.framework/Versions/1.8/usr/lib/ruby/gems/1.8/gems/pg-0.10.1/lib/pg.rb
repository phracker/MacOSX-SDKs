#!/usr/bin/env ruby

begin
	require 'pg_ext'
rescue LoadError => err
	# If it's a Windows binary gem, try the <major>.<minor> subdirectory
	if RUBY_PLATFORM =~/(mswin|mingw)/i
		major_minor = RUBY_VERSION[ /^(\d+\.\d+)/ ] or
			raise "Oops, can't extract the major/minor version from #{RUBY_VERSION.dump}"
		require "#{major_minor}/pg_ext"
	else
		raise
	end

end


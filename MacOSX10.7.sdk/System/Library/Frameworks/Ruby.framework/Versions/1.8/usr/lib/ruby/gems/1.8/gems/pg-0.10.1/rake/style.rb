# 
# Style Fixup Rake Tasks

# 
# Authors:
# * Michael Granger <ged@FaerieMUD.org>
# 


### Coding style checks and fixes
namespace :style do
	
	BLANK_LINE = /^\s*$/
	GOOD_INDENT = /^(\t\s*)?\S/

	# A list of the files that have legitimate leading whitespace, etc.
	PROBLEM_FILES = [ SPECDIR + 'config_spec.rb' ]
	
	desc "Check source files for inconsistent indent and fix them"
	task :fix_indent do
		files = LIB_FILES + SPEC_FILES

		badfiles = Hash.new {|h,k| h[k] = [] }
		
		trace "Checking files for indentation"
		files.each do |file|
			if PROBLEM_FILES.include?( file )
				trace "  skipping problem file #{file}..."
				next
			end
			
			trace "  #{file}"
			linecount = 0
			file.each_line do |line|
				linecount += 1
				
				# Skip blank lines
				next if line =~ BLANK_LINE
				
				# If there's a line with incorrect indent, note it and skip to the 
				# next file
				if line !~ GOOD_INDENT
					trace "    Bad line %d: %p" % [ linecount, line ]
					badfiles[file] << [ linecount, line ]
				end
			end
		end

		if badfiles.empty?
			log "No indentation problems found."
		else
			log "Found incorrect indent in #{badfiles.length} files:\n  "
			badfiles.each do |file, badlines|
				log "  #{file}:\n" +
					"    " + badlines.collect {|badline| "%5d: %p" % badline }.join( "\n    " )
			end
		end
	end

end



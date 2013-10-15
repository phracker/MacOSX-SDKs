# 
# Documentation Rake tasks
# 

require 'rake/clean'


# Append docs/lib to the load path if it exists for documentation
# helpers.
DOCSLIB = DOCSDIR + 'lib'
$LOAD_PATH.unshift( DOCSLIB.to_s ) if DOCSLIB.exist?

# Make relative string paths of all the stuff we need to generate docs for
DOCFILES = Rake::FileList[ LIB_FILES + EXT_FILES + GEMSPEC.extra_rdoc_files ]

# Documentation coverage constants
COVERAGE_DIR    = BASEDIR + 'coverage'
COVERAGE_REPORT = COVERAGE_DIR + 'documentation.txt'


# Prefer YARD, fallback to RDoc
begin
	require 'yard'
	require 'yard/rake/yardoc_task'

	# Undo the lazy-assed monkeypatch yard/globals.rb installs and
	# re-install them as mixins as they should have been from the
	# start
	# <metamonkeypatch>
	class Object
		remove_method :log
		remove_method :P
	end

	module YardGlobals
		def P(namespace, name = nil)
			namespace, name = nil, namespace if name.nil?
			YARD::Registry.resolve(namespace, name, false, true)
		end

		def log
			YARD::Logger.instance
		end
	end

	class YARD::CLI::Base; include YardGlobals; end
	class YARD::CLI::Command; include YardGlobals; end
	class YARD::Parser::SourceParser; extend YardGlobals; include YardGlobals; end
	class YARD::Parser::CParser; include YardGlobals; end
	class YARD::CodeObjects::Base; include YardGlobals; end
	class YARD::Handlers::Base; include YardGlobals; end
	class YARD::Handlers::Processor; include YardGlobals; end
	class YARD::Serializers::Base; include YardGlobals; end
	class YARD::RegistryStore; include YardGlobals; end
	class YARD::Docstring; include YardGlobals; end
	module YARD::Templates::Helpers::ModuleHelper; include YardGlobals; end
	module YARD::Templates::Helpers::HtmlHelper; include YardGlobals; end

	if vvec(RUBY_VERSION) >= vvec("1.9.1")
		# Monkeypatched to allow more than two '#' characters at the beginning
		# of the comment line.
		# Patched from yard-0.5.8
		require 'yard/parser/ruby/ruby_parser'
		class YARD::Parser::Ruby::RipperParser < Ripper
			def on_comment(comment)
				visit_ns_token(:comment, comment)
				case comment
				when /\A# @group\s+(.+)\s*\Z/
					@groups.unshift [lineno, $1]
					return
				when /\A# @endgroup\s*\Z/
					@groups.unshift [lineno, nil]
					return
				end

				comment = comment.gsub(/^\#+\s{0,1}/, '').chomp
				append_comment = @comments[lineno - 1]

				if append_comment && @comments_last_column == column
					@comments.delete(lineno - 1)
					comment = append_comment + "\n" + comment
				end

				@comments[lineno] = comment
				@comments_last_column = column
			end
		end # class YARD::Parser::Ruby::RipperParser
	end

	# </metamonkeypatch>

	YARD_OPTIONS = [] unless defined?( YARD_OPTIONS )

	yardoctask = YARD::Rake::YardocTask.new( :apidocs ) do |task|
		task.files   = DOCFILES
		task.options = YARD_OPTIONS
		task.options << '--debug' << '--verbose' if $trace
	end
	yardoctask.before = lambda {
		trace "Calling yardoc like:",
			"  yardoc %s" % [ quotelist(yardoctask.options + yardoctask.files).join(' ') ]
	}

	YARDOC_CACHE = BASEDIR + '.yardoc'
	CLOBBER.include( YARDOC_CACHE.to_s )

rescue LoadError
	require 'rdoc/task'

	desc "Build API documentation in #{API_DOCSDIR}"
	RDoc::Task.new( :apidocs ) do |task|
		task.main     = "README"
		task.rdoc_files.include( DOCFILES )
		task.rdoc_dir = API_DOCSDIR.to_s
		task.options  = RDOC_OPTIONS
	end
end

# Need the DOCFILES to exist to build the API docs
task :apidocs => DOCFILES

CLEAN.include( API_DOCSDIR.to_s )


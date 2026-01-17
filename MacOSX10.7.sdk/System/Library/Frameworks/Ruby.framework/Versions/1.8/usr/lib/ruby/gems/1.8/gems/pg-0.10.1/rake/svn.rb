# 
# Subversion Rake Tasks

# 
# Authors:
# * Michael Granger <ged@FaerieMUD.org>
# 

require 'pp'
require 'yaml'
require 'date'
require 'time'
require 'abbrev'

unless defined?( SVN_DOTDIR )

	# Subversion constants -- directory names for releases and tags
	SVN_TRUNK_DIR    = 'trunk'
	SVN_RELEASES_DIR = 'releases'
	SVN_BRANCHES_DIR = 'branches'
	SVN_TAGS_DIR     = 'tags'

	SVN_DOTDIR       = BASEDIR + '.svn'
	SVN_ENTRIES      = SVN_DOTDIR + 'entries'

	# Ignore .svn directories in the various FileLists used by the main Rakefile
	[
		BIN_FILES,
		LIB_FILES,
		EXT_FILES,
		DATA_FILES,
		SPEC_FILES,
		TEST_FILES,
		EXTRA_PKGFILES,
	].each {|filelist| filelist.exclude(/\.svn/) }

	# Strftime format for tags/releases
	TAG_TIMESTAMP_FORMAT = '%Y%m%d-%H%M%S'
	TAG_TIMESTAMP_PATTERN = /\d{4}\d{2}\d{2}-\d{6}/

	RELEASE_VERSION_PATTERN = /\d+\.\d+\.\d+/

	DEFAULT_KEYWORDS = %w[Date Rev Author URL Id]
	KEYWORDED_FILEDIRS = %w[applets spec bin etc ext experiments examples lib misc docs]
	KEYWORDED_FILEPATTERN = /
		^(?:
			(?:meta)?rakefile.*									# Rakefiles
			|
			.*\.(?:rb|c|h|js|html|css|template|erb|page)		# Source file extensions
			|
			readme|install|todo
		)$/ix



	###
	### Subversion-specific Helpers
	###
	module SubversionHelpers

		###############
		module_function
		###############

		### Return a new tag for the given time
		def make_new_tag( time=Time.now )
			return time.strftime( TAG_TIMESTAMP_FORMAT )
		end


		### Get the subversion information for the current working directory as
		### a hash.
		def get_svn_info( dir='.' )
			return {} unless File.directory?( File.join(dir, '.svn') )
			info = IO.read( '|-' ) or exec 'svn', 'info', dir.to_s
			return YAML.load( info ) # 'svn info' outputs valid YAML! Yay!
		rescue NotImplementedError
			trace "No fork(), proceeding without svn info..."
			return {}
		end


		### Get a list of the objects registered with subversion under the specified directory and
		### return them as an Array of Pathame objects.
		def get_svn_filelist( dir='.' )
			list = IO.read( '|-' ) or exec 'svn', 'st', '-v', '--ignore-externals', dir

			# Split into lines, filter out the unknowns, and grab the filenames as Pathnames
			# :FIXME: This will break if we ever put in a file with spaces in its name. This
			# will likely be the least of our worries if we do so, however, so it's not worth
			# the additional complexity to make it handle that case. If we do need that, there's
			# always the --xml output for 'svn st'...
			return list.split( $/ ).
				reject {|line| line =~ /^(\?|(\s*|--- .*)$)/ }.
				collect {|fn| Pathname(fn[/\S+$/]) }
		end

		### Return the URL to the repository root for the specified +dir+.
		def get_svn_repo_root( dir='.' )
			info = get_svn_info( dir )
			return info['Repository Root']
		end


		### Return the Subversion URL to the given +dir+.
		def get_svn_url( dir='.' )
			info = get_svn_info( dir )
			return info['URL']
		end


		### Return the path of the specified +dir+ under the svn root of the 
		### checkout.
		def get_svn_path( dir='.' )
			root = get_svn_repo_root( dir )
			url = get_svn_url( dir )

			return url.sub( root + '/', '' )
		end


		### Return the keywords for the specified array of +files+ as a Hash keyed by filename.
		def get_svn_keyword_map( *files )
			files.flatten!
			files.push( '.' ) if files.empty?

			cmd = ['svn', 'pg', 'svn:keywords', *files]

			# trace "Executing: svn pg svn:keywords " + files.join(' ')
			output = IO.read( '|-' ) or exec( 'svn', 'pg', 'svn:keywords', *files )

			kwmap = {}
			output.split( "\n" ).each do |line|
				next if line !~ /\s+-\s+/
				path, keywords = line.split( /\s+-\s+/, 2 )
				kwmap[ path ] = keywords.split
			end

			return kwmap
		end


		### Return the latest revision number of the specified +dir+ as an Integer.
		def get_svn_rev( dir='.' )
			info = get_svn_info( dir )
			return info['Revision']
		end
		alias get_vcs_rev get_svn_rev


		### Return the latest revision number of the specified +dir+ as an Integer.
		def get_last_changed_rev( dir='.' )
			info = get_svn_info( dir )
			return info['Last Changed Rev']
		end


		### Return a list of the entries at the specified Subversion url. If
		### no +url+ is specified, it will default to the list in the URL
		### corresponding to the current working directory.
		def svn_ls( url=nil )
			url ||= get_svn_url()
			list = IO.read( '|-' ) or exec 'svn', 'ls', url

			trace 'svn ls of %s: %p' % [url, list] if $trace

			return [] if list.nil? || list.empty?
			return list.split( $INPUT_RECORD_SEPARATOR )
		end


		### Return the URL of the latest timestamp in the tags directory.
		def get_latest_svn_timestamp_tag
			rooturl = get_svn_repo_root()
			tagsurl = rooturl + "/#{SVN_TAGS_DIR}"

			tags = svn_ls( tagsurl ).grep( TAG_TIMESTAMP_PATTERN ).sort
			return nil if tags.nil? || tags.empty?
			return tagsurl + '/' + tags.last
		end


		### Get a subversion diff of the specified targets and return it. If no targets are
		### specified, the current directory will be diffed instead.
		def get_svn_diff( *targets )
			targets << BASEDIR if targets.empty?
			trace "Getting svn diff for targets: %p" % [targets]
			log = IO.read( '|-' ) or exec 'svn', 'diff', *(targets.flatten)

			return log
		end


		### Generate a commit log and invoke the user's editor on it.
		def edit_commit_log
			diff = make_commit_log()

			File.open( COMMIT_MSG_FILE, File::WRONLY|File::TRUNC|File::CREAT ) do |fh|
				fh.print( diff )
			end

			edit( COMMIT_MSG_FILE )
		end


		### Get a subversion status as an Array of tuples of the form:
		###   [ <status>, <path> ]
		def get_svn_status( *targets )
			targets << BASEDIR if targets.empty?
			trace "Getting svn status for targets: %p" % [targets]
			status = IO.read( '|-' ) or exec 'svn', 'st', '--ignore-externals', *(targets.flatten)
			entries = status.split( /\n/ ).
				select {|line| line !~ /^(\s*|--- .*)$/ }.
				collect do |line|
					flag, path = line.strip.split( /\s+/, 2 )
					[ flag, Pathname.new(path) ]
				end

			return entries
		end


		### Return the URL of the latest timestamp in the tags directory.
		def get_latest_release_tag
			rooturl    = get_svn_repo_root()
			releaseurl = rooturl + "/#{SVN_RELEASES_DIR}"

			tags = svn_ls( releaseurl ).grep( RELEASE_VERSION_PATTERN ).sort_by do |tag|
				tag[RELEASE_VERSION_PATTERN].split('.').collect {|i| Integer(i) }
			end
			return nil if tags.empty?

			return releaseurl + '/' + tags.last
		end


		### Return the names of all existing branches.
		def get_branch_names
			rooturl     = get_svn_repo_root()
			branchesurl = rooturl + "/#{SVN_BRANCHES_DIR}"

			return svn_ls( branchesurl )
		end


		### Extract a diff from the specified subversion working +dir+ and return it.
		def make_svn_commit_log( dir='.' )
			diff = IO.read( '|-' ) or exec 'svn', 'diff'
			fail "No differences." if diff.empty?

			return diff
		end


		### Extract the svn log from the specified subversion working +dir+, 
		### starting from rev +start+ and ending with rev +finish+, and return it.
		def make_svn_log( dir='.', start='PREV', finish='HEAD' )
			trace "svn log -r#{start}:#{finish} #{dir}"
			log = IO.read( '|-' ) or exec 'svn', 'log', "-r#{start}:#{finish}", dir
			fail "No log between #{start} and #{finish}." if log.empty?

			return log
		end


		### Extract the verbose XML svn log from the specified subversion working +dir+, 
		### starting from rev +start+ and ending with rev +finish+, and return it.
		def make_xml_svn_log( dir='.', start='PREV', finish='HEAD' )
			trace "svn log --xml --verbose -r#{start}:#{finish} #{dir}"
			log = IO.read( '|-' ) or exec 'svn', 'log', '--verbose', '--xml', "-r#{start}:#{finish}", dir
			fail "No log between #{start} and #{finish}." if log.empty?

			return log
		end


		### Create a changelog from the subversion log of the specified +dir+ and return it.
		def make_svn_changelog( dir='.' )
			require 'xml/libxml'

			changelog = ''
			path_prefix = '/' + get_svn_path( dir ) + '/'

			xmllog = make_xml_svn_log( dir, 0 )

			parser = XML::Parser.string( xmllog )
			root = parser.parse.root
			root.find( '//log/logentry' ).to_a.reverse.each do |entry|
				trace "Making a changelog entry for r%s" % [ entry['revision'] ]

				added   = []
				deleted = []
				changed = []

				entry.find( 'paths/path').each do |path|
					pathname = path.content
					pathname.sub!( path_prefix , '' ) if pathname.count('/') > 1

					case path['action']
					when 'A', 'R'
						if path['copyfrom-path']
							verb = path['action'] == 'A' ? 'renamed' : 'copied'
							added << "%s\n#{FILE_INDENT}-> #{verb} from %s@r%s" % [
								pathname,
								path['copyfrom-path'],
								path['copyfrom-rev'],
							]
						else
							added << "%s (new)" % [ pathname ]
						end

					when 'M'
						changed << pathname

					when 'D'
						deleted << pathname

					else
						log "Unknown action %p in rev %d" % [ path['action'], entry['revision'] ]
					end

				end

				date = Time.parse( entry.find_first('date').content )

				# cvs2svn doesn't set 'author'
				author = 'unknown'
				if entry.find_first( 'author' )
					author = entry.find_first( 'author' ).content
				end

				msg = entry.find_first( 'msg' ).content
				rev = entry['revision']

				changelog << "-- #{date.rfc2822} by #{author} (r#{rev}) -----\n"
				changelog << "   Added:   " << humanize_file_list(added)   << "\n" unless added.empty?
				changelog << "   Changed: " << humanize_file_list(changed) << "\n" unless changed.empty?
				changelog << "   Deleted: " << humanize_file_list(deleted) << "\n" unless deleted.empty?
				changelog << "\n"

				indent = msg[/^(\s*)/] + LOG_INDENT

				changelog << indent << msg.strip.gsub(/\n\s*/m, "\n#{indent}")
				changelog << "\n\n\n"
			end

			return changelog
		end


		### Returns a human-scannable file list by joining and truncating the list if it's too long.
		def humanize_file_list( list, indent=FILE_INDENT )
			listtext = list[0..5].join( "\n#{indent}" )
			if list.length > 5
				listtext << " (and %d other/s)" % [ list.length - 5 ]
			end

			return listtext
		end


		### Add the list of +pathnames+ to the svn:ignore list.
		def svn_ignore_files( *pathnames )
			pathnames.flatten!

			map = pathnames.inject({}) do |map,path|
				map[ path.dirname ] ||= []
				map[ path.dirname ] << path.basename
				map
			end

			trace "Ignoring %d files in %d directories." % [ pathnames.length, map.length ]

			map.each do |dir, files|
				trace "  %s: %p" % [ dir, files ]
				io = open( '|-' ) or exec 'svn', 'pg', 'svn:ignore', dir
				ignorelist = io.read.strip
				ignorelist << "\n" << files.join("\n")
				system 'svn', 'ps', 'svn:ignore', ignorelist, dir
			end
		end


		### Delete the files in the given +filelist+ after confirming with the user.
		def delete_extra_files( filelist )
			description = humanize_file_list( filelist, '  ' )
			log "Files to delete:\n ", description
			ask_for_confirmation( "Really delete them?", false ) do
				filelist.each do |f|
					rm_rf( f, :verbose => true )
				end
			end
		end

	end # module SubversionHelpers


	###
	### Tasks
	###

	desc "Subversion tasks"
	namespace :svn do
		include SubversionHelpers

		desc "Copy the HEAD revision of the current #{SVN_TRUNK_DIR}/ to #{SVN_TAGS_DIR}/ with a " +
			 "current timestamp."
		task :tag do
			svninfo   = get_svn_info()
			tag       = make_new_tag()
			svntrunk  = svninfo['Repository Root'] + "/#{SVN_TRUNK_DIR}"
			svntagdir = svninfo['Repository Root'] + "/#{SVN_TAGS_DIR}"
			svntag    = svntagdir + '/' + tag

			desc = "Tagging trunk as #{svntag}"
			ask_for_confirmation( desc ) do
				msg = prompt_with_default( "Commit log: ", "Tagging for code push" )
				run 'svn', 'cp', '-m', msg, svntrunk, svntag
			end
		end


		desc "Copy the HEAD revision of the current #{SVN_TRUNK_DIR}/ to #{SVN_BRANCHES_DIR} with a " +
		     "user-specified name."
		task :branch, [:name] do |task, args|
			branchname = args.name
			unless branchname
				branchname = prompt( "Branch name" ) or abort
			end

			svninfo      = get_svn_info()
			svntrunk     = Pathname.new( svninfo['Repository Root'] ) + SVN_TRUNK_DIR
			svnbranchdir = Pathname.new( svninfo['Repository Root'] ) + SVN_BRANCHES_DIR
			svnbranch    = svnbranchdir + branchname

			desc = "Making a new branch: #{svnbranch}"
			ask_for_confirmation( desc ) do
				msg = prompt_with_default( "Commit log: ", "Making a '#{args.name}' branch" )
				run 'svn', 'cp', '-m', msg, svntrunk, svnbranch
				ask_for_confirmation( "Switch to the new branch?", false ) do
					run 'svn', 'sw', svnbranch
				end
			end
		end


		desc "Switch the working copy to the named branch"
		task :switch, [:name] do |task, args|
			branches = get_branch_names().collect {|name| name.chomp('/') }

			unless args.name
				log "Branches are:\n" + branches.collect {|br| "  #{br}" }.join( "\n" )

				begin
					oldproc = Readline.completion_proc
					abbrev = branches.abbrev 
					Readline.completion_proc = lambda{|string| abbrev[string] }

					name = prompt( "Branch to switch to" ) or abort
					args.with_defaults( :name => name )
				ensure
					Readline.completion_proc = oldproc unless oldproc.nil?
				end
			end

			svninfo = get_svn_info()
			abort "Branch '#{args.name}' does not exist" unless branches.include?( args.name )
			branchuri = Pathname.new( svninfo['Repository Root'] ) + SVN_BRANCHES_DIR + args.name
			run 'svn', 'sw', branchuri
		end
		task :sw => :switch


		desc "Switch to the trunk if the working copy isn't there already."
		task :trunk do
			svninfo      = get_svn_info()
			svntrunk     = Pathname.new( svninfo['Repository Root'] ) + SVN_TRUNK_DIR

			if svninfo['URL'] != svntrunk.to_s
				log "Switching to #{svntrunk}"
				run 'svn', 'sw', svntrunk
			else
				log "You are already on trunk (#{svntrunk})"
			end
		end


		desc "Copy the most recent tag to #{SVN_RELEASES_DIR}/#{PKG_VERSION}"
		task :prep_release do
			last_tag    = get_latest_svn_timestamp_tag()
			svninfo     = get_svn_info()
			svnroot     = Pathname.new( svninfo['Repository Root'] )
			svntrunk    = svnroot + SVN_TRUNK_DIR
			svnrel      = svnroot + SVN_RELEASES_DIR
			release     = PKG_VERSION
			svnrelease  = svnrel + release

			unless svn_ls( svnrel.dirname ).include?( svnrel.basename.to_s + '/' )
				log "Releases path #{svnrel} does not exist."
				ask_for_confirmation( "To continue I'll need to create it." ) do
					run 'svn', 'mkdir', svnrel, '-m', 'Creating releases/ directory'
				end
			else
				trace "Found release dir #{svnrel}"
			end

			releases = svn_ls( svnrel ).collect {|name| name.sub(%r{/$}, '') }
			trace "Releases: %p" % [releases]
			if releases.include?( release )
				error "Version #{release} already has a branch (#{svnrelease}). Did you mean " +
					"to increment the version in #{VERSION_FILE}?"
				fail
			else
				trace "No #{release} version currently exists"
			end

			desc = "Tagging trunk as #{svnrelease}..."
			ask_for_confirmation( desc ) do
				msg = prompt_with_default( "Commit log: ", "Branching for release" )
				run 'svn', 'cp', '-m', msg, svntrunk, svnrelease
			end
		end

		### Task for debugging the #get_target_args helper
		task :show_targets do
			$stdout.puts "Targets from ARGV (%p): %p" % [ARGV, get_target_args()]
		end


		desc "Update from Subversion"
		task :update do
			run 'svn', 'up', '--ignore-externals'
		end


		desc "Add/ignore any files that are unknown in the working copy"
		task :newfiles do
			log "Checking for new files..."
			entries = get_svn_status()

			unless entries.empty?
				files_to_add = []
				files_to_ignore = []
				files_to_delete = []

				entries.find_all {|entry| entry[0] == '?'}.each do |entry|
					action = prompt_with_default( "  #{entry[1]}: (a)dd, (i)gnore, (s)kip (d)elete", 's' )
					case action
					when 'a'
						files_to_add << entry[1]
					when 'i'
						files_to_ignore << entry[1]
					when 'd'
						files_to_delete << entry[1]
					end
				end

				unless files_to_add.empty?
					run 'svn', 'add', *files_to_add
				end

				unless files_to_ignore.empty?
					svn_ignore_files( *files_to_ignore )
				end

				unless files_to_delete.empty?
					delete_extra_files( files_to_delete )
				end
			end
		end
		task :add => :newfiles


		desc "Check in all the changes in your current working copy"
		task :checkin => ['svn:update', 'svn:newfiles', 'test', 'svn:fix_keywords', COMMIT_MSG_FILE] do
			targets = get_target_args()
			$stderr.puts '---', File.read( COMMIT_MSG_FILE ), '---'
			ask_for_confirmation( "Continue with checkin?" ) do
				run 'svn', 'ci', '-F', COMMIT_MSG_FILE, targets
				rm_f COMMIT_MSG_FILE
			end
		end
		task :commit => :checkin
		task :ci => :checkin


		task :clean do
			rm_f COMMIT_MSG_FILE
		end


		desc "Check and fix any missing keywords for any files in the project which need them"
		task :fix_keywords do
			log "Checking subversion keywords..."
			paths = get_svn_filelist( BASEDIR ).
				select {|path| path.file? && path.to_s =~ KEYWORDED_FILEPATTERN }

			trace "Looking at %d paths for keywords:\n  %p" % [paths.length, paths]
			kwmap = get_svn_keyword_map( paths )

			buf = ''
			PP.pp( kwmap, buf, 132 )
			trace "keyword map is: %s" % [buf]

			files_needing_fixups = paths.find_all do |path|
				(kwmap[path.to_s] & DEFAULT_KEYWORDS) != DEFAULT_KEYWORDS
			end

			unless files_needing_fixups.empty?
				$stderr.puts "Files needing keyword fixes: ",
					files_needing_fixups.collect {|f|
						"  %s: %s" % [f, kwmap[f] ? kwmap[f].join(' ') : "(no keywords)"]
					}
				ask_for_confirmation( "Will add default keywords to these files." ) do
					run 'svn', 'ps', 'svn:keywords', DEFAULT_KEYWORDS.join(' '), *files_needing_fixups
				end
			else
				log "Keywords are all up to date."
			end
		end


		task :debug_helpers do
			methods = [
				:get_last_changed_rev,
				:get_latest_release_tag,
				:get_latest_svn_timestamp_tag,
				:get_svn_diff,
				:get_svn_filelist,
				:get_svn_info,
				:get_svn_keyword_map,
				:get_svn_path,
				:get_svn_repo_root,
				:get_svn_rev,
				:get_svn_status,
				:get_svn_url,
				:svn_ls,
			]
			maxlen = methods.collect {|sym| sym.to_s.length }.max

			methods.each do |meth|
				res = send( meth )
				puts "%*s => %p" % [ maxlen, colorize(meth.to_s, :cyan), res ]
			end
		end

	end

	if SVN_DOTDIR.exist?
		trace "Defining subversion VCS tasks"

		desc "Check in all the changes in your current working copy"
		task :ci => 'svn:ci'
		desc "Check in all the changes in your current working copy"
		task :checkin => 'svn:ci'

		desc "Tag a release"
		task :prep_release => 'svn:prep_release'

		file COMMIT_MSG_FILE do
			edit_commit_log()
		end
	else
		trace "Not defining subversion tasks: no #{SVN_DOTDIR}"
	end

end # unless defined?( SVN_DOTDIR )


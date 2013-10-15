# 
# Mercurial Rake Tasks

require 'enumerator'

# 
# Authors:
# * Michael Granger <ged@FaerieMUD.org>
# 

unless defined?( HG_DOTDIR )

	# Mercurial constants
	HG_DOTDIR = BASEDIR + '.hg'
	HG_STORE  = HG_DOTDIR + 'store'

	IGNORE_FILE = BASEDIR + '.hgignore'


	### 
	### Helpers
	### 

	module MercurialHelpers
		require './helpers.rb' unless defined?( RakefileHelpers )
		include RakefileHelpers

		###############
		module_function
		###############

		### Generate a commit log from a diff and return it as a String.
		def make_commit_log
			diff = read_command_output( 'hg', 'diff' )
			fail "No differences." if diff.empty?

			return diff
		end

		### Generate a commit log and invoke the user's editor on it.
		def edit_commit_log
			diff = make_commit_log()

			File.open( COMMIT_MSG_FILE, File::WRONLY|File::TRUNC|File::CREAT ) do |fh|
				fh.print( diff )
			end

			edit( COMMIT_MSG_FILE )
		end

		### Generate a changelog.
		def make_changelog
			log = read_command_output( 'hg', 'log', '--style', 'compact' )
			return log
		end

		### Get the 'tip' info and return it as a Hash
		def get_tip_info
			data = read_command_output( 'hg', 'tip' )
			return YAML.load( data )
		end

		### Return the ID for the current rev
		def get_current_rev
			id = read_command_output( 'hg', '-q', 'identify' )
			return id.chomp
		end

		### Read the list of existing tags and return them as an Array
		def get_tags
			taglist = read_command_output( 'hg', 'tags' )
			return taglist.split( /\n/ )
		end


		### Read any remote repo paths known by the current repo and return them as a hash.
		def get_repo_paths
			paths = {}
			pathspec = read_command_output( 'hg', 'paths' )
			pathspec.split.each_slice( 3 ) do |name, _, url|
				paths[ name ] = url
			end
			return paths
		end

		### Return the list of files which are not of status 'clean'
		def get_uncommitted_files
			list = read_command_output( 'hg', 'status', '-n', '--color', 'never' )
			list = list.split( /\n/ )

			trace "Changed files: %p" % [ list ]
			return list
		end

		### Return the list of files which are of status 'unknown'
		def get_unknown_files
			list = read_command_output( 'hg', 'status', '-un', '--color', 'never' )
			list = list.split( /\n/ )

			trace "New files: %p" % [ list ]
			return list
		end

		### Returns a human-scannable file list by joining and truncating the list if it's too long.
		def humanize_file_list( list, indent=FILE_INDENT )
			listtext = list[0..5].join( "\n#{indent}" )
			if list.length > 5
				listtext << " (and %d other/s)" % [ list.length - 5 ]
			end

			return listtext
		end


		### Add the list of +pathnames+ to the .hgignore list.
		def hg_ignore_files( *pathnames )
			patterns = pathnames.flatten.collect do |path|
				'^' + Regexp.escape(path) + '$'
			end
			trace "Ignoring %d files." % [ pathnames.length ]

			IGNORE_FILE.open( File::CREAT|File::WRONLY|File::APPEND, 0644 ) do |fh|
				fh.puts( patterns )
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

	end # module MercurialHelpers


	### Rakefile support
	def get_vcs_rev( dir='.' )
		return MercurialHelpers.get_current_rev
	end
	def make_changelog
		return MercurialHelpers.make_changelog
	end


	###
	### Tasks
	###

	desc "Mercurial tasks"
	namespace :hg do
		include MercurialHelpers

		desc "Prepare for a new release"
		task :prep_release do
			uncommitted_files = get_uncommitted_files()
			unless uncommitted_files.empty?
				log "Uncommitted files:\n",
				    *uncommitted_files.map {|fn| "  #{fn}\n" }
				ask_for_confirmation( "\nRelease anyway?", true ) do
					log "Okay, releasing with uncommitted versions."
				end
			end

			tags = get_tags()
			rev = get_current_rev()
			pkg_version_tag = "v#{PKG_VERSION}"

			# Look for a tag for the current release version, and if it exists abort
			if tags.include?( pkg_version_tag )
				error "Version #{PKG_VERSION} already has a tag. Did you mean " +
					"to increment the version in #{VERSION_FILE}?"
				fail
			end

			# Sign the current rev
			log "Signing rev #{rev}"
			run 'hg', 'sign'

			# Tag the current rev
			log "Tagging rev #{rev} as #{pkg_version_tag}"
			run 'hg', 'tag', pkg_version_tag

			# Offer to push
			Rake::Task['hg:push'].invoke
		end

		desc "Check for new files and offer to add/ignore/delete them."
		task :newfiles do
			log "Checking for new files..."

			entries = get_unknown_files()

			unless entries.empty?
				files_to_add = []
				files_to_ignore = []
				files_to_delete = []

				entries.each do |entry|
					action = prompt_with_default( "  #{entry}: (a)dd, (i)gnore, (s)kip (d)elete", 's' )
					case action
					when 'a'
						files_to_add << entry
					when 'i'
						files_to_ignore << entry
					when 'd'
						files_to_delete << entry
					end
				end

				unless files_to_add.empty?
					run 'hg', 'add', *files_to_add
				end

				unless files_to_ignore.empty?
					hg_ignore_files( *files_to_ignore )
				end

				unless files_to_delete.empty?
					delete_extra_files( files_to_delete )
				end
			end
		end
		task :add => :newfiles


		desc "Pull and update from the default repo"
		task :pull do
			paths = get_repo_paths()
			if origin_url = paths['default']
				ask_for_confirmation( "Pull and update from '#{origin_url}'?", false ) do
					Rake::Task['hg:pull_without_confirmation'].invoke
				end
			else
				trace "Skipping pull: No 'default' path."
			end
		end


		desc "Pull and update without confirmation"
		task :pull_without_confirmation do
			run 'hg', 'pull', '-u'
		end


		desc "Update to tip"
		task :update do
			run 'hg', 'update'
		end


		desc "Clobber all changes (hg up -C)"
		task :update_and_clobber do
			run 'hg', 'update', '-C'
		end


		desc "Check the current code in if tests pass"
		task :checkin => ['hg:pull', 'hg:newfiles', 'test', COMMIT_MSG_FILE] do
			targets = get_target_args()
			$stderr.puts '---', File.read( COMMIT_MSG_FILE ), '---'
			ask_for_confirmation( "Continue with checkin?" ) do
				run 'hg', 'ci', '-l', COMMIT_MSG_FILE, targets
				rm_f COMMIT_MSG_FILE
			end
			Rake::Task['hg:push'].invoke
		end
		task :commit => :checkin
		task :ci => :checkin

		CLEAN.include( COMMIT_MSG_FILE )

		desc "Push to the default origin repo (if there is one)"
		task :push do
			paths = get_repo_paths()
			if origin_url = paths['default']
				ask_for_confirmation( "Push to '#{origin_url}'?", false ) do
					Rake::Task['hg:push_without_confirmation'].invoke
				end
			else
				trace "Skipping push: No 'default' path."
			end
		end

		desc "Push to the default repo without confirmation"
		task :push_without_confirmation do
			run 'hg', 'push'
		end

	end

	if HG_DOTDIR.exist?
		trace "Defining mercurial VCS tasks"

		desc "Check in all the changes in your current working copy"
		task :ci => 'hg:ci'
		desc "Check in all the changes in your current working copy"
		task :checkin => 'hg:ci'

		desc "Tag and sign revision before a release"
		task :prep_release => 'hg:prep_release'

		file COMMIT_MSG_FILE do
			edit_commit_log()
		end

	else
		trace "Not defining mercurial tasks: no #{HG_DOTDIR}"
	end

end



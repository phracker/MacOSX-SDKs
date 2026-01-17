# 
# Manual-generation Rake tasks and classes

# 
# Authors:
# * Michael Granger <ged@FaerieMUD.org>
# * Mahlon E. Smith <mahlon@martini.nu>
# 
# This was born out of a frustration with other static HTML generation modules
# and systems. I've tried webby, webgen, rote, staticweb, staticmatic, and
# nanoc, but I didn't find any of them really suitable (except rote, which was
# excellent but apparently isn't maintained and has a fundamental
# incompatibilty with Rake because of some questionable monkeypatching.)
# 
# So, since nothing seemed to scratch my itch, I'm going to scratch it myself.
# 

require 'pathname'
require 'singleton'
require 'rake/tasklib'
require 'erb'


### Namespace for Manual-generation classes
module Manual

	### Manual page-generation class
	class Page

		### An abstract filter class for manual content transformation.
		class Filter
			include Singleton

			# A list of inheriting classes, keyed by normalized name
			@derivatives = {}
			class << self; attr_reader :derivatives; end

			### Inheritance callback -- keep track of all inheriting classes for
			### later.
			def self::inherited( subclass )
				key = subclass.name.
					sub( /^.*::/, '' ).
					gsub( /[^[:alpha:]]+/, '_' ).
					downcase.
					sub( /filter$/, '' )

				self.derivatives[ key ] = subclass
				self.derivatives[ key.to_sym ] = subclass

				super
			end


			### Export any static resources required by this filter to the given +output_dir+.
			def export_resources( output_dir )
				# No-op by default
			end


			### Process the +page+'s source with the filter and return the altered content.
			def process( source, page, metadata )
				raise NotImplementedError,
					"%s does not implement the #process method" % [ self.class.name ]
			end
		end # class Filter


		### The default page configuration if none is specified.
		DEFAULT_CONFIG = {
			'filters' => [ 'erb', 'links', 'textile' ],
			'layout'  => 'default.page',
			'cleanup' => false,
		  }.freeze

		# Pattern to match a source page with a YAML header
		PAGE_WITH_YAML_HEADER = /
			\A---\s*$	# It should should start with three hyphens
			(.*?)		# ...have some YAML stuff
			^---\s*$	# then have another three-hyphen line,
			(.*)\Z		# then the rest of the document
		  /xm

		# Options to pass to libtidy
		TIDY_OPTIONS = {
			:show_warnings     => true,
			:indent            => true,
			:indent_attributes => false,
			:indent_spaces     => 4,
			:vertical_space    => true,
			:tab_size          => 4,
			:wrap_attributes   => true,
			:wrap              => 100,
			:char_encoding     => 'utf8'
		  }


		### Create a new page-generator for the given +sourcefile+, which will use
		### ones of the templates in +layouts_dir+ as a wrapper. The +basepath+ 
		### is the path to the base output directory, and the +catalog+ is the
		### Manual::PageCatalog to which the page belongs.
		def initialize( catalog, sourcefile, layouts_dir, basepath='.' )
			@catalog     = catalog
			@sourcefile  = Pathname.new( sourcefile )
			@layouts_dir = Pathname.new( layouts_dir )
			@basepath    = basepath

			rawsource = @sourcefile.read
			@config, @source = self.read_page_config( rawsource )

			# $stderr.puts "Config is: %p" % [@config],
			# 	"Source is: %p" % [ @source[0,100] ]
			@filters = self.load_filters( @config['filters'] )

			super()
		end


		######
		public
		######

		# The Manual::PageCatalog to which the page belongs
		attr_reader :catalog

		# The relative path to the base directory, for prepending to page paths
		attr_reader :basepath

		# The Pathname object that specifys the page source file
		attr_reader :sourcefile

		# The configured layouts directory as a Pathname object.
		attr_reader :layouts_dir

		# The page configuration, as read from its YAML header
		attr_reader :config

		# The raw source of the page
		attr_reader :source

		# The filters the page will use to render itself
		attr_reader :filters


		### Generate HTML output from the page and return it.
		def generate( metadata )
			content = self.generate_content( @source, metadata )

			layout = self.config['layout'].sub( /\.page$/, '' )
			templatepath = @layouts_dir + "#{layout}.page"
			template = nil
			if Object.const_defined?( :Encoding )
				template = ERB.new( templatepath.read(:encoding => 'UTF-8') )
			else
				template = ERB.new( templatepath.read )
			end

			page = self
			html = template.result( binding() )

			# Use Tidy to clean up the html if 'cleanup' is turned on, but remove the Tidy
			# meta-generator propaganda/advertising.
			html = self.cleanup( html ).sub( %r:<meta name="generator"[^>]*tidy[^>]*/>:im, '' ) if
				self.config['cleanup']

			return html
		end


		### Return the page title as specified in the YAML options
		def title
			return self.config['title'] || self.sourcefile.basename
		end


		### Run the various filters on the given input and return the transformed
		### content.
		def generate_content( input, metadata )
			return @filters.inject( input ) do |source, filter|
				filter.process( source, self, metadata )
			end
		end


		### Trim the YAML header from the provided page +source+, convert it to
		### a Ruby object, and return it.
		def read_page_config( source )
			unless source =~ PAGE_WITH_YAML_HEADER
				return DEFAULT_CONFIG.dup, source
			end

			pageconfig = YAML.load( $1 )
			source = $2

			return DEFAULT_CONFIG.merge( pageconfig ), source
		end


		### Clean up and return the given HTML +source+.
		def cleanup( source )
			require 'tidy'

			Tidy.path = '/usr/lib/libtidy.dylib'
			Tidy.open( TIDY_OPTIONS ) do |tidy|
				tidy.options.output_xhtml = true

				xml = tidy.clean( source )
				errors = tidy.errors
				error_message( errors.join ) unless errors.empty?
				trace tidy.diagnostics
				return xml
			end
		rescue LoadError => err
			trace "No cleanup: " + err.message
			return source
		end


		### Get (singleton) instances of the filters named in +filterlist+ and return them.
		def load_filters( filterlist )
			filterlist.flatten.collect do |key|
				raise ArgumentError, "filter '#{key}' is not loaded" unless
					Manual::Page::Filter.derivatives.key?( key )
				Manual::Page::Filter.derivatives[ key ].instance
			end
		end


		### Build the index relative to the receiving page and return it as a String
		def make_index_html
			items = [ '<div class="index">' ]

			@catalog.traverse_page_hierarchy( self ) do |type, title, path|
				case type
				when :section
					items << %Q{<div class="section">}
					items << %Q{<h2><a href="#{self.basepath + path}/">#{title}</a></h2>}
					items << '<ul class="index-section">'

				when :current_section
					items << %Q{<div class="section current-section">}
					items << %Q{<h2><a href="#{self.basepath + path}/">#{title}</a></h2>}
					items << '<ul class="index-section current-index-section">'

				when :section_end, :current_section_end
					items << '</ul></div>'

				when :entry
					items << %Q{<li><a href="#{self.basepath + path}.html">#{title}</a></li>}

				when :current_entry
					items << %Q{<li class="current-entry">#{title}</li>}

				else
					raise "Unknown index entry type %p" % [ type ]
				end

			end

			items << '</div>'

			return items.join("\n")
		end

	end


	### A catalog of Manual::Page objects that can be referenced by various criteria.
	class PageCatalog

		### Create a new PageCatalog that will load Manual::Page objects for .page files 
		### in the specified +sourcedir+.
		def initialize( sourcedir, layoutsdir )			
			@sourcedir = sourcedir
			@layoutsdir = layoutsdir

			@pages       = []
			@path_index  = {}
			@uri_index   = {}
			@title_index = {}
			@hierarchy   = {}

			self.find_and_load_pages
		end


		######
		public
		######

		# An index of the pages in the catalog by Pathname
		attr_reader :path_index

		# An index of the pages in the catalog by title
		attr_reader :title_index

		# An index of the pages in the catalog by the URI of their source relative to the source 
		# directory
		attr_reader :uri_index

		# The hierarchy of pages in the catalog, suitable for generating an on-page index
		attr_reader :hierarchy

		# An Array of all Manual::Page objects found
		attr_reader :pages

		# The Pathname location of the .page files.
		attr_reader :sourcedir

		# The Pathname location of look and feel templates.
		attr_reader :layoutsdir


		### Traverse the catalog's #hierarchy, yielding to the given +builder+
		### block for each entry, as well as each time a sub-hash is entered or
		### exited, setting the +type+ appropriately. Valid values for +type+ are:
		###	 
		###		:entry, :section, :section_end
		###
		### If the optional +from+ value is given, it should be the Manual::Page object
		### which is considered "current"; if the +from+ object is the same as the 
		### hierarchy entry being yielded, it will be yielded with the +type+ set to 
		### one of:
		### 
		###     :current_entry, :current_section, :current_section_end
		###
		### each of which correspond to the like-named type from above.
		def traverse_page_hierarchy( from=nil, &builder ) # :yields: type, title, path
			raise LocalJumpError, "no block given" unless builder
			self.traverse_hierarchy( Pathname.new(''), self.hierarchy, from, &builder )
		end


		#########
		protected
		#########

		### Sort and traverse the specified +hash+ recursively, yielding for each entry.
		def traverse_hierarchy( path, hash, from=nil, &builder )
			# Now generate the index in the sorted order
			sort_hierarchy( hash ).each do |subpath, page_or_section|
				if page_or_section.is_a?( Hash )
					self.handle_section_callback( path + subpath, page_or_section, from, &builder )
				else
					next if subpath == INDEX_PATH
					self.handle_page_callback( path + subpath, page_or_section, from, &builder )
				end
			end
		end


		### Return the specified hierarchy of pages as a sorted Array of tuples. 
		### Sort the hierarchy using the 'index' config value of either the
		### page, or the directory's index page if it's a directory.
		def sort_hierarchy( hierarchy )
			hierarchy.sort_by do |subpath, page_or_section|

				# Directory
				if page_or_section.is_a?( Hash )

					# Use the index of the index page if it exists
					if page_or_section[INDEX_PATH]
						idx = page_or_section[INDEX_PATH].config['index']
						trace "Index page's index for directory '%s' is: %p" % [ subpath, idx ]
						idx.to_s || subpath.to_s
					else
						trace "Using the path for the sort of directory %p" % [ subpath ]
						subpath.to_s
					end

				# Page
				else
					if subpath == INDEX_PATH
						trace "Sort index for index page %p is 0" % [ subpath ]
						'0'
					else
						idx = page_or_section.config['index']
						trace "Sort index for page %p is: %p" % [ subpath, idx ]
						idx.to_s || subpath.to_s
					end
				end

			end # sort_by
		end


		INDEX_PATH = Pathname.new('index')

		### Build up the data structures necessary for calling the +builder+ callback
		### for an index section and call it, then recurse into the section contents.
		def handle_section_callback( path, section, from=nil, &builder )
			from_current = false
			trace "Section handler: path=%p, section keys=%p, from=%s" %
				[ path, section.keys, from.sourcefile ]

			# Call the callback with :section -- determine the section title from
			# the 'index.page' file underneath it, or the directory name if no 
			# index.page exists.
			if section.key?( INDEX_PATH )
				if section[INDEX_PATH].sourcefile.dirname == from.sourcefile.dirname
					from_current = true
					builder.call( :current_section, section[INDEX_PATH].title, path )
				else
					builder.call( :section, section[INDEX_PATH].title, path )
				end
			else
				title = File.dirname( path ).gsub( /_/, ' ' )
				builder.call( :section, title, path )
			end

			# Recurse
			self.traverse_hierarchy( path, section, from, &builder )

			# Call the callback with :section_end
			if from_current
				builder.call( :current_section_end, '', path )
			else
				builder.call( :section_end, '', path )
			end
		end


		### Yield the specified +page+ to the builder
		def handle_page_callback( path, page, from=nil )
			if from == page
				yield( :current_entry, page.title, path )
			else
				yield( :entry, page.title, path )
			end
		end


		### Find and store

		### Find all .page files under the configured +sourcedir+ and create a new
		### Manual::Page object for each one.
		def find_and_load_pages
			Pathname.glob( @sourcedir + '**/*.page' ).each do |pagefile|
				path_to_base = @sourcedir.relative_path_from( pagefile.dirname )

				page = Manual::Page.new( self, pagefile, @layoutsdir, path_to_base )
				hierpath = pagefile.relative_path_from( @sourcedir )

				@pages << page
				@path_index[ pagefile ]     = page
				@title_index[ page.title ]  = page
				@uri_index[ hierpath.to_s ] = page

				# Place the page in the page hierarchy by using inject to find and/or create the 
				# necessary subhashes. The last run of inject will return the leaf hash in which
				# the page will live
				section = hierpath.dirname.split[1..-1].inject( @hierarchy ) do |hier, component|
					hier[ component ] ||= {}
					hier[ component ]
				end

				section[ pagefile.basename('.page') ] = page
			end
		end

	end


	### A Textile filter for the manual generation tasklib, implemented using RedCloth.
	class TextileFilter < Manual::Page::Filter

		### Load RedCloth when the filter is first created
		def initialize( *args )
			require 'redcloth'
			super
		end


		### Process the given +source+ as Textile and return the resulting HTML
		### fragment.
		def process( source, *ignored )
			formatter = RedCloth::TextileDoc.new( source )
			formatter.hard_breaks = false
			formatter.no_span_caps = true
			return formatter.to_html
		end

	end


	### An ERB filter for the manual generation tasklib, implemented using Erubis.
	class ErbFilter < Manual::Page::Filter

		### Process the given +source+ as ERB and return the resulting HTML
		### fragment.
		def process( source, page, metadata )
			template_name = page.sourcefile.basename
			template = ERB.new( source )
			return template.result( binding() )
		end

	end


	### Manual generation task library
	class GenTask < Rake::TaskLib

		# Default values for task config variables
		DEFAULT_NAME         = :manual
		DEFAULT_BASE_DIR     = Pathname.new( 'docs/manual' )
		DEFAULT_SOURCE_DIR   = 'source'
		DEFAULT_LAYOUTS_DIR  = 'layouts'
		DEFAULT_OUTPUT_DIR   = 'output'
		DEFAULT_RESOURCE_DIR = 'resources'
		DEFAULT_LIB_DIR      = 'lib'
		DEFAULT_METADATA     = OpenStruct.new


		### Define a new manual-generation task with the given +name+.
		def initialize( name=:manual )
			@name           = name

			@source_dir		= DEFAULT_SOURCE_DIR
			@layouts_dir	= DEFAULT_LAYOUTS_DIR
			@output_dir		= DEFAULT_OUTPUT_DIR
			@resource_dir	= DEFAULT_RESOURCE_DIR
			@lib_dir	    = DEFAULT_LIB_DIR
			@metadata		= DEFAULT_METADATA

			yield( self ) if block_given?

			self.define
		end


		######
		public
		######

		attr_accessor :base_dir,
			:source_dir,
			:layouts_dir,
			:output_dir,
			:resource_dir,
			:lib_dir,
			:metadata

		attr_reader :name


		### Set up the tasks for building the manual
		def define

			# Set up a description if the caller hasn't already defined one
			unless Rake.application.last_comment
				desc "Generate the manual"
			end

			# Make Pathnames of the directories relative to the base_dir
			basedir     = Pathname.new( @base_dir )
			sourcedir   = basedir + @source_dir
			layoutsdir  = basedir + @layouts_dir
			outputdir   = @output_dir
			resourcedir = basedir + @resource_dir
			libdir      = basedir + @lib_dir

			load_filter_libraries( libdir )
			catalog = Manual::PageCatalog.new( sourcedir, layoutsdir )

			# Declare the tasks outside the namespace that point in
			task @name => "#@name:build"
			task "clobber_#@name" => "#@name:clobber"

			namespace( self.name ) do
				setup_resource_copy_tasks( resourcedir, outputdir )
				manual_pages = setup_page_conversion_tasks( sourcedir, outputdir, catalog )

				desc "Build the manual"
				task :build => [ :apidocs, :copy_resources, :copy_apidocs, :generate_pages ]

				task :clobber do
					RakeFileUtils.verbose( $verbose ) do
						rm_f manual_pages.to_a
					end
					remove_dir( outputdir ) if ( outputdir + '.buildtime' ).exist?
				end

				desc "Remove any previously-generated parts of the manual and rebuild it"
				task :rebuild => [ :clobber, self.name ]

				desc "Watch for changes to the source files and rebuild when they change"
				task :autobuild do
					scope = [ self.name ]
					loop do
						t = Rake.application.lookup( :build, scope )
						t.reenable
						t.prerequisites.each do |pt|
							if task = Rake.application.lookup( pt, scope )
								task.reenable
							else
								trace "Hmmm... no %p task in scope %p?" % [ pt, scope ]
							end
						end
						t.invoke
						sleep 2
						trace "  waking up..."
					end
				end
	        end

		end # def define


		### Load the filter libraries provided in the given +libdir+
		def load_filter_libraries( libdir )
			Pathname.glob( libdir + '*.rb' ) do |filterlib|
				trace "  loading filter library #{filterlib}"
				require( filterlib )
			end
		end


		### Set up the main HTML-generation task that will convert files in the given +sourcedir+ to
		### HTML in the +outputdir+
		def setup_page_conversion_tasks( sourcedir, outputdir, catalog )

			# we need to figure out what HTML pages need to be generated so we can set up the
			# dependency that causes the rule to be fired for each one when the task is invoked.
			manual_sources = FileList[ catalog.path_index.keys.map {|pn| pn.to_s} ]
			trace "   found %d source files" % [ manual_sources.length ]

			# Map .page files to their equivalent .html output
			html_pathmap = "%%{%s,%s}X.html" % [ sourcedir, outputdir ]
			manual_pages = manual_sources.pathmap( html_pathmap )
			trace "Mapping sources like so: \n  %p -> %p" %
				[ manual_sources.first, manual_pages.first ]

			# Output directory task
			directory( outputdir.to_s )
			file outputdir.to_s do
				touch outputdir + '.buildtime'
			end

			# Rule to generate .html files from .page files
			rule( 
				%r{#{outputdir}/.*\.html$} => [
					proc {|name| name.sub(/\.[^.]+$/, '.page').sub( outputdir, sourcedir) },
					outputdir.to_s
			 	]) do |task|

				source = Pathname.new( task.source )
				target = Pathname.new( task.name )
				log "  #{ source } -> #{ target }"

				page = catalog.path_index[ source ]
				#trace "  page object is: %p" % [ page ]

				target.dirname.mkpath
				target.open( File::WRONLY|File::CREAT|File::TRUNC ) do |io|
					io.write( page.generate(metadata) )
				end
			end

			# Group all the manual page output files targets into a containing task
			desc "Generate any pages of the manual that have changed"
			task :generate_pages => manual_pages
			return manual_pages
		end


		### Copy method for resources -- passed as a block to the various file tasks that copy
		### resources to the output directory.
		def copy_resource( task )
			source = task.prerequisites[ 1 ]
			target = task.name

			when_writing do
				trace "  #{source} -> #{target}"
				mkpath File.dirname( target ), :verbose => $trace unless
					File.directory?( File.dirname(target) )
				install source, target, :mode => 0644, :verbose => $trace
			end
		end


		### Set up a rule for copying files from the resources directory to the output dir.
		def setup_resource_copy_tasks( resourcedir, outputdir )
			resources = FileList[ resourcedir + '**/*.{js,css,png,gif,jpg,html,svg,svgz,swf}' ]
			resources.exclude( /\.svn/ )
			target_pathmap = "%%{%s,%s}p" % [ resourcedir, outputdir ]
			targets = resources.pathmap( target_pathmap )
			copier = self.method( :copy_resource ).to_proc

			# Create a file task to copy each file to the output directory
			resources.each_with_index do |resource, i|
				file( targets[i] => [ outputdir.to_s, resource ], &copier )
			end

			desc "Copy API documentation to the manual output directory"
			task :copy_apidocs => :apidocs do
				cp_r( API_DOCSDIR, outputdir )
			end

			# Now group all the resource file tasks into a containing task
			desc "Copy manual resources to the output directory"
			task :copy_resources => targets do
				log "Copying manual resources"
			end
		end

	end # class Manual::GenTask

end



### Task: manual generation
if MANUALDIR.exist?
	MANUALOUTPUTDIR = MANUALDIR + 'output'
	trace "Manual will be generated in: #{MANUALOUTPUTDIR}"

	begin
		directory MANUALOUTPUTDIR.to_s

		Manual::GenTask.new do |manual|
			manual.metadata.version = PKG_VERSION
			manual.metadata.api_dir = API_DOCSDIR
			manual.output_dir = MANUALOUTPUTDIR
			manual.base_dir = MANUALDIR
			manual.source_dir = 'src'
		end

		CLOBBER.include( MANUALOUTPUTDIR.to_s )

	rescue LoadError => err
		task :no_manual do
			$stderr.puts "Manual-generation tasks not defined: %s" % [ err.message ]
		end

		task :manual => :no_manual
		task :clobber_manual => :no_manual
	end

else
	TEMPLATEDIR = RAKE_TASKDIR + 'manualdir'

	if TEMPLATEDIR.exist?

		desc "Create a manual for this project from a template"
		task :manual do
			log "No manual directory (#{MANUALDIR}) currently exists."
			ask_for_confirmation( "Create a new manual directory tree from a template?" ) do
				MANUALDIR.mkpath

				%w[layouts lib output resources src].each do |dir|
					FileUtils.mkpath( MANUALDIR + dir, :mode => 0755, :verbose => true, :noop => $dryrun )
				end

				Pathname.glob( TEMPLATEDIR + '**/*.{rb,css,png,js,erb,page}' ).each do |tmplfile|
					trace "extname is: #{tmplfile.extname}"

					# Render ERB files
					if tmplfile.extname == '.erb'
						rname = tmplfile.basename( '.erb' )
						target = MANUALDIR + tmplfile.dirname.relative_path_from( TEMPLATEDIR ) + rname
						template = ERB.new( tmplfile.read, nil, '<>' )

						target.dirname.mkpath( :mode => 0755, :verbose => true, :noop => $dryrun ) unless
						 	target.dirname.directory?
						html = template.result( binding() )
						log "generating #{target}: html => #{html[0,20]}"

						target.open( File::WRONLY|File::CREAT|File::EXCL, 0644 ) do |fh|
							fh.print( html )
						end

					# Just copy anything else
					else
						target = MANUALDIR + tmplfile.relative_path_from( TEMPLATEDIR )
						FileUtils.mkpath target.dirname,
							:mode => 0755, :verbose => true, :noop => $dryrun unless target.dirname.directory?
						FileUtils.install tmplfile, target,
							:mode => 0644, :verbose => true, :noop => $dryrun
					end
				end
			end

		end # task :manual

	end
end



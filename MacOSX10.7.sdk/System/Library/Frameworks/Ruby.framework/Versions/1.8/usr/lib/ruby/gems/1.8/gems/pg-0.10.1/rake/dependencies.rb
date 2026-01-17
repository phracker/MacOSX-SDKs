# 
# Dependency-checking and Installation Rake Tasks

# 

require 'rubygems/dependency_installer'
require 'rubygems/source_index'
require 'rubygems/requirement'
require 'rubygems/doc_manager'

### Install the specified +gems+ if they aren't already installed.
def install_gems( gems )
	
	defaults = Gem::DependencyInstaller::DEFAULT_OPTIONS.merge({
		:generate_rdoc     => true,
		:generate_ri       => true,
		:install_dir       => Gem.dir,
		:format_executable => false,
		:test              => false,
		:version           => Gem::Requirement.default,
	  })
    
	# Check for root
	if Process.euid != 0
		$stderr.puts "This probably won't work, as you aren't root, but I'll try anyway"
	end

	gemindex = Gem::SourceIndex.from_installed_gems

	gems.each do |gemname, reqstring|
		requirement = Gem::Requirement.new( reqstring )
		trace "requirement is: %p" % [ requirement ]
		
		trace "Searching for an installed #{gemname}..."
		specs = gemindex.find_name( gemname )
		trace "...found %d specs: %s" %
			[ specs.length, specs.collect {|s| "%s %s" % [s.name, s.version] }.join(', ') ]
		
		if spec = specs.find {|spec| requirement.satisfied_by?(spec.version) }
			log "Version %s of %s is already installed (needs %s); skipping..." % 
				[ spec.version, spec.name, requirement ]
			next
		end

		rgv = Gem::Version.new( Gem::RubyGemsVersion )
		installer = nil
		
		log "Trying to install #{gemname.inspect} #{requirement}..."
		if rgv >= Gem::Version.new( '1.1.1' )
			installer = Gem::DependencyInstaller.new
			installer.install( gemname, requirement )
		else
			installer = Gem::DependencyInstaller.new( gemname )
			installer.install
		end

		installer.installed_gems.each do |spec|
			log "Installed: %s" % [ spec.full_name ]
		end

	end
end


### Task: install runtime dependencies
desc "Install runtime dependencies as gems"
task :install_dependencies do
	install_gems( DEPENDENCIES )
end

### Task: install gems for development tasks
desc "Install development dependencies as gems"
task :install_dev_dependencies do
	install_gems( DEVELOPMENT_DEPENDENCIES )
end


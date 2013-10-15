#####################################################################
###	P A C K A G I N G   T A S K S
#####################################################################

require 'rbconfig'
require 'pathname'
require 'rubygems/package_task'


include Config

### Task: prerelease
desc "Append the package build number to package versions"
task :prerelease do
	GEMSPEC.version.version << "pre#{PKG_BUILD}"
	Rake::Task[:gem].clear

	Gem::PackageTask.new( GEMSPEC ) do |pkg|
		pkg.need_zip = true
		pkg.need_tar = true
	end
end


### Task: gem
### Task: package
Rake::PackageTask.new( PKG_NAME, PKG_VERSION ) do |task|
  	task.need_tar_gz   = true
	task.need_tar_bz2  = true
	task.need_zip      = true
	task.package_dir   = PKGDIR.to_s
  	task.package_files = RELEASE_FILES.collect {|f| f.to_s }
end
task :package => [:gem]


Gem::PackageTask.new( GEMSPEC ) do |pkg|
	pkg.need_zip = true
	pkg.need_tar = true
end


### Task: install
desc "Install #{PKG_NAME} as a conventional library"
task :install => "spec:quiet" do
	log "Installing #{PKG_NAME} as a conventional library"
	sitelib = Pathname.new( CONFIG['sitelibdir'] )
	sitearch = Pathname.new( CONFIG['sitearchdir'] )
	Dir.chdir( LIBDIR ) do
		LIB_FILES.collect {|path| Pathname(path) }.each do |libfile|
			relpath = libfile.relative_path_from( LIBDIR )
			target = sitelib + relpath
			FileUtils.mkpath target.dirname,
				:mode => 0755, :verbose => true, :noop => $dryrun unless target.dirname.directory?
			FileUtils.install relpath, target,
				:mode => 0644, :verbose => true, :noop => $dryrun
		end
	end
	if EXTDIR.exist?
		trace "  looking for a binary extension (%s)" % [ EXTDIR + "*.#{Config::CONFIG['DLEXT']}" ]
		Dir.chdir( EXTDIR ) do
			Pathname.glob( "*.#{Config::CONFIG['DLEXT']}" ) do |dl|
				trace "    found: #{dl}"
				target = sitearch + dl.basename
				FileUtils.install dl, target, 
					:mode => 0755, :verbose => true, :noop => $dryrun
			end
		end
	end
end



### Task: install_gem
desc "Install #{PKG_NAME} from a locally-built gem"
task :install_gem => [:package] do
	$stderr.puts 
	installer = Gem::Installer.new( %{pkg/#{PKG_FILE_NAME}.gem} )
	installer.install
end


### Task: uninstall
desc "Uninstall #{PKG_NAME} if it's been installed as a conventional library"
task :uninstall do
	log "Uninstalling conventionally-installed #{PKG_NAME} library files"
	sitelib = Pathname.new( CONFIG['sitelibdir'] )
	sitearch = Pathname.new( CONFIG['sitearchdir'] )

	Dir.chdir( LIBDIR ) do
		LIB_FILES.collect {|path| Pathname(path) }.each do |libfile|
			relpath = libfile.relative_path_from( LIBDIR )
			target = sitelib + relpath
			FileUtils.rm_f target, :verbose => true, :noop => $dryrun
			FileUtils.rm_rf( target.dirname, :verbose => true, :noop => $dryrun ) if
				target.dirname.entries.empty?
		end
	end
	if EXTDIR.exist?
		trace "  looking for a binary extension (%s)" % [ EXTDIR + "*.#{Config::CONFIG['DLEXT']}" ]
		Dir.chdir( EXTDIR ) do
			Pathname.glob( "*.#{Config::CONFIG['DLEXT']}" ) do |dl|
				trace "    found: #{dl}"
				target = sitearch + dl.basename
				FileUtils.rm target, :verbose => true, :noop => $dryrun
			end
		end
	end
end


### Task: uninstall_gem
desc "Install the #{PKG_NAME} gem"
task :uninstall_gem => [:clean] do
	uninstaller = Gem::Uninstaller.new( PKG_FILE_NAME )
	uninstaller.uninstall
end



desc "Add development depdendencies to the gemspec -- this is meant to be chained " +
     "together with :gem"
task :include_dev_dependencies do
	DEVELOPMENT_DEPENDENCIES.each do |name, version|
		version = '>= 0' if version.length.zero?
		GEMSPEC.add_development_dependency( name, version )
	end
end


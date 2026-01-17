# 
# Rake tasklib for testing tasks

# 
# Authors:
# * Michael Granger <ged@FaerieMUD.org>
# 

unless defined?( COVERAGE_MINIMUM )
	if ENV['COVVERAGE_MINIMUM']
		COVERAGE_MINIMUM = Float( ENV['COVERAGE_MINIMUM'] )
	else
		COVERAGE_MINIMUM = 85.0 
	end
end
SPEC_FILES       = [] unless defined?( SPEC_FILES )
TEST_FILES       = [] unless defined?( TEST_FILES )

COMMON_RSPEC_OPTS = [] unless defined?( COMMON_RSPEC_OPTS )

COVERAGE_TARGETDIR = BASEDIR + 'coverage' unless defined?( COVERAGE_TARGETDIR )
RCOV_EXCLUDES      = 'spec,tests,/Library/Ruby,/var/lib,/usr/local/lib' unless
	defined?( RCOV_EXCLUDES )


desc "Run all defined tests"
task :test do
	unless SPEC_FILES.empty?
		log "Running specs"
		Rake::Task['spec:quiet'].invoke
	end

	unless TEST_FILES.empty?
		log "Running unit tests"
		Rake::Task[:unittests].invoke 
	end
end


### RSpec specifications
begin
	gem 'rspec', '>= 2.0.0'

	require 'rspec'
	require 'rspec/core/rake_task'

	### Task: spec
	desc "Run specs"
	task :spec => 'spec:doc'
	task :specs => :spec

	namespace :spec do
		desc "Run rspec every time there's a change to one of the files"
		task :autotest do
			require 'autotest'
			Autotest.add_discovery { "rspec2" }
			Autotest.run
		end

		desc "Generate regular color 'doc' spec output"
		RSpec::Core::RakeTask.new( :doc ) do |task|
			task.rspec_opts = COMMON_RSPEC_OPTS + ['-f', 'd', '-c']
		end

		desc "Generate spec output with profiling"
		RSpec::Core::RakeTask.new( :profile ) do |task|
			task.rspec_opts = COMMON_RSPEC_OPTS + ['-f', 'p', '-p']
		end

		desc "Generate quiet non-colored plain-text output"
		RSpec::Core::RakeTask.new( :quiet ) do |task|
			task.rspec_opts = COMMON_RSPEC_OPTS + ['-f', 'p']
		end

		desc "Generate HTML output"
		RSpec::Core::RakeTask.new( :html ) do |task|
			task.rspec_opts = COMMON_RSPEC_OPTS + ['-f', 'h']
		end


	end

	### Task: coverage (via RCov)
	desc "Build test coverage reports"
	RSpec::Core::RakeTask.new( :coverage ) do |task|
		task.ruby_opts = [ "-I#{LIBDIR}" ]
		task.rspec_opts = ['-f', 'p', '-b']
		task.rcov_opts = RCOV_OPTS
		task.rcov = true
	end

	### Task: rcov
	task :rcov => :coverage

	### Other coverage tasks
	namespace :coverage do
		desc "Generate a detailed text coverage report"
		RSpec::Core::RakeTask.new( :text ) do |task|
			task.rcov_opts = RCOV_OPTS + ['--text-report']
			task.rcov = true
		end

		desc "Show differences in coverage from last run"
		RSpec::Core::RakeTask.new( :diff ) do |task|
			task.rspec_opts = ['-f', 'p', '-b']
			task.rcov_opts = RCOV_OPTS - ['--save'] + ['--text-coverage-diff']
			task.rcov = true
		end

		desc "Run RCov in 'spec-only' mode to check coverage from specs"
		RSpec::Core::RakeTask.new( :speconly ) do |task|
			task.rcov_opts = ['--exclude', RCOV_EXCLUDES, '--text-report', '--save']
			task.rcov = true
		end
	end

	CLOBBER.include( COVERAGE_TARGETDIR )
rescue LoadError => err
	task :no_rspec do
		$stderr.puts "Specification tasks not defined: %s" % [ err.message ]
	end

	task :spec => :no_rspec
	namespace :spec do
		task :autotest => :no_rspec
		task :doc => :no_rspec
		task :profile => :no_rspec
		task :quiet => :no_rspec
		task :html => :no_rspec
	end
end


### Test::Unit tests
begin
	require 'rake/testtask'

	Rake::TestTask.new( :unittests ) do |task|
		task.libs += [LIBDIR]
		task.test_files = TEST_FILES
		task.verbose = true
	end

rescue LoadError => err
	task :no_test do
		$stderr.puts "Test tasks not defined: %s" % [ err.message ]
	end

	task :unittests => :no_rspec
end



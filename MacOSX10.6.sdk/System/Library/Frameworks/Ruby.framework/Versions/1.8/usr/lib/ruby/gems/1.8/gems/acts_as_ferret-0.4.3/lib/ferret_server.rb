require 'drb'
require 'thread'
require 'yaml'
require 'erb'

################################################################################
module ActsAsFerret
  module Remote

    ################################################################################
    class Config

      ################################################################################
      DEFAULTS = {
        'host'      => 'localhost',
        'port'      => '9009',
        'cf'        => "#{RAILS_ROOT}/config/ferret_server.yml",
        'pid_file'  => "#{RAILS_ROOT}/log/ferret_server.pid",
        'log_file'  => "#{RAILS_ROOT}/log/ferret_server.log",
        'log_level' => 'debug',
      }

      ################################################################################
      # load the configuration file and apply default settings
      def initialize (file=DEFAULTS['cf'])
        @everything = YAML.load(ERB.new(IO.read(file)).result)
        raise "malformed ferret server config" unless @everything.is_a?(Hash)
        @config = DEFAULTS.merge(@everything[RAILS_ENV] || {})
        @config['uri'] = "druby://#{host}:#{port}" if @everything[RAILS_ENV]
      end

      ################################################################################
      # treat the keys of the config data as methods
      def method_missing (name, *args)
        @config.has_key?(name.to_s) ? @config[name.to_s] : super
      end

    end

    #################################################################################
    # This class acts as a drb server listening for indexing and
    # search requests from models declared to 'acts_as_ferret :remote => true'
    #
    # Usage: 
    # - modify RAILS_ROOT/config/ferret_server.yml to suit your needs. 
    # - environments for which no section in the config file exists will use 
    #   the index locally (good for unit tests/development mode)
    # - run script/ferret_server to start the server:
    # script/ferret_server -e production start
    # - to stop the server run
    # script/ferret_server -e production stop
    #
    class Server

      #################################################################################
      # FIXME include detection of OS and include the correct file
      require 'unix_daemon'
      include(ActsAsFerret::Remote::UnixDaemon)

      ################################################################################
      cattr_accessor :running

      ################################################################################
      def initialize
        @cfg = ActsAsFerret::Remote::Config.new
        ActiveRecord::Base.allow_concurrency = true
        ActiveRecord::Base.logger = @logger = Logger.new(@cfg.log_file)
        ActiveRecord::Base.logger.level = Logger.const_get(@cfg.log_level.upcase) rescue Logger::DEBUG
      end

      ################################################################################
      # start the server
      def start
        raise "ferret_server not configured for #{RAILS_ENV}" unless (@cfg.uri rescue nil)
        $stdout.puts("starting ferret server...")

        platform_daemon do 
          self.class.running = true
          DRb.start_service(@cfg.uri, self)
          DRb.thread.join
        end
      rescue Exception => e
        @logger.error(e.to_s)
        raise
      end

      #################################################################################
      # handles all incoming method calls, and sends them on to the LocalIndex
      # instance of the correct model class.
      #
      # Calls are not queued atm, so this will block until the call returned.
      #
      def method_missing(name, *args)
        @logger.debug "\#method_missing(#{name.inspect}, #{args.inspect})"
        retried = false
        with_class args.shift do |clazz|
          reconnect_when_needed(clazz) do
            # using respond_to? here so we not have to catch NoMethodError
            # which would silently catch those from deep inside the indexing
            # code, too...
            if clazz.aaf_index.respond_to?(name)
              clazz.aaf_index.send name, *args
            elsif clazz.respond_to?(name)
              @logger.debug "no luck, trying to call class method instead"
              clazz.send name, *args
            else
              raise NoMethodError.new("method #{name} not supported by DRb server")
            end
          end
        end
      rescue => e
        @logger.error "ferret server error #{$!}\n#{$!.backtrace.join "\n"}"
        raise e
      end

      # make sure we have a versioned index in place, building one if necessary
      def ensure_index_exists(class_name)
        @logger.debug "DRb server: ensure_index_exists for class #{class_name}"
        with_class class_name do |clazz|
          dir = clazz.aaf_configuration[:index_dir]
          unless File.directory?(dir) && File.file?(File.join(dir, 'segments')) && dir =~ %r{/\d+(_\d+)?$}
            rebuild_index(clazz)
          end
        end
      end

      # disconnects the db connection for the class specified by class_name
      # used only in unit tests to check the automatic reconnection feature
      def db_disconnect!(class_name)
        with_class class_name do |clazz|
          clazz.connection.disconnect!
        end
      end

      # hides LocalIndex#rebuild_index to implement index versioning
      def rebuild_index(clazz, *models)
        with_class clazz do |clazz|
          models = models.flatten.uniq.map(&:constantize)
          models << clazz unless models.include?(clazz)
          index = new_index_for(clazz, models)
          reconnect_when_needed(clazz) do
            @logger.debug "DRb server: rebuild index for class(es) #{models.inspect} in #{index.options[:path]}"
            index.index_models models
          end
          new_version = File.join clazz.aaf_configuration[:index_base_dir], Time.now.utc.strftime('%Y%m%d%H%M%S')
          # create a unique directory name (needed for unit tests where 
          # multiple rebuilds per second may occur)
          if File.exists?(new_version)
            i = 0
            i+=1 while File.exists?("#{new_version}_#{i}")
            new_version << "_#{i}"
          end
          
          File.rename index.options[:path], new_version
          clazz.index_dir = new_version 
        end
      end


      protected

        def with_class(clazz, *args)
          clazz = clazz.constantize if String === clazz
          yield clazz, *args
        end

        def reconnect_when_needed(clazz)
          retried = false
          begin
            yield
          rescue ActiveRecord::StatementInvalid => e
            if e.message =~ /MySQL server has gone away/
              if retried
                raise e
              else
                @logger.info "StatementInvalid caught, trying to reconnect..."
                clazz.connection.reconnect!
                retried = true
                retry
              end
            else
              @logger.error "StatementInvalid caught, but unsure what to do with it: #{e}"
              raise e
            end
          end
        end

        def new_index_for(clazz, models)
          aaf_configuration = clazz.aaf_configuration
          ferret_cfg = aaf_configuration[:ferret].dup
          ferret_cfg.update :auto_flush  => false, 
                            :create      => true,
                            :field_infos => ActsAsFerret::field_infos(models),
                            :path        => File.join(aaf_configuration[:index_base_dir], 'rebuild')
          returning Ferret::Index::Index.new(ferret_cfg) do |i|
            i.batch_size = aaf_configuration[:reindex_batch_size]
            i.logger = @logger
          end
        end

    end
  end
end

require 'drb'
require 'thread'
require 'yaml'
require 'erb'


module ActsAsFerret

  module Remote

    module Config
      class << self
        DEFAULTS = {
          'host' => 'localhost',
          'port' => '9009'
        }
        # read connection settings from config file
        def load(file = "#{RAILS_ROOT}/config/ferret_server.yml")
          config = DEFAULTS.merge(YAML.load(ERB.new(IO.read(file)).result))
          if config = config[RAILS_ENV]
            config[:uri] = "druby://#{config['host']}:#{config['port']}"
            return config
          end
          {}
        end
      end
    end

    # This class acts as a drb server listening for indexing and
    # search requests from models declared to 'acts_as_ferret :remote => true'
    #
    # Usage: 
    # - modify RAILS_ROOT/config/ferret_server.yml to suit your needs. 
    # - environments for which no section in the config file exists will use 
    #   the index locally (good for unit tests/development mode)
    # - run script/ferret_start to start the server:
    # RAILS_ENV=production script/ferret_start
    #
    class Server

      cattr_accessor :running

      def self.start(uri = nil)
        ActiveRecord::Base.allow_concurrency = true
        ActiveRecord::Base.logger = Logger.new("#{RAILS_ROOT}/log/ferret_server.log")
        uri ||= ActsAsFerret::Remote::Config.load[:uri]
        DRb.start_service(uri, ActsAsFerret::Remote::Server.new)
        self.running = true
      end

      def initialize
        @logger = ActiveRecord::Base.logger
      end

      # handles all incoming method calls, and sends them on to the LocalIndex
      # instance of the correct model class.
      #
      # Calls are not queued atm, so this will block until the call returned.
      #
      def method_missing(name, *args)
        @logger.debug "\#method_missing(#{name.inspect}, #{args.inspect})"
        with_class args.shift do |clazz|
          begin
            clazz.aaf_index.send name, *args
          rescue NoMethodError
            @logger.debug "no luck, trying to call class method instead"
            clazz.send name, *args
          end
        end
      rescue
        @logger.error "ferret server error #{$!}\n#{$!.backtrace.join '\n'}"
        raise
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

      # hides LocalIndex#rebuild_index to implement index versioning
      def rebuild_index(clazz, *models)
        with_class clazz do |clazz|
          models = models.flatten.uniq.map(&:constantize)
          models << clazz unless models.include?(clazz)
          index = new_index_for(clazz, models)
          @logger.debug "DRb server: rebuild index for class(es) #{models.inspect} in #{index.options[:path]}"
          index.index_models models
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

        def new_index_for(clazz, models)
          aaf_configuration = clazz.aaf_configuration
          ferret_cfg = aaf_configuration[:ferret].dup
          ferret_cfg.update :auto_flush  => false, 
                            :create      => true,
                            :field_infos => ActsAsFerret::field_infos(models),
                            :path        => File.join(aaf_configuration[:index_base_dir], 'rebuild')
          returning Ferret::Index::Index.new ferret_cfg do |i|
            i.batch_size = aaf_configuration[:reindex_batch_size]
            i.logger = @logger
          end
        end

    end
  end
end

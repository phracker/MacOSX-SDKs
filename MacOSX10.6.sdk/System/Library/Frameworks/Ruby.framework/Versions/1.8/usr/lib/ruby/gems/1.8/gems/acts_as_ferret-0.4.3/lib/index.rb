module ActsAsFerret

  # base class for local and remote indexes
  class AbstractIndex

    attr_reader :aaf_configuration
    attr_accessor :logger
    def initialize(aaf_configuration)
      @aaf_configuration = aaf_configuration
      @logger = Logger.new("#{RAILS_ROOT}/log/ferret_index.log")
    end
    
    class << self
      def proxy_method(name, *args)
        define_method name do |*args|
          @server.send name, model_class_name, *args
        end
      end

      def index_proxy_method(*names)
        names.each do |name|
          define_method name do |*args|
            @server.send :"index_#{name}", model_class_name, *args
          end
        end
      end

    end
  end

end

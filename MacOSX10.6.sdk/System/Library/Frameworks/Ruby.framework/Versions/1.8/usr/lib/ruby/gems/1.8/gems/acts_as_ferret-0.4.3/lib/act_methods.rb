module ActsAsFerret #:nodoc:
        
  # This module defines the acts_as_ferret method and is included into 
  # ActiveRecord::Base
  module ActMethods
          
    
    def reloadable?; false end
    
    # declares a class as ferret-searchable. 
    #
    # ====options:
    # fields:: names all fields to include in the index. If not given,
    #          all attributes of the class will be indexed. You may also give
    #          symbols pointing to instance methods of your model here, i.e. 
    #          to retrieve and index data from a related model. 
    #
    # additional_fields:: names fields to include in the index, in addition 
    #                     to those derived from the db scheme. use if you want 
    #                     to add custom fields derived from methods to the db 
    #                     fields (which will be picked by aaf). This option will 
    #                     be ignored when the fields option is given, in that 
    #                     case additional fields get specified there.
    #
    # index_dir:: declares the directory where to put the index for this class.
    #             The default is RAILS_ROOT/index/RAILS_ENV/CLASSNAME. 
    #             The index directory will be created if it doesn't exist.
    #
    # single_index:: set this to true to let this class use a Ferret
    #                index that is shared by all classes having :single_index set to true.
    #                :store_class_name is set to true implicitly, as well as index_dir, so 
    #                don't bother setting these when using this option. the shared index
    #                will be located in index/<RAILS_ENV>/shared .
    #
    # store_class_name:: to make search across multiple models (with either
    #                    single_index or the multi_search method) useful, set
    #                    this to true. the model class name will be stored in a keyword field 
    #                    named class_name
    #
    # reindex_batch_size:: reindexing is done in batches of this size, default is 1000
    # mysql_fast_batches:: set this to false to disable the faster mysql batching
    #                      algorithm if this model uses a non-integer primary key named
    #                      'id' on MySQL.
    #
    # ferret:: Hash of Options that directly influence the way the Ferret engine works. You 
    #          can use most of the options the Ferret::I class accepts here, too. Among the 
    #          more useful are:
    #
    #     or_default:: whether query terms are required by
    #                  default (the default, false), or not (true)
    # 
    #     analyzer:: the analyzer to use for query parsing (default: nil,
    #                which means the ferret StandardAnalyzer gets used)
    #
    #     default_field:: use to set one or more fields that are searched for query terms
    #                     that don't have an explicit field list. This list should *not*
    #                     contain any untokenized fields. If it does, you're asking
    #                     for trouble (i.e. not getting results for queries having
    #                     stop words in them). Aaf by default initializes the default field 
    #                     list to contain all tokenized fields. If you use :single_index => true, 
    #                     you really should set this option specifying your default field
    #                     list (which should be equal in all your classes sharing the index).
    #                     Otherwise you might get incorrect search results and you won't get 
    #                     any lazy loading of stored field data.
    #
    # For downwards compatibility reasons you can also specify the Ferret options in the 
    # last Hash argument.
    def acts_as_ferret(options={}, ferret_options={})
      # default to DRb mode
      options[:remote] = true if options[:remote].nil?

      # force local mode if running *inside* the Ferret server - somewhere the
      # real indexing has to be done after all :-)
      # Usually the automatic detection of server mode works fine, however if you 
      # require your model classes in environment.rb they will get loaded before the 
      # DRb server is started, so this code is executed too early and detection won't 
      # work. In this case you'll get endless loops resulting in "stack level too deep" 
      # errors. 
      # To get around this, start the DRb server with the environment variable 
      # FERRET_USE_LOCAL_INDEX set to '1'.
      logger.debug "Asked for a remote server ? #{options[:remote].inspect}, ENV[\"FERRET_USE_LOCAL_INDEX\"] is #{ENV["FERRET_USE_LOCAL_INDEX"].inspect}, looks like we are#{ActsAsFerret::Remote::Server.running || ENV['FERRET_USE_LOCAL_INDEX'] ? '' : ' not'} the server"
      options.delete(:remote) if ENV["FERRET_USE_LOCAL_INDEX"] || ActsAsFerret::Remote::Server.running

      if options[:remote] && options[:remote] !~ /^druby/
        # read server location from config/ferret_server.yml
        options[:remote] = ActsAsFerret::Remote::Config.new.uri rescue nil
      end

      if options[:remote]
        logger.debug "Will use remote index server which should be available at #{options[:remote]}"
      else
        logger.debug "Will use local index."
      end


      extend ClassMethods
      extend SharedIndexClassMethods if options[:single_index]

      include InstanceMethods
      include MoreLikeThis::InstanceMethods

      # AR hooks
      after_create  :ferret_create
      after_update  :ferret_update
      after_destroy :ferret_destroy      

      cattr_accessor :aaf_configuration

      # default config
      self.aaf_configuration = { 
        :index_dir => "#{ActsAsFerret::index_dir}/#{self.name.underscore}",
        :store_class_name => false,
        :name => self.table_name,
        :class_name => self.name,
        :single_index => false,
        :reindex_batch_size => 1000,
        :ferret => {},                    # Ferret config Hash
        :ferret_fields => {},             # list of indexed fields that will be filled later
        :enabled => true,                 # used for class-wide disabling of Ferret
        :mysql_fast_batches => true       # turn off to disable the faster, id based batching mechanism for MySQL
      }

      # merge aaf options with args
      aaf_configuration.update(options) if options.is_a?(Hash)
      # apply appropriate settings for shared index
      if aaf_configuration[:single_index] 
        aaf_configuration[:index_dir] = "#{ActsAsFerret::index_dir}/shared" 
        aaf_configuration[:store_class_name] = true 
      end

      # set ferret default options
      aaf_configuration[:ferret].reverse_merge!( :or_default => false, 
                                                 :handle_parse_errors => true,
                                                 :default_field => nil # will be set later on
                                                 #:max_clauses => 512,
                                                 #:analyzer => Ferret::Analysis::StandardAnalyzer.new,
                                                 # :wild_card_downcase => true
                                               )

      # merge ferret options with those from second parameter hash
      aaf_configuration[:ferret].update(ferret_options) if ferret_options.is_a?(Hash)

      unless options[:remote]
        ActsAsFerret::ensure_directory aaf_configuration[:index_dir] 
        aaf_configuration[:index_base_dir] = aaf_configuration[:index_dir]
        aaf_configuration[:index_dir] = find_last_index_version(aaf_configuration[:index_dir])
        logger.debug "using index in #{aaf_configuration[:index_dir]}"
      end

      # these properties are somewhat vital to the plugin and shouldn't
      # be overwritten by the user:
      aaf_configuration[:ferret].update(
        :key               => (aaf_configuration[:single_index] ? [:id, :class_name] : :id),
        :path              => aaf_configuration[:index_dir],
        :auto_flush        => true, # slower but more secure in terms of locking problems TODO disable when running in drb mode?
        :create_if_missing => true
      )
      
      if aaf_configuration[:fields]
        add_fields(aaf_configuration[:fields])
      else
        add_fields(self.new.attributes.keys.map { |k| k.to_sym })
        add_fields(aaf_configuration[:additional_fields])
      end

      # now that all fields have been added, we can initialize the default
      # field list to be used by the query parser.
      # It will include all content fields *not* marked as :untokenized.
      # This fixes the otherwise failing CommentTest#test_stopwords. Basically
      # this means that by default only tokenized fields (which is the default)
      # will be searched. If you want to search inside the contents of an
      # untokenized field, you'll have to explicitly specify it in your query.
      #
      # Unfortunately this is not very useful with a shared index (see
      # http://projects.jkraemer.net/acts_as_ferret/ticket/85)
      # You should consider specifying the default field list to search for as
      # part of the ferret_options hash in your call to acts_as_ferret.
      aaf_configuration[:ferret][:default_field] ||= if aaf_configuration[:single_index]
        logger.warn "You really should set the acts_as_ferret :default_field option when using a shared index!"
        '*'
      else
        aaf_configuration[:ferret_fields].keys.select do |f| 
          aaf_configuration[:ferret_fields][f][:index] != :untokenized
        end
      end
      logger.info "default field list: #{aaf_configuration[:ferret][:default_field].inspect}"

      if options[:remote]
        aaf_index.ensure_index_exists
      end
    end


    protected
    
    # find the most recent version of an index
    def find_last_index_version(basedir)
      # check for versioned index
      versions = Dir.entries(basedir).select do |f| 
        dir = File.join(basedir, f)
        File.directory?(dir) && File.file?(File.join(dir, 'segments')) && f =~ /^\d+(_\d+)?$/
      end
      if versions.any?
        # select latest version
        versions.sort!
        File.join basedir, versions.last
      else
        basedir
      end
    end


    # helper that defines a method that adds the given field to a ferret 
    # document instance
    def define_to_field_method(field, options = {})
      if options[:boost].is_a?(Symbol)
        dynamic_boost = options[:boost]
        options.delete :boost
      end
      options.reverse_merge!( :store       => :no, 
                              :highlight   => :yes, 
                              :index       => :yes, 
                              :term_vector => :with_positions_offsets,
                              :boost       => 1.0 )
      options[:term_vector] = :no if options[:index] == :no
      aaf_configuration[:ferret_fields][field] = options

      define_method("#{field}_to_ferret".to_sym) do
        begin
          val = content_for_field_name(field, dynamic_boost)
        rescue
          logger.warn("Error retrieving value for field #{field}: #{$!}")
          val = ''
        end
        logger.debug("Adding field #{field} with value '#{val}' to index")
        val
      end
    end

    def add_fields(field_config)
      if field_config.is_a? Hash
        field_config.each_pair do |key,val|
          define_to_field_method(key,val)                  
        end
      elsif field_config.respond_to?(:each)
        field_config.each do |field| 
          define_to_field_method(field)
        end                
      end
    end

  end

end

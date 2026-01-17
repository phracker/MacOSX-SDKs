module ActsAsFerret
  class LocalIndex < AbstractIndex
    include MoreLikeThis::IndexMethods

    def initialize(aaf_configuration)
      super
      ensure_index_exists
    end

    def reopen!
      if @ferret_index
        @ferret_index.close
        @ferret_index = nil
      end
      logger.debug "reopening index at #{aaf_configuration[:ferret][:path]}"
      ferret_index
    end

    # The 'real' Ferret Index instance
    def ferret_index
      ensure_index_exists
      returning @ferret_index ||= Ferret::Index::Index.new(aaf_configuration[:ferret]) do
        @ferret_index.batch_size = aaf_configuration[:reindex_batch_size]
        @ferret_index.logger = logger
      end
    end

    # Checks for the presence of a segments file in the index directory
    # Rebuilds the index if none exists.
    def ensure_index_exists
      logger.debug "LocalIndex: ensure_index_exists at #{aaf_configuration[:index_dir]}"
      unless File.file? "#{aaf_configuration[:index_dir]}/segments"
        ActsAsFerret::ensure_directory(aaf_configuration[:index_dir])
        close
        rebuild_index 
      end
    end

    # Closes the underlying index instance
    def close
      @ferret_index.close if @ferret_index
    rescue StandardError 
      # is raised when index already closed
    ensure
      @ferret_index = nil
    end

    # rebuilds the index from all records of the model class this index belongs
    # to. Arguments can be given in shared index scenarios to name multiple
    # model classes to include in the index
    def rebuild_index(*models)
      models << aaf_configuration[:class_name] unless models.include?(aaf_configuration[:class_name])
      models = models.flatten.uniq.map(&:constantize)
      logger.debug "rebuild index: #{models.inspect}"
      index = Ferret::Index::Index.new(aaf_configuration[:ferret].dup.update(:auto_flush => false, 
                                                                             :field_infos => ActsAsFerret::field_infos(models),
                                                                             :create => true))
      index.batch_size = aaf_configuration[:reindex_batch_size]
      index.logger = logger
      index.index_models models
    end

    def bulk_index(ids, options)
      ferret_index.bulk_index(aaf_configuration[:class_name].constantize, ids, options)
    end

    # Parses the given query string into a Ferret Query object.
    def process_query(query)
      # work around ferret bug in #process_query (doesn't ensure the
      # reader is open)
      ferret_index.synchronize do
        ferret_index.send(:ensure_reader_open)
        original_query = ferret_index.process_query(query)
      end
    end

    # Total number of hits for the given query. 
    # To count the results of a multi_search query, specify an array of 
    # class names with the :multi option.
    def total_hits(query, options = {})
      index = (models = options.delete(:multi)) ? multi_index(models) : ferret_index
      index.search(query, options).total_hits
    end

    def determine_lazy_fields(options = {})
      stored_fields = options[:lazy]
      if stored_fields && !(Array === stored_fields)
        stored_fields = aaf_configuration[:ferret_fields].select { |field, config| config[:store] == :yes }.map(&:first)
      end
      logger.debug "stored_fields: #{stored_fields}"
      return stored_fields
    end

    # Queries the Ferret index to retrieve model class, id, score and the
    # values of any fields stored in the index for each hit.
    # If a block is given, these are yielded and the number of total hits is
    # returned. Otherwise [total_hits, result_array] is returned.
    def find_id_by_contents(query, options = {})
      result = []
      index = ferret_index
      logger.debug "query: #{ferret_index.process_query query}" if logger.debug?
      lazy_fields = determine_lazy_fields options

      total_hits = index.search_each(query, options) do |hit, score|
        doc = index[hit]
        model = aaf_configuration[:store_class_name] ? doc[:class_name] : aaf_configuration[:class_name]
        # fetch stored fields if lazy loading
        data = {}
        lazy_fields.each { |field| data[field] = doc[field] } if lazy_fields
        if block_given?
          yield model, doc[:id], score, data
        else
          result << { :model => model, :id => doc[:id], :score => score, :data => data }
        end
      end
      #logger.debug "id_score_model array: #{result.inspect}"
      return block_given? ? total_hits : [total_hits, result]
    end

    # Queries multiple Ferret indexes to retrieve model class, id and score for 
    # each hit. Use the models parameter to give the list of models to search.
    # If a block is given, model, id and score are yielded and the number of 
    # total hits is returned. Otherwise [total_hits, result_array] is returned.
    def id_multi_search(query, models, options = {})
      index = multi_index(models)
      result = []
      lazy_fields = determine_lazy_fields options
      total_hits = index.search_each(query, options) do |hit, score|
        doc = index[hit]
        # fetch stored fields if lazy loading
        data = {}
        lazy_fields.each { |field| data[field] = doc[field] } if lazy_fields
        raise "':store_class_name => true' required for multi_search to work" if doc[:class_name].blank?
        if block_given?
          yield doc[:class_name], doc[:id], score, doc, data
        else
          result << { :model => doc[:class_name], :id => doc[:id], :score => score, :data => data }
        end
      end
      return block_given? ? total_hits : [ total_hits, result ]
    end

    ######################################
    # methods working on a single record
    # called from instance_methods, here to simplify interfacing with the
    # remote ferret server
    # TODO having to pass id and class_name around like this isn't nice
    ######################################

    # add record to index
    # record may be the full AR object, a Ferret document instance or a Hash
    def add(record)
      record = record.to_doc unless Hash === record || Ferret::Document === record
      ferret_index << record
    end
    alias << add

    # delete record from index
    def remove(id, class_name)
      ferret_index.query_delete query_for_record(id, class_name)
    end

    # highlight search terms for the record with the given id.
    def highlight(id, class_name, query, options = {})
      options.reverse_merge! :num_excerpts => 2, :pre_tag => '<em>', :post_tag => '</em>'
      highlights = []
      ferret_index.synchronize do
        doc_num = document_number(id, class_name)
        if options[:field]
          highlights << ferret_index.highlight(query, doc_num, options)
        else
          query = process_query(query) # process only once
          aaf_configuration[:ferret_fields].each_pair do |field, config|
            next if config[:store] == :no || config[:highlight] == :no
            options[:field] = field
            highlights << ferret_index.highlight(query, doc_num, options)
          end
        end
      end
      return highlights.compact.flatten[0..options[:num_excerpts]-1]
    end

    # retrieves the ferret document number of the record with the given id.
    def document_number(id, class_name)
      hits = ferret_index.search(query_for_record(id, class_name))
      return hits.hits.first.doc if hits.total_hits == 1
      raise "cannot determine document number from primary key: #{id}"
    end

    # build a ferret query matching only the record with the given id
    # the class name only needs to be given in case of a shared index configuration
    def query_for_record(id, class_name = nil)
      Ferret::Search::TermQuery.new(:id, id.to_s)
    end


    protected

    # returns a MultiIndex instance operating on a MultiReader
    def multi_index(model_classes)
      model_classes.map!(&:constantize) if String === model_classes.first
      model_classes.sort! { |a, b| a.name <=> b.name }
      key = model_classes.inject("") { |s, clazz| s + clazz.name }
      multi_config = aaf_configuration[:ferret].dup
      multi_config.delete :default_field  # we don't want the default field list of *this* class for multi_searching
      ActsAsFerret::multi_indexes[key] ||= MultiIndex.new(model_classes, multi_config)
    end
 
  end

end

module ActsAsFerret
        
  module ClassMethods

    # rebuild the index from all data stored for this model.
    # This is called automatically when no index exists yet.
    #
    # When calling this method manually, you can give any additional 
    # model classes that should also go into this index as parameters. 
    # Useful when using the :single_index option.
    # Note that attributes named the same in different models will share
    # the same field options in the shared index.
    def rebuild_index(*models)
      models << self unless models.include?(self)
      aaf_index.rebuild_index models.map(&:to_s)
      index_dir = find_last_index_version(aaf_configuration[:index_base_dir]) unless aaf_configuration[:remote]
    end

    # runs across all records yielding those to be indexed when the index is rebuilt
    def records_for_rebuild(batch_size = 1000)
      transaction do
        if connection.class.name =~ /Mysql/ && primary_key == 'id'
          logger.info "using mysql specific batched find :all"
          offset = 0
          while (rows = find :all, :conditions => ["id > ?", offset ], :limit => batch_size).any?
            offset = rows.last.id
            yield rows, offset
          end
        else
          # sql server adapter won't batch correctly without defined ordering
          order = "#{primary_key} ASC" if connection.class.name =~ /SQLServer/
          0.step(self.count, batch_size) do |offset|
            yield find( :all, :limit => batch_size, :offset => offset, :order => order ), offset
          end
        end
      end
    end

    # Switches this class to a new index located in dir.
    # Used by the DRb server when switching to a new index version.
    def index_dir=(dir)
      logger.debug "changing index dir to #{dir}"
      aaf_configuration[:index_dir] = aaf_configuration[:ferret][:path] = dir
      aaf_index.reopen!
      logger.debug "index dir is now #{dir}"
    end
    
    # Retrieve the index instance for this model class. This can either be a
    # LocalIndex, or a RemoteIndex instance.
    # 
    # Index instances are stored in a hash, using the index directory
    # as the key. So model classes sharing a single index will share their
    # Index object, too.
    def aaf_index
      ActsAsFerret::ferret_indexes[aaf_configuration[:index_dir]] ||= create_index_instance
    end 
    
    # Finds instances by searching the Ferret index. Terms are ANDed by default, use 
    # OR between terms for ORed queries. Or specify +:or_default => true+ in the
    # +:ferret+ options hash of acts_as_ferret.
    #
    # == options:
    # offset::      first hit to retrieve (useful for paging)
    # limit::       number of hits to retrieve, or :all to retrieve
    #               all results
    # lazy::        Array of field names whose contents should be read directly
    #               from the index. Those fields have to be marked 
    #               +:store => :yes+ in their field options. Give true to get all
    #               stored fields. Note that if you have a shared index, you have 
    #               to explicitly state the fields you want to fetch, true won't
    #               work here)
    # models::      only for single_index scenarios: an Array of other Model classes to 
    #               include in this search. Use :all to query all models.
    #
    # +find_options+ is a hash passed on to active_record's find when
    # retrieving the data from db, useful to i.e. prefetch relationships with
    # :include or to specify additional filter criteria with :conditions.
    #
    # This method returns a +SearchResults+ instance, which really is an Array that has 
    # been decorated with a total_hits attribute holding the total number of hits.
    #
    # Please keep in mind that the number of total hits might be wrong if you specify 
    # both ferret options and active record find_options that somehow limit the result 
    # set (e.g. +:num_docs+ and some +:conditions+).
    def find_with_ferret(q, options = {}, find_options = {})
      total_hits, result = find_records_lazy_or_not q, options, find_options
      logger.debug "Query: #{q}\ntotal hits: #{total_hits}, results delivered: #{result.size}"
      return SearchResults.new(result, total_hits)
    end 
    alias find_by_contents find_with_ferret

   

    # Returns the total number of hits for the given query 
    # To count the results of a multi_search query, specify an array of 
    # class names with the :models option.
    def total_hits(q, options={})
      if models = options[:models]
        options[:models] = add_self_to_model_list_if_necessary(models).map(&:to_s)
      end
      aaf_index.total_hits(q, options)
    end

    # Finds instance model name, ids and scores by contents. 
    # Useful e.g. if you want to search across models or do not want to fetch
    # all result records (yet).
    #
    # Options are the same as for find_by_contents
    #
    # A block can be given too, it will be executed with every result:
    # find_id_by_contents(q, options) do |model, id, score|
    #    id_array << id
    #    scores_by_id[id] = score 
    # end
    # NOTE: in case a block is given, only the total_hits value will be returned
    # instead of the [total_hits, results] array!
    # 
    def find_id_by_contents(q, options = {}, &block)
      deprecated_options_support(options)
      aaf_index.find_id_by_contents(q, options, &block)
    end

    # requires the store_class_name option of acts_as_ferret to be true
    # for all models queried this way.
    def multi_search(query, additional_models = [], options = {}, find_options = {})
      result = []

      if options[:lazy]
        logger.warn "find_options #{find_options} are ignored because :lazy => true" unless find_options.empty?
        total_hits = id_multi_search(query, additional_models, options) do |model, id, score, data|
          result << FerretResult.new(model, id, score, data)
        end
      else
        id_arrays = {}
        rank = 0
        total_hits = id_multi_search(query, additional_models, options) do |model, id, score, data|
          id_arrays[model] ||= {}
          id_arrays[model][id] = [ rank += 1, score ]
        end
        result = retrieve_records(id_arrays, find_options)
      end

      SearchResults.new(result, total_hits)
    end
    
    # returns an array of hashes, each containing :class_name,
    # :id and :score for a hit.
    #
    # if a block is given, class_name, id and score of each hit will 
    # be yielded, and the total number of hits is returned.
    def id_multi_search(query, additional_models = [], options = {}, &proc)
      deprecated_options_support(options)
      additional_models = add_self_to_model_list_if_necessary(additional_models)
      aaf_index.id_multi_search(query, additional_models.map(&:to_s), options, &proc)
    end
    

    protected

    def add_self_to_model_list_if_necessary(models)
      models = [ models ] unless models.is_a? Array
      models << self unless models.include?(self)
    end

    def find_records_lazy_or_not(q, options = {}, find_options = {})
      if options[:lazy]
        logger.warn "find_options #{find_options} are ignored because :lazy => true" unless find_options.empty?
        lazy_find_by_contents q, options
      else
        ar_find_by_contents q, options, find_options
      end
    end

    def ar_find_by_contents(q, options = {}, find_options = {})
      result_ids = {}
      total_hits = find_id_by_contents(q, options) do |model, id, score, data|
        # stores ids, index of each id for later ordering of
        # results, and score
        result_ids[id] = [ result_ids.size + 1, score ]
      end

      result = retrieve_records( { self.name => result_ids }, find_options )
      
      if find_options[:conditions]
        if options[:limit] != :all
          # correct result size if the user specified conditions
          #  wenn conditions: options[:limit] != :all --> ferret-query mit :all wiederholen und select count machen
          result_ids = {}
          find_id_by_contents(q, options.update(:limit => :all)) do |model, id, score, data|
            result_ids[id] = [ result_ids.size + 1, score ]
          end
          total_hits = count_records( { self.name => result_ids }, find_options )
        else
          total_hits = result.length
        end
      end

      [ total_hits, result ]
    end

    def lazy_find_by_contents(q, options = {})
      result = []
      total_hits = find_id_by_contents(q, options) do |model, id, score, data|
        result << FerretResult.new(model, id, score, data)
      end
      [ total_hits, result ]
    end


    def model_find(model, id, find_options = {})
      model.constantize.find(id, find_options)
    end

    # retrieves search result records from a data structure like this:
    # { 'Model1' => { '1' => [ rank, score ], '2' => [ rank, score ] }
    #
    # TODO: in case of STI AR will filter out hits from other 
    # classes for us, but this
    # will lead to less results retrieved --> scoping of ferret query
    # to self.class is still needed.
    # from the ferret ML (thanks Curtis Hatter)
    # > I created a method in my base STI class so I can scope my query. For scoping
    # > I used something like the following line:
    # > 
    # > query << " role:#{self.class.eql?(Contents) '*' : self.class}"
    # > 
    # > Though you could make it more generic by simply asking
    # > "self.descends_from_active_record?" which is how rails decides if it should
    # > scope your "find" query for STI models. You can check out "base.rb" in
    # > activerecord to see that.
    # but maybe better do the scoping in find_id_by_contents...
    def retrieve_records(id_arrays, find_options = {})
      result = []
      # get objects for each model
      id_arrays.each do |model, id_array|
        next if id_array.empty?
        begin
          model = model.constantize
        rescue
          raise "Please use ':store_class_name => true' if you want to use multi_search.\n#{$!}"
        end

        # check for include association that might only exist on some models in case of multi_search
        filtered_include_options = []
        if include_options = find_options[:include]
          include_options.each do |include_option|
            filtered_include_options << include_option if model.reflections.has_key?(include_option.is_a?(Hash) ? include_option.keys[0].to_sym : include_option.to_sym)
          end
        end
        filtered_include_options=nil if filtered_include_options.empty?

        # fetch
        tmp_result = nil
        model.send(:with_scope, :find => find_options) do 
          tmp_result = model.find( :all, :conditions => [ 
            "#{model.table_name}.#{model.primary_key} in (?)", id_array.keys ],  
            :include => filtered_include_options ) 
        end

        # set scores and rank
        tmp_result.each do |record|
          record.ferret_rank, record.ferret_score = id_array[record.id.to_s]
        end
        # merge with result array
        result.concat tmp_result
      end
      
      # order results as they were found by ferret, unless an AR :order
      # option was given
      result.sort! { |a, b| a.ferret_rank <=> b.ferret_rank } unless find_options[:order]
      return result
    end

    def count_records(id_arrays, find_options = {})
      count = 0
      id_arrays.each do |model, id_array|
        next if id_array.empty?
        begin
          model = model.constantize
          model.send(:with_scope, :find => find_options) do 
            count += model.count(:conditions => [ "#{model.table_name}.#{model.primary_key} in (?)",
                                                  id_array.keys ]) 
          end
        rescue TypeError
          raise "#{model} must use :store_class_name option if you want to use multi_search against it.\n#{$!}"
        end
      end
      count
    end

    def deprecated_options_support(options)
      if options[:num_docs]
        logger.warn ":num_docs is deprecated, use :limit instead!"
        options[:limit] ||= options[:num_docs]
      end
      if options[:first_doc]
        logger.warn ":first_doc is deprecated, use :offset instead!"
        options[:offset] ||= options[:first_doc]
      end
    end

    # creates a new Index instance.
    def create_index_instance
      if aaf_configuration[:remote]
       RemoteIndex
      elsif aaf_configuration[:single_index]
        SharedIndex
      else
        LocalIndex
      end.new(aaf_configuration)
    end

  end
  
end


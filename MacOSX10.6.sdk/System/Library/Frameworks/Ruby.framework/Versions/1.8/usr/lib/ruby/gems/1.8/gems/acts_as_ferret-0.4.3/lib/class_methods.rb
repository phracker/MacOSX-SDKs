module ActsAsFerret
        
  module ClassMethods

    # Disables ferret index updates for this model. When a block is given,
    # Ferret will be re-enabled again after executing the block.
    def disable_ferret
      aaf_configuration[:enabled] = false
      if block_given?
        yield
        enable_ferret
      end
    end

    def enable_ferret
      aaf_configuration[:enabled] = true
    end

    def ferret_enabled?
      aaf_configuration[:enabled]
    end

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

    # re-index a number records specified by the given ids. Use for large
    # indexing jobs i.e. after modifying a lot of records with Ferret disabled.
    # Please note that the state of Ferret (enabled or disabled at class or
    # record level) is not checked by this method, so if you need to do so
    # (e.g. because of a custom ferret_enabled? implementation), you have to do
    # so yourself.
    def bulk_index(*ids)
      options = Hash === ids.last ? ids.pop : {}
      ids = ids.first if ids.size == 1 && ids.first.is_a?(Enumerable)
      aaf_index.bulk_index(ids, options)
    end

    # true if our db and table appear to be suitable for the mysql fast batch
    # hack (see
    # http://weblog.jamisbuck.org/2007/4/6/faking-cursors-in-activerecord)
    def use_fast_batches?
      if connection.class.name =~ /Mysql/ && primary_key == 'id' && aaf_configuration[:mysql_fast_batches]
        logger.info "using mysql specific batched find :all. Turn off with  :mysql_fast_batches => false if you encounter problems (i.e. because of non-integer UUIDs in the id column)"
        true
      end
    end

    # runs across all records yielding those to be indexed when the index is rebuilt
    def records_for_rebuild(batch_size = 1000)
      transaction do
        if use_fast_batches?
          offset = 0
          while (rows = find :all, :conditions => [ "#{table_name}.id > ?", offset ], :limit => batch_size).any?
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

    # yields the records with the given ids, in batches of batch_size
    def records_for_bulk_index(ids, batch_size = 1000)
      transaction do
        offset = 0
        ids.each_slice(batch_size) do |id_slice|
          logger.debug "########## slice: #{id_slice.join(',')}"
          records = find( :all, :conditions => ["id in (?)", id_slice] )
          logger.debug "########## slice records: #{records.inspect}"
          #yield records, offset
          yield find( :all, :conditions => ["id in (?)", id_slice] ), offset
          offset += batch_size
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
    # You may either use the +offset+ and +limit+ options to implement your own
    # pagination logic, or use the +page+ and +per_page+ options to use the
    # built in pagination support which is compatible with will_paginate's view
    # helpers. If +page+ and +per_page+ are given, +offset+ and +limit+ will be
    # ignored.
    #
    # == options:
    # page::        page of search results to retrieve
    # per_page::    number of search results that are displayed per page
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
    # multi::       Specify additional model classes to search through. Each of
    #               these, as well as this class, has to have the
    #               :store_class_name option set to true. This option replaces the
    #               multi_search method.
    #
    # +find_options+ is a hash passed on to active_record's find when
    # retrieving the data from db, useful to i.e. prefetch relationships with
    # :include or to specify additional filter criteria with :conditions.
    #
    # This method returns a +SearchResults+ instance, which really is an Array that has 
    # been decorated with a total_hits attribute holding the total number of hits.
    # Additionally, SearchResults is compatible with the pagination helper
    # methods of the will_paginate plugin.
    #
    # Please keep in mind that the number of results delivered might be less than 
    # +limit+ if you specify any active record conditions that further limit 
    # the result. Use +limit+ and +offset+ as AR find_options instead.
    # +page+ and +per_page+ are supposed to work regardless of any 
    # +conitions+ present in +find_options+.
    def find_with_ferret(q, options = {}, find_options = {})
      if options[:per_page]
        options[:page] = options[:page] ? options[:page].to_i : 1
        limit = options[:per_page]
        offset = (options[:page] - 1) * limit
        if find_options[:conditions] && !options[:multi]
          find_options[:limit] = limit
          find_options[:offset] = offset
          options[:limit] = :all
          options.delete :offset
        else
          # do pagination with ferret (or after everything is done in the case
          # of multi_search)
          options[:limit] = limit
          options[:offset] = offset
        end
      elsif find_options[:conditions]
        if options[:multi]
          # multisearch ignores find_options limit and offset
          options[:limit] ||= find_options.delete(:limit)
          options[:offset] ||= find_options.delete(:offset)
        else
          # let the db do the limiting and offsetting for single-table searches
          find_options[:limit] ||= options.delete(:limit)
          find_options[:offset] ||= options.delete(:offset)
          options[:limit] = :all
        end
      end

      total_hits, result = if options[:multi].blank?
        find_records_lazy_or_not q, options, find_options
      else
        _multi_search q, options.delete(:multi), options, find_options
      end
      logger.debug "Query: #{q}\ntotal hits: #{total_hits}, results delivered: #{result.size}"
      SearchResults.new(result, total_hits, options[:page], options[:per_page])
    end 
    alias find_by_contents find_with_ferret

   

    # Returns the total number of hits for the given query 
    # To count the results of a query across multiple models, specify an array of 
    # class names with the :multi option.
    #
    # Note that since we don't query the database here, this method won't deliver 
    # the expected results when used on an AR association.
    def total_hits(q, options={})
      if options[:models]
        # backwards compatibility
        logger.warn "the :models option of total_hits is deprecated, please use :multi instead"
        options[:multi] = options[:models] 
      end
      if models = options[:multi]
        options[:multi] = add_self_to_model_list_if_necessary(models).map(&:to_s)
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

    
    # returns an array of hashes, each containing :class_name,
    # :id and :score for a hit.
    #
    # if a block is given, class_name, id and score of each hit will 
    # be yielded, and the total number of hits is returned.
    def id_multi_search(query, additional_models = [], options = {}, &proc)
      deprecated_options_support(options)
      models = add_self_to_model_list_if_necessary(additional_models)
      aaf_index.id_multi_search(query, models.map(&:to_s), options, &proc)
    end
    

    protected

    def _multi_search(query, additional_models = [], options = {}, find_options = {})
      result = []

      if options[:lazy]
        logger.warn "find_options #{find_options} are ignored because :lazy => true" unless find_options.empty?
        total_hits = id_multi_search(query, additional_models, options) do |model, id, score, data|
          result << FerretResult.new(model, id, score, data)
        end
      else
        id_arrays = {}
        rank = 0

        limit = options.delete(:limit)
        offset = options.delete(:offset) || 0
        options[:limit] = :all
        total_hits = id_multi_search(query, additional_models, options) do |model, id, score, data|
          id_arrays[model] ||= {}
          id_arrays[model][id] = [ rank += 1, score ]
        end
        result = retrieve_records(id_arrays, find_options)
        total_hits = result.size if find_options[:conditions]
 #       total_hits += offset if offset
        if limit && limit != :all
          result = result[offset..limit+offset-1]
        end
      end
      [total_hits, result]
    end

    def add_self_to_model_list_if_necessary(models)
      models = [ models ] unless models.is_a? Array
      models << self unless models.include?(self)
      models
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
        # stores ids, index and score of each hit for later ordering of
        # results
        result_ids[id] = [ result_ids.size + 1, score ]
      end

      result = retrieve_records( { self.name => result_ids }, find_options )
      
      # count total_hits via sql when using conditions or when we're called
      # from an ActiveRecord association.
      if find_options[:conditions] or caller.find{ |call| call =~ %r{active_record/associations} }
        # chances are the ferret result count is not our total_hits value, so
        # we correct this here.
        if options[:limit] != :all || options[:page] || options[:offset] || find_options[:limit] || find_options[:offset]
          # our ferret result has been limited, so we need to re-run that
          # search to get the full result set from ferret.
          result_ids = {}
          find_id_by_contents(q, options.update(:limit => :all, :offset => 0)) do |model, id, score, data|
            result_ids[id] = [ result_ids.size + 1, score ]
          end
          # Now ask the database for the total size of the final result set.
          total_hits = count_records( { self.name => result_ids }, find_options )
        else
          # what we got from the database is our full result set, so take
          # it's size
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

        # merge conditions
        conditions = combine_conditions([ "#{model.table_name}.#{model.primary_key} in (?)", 
                                          id_array.keys ], 
                                        find_options[:conditions])

        # check for include association that might only exist on some models in case of multi_search
        filtered_include_options = []
        if include_options = find_options[:include]
          include_options = [ include_options ] unless include_options.respond_to?(:each)
          include_options.each do |include_option|
            filtered_include_options << include_option if model.reflections.has_key?(include_option.is_a?(Hash) ? include_option.keys[0].to_sym : include_option.to_sym)
          end
        end
        filtered_include_options = nil if filtered_include_options.empty?

        # fetch
        tmp_result = model.find(:all, find_options.merge(:conditions => conditions, 
                                                         :include => filtered_include_options))

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
      count_options = find_options.dup
      count_options.delete :limit
      count_options.delete :offset
      count = 0
      id_arrays.each do |model, id_array|
        next if id_array.empty?
        begin
          model = model.constantize
          # merge conditions
          conditions = combine_conditions([ "#{model.table_name}.#{model.primary_key} in (?)", id_array.keys ], 
                                          find_options[:conditions])
          opts = find_options.merge :conditions => conditions
          opts.delete :limit; opts.delete :offset
          count += model.count opts
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

    # combine our conditions with those given by user, if any
    def combine_conditions(conditions, additional_conditions = [])
      returning conditions do
        if additional_conditions && additional_conditions.any?
          cust_opts = additional_conditions.respond_to?(:shift) ? additional_conditions.dup : [ additional_conditions ]
          conditions.first << " and " << cust_opts.shift
          conditions.concat(cust_opts)
        end
      end
    end

  end
  
end


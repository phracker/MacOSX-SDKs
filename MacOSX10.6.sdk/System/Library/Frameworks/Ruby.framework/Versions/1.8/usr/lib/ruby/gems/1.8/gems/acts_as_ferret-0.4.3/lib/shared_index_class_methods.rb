module ActsAsFerret
  
  # class methods for classes using acts_as_ferret :single_index => true
  module SharedIndexClassMethods

    def find_id_by_contents(q, options = {}, &block)
      # add class name scoping to query if necessary
      unless options[:models] == :all # search needs to be restricted by one or more class names
        options[:models] ||= [] 
        # add this class to the list of given models
        options[:models] << self unless options[:models].include?(self)
        # keep original query 
        original_query = q
        
        if original_query.is_a? String
          model_query = options[:models].map(&:name).join '|'
          q += %{ +class_name:"#{model_query}"}
        else
          q = Ferret::Search::BooleanQuery.new
          q.add_query(original_query, :must)
          model_query = Ferret::Search::BooleanQuery.new
          options[:models].each do |model|
            model_query.add_query(Ferret::Search::TermQuery.new(:class_name, model.name), :should)
          end
          q.add_query(model_query, :must)
        end
      end
      options.delete :models
      
      super(q, options, &block)
    end

    # Overrides the standard find_by_contents for searching a shared index.
    #
    # please note that records from different models will be fetched in
    # separate sql calls, so any sql order_by clause given with 
    # find_options[:order] will be ignored.
    def find_by_contents(q, options = {}, find_options = {})
      if order = find_options.delete(:order)
        logger.warn "using a shared index, so ignoring order_by clause #{order}"
      end
      total_hits, result = find_records_lazy_or_not q, options, find_options
      # sort so results have the same order they had when originally retrieved
      # from ferret
      return SearchResults.new(result, total_hits)
    end

    protected

    def ar_find_by_contents(q, options = {}, find_options = {})
      total_hits, id_arrays = collect_results(q, options)
      result = retrieve_records(id_arrays, find_options)
      result.sort! { |a, b| id_arrays[a.class.name][a.id.to_s].first <=> id_arrays[b.class.name][b.id.to_s].first }
      [ total_hits, result ]
    end

    def collect_results(q, options = {})
      id_arrays = {}
      # get object ids for index hits
      rank = 0
      total_hits = find_id_by_contents(q, options) do |model, id, score, data|
        id_arrays[model] ||= {}
        # store result rank and score
        id_arrays[model][id] = [ rank += 1, score ]
      end
      [ total_hits, id_arrays ]
    end

    
    # determine all field names in the shared index
    # TODO unused
#    def single_index_field_names(models)
#      @single_index_field_names ||= (
#          searcher = Ferret::Search::Searcher.new(class_index_dir)
#          if searcher.reader.respond_to?(:get_field_names)
#            (searcher.reader.send(:get_field_names) - ['id', 'class_name']).to_a
#          else
#            puts <<-END
#unable to retrieve field names for class #{self.name}, please 
#consider naming all indexed fields in your call to acts_as_ferret!
#            END
#            models.map { |m| m.content_columns.map { |col| col.name } }.flatten
#          end
#      )
#
#    end
 
  end
end


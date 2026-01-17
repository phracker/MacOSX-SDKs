module ActsAsFerret #:nodoc:
  
      # this class is not threadsafe
      class MultiIndex
        
        def initialize(model_classes, options = {})
          @model_classes = model_classes
          # ensure all models indexes exist
          @model_classes.each { |m| m.aaf_index.ensure_index_exists }
          default_fields = @model_classes.inject([]) do |fields, c| 
            fields + [ c.aaf_configuration[:ferret][:default_field] ].flatten
          end
          @options = { 
            :default_field => default_fields
          }.update(options)
        end
        
        def search(query, options={})
          #puts "querystring: #{query.to_s}"
          query = process_query(query)
          #puts "parsed query: #{query.to_s}"
          searcher.search(query, options)
        end

        def search_each(query, options = {}, &block)
          query = process_query(query)
          searcher.search_each(query, options, &block)
        end

        # checks if all our sub-searchers still are up to date
        def latest?
          return false unless @reader
          # segfaults with 0.10.4 --> TODO report as bug @reader.latest?
          @sub_readers.each do |r| 
            return false unless r.latest? 
          end
          true
        end
         
        def searcher
          ensure_searcher
          @searcher
        end
        
        def doc(i)
          searcher[i]
        end
        alias :[] :doc
        
        def query_parser
          @query_parser ||= Ferret::QueryParser.new(@options)
        end
        
        def process_query(query)
          query = query_parser.parse(query) if query.is_a?(String)
          return query
        end

        def close
          @searcher.close if @searcher
          @reader.close if @reader
        end

        protected

          def ensure_searcher
            unless latest?
              @sub_readers = @model_classes.map { |clazz| 
                begin
                  reader = Ferret::Index::IndexReader.new(clazz.aaf_configuration[:index_dir])
                rescue Exception
                  raise "error opening #{clazz.aaf_configuration[:index_dir]}: #{$!}"
                end
              }
              close
              @reader = Ferret::Index::IndexReader.new(@sub_readers)
              @searcher = Ferret::Search::Searcher.new(@reader)
            end
          end

      end # of class MultiIndex

end

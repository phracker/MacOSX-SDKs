module ActsAsFerret #:nodoc:

    module MoreLikeThis

      module InstanceMethods

        # returns other instances of this class, which have similar contents
        # like this one. Basically works like this: find out n most interesting
        # (i.e. characteristic) terms from this document, and then build a
        # query from those which is run against the whole index. Which terms
        # are interesting is decided on variour criteria which can be
        # influenced by the given options. 
        #
        # The algorithm used here is a quite straight port of the MoreLikeThis class
        # from Apache Lucene.
        #
        # options are:
        # :field_names : Array of field names to use for similarity search (mandatory)
        # :min_term_freq => 2,  # Ignore terms with less than this frequency in the source doc.
        # :min_doc_freq => 5,   # Ignore words which do not occur in at least this many docs
        # :min_word_length => nil, # Ignore words shorter than this length (longer words tend to 
        #                            be more characteristic for the document they occur in).
        # :max_word_length => nil, # Ignore words if greater than this len.
        # :max_query_terms => 25,  # maximum number of terms in the query built
        # :max_num_tokens => 5000, # maximum number of tokens to examine in a single field
        # :boost => false,         # when true, a boost according to the relative score of 
        #                            a term is applied to this Term's TermQuery.
        # :similarity => 'DefaultAAFSimilarity'   # the similarity implementation to use (the default 
        #                                           equals Ferret's internal similarity implementation)
        # :analyzer => 'Ferret::Analysis::StandardAnalyzer' # class name of the analyzer to use
        # :append_to_query => nil # proc taking a query object as argument, which will be called after generating the query. can be used to further manipulate the query used to find related documents, i.e. to constrain the search to a given class in single table inheritance scenarios
        # ferret_options : Ferret options handed over to find_by_contents (i.e. for limits and sorting)
        # ar_options : options handed over to find_by_contents for AR scoping
        def more_like_this(options = {}, ferret_options = {}, ar_options = {})
          options = {
            :field_names => nil,  # Default field names
            :min_term_freq => 2,  # Ignore terms with less than this frequency in the source doc.
            :min_doc_freq => 5,   # Ignore words which do not occur in at least this many docs
            :min_word_length => 0, # Ignore words if less than this len. Default is not to ignore any words.
            :max_word_length => 0, # Ignore words if greater than this len. Default is not to ignore any words.
            :max_query_terms => 25,  # maximum number of terms in the query built
            :max_num_tokens => 5000, # maximum number of tokens to analyze when analyzing contents
            :boost => false,      
            :similarity => 'ActsAsFerret::MoreLikeThis::DefaultAAFSimilarity',  # class name of the similarity implementation to use
            :analyzer => 'Ferret::Analysis::StandardAnalyzer', # class name of the analyzer to use
            :append_to_query => nil,
            :base_class => self.class # base class to use for querying, useful in STI scenarios where BaseClass.find_by_contents can be used to retrieve results from other classes, too
          }.update(options)
          #index.search_each('id:*') do |doc, score|
          #  puts "#{doc} == #{index[doc][:description]}"
          #end
          clazz = options[:base_class]
          options[:base_class] = clazz.name
          query = clazz.aaf_index.build_more_like_this_query(self.id, self.class.name, options)
          options[:append_to_query].call(query) if options[:append_to_query]
          clazz.find_by_contents(query, ferret_options, ar_options)
        end

      end

      module IndexMethods

        # TODO to allow morelikethis for unsaved records, we have to give the
        # unsaved record's data to this method. check how this will work out
        # via drb...
        def build_more_like_this_query(id, class_name, options)
          [:similarity, :analyzer].each { |sym| options[sym] = options[sym].constantize.new }
          ferret_index.synchronize do # avoid that concurrent writes close our reader
            ferret_index.send(:ensure_reader_open)
            reader = ferret_index.send(:reader)
            term_freq_map = retrieve_terms(id, class_name, reader, options)
            priority_queue = create_queue(term_freq_map, reader, options)
            create_query(id, class_name, priority_queue, options)
          end
        end

        protected
        
        def create_query(id, class_name, priority_queue, options={})
          query = Ferret::Search::BooleanQuery.new
          qterms = 0
          best_score = nil
          while(cur = priority_queue.pop)
            term_query = Ferret::Search::TermQuery.new(cur.field, cur.word)
            
            if options[:boost]
              # boost term according to relative score
              # TODO untested
              best_score ||= cur.score
              term_query.boost = cur.score / best_score
            end
            begin
              query.add_query(term_query, :should) 
            rescue Ferret::Search::BooleanQuery::TooManyClauses
              break
            end
            qterms += 1
            break if options[:max_query_terms] > 0 && qterms >= options[:max_query_terms]
          end
          # exclude the original record 
          query.add_query(query_for_record(id, class_name), :must_not)
          return query
        end

        

        # creates a term/term_frequency map for terms from the fields
        # given in options[:field_names]
        def retrieve_terms(id, class_name, reader, options)
          raise "more_like_this atm only works on saved records" if id.nil?
          document_number = document_number(id, class_name) rescue nil
          field_names = options[:field_names]
          max_num_tokens = options[:max_num_tokens]
          term_freq_map = Hash.new(0)
          doc = nil
          record = nil
          field_names.each do |field|
            #puts "field: #{field}"
            term_freq_vector = reader.term_vector(document_number, field) if document_number
            #if false
            if term_freq_vector
              # use stored term vector
              # puts 'using stored term vector'
              term_freq_vector.terms.each do |term|
                term_freq_map[term.text] += term.positions.size unless noise_word?(term.text, options)
              end
            else
              # puts 'no stored term vector'
              # no term vector stored, but we have stored the contents in the index
              # -> extract terms from there
              content = nil
              if document_number
                doc = reader[document_number]
                content = doc[field]
              end
              unless content
                # no term vector, no stored content, so try content from this instance
                record ||= options[:base_class].constantize.find(id)
                content = record.content_for_field_name(field.to_s)
              end
              puts "have doc: #{doc[:id]} with #{field} == #{content}"
              token_count = 0
              
              ts = options[:analyzer].token_stream(field, content)
              while token = ts.next
                break if (token_count+=1) > max_num_tokens
                next if noise_word?(token.text, options)
                term_freq_map[token.text] += 1
              end
            end
          end
          term_freq_map
        end

        # create an ordered(by score) list of word,fieldname,score 
        # structures
        def create_queue(term_freq_map, reader, options)
          pq = Array.new(term_freq_map.size)
          
          similarity = options[:similarity]
          num_docs = reader.num_docs
          term_freq_map.each_pair do |word, tf|
            # filter out words that don't occur enough times in the source
            next if options[:min_term_freq] && tf < options[:min_term_freq]
            
            # go through all the fields and find the largest document frequency
            top_field = options[:field_names].first
            doc_freq = 0
            options[:field_names].each do |field_name| 
              freq = reader.doc_freq(field_name, word)
              if freq > doc_freq 
                top_field = field_name
                doc_freq = freq
              end
            end
            # filter out words that don't occur in enough docs
            next if options[:min_doc_freq] && doc_freq < options[:min_doc_freq]
            next if doc_freq == 0 # index update problem ?
            
            idf = similarity.idf(doc_freq, num_docs)
            score = tf * idf
            pq << FrequencyQueueItem.new(word, top_field, score)
          end
          pq.compact!
          pq.sort! { |a,b| a.score<=>b.score }
          return pq
        end
        
        def noise_word?(text, options)
          len = text.length
          (
            (options[:min_word_length] > 0 && len < options[:min_word_length]) ||
            (options[:max_word_length] > 0 && len > options[:max_word_length]) ||
            (options[:stop_words] && options.include?(text))
          )
        end

      end

      class DefaultAAFSimilarity
        def idf(doc_freq, num_docs)
          return 0.0 if num_docs == 0
          return Math.log(num_docs.to_f/(doc_freq+1)) + 1.0
        end
      end


      class FrequencyQueueItem
        attr_reader :word, :field, :score
        def initialize(word, field, score)
          @word = word; @field = field; @score = score
        end
      end

    end
end


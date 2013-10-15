require 'monitor'

module Ferret::Index
  module SynchroLockMixin
    def synchrolock
      trys = 5
      begin
        synchronize {yield}
      rescue Ferret::Store::Lock::LockError => e
        if (trys -= 1) <= 0
          raise e
        else
          retry
        end
      end
    end
  end
  # This is a simplified interface to the index. See the TUTORIAL for more
  # information on how to use this class.
  class Index
    include MonitorMixin

    include Ferret::Store
    include Ferret::Search

    attr_reader :options

    # If you create an Index without any options, it'll simply create an index
    # in memory. But this class is highly configurable and every option that
    # you can supply to IndexWriter and QueryParser, you can also set here.
    # Please look at the options for the constructors to these classes.
    #
    # === Options
    #
    # See;
    #
    # * QueryParser
    # * IndexWriter
    #
    # default_input_field::   Default: "id". This specifies the default field
    #                         that will be used when you add a simple string
    #                         to the index using #add_document or <<.
    # id_field:               Default: "id". This field is as the field to
    #                         search when doing searches on a term. For
    #                         example, if you do a lookup by term "cat", ie
    #                         index["cat"], this will be the field that is
    #                         searched.
    # key::                   Default: nil. Expert: This should only be used
    #                         if you really know what you are doing. Basically
    #                         you can set a field or an array of fields to be
    #                         the key for the index. So if you add a document
    #                         with a same key as an existing document, the
    #                         existing document will be replaced by the new
    #                         object.  Using a multiple field key will slow
    #                         down indexing so it should not be done if
    #                         performance is a concern. A single field key (or
    #                         id) should be find however. Also, you must make
    #                         sure that your key/keys are either untokenized
    #                         or that they are not broken up by the analyzer.
    # auto_flush::            Default: false. Set this option to true if you
    #                         want the index automatically flushed every time
    #                         you do a write (includes delete) to the index.
    #                         This is useful if you have multiple processes
    #                         accessing the index and you don't want lock
    #                         errors. Setting :auto_flush to true has a huge
    #                         performance impact so don't use it if you are
    #                         concerned about performance. In that case you
    #                         should think about setting up a DRb indexing
    #                         service.
    # lock_retry_time::       Default: 2 seconds. This parameter specifies how
    #                         long to wait before retrying to obtain the
    #                         commit lock when detecting if the IndexReader is
    #                         at the latest version.
    # close_dir::             Default: false.  If you explicitly pass a
    #                         Directory object to this class and you want
    #                         Index to close it when it is closed itself then
    #                         set this to true.
    # 
    # Some examples;
    #
    #   index = Index::Index.new(:analyzer => WhiteSpaceAnalyzer.new())
    #
    #   index = Index::Index.new(:path => '/path/to/index',
    #                            :create_if_missing => false,
    #                            :auto_flush => true)
    #
    #   index = Index::Index.new(:dir => directory,
    #                            :default_slop => 2,
    #                            :handle_parse_errors => false)
    #
    # You can also pass a block if you like. The index will be yielded and
    # closed at the index of the box. For example;
    #
    #   Ferret::I.new() do |index|
    #     # do stuff with index. Most of your actions will be cached.
    #   end
    def initialize(options = {}, &block)
      super()

      if options[:key]
        @key = options[:key]
        if @key.is_a?(Array)
          @key.flatten.map {|k| k.to_s.intern}
        end
      else
        @key = nil
      end

      if (fi = options[:field_infos]).is_a?(String)
        options[:field_infos] = FieldInfos.load(fi)
      end

      @close_dir = options[:close_dir]
      if options[:dir].is_a?(String)
        options[:path] = options[:dir]
      end
      if options[:path]
        @close_dir = true
        begin
          @dir = FSDirectory.new(options[:path], options[:create])
        rescue IOError => io
          @dir = FSDirectory.new(options[:path],
                                 options[:create_if_missing] != false)
        end
      elsif options[:dir]
        @dir = options[:dir]
      else
        options[:create] = true # this should always be true for a new RAMDir
        @close_dir = true
        @dir = RAMDirectory.new
      end

      @dir.extend(MonitorMixin).extend(SynchroLockMixin)
      options[:dir] = @dir
      options[:lock_retry_time]||= 2
      @options = options
      if (!@dir.exists?("segments")) || options[:create]
        IndexWriter.new(options).close
      end
      options[:analyzer]||= Ferret::Analysis::StandardAnalyzer.new

      @searcher = nil
      @writer = nil
      @reader = nil

      @options.delete(:create) # only create the first time if at all
      @auto_flush = @options[:auto_flush] || false
      if (@options[:id_field].nil? and @key.is_a?(Symbol))
        @id_field = @key
      else
        @id_field = @options[:id_field] || :id
      end
      @default_field = (@options[:default_field]||= :*)
      @default_input_field = options[:default_input_field] || @id_field

      if @default_input_field.respond_to?(:intern)
        @default_input_field = @default_input_field.intern
      end
      @open = true
      @qp = nil
      if block
        yield self
        self.close
      end
    end

    # Returns an array of strings with the matches highlighted. The +query+ can
    # either a query String or a Ferret::Search::Query object. The doc_id is
    # the id of the document you want to highlight (usually returned by the
    # search methods). There are also a number of options you can pass;
    #
    # === Options
    #
    # field::            Default: @options[:default_field]. The default_field
    #                    is the field that is usually highlighted but you can
    #                    specify which field you want to highlight here. If
    #                    you want to highlight multiple fields then you will
    #                    need to call this method multiple times.
    # excerpt_length::   Default: 150. Length of excerpt to show. Highlighted
    #                    terms will be in the centre of the excerpt. Set to
    #                    :all to highlight the entire field.
    # num_excerpts::     Default: 2. Number of excerpts to return.
    # pre_tag::          Default: "<b>". Tag to place to the left of the
    #                    match.  You'll probably want to change this to a
    #                    "<span>" tag with a class. Try "\033[36m" for use in
    #                    a terminal.
    # post_tag::         Default: "</b>". This tag should close the
    #                    +:pre_tag+. Try tag "\033[m" in the terminal.
    # ellipsis::         Default: "...". This is the string that is appended
    #                    at the beginning and end of excerpts (unless the
    #                    excerpt hits the start or end of the field.
    #                    Alternatively you may want to use the HTML entity
    #                    &#8230; or the UTF-8 string "\342\200\246".
    def highlight(query, doc_id, options = {})
      @dir.synchronize do
        ensure_searcher_open()
        @searcher.highlight(do_process_query(query),
                            doc_id,
                            options[:field]||@options[:default_field],
                            options)
      end
    end

    # Closes this index by closing its associated reader and writer objects.
    def close
      @dir.synchronize do
        if not @open
          raise(StandardError, "tried to close an already closed directory")
        end
        @searcher.close() if @searcher
        @reader.close() if @reader
        @writer.close() if @writer
        @dir.close() if @close_dir

        @open = false
      end
    end

    # Get the reader for this index.
    # NOTE:: This will close the writer from this index.
    def reader
      ensure_reader_open()
      return @reader
    end

    # Get the searcher for this index.
    # NOTE:: This will close the writer from this index.
    def searcher
      ensure_searcher_open()
      return @searcher
    end

    # Get the writer for this index.
    # NOTE:: This will close the reader from this index.
    def writer
      ensure_writer_open()
      return @writer
    end

    # Adds a document to this index, using the provided analyzer instead of
    # the local analyzer if provided.  If the document contains more than
    # IndexWriter::MAX_FIELD_LENGTH terms for a given field, the remainder are
    # discarded.
    #
    # There are three ways to add a document to the index. 
    # To add a document you can simply add a string or an array of strings.
    # This will store all the strings in the "" (ie empty string) field
    # (unless you specify the default_field when you create the index).
    #
    #   index << "This is a new document to be indexed"
    #   index << ["And here", "is another", "new document", "to be indexed"]
    # 
    # But these are pretty simple documents. If this is all you want to index
    # you could probably just use SimpleSearch. So let's give our documents
    # some fields;
    # 
    #   index << {:title => "Programming Ruby", :content => "blah blah blah"}
    #   index << {:title => "Programming Ruby", :content => "yada yada yada"}
    # 
    # Or if you are indexing data stored in a database, you'll probably want
    # to store the id;
    # 
    #   index << {:id => row.id, :title => row.title, :date => row.date}
    # 
    # See FieldInfos for more information on how to set field properties.
    def add_document(doc, analyzer = nil)
      @dir.synchrolock do
        ensure_writer_open()
        if doc.is_a?(String) or doc.is_a?(Array)
          doc = {@default_input_field => doc}
        end

        # delete existing documents with the same key
        if @key
          if @key.is_a?(Array)
            query = @key.inject(BooleanQuery.new()) do |bq, field|
              bq.add_query(TermQuery.new(field, doc[field].to_s), :must)
              bq
            end
            query_delete(query)
          else
            id = doc[@key].to_s
            if id
              ensure_writer_open()
              @writer.delete(@key, id)
              @writer.commit
            end
          end
        end
        ensure_writer_open()

        if analyzer
          old_analyzer = @writer.analyzer
          @writer.analyzer = analyzer
          @writer.add_document(doc)
          @writer.analyzer = old_analyzer
        else
          @writer.add_document(doc)
        end

        flush() if @auto_flush
      end
    end
    alias :<< :add_document

    # Run a query through the Searcher on the index. A TopDocs object is
    # returned with the relevant results. The +query+ is a built in Query
    # object or a query string that can be parsed by the Ferret::QueryParser.
    # Here are the options;
    #
    # === Options
    #
    # offset::      Default: 0. The offset of the start of the section of the
    #               result-set to return. This is used for paging through
    #               results. Let's say you have a page size of 10. If you
    #               don't find the result you want among the first 10 results
    #               then set +:offset+ to 10 and look at the next 10 results,
    #               then 20 and so on.
    # limit::       Default: 10. This is the number of results you want
    #               returned, also called the page size. Set +:limit+ to
    #               +:all+ to return all results
    # sort::        A Sort object or sort string describing how the field
    #               should be sorted. A sort string is made up of field names
    #               which cannot contain spaces and the word "DESC" if you
    #               want the field reversed, all separated by commas. For
    #               example; "rating DESC, author, title". Note that Ferret
    #               will try to determine a field's type by looking at the
    #               first term in the index and seeing if it can be parsed as
    #               an integer or a float. Keep this in mind as you may need
    #               to specify a fields type to sort it correctly. For more
    #               on this, see the documentation for SortField
    # filter::      a Filter object to filter the search results with
    # filter_proc:: a filter Proc is a Proc which takes the doc_id, the score
    #               and the Searcher object as its parameters and returns a
    #               Boolean value specifying whether the result should be
    #               included in the result set.
    def search(query, options = {})
      @dir.synchronize do
        return do_search(query, options)
      end
    end

    # Run a query through the Searcher on the index. A TopDocs object is
    # returned with the relevant results. The +query+ is a Query object or a
    # query string that can be validly parsed by the Ferret::QueryParser. The
    # Searcher#search_each method yields the internal document id (used to
    # reference documents in the Searcher object like this;
    # +searcher[doc_id]+) and the search score for that document. It is
    # possible for the score to be greater than 1.0 for some queries and
    # taking boosts into account. This method will also normalize scores to
    # the range 0.0..1.0 when the max-score is greater than 1.0. Here are the
    # options;
    #
    # === Options
    #
    # offset::      Default: 0. The offset of the start of the section of the
    #               result-set to return. This is used for paging through
    #               results. Let's say you have a page size of 10. If you
    #               don't find the result you want among the first 10 results
    #               then set +:offset+ to 10 and look at the next 10 results,
    #               then 20 and so on.
    # limit::       Default: 10. This is the number of results you want
    #               returned, also called the page size. Set +:limit+ to
    #               +:all+ to return all results
    # sort::        A Sort object or sort string describing how the field
    #               should be sorted. A sort string is made up of field names
    #               which cannot contain spaces and the word "DESC" if you
    #               want the field reversed, all separated by commas. For
    #               example; "rating DESC, author, title". Note that Ferret
    #               will try to determine a field's type by looking at the
    #               first term in the index and seeing if it can be parsed as
    #               an integer or a float. Keep this in mind as you may need
    #               to specify a fields type to sort it correctly. For more
    #               on this, see the documentation for SortField
    # filter::      a Filter object to filter the search results with
    # filter_proc:: a filter Proc is a Proc which takes the doc_id, the score
    #               and the Searcher object as its parameters and returns a
    #               Boolean value specifying whether the result should be
    #               included in the result set.
    # 
    # returns:: The total number of hits.
    #
    # === Example
    # eg.
    #   index.search_each(query, options = {}) do |doc, score|
    #     puts "hit document number #{doc} with a score of #{score}"
    #   end
    #
    def search_each(query, options = {}) # :yield: doc, score
      @dir.synchronize do
        ensure_searcher_open()
        query = do_process_query(query)

        @searcher.search_each(query, options) do |doc, score|
          yield doc, score
        end
      end
    end

    # Retrieves a document/documents from the index. The method for retrieval
    # depends on the type of the argument passed.
    #
    # If +arg+ is an Integer then return the document based on the internal
    # document number.
    #
    # If +arg+ is a Range, then return the documents within the range based on
    # internal document number.
    #
    # If +arg+ is a String then search for the first document with +arg+ in
    # the +id+ field. The +id+ field is either :id or whatever you set
    # :id_field parameter to when you create the Index object.
    def doc(*arg)
      @dir.synchronize do
        id = arg[0]
        if id.kind_of?(String) or id.kind_of?(Symbol)
          ensure_reader_open()
          term_doc_enum = @reader.term_docs_for(@id_field, id.to_s)
          return term_doc_enum.next? ? @reader[term_doc_enum.doc] : nil
        else
          ensure_reader_open(false)
          return @reader[*arg]
        end
      end
    end
    alias :[] :doc

    # Deletes a document/documents from the index. The method for determining
    # the document to delete depends on the type of the argument passed.
    #
    # If +arg+ is an Integer then delete the document based on the internal
    # document number. Will raise an error if the document does not exist.
    #
    # If +arg+ is a String then search for the documents with +arg+ in the
    # +id+ field. The +id+ field is either :id or whatever you set :id_field
    # parameter to when you create the Index object. Will fail quietly if the
    # no document exists.
    def delete(arg)
      @dir.synchrolock do
        ensure_writer_open()
        if arg.is_a?(String) or arg.is_a?(Symbol)
          ensure_writer_open()
          @writer.delete(@id_field, arg.to_s)
        elsif arg.is_a?(Integer)
          ensure_reader_open()
          cnt = @reader.delete(arg)
        else
          raise ArgumentError, "Cannot delete for arg of type #{arg.class}"
        end
        flush() if @auto_flush
      end
      return self
    end

    # Delete all documents returned by the query.
    # 
    # query:: The query to find documents you wish to delete. Can either be a
    #         string (in which case it is parsed by the standard query parser)
    #         or an actual query object.
    def query_delete(query)
      @dir.synchrolock do
        ensure_writer_open()
        ensure_searcher_open()
        query = do_process_query(query)
        @searcher.search_each(query, :limit => :all) do |doc, score|
          @reader.delete(doc)
        end
        flush() if @auto_flush
      end
    end

    # Returns true if document +n+ has been deleted 
    def deleted?(n)
      @dir.synchronize do 
        ensure_reader_open()
        return @reader.deleted?(n) 
      end
    end

    # Update the document referenced by the document number +id+ if +id+ is an
    # integer or all of the documents which have the term +id+ if +id+ is a
    # term..
    #
    # id::      The number of the document to update. Can also be a string
    #           representing the value in the +id+ field. Also consider using
    #           the :key attribute.
    # new_doc:: The document to replace the old document with
    def update(id, new_doc)
      @dir.synchrolock do
        ensure_writer_open()
        delete(id)
        if id.is_a?(String) or id.is_a?(Symbol)
          @writer.commit
        else
          ensure_writer_open()
        end
        @writer << new_doc
        flush() if @auto_flush
      end
    end

    # Update all the documents returned by the query.
    #
    # query::   The query to find documents you wish to update. Can either be
    #           a string (in which case it is parsed by the standard query
    #           parser) or an actual query object.
    # new_val:: The values we are updating. This can be a string in which case
    #           the default field is updated, or it can be a hash, in which
    #           case, all fields in the hash are merged into the old hash.
    #           That is, the old fields are replaced by values in the new hash
    #           if they exist.
    #
    # === Example
    #
    #   index << {:id => "26", :title => "Babylon", :artist => "David Grey"}
    #   index << {:id => "29", :title => "My Oh My", :artist => "David Grey"}
    #
    #   # correct 
    #   index.query_update('artist:"David Grey"', {:artist => "David Gray"})
    #
    #   index["26"]
    #     #=> {:id => "26", :title => "Babylon", :artist => "David Gray"}
    #   index["28"]
    #     #=> {:id => "28", :title => "My Oh My", :artist => "David Gray"}
    #
    def query_update(query, new_val)
      @dir.synchrolock do
        ensure_writer_open()
        ensure_searcher_open()
        docs_to_add = []
        query = do_process_query(query)
        @searcher.search_each(query) do |id, score|
          document = @searcher[id].load
          if new_val.is_a?(Hash)
            document.merge!(new_val)
          else new_val.is_a?(String) or new_val.is_a?(Symbol)
            document[@default_input_field] = new_val.to_s
          end
          docs_to_add << document
          @reader.delete(id)
        end
        ensure_writer_open()
        docs_to_add.each {|doc| @writer << doc }
        flush() if @auto_flush
      end
    end

    # Returns true if any documents have been deleted since the index was last
    # flushed.
    def has_deletions?()
      @dir.synchronize do
        ensure_reader_open()
        return @reader.has_deletions?
      end
    end
    
    # Flushes all writes to the index. This will not optimize the index but it
    # will make sure that all writes are written to it.
    #
    # NOTE: this is not necessary if you are only using this class. All writes
    # will automatically flush when you perform an operation that reads the
    # index.
    def flush()
      @dir.synchronize do
        if @reader
          if @searcher
            @searcher.close
            @searcher = nil
          end
          @reader.commit
        elsif @writer
          @writer.commit
        end
      end
    end
    alias :commit :flush

    # optimizes the index. This should only be called when the index will no
    # longer be updated very often, but will be read a lot.
    def optimize()
      @dir.synchrolock do
        ensure_writer_open()
        @writer.optimize()
        @writer.close()
        @writer = nil
      end
    end

    # returns the number of documents in the index
    def size()
      @dir.synchronize do
        ensure_reader_open()
        return @reader.num_docs()
      end
    end

    # Merges all segments from an index or an array of indexes into this
    # index. You can pass a single Index::Index, Index::Reader,
    # Store::Directory or an array of any single one of these.
    #
    # This may be used to parallelize batch indexing. A large document
    # collection can be broken into sub-collections. Each sub-collection can
    # be indexed in parallel, on a different thread, process or machine and
    # perhaps all in memory. The complete index can then be created by
    # merging sub-collection indexes with this method.
    #
    # After this completes, the index is optimized.
    def add_indexes(indexes)
      @dir.synchrolock do
        ensure_writer_open()
        indexes = [indexes].flatten   # make sure we have an array
        return if indexes.size == 0 # nothing to do
        if indexes[0].is_a?(Index)
          indexes.delete(self) # don't merge with self
          indexes = indexes.map {|index| index.reader }
        elsif indexes[0].is_a?(Ferret::Store::Directory)
          indexes.delete(@dir) # don't merge with self
          indexes = indexes.map {|dir| IndexReader.new(dir) }
        elsif indexes[0].is_a?(IndexReader)
          indexes.delete(@reader) # don't merge with self
        else
          raise ArgumentError, "Unknown index type when trying to merge indexes"
        end
        ensure_writer_open
        @writer.add_readers(indexes)
      end
    end

    # This is a simple utility method for saving an in memory or RAM index to
    # the file system. The same thing can be achieved by using the
    # Index::Index#add_indexes method and you will have more options when
    # creating the new index, however this is a simple way to turn a RAM index
    # into a file system index.
    #
    # directory:: This can either be a Store::Directory object or a String
    #             representing the path to the directory where you would
    #             like to store the index.
    #
    # create::    True if you'd like to create the directory if it doesn't
    #             exist or copy over an existing directory. False if you'd
    #             like to merge with the existing directory. This defaults to
    #             false.
    def persist(directory, create = true)
      synchronize do
        close_all()
        old_dir = @dir
        if directory.is_a?(String)
          @dir = FSDirectory.new(directory, create)
        elsif directory.is_a?(Ferret::Store::Directory)
          @dir = directory
        end
        @dir.extend(MonitorMixin).extend(SynchroLockMixin)
        @options[:dir] = @dir
        @options[:create_if_missing] = true
        add_indexes([old_dir])
      end
    end

    def to_s
      buf = ""
      (0...(size)).each do |i|
        buf << self[i].to_s + "\n" if not deleted?(i)
      end
      buf
    end

    # Returns an Explanation that describes how +doc+ scored against
    # +query+.
    # 
    # This is intended to be used in developing Similarity implementations,
    # and, for good performance, should not be displayed with every hit.
    # Computing an explanation is as expensive as executing the query over the
    # entire index.
    def explain(query, doc)
      @dir.synchronize do
        ensure_searcher_open()
        query = do_process_query(query)

        return @searcher.explain(query, doc)
      end
    end

    # Turn a query string into a Query object with the Index's QueryParser
    def process_query(query)
      @dir.synchronize do
        ensure_searcher_open()
        return do_process_query(query)
      end
    end

    # Returns the field_infos object so that you can add new fields to the
    # index.
    def field_infos
      @dir.synchrolock do
        ensure_writer_open()
        return @writer.field_infos
      end
    end


    protected
      def ensure_writer_open()
        raise "tried to use a closed index" if not @open
        return if @writer
        if @reader
          @searcher.close if @searcher
          @reader.close
          @reader = nil
          @searcher = nil
        end
        @writer = IndexWriter.new(@options)
      end

      # returns the new reader if one is opened
      def ensure_reader_open(get_latest = true)
        raise "tried to use a closed index" if not @open
        if @reader
          if get_latest
            latest = false
            begin
              latest = @reader.latest?
            rescue Lock::LockError => le
              sleep(@options[:lock_retry_time]) # sleep for 2 seconds and try again
              latest = @reader.latest?
            end
            if not latest
              @searcher.close if @searcher
              @reader.close
              return @reader = IndexReader.new(@dir)
            end
          end
        else
          if @writer
            @writer.close
            @writer = nil
          end
          return @reader = IndexReader.new(@dir)
        end
        return false
      end

      def ensure_searcher_open()
        raise "tried to use a closed index" if not @open
        if ensure_reader_open() or not @searcher
          @searcher = Searcher.new(@reader)
        end
      end

    private
      def do_process_query(query)
        if query.is_a?(String)
          if @qp.nil?
            @qp = Ferret::QueryParser.new(@options)
          end
          # we need to set this every time, in case a new field has been added
          @qp.fields =
              @reader.fields unless options[:all_fields] || options[:fields]
          @qp.tokenized_fields =
              @reader.tokenized_fields unless options[:tokenized_fields]
          query = @qp.parse(query)
        end
        return query
      end

      def do_search(query, options)
        ensure_searcher_open()
        query = do_process_query(query)

        return @searcher.search(query, options)
      end

      def close_all()
        @dir.synchronize do
          @searcher.close if @searcher
          @reader.close if @reader
          @writer.close if @writer
          @reader = nil
          @searcher = nil
          @writer = nil
        end
      end
  end
end

module Ferret
  I = Index::Index
end

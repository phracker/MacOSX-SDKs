module ActsAsFerret #:nodoc:

  module InstanceMethods
    include ResultAttributes

    # Returns an array of strings with the matches highlighted. The +query+ can
    # either be a String or a Ferret::Search::Query object.
    # 
    # === Options
    #
    # field::            field to take the content from. This field has 
    #                    to have it's content stored in the index 
    #                    (:store => :yes in your call to aaf). If not
    #                    given, all stored fields are searched, and the
    #                    highlighted content found in all of them is returned.
    #                    set :highlight => :no in the field options to
    #                    avoid highlighting of contents from a :stored field.
    # excerpt_length::   Default: 150. Length of excerpt to show. Highlighted
    #                    terms will be in the centre of the excerpt.
    # num_excerpts::     Default: 2. Number of excerpts to return.
    # pre_tag::          Default: "<em>". Tag to place to the left of the
    #                    match.  
    # post_tag::         Default: "</em>". This tag should close the
    #                    +:pre_tag+.
    # ellipsis::         Default: "...". This is the string that is appended
    #                    at the beginning and end of excerpts (unless the
    #                    excerpt hits the start or end of the field. You'll
    #                    probably want to change this so a Unicode elipsis
    #                    character.
    def highlight(query, options = {})
      self.class.aaf_index.highlight(id, self.class.name, query, options)
    end
    
    # re-eneable ferret indexing after a call to #disable_ferret
    def ferret_enable; @ferret_disabled = nil end
    
    # returns true if ferret indexing is enabled
    # the optional parameter will be true if the method is called by rebuild_index, 
    # and false otherwise. I.e. useful to enable a model only for indexing during 
    # scheduled reindex runs.
    def ferret_enabled?(is_rebuild = false); @ferret_disabled.nil? end

    # Disable Ferret for a specified amount of time. ::once will disable
    # Ferret for the next call to #save (this is the default), ::always will 
    # do so for all subsequent calls.
    # To manually trigger reindexing of a record, you can call #ferret_update 
    # directly. 
    #
    # When given a block, this will be executed without any ferret indexing of 
    # this object taking place. The optional argument in this case can be used 
    # to indicate if the object should be indexed after executing the block
    # (::index_when_finished). Automatic Ferret indexing of this object will be 
    # turned on after the block has been executed. If passed ::index_when_true, 
    # the index will only be updated if the block evaluated not to false or nil.
    def disable_ferret(option = :once)
      if block_given?
        @ferret_disabled = :always
        result = yield
        ferret_enable
        ferret_update if option == :index_when_finished || (option == :index_when_true && result)
        result
      elsif [:once, :always].include?(option)
        @ferret_disabled = option
      else
        raise ArgumentError.new("Invalid Argument #{option}")
      end
    end

    # add to index
    def ferret_create
      if ferret_enabled?
        logger.debug "ferret_create/update: #{self.class.name} : #{self.id}"
        self.class.aaf_index << self
      else
        ferret_enable if @ferret_disabled == :once
      end
      true # signal success to AR
    end
    alias :ferret_update :ferret_create
    

    # remove from index
    def ferret_destroy
      logger.debug "ferret_destroy: #{self.class.name} : #{self.id}"
      begin
        self.class.aaf_index.remove self.id, self.class.name
      rescue
        logger.warn("Could not find indexed value for this object: #{$!}\n#{$!.backtrace}")
      end
      true # signal success to AR
    end
    
    # turn this instance into a ferret document (which basically is a hash of
    # fieldname => value pairs)
    def to_doc
      logger.debug "creating doc for class: #{self.class.name}, id: #{self.id}"
      returning doc = Ferret::Document.new do
        # store the id of each item
        doc[:id] = self.id

        # store the class name if configured to do so
        doc[:class_name] = self.class.name if aaf_configuration[:store_class_name]
      
        # iterate through the fields and add them to the document
        aaf_configuration[:ferret_fields].each_pair do |field, config|
          doc[field] = self.send("#{field}_to_ferret") unless config[:ignore]
        end
      end
    end

    def document_number
      self.class.aaf_index.document_number(id, self.class.name)
    end

    def query_for_record
      self.class.aaf_index.query_for_record(id, self.class.name)
    end

    def content_for_field_name(field)
      self[field] || self.instance_variable_get("@#{field.to_s}".to_sym) || self.send(field.to_sym)
    end


  end

end

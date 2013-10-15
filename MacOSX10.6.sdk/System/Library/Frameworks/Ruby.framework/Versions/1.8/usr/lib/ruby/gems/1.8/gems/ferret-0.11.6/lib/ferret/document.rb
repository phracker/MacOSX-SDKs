module Ferret
  # Instead of using documents to add data to an index you can use Hashes and
  # Arrays. The only real benefits of using a Document over a Hash are pretty
  # printing and the boost attribute. You can add the boost attribute to
  # Hashes and arrays using the BoostMixin. For example;
  #
  #    class Hash
  #      include BoostMixin
  #    end
  #
  #    class Array
  #      include BoostMixin
  #    end
  #
  #    class String
  #      include BoostMixin
  #    end
  module BoostMixin
    attr_accessor :boost
  end

  # Documents are the unit of indexing and search.
  #
  # A Document is a set of fields.  Each field has a name and an array of
  # textual values. If you are coming from a Lucene background you should note
  # that Fields don't have any properties except for the boost property. You
  # should use the Ferret::Index::FieldInfos class to set field properties
  # across the whole index instead.
  # 
  # === Boost
  #
  # The boost attribute makes a Document more important in the index. That is,
  # you can increase the score of a match for queries that match a particular
  # document, making it more likely to appear at the top of search results.
  # You may, for example, want to boost products that have a higher user
  # rating so that they are more likely to appear in search results.
  #
  # Note: that fields which are _not_ stored (see Ferret::Index::FieldInfos)
  # are _not_ available in documents retrieved from the index, e.g.
  # Ferret::Search::Searcher#doc or Ferret::Index::IndexReader#doc.
  #
  # Note: that modifying a Document retrieved from the index will not modify
  # the document contained within the index. You need to delete the old
  # version of the document and add the new version of the document.
  class Document < Hash
    include BoostMixin

    # Create a new Document object with a boost. The boost defaults to 1.0.
    def initialize(boost = 1.0)
      @boost = boost
    end

    # Return true if the documents are equal, ie they have the same fields
    def eql?(o)
      return (o.is_a? Document and (o.boost == @boost) and
              (self.keys == o.keys) and (self.values == o.values))
    end
    alias :== :eql?

    # Create a string representation of the document
    def to_s
      buf = ["Document {"]
      self.keys.sort_by {|key| key.to_s}.each do |key|
        val = self[key]
        val_str = if val.instance_of? Array then %{["#{val.join('", "')}"]}
                  elsif val.is_a? Field then val.to_s
                  else %{"#{val.to_s}"}
                  end
        buf << "  :#{key} => #{val_str}"
      end
      buf << ["}#{@boost == 1.0 ? "" : "^" + @boost.to_s}"]
      return buf.join("\n")
    end
  end

  # A Field is a section of a Document. A Field is basically an array with a
  # boost attribute. It also provides pretty printing of the field with the
  # #to_s method.
  #
  # === Boost
  #
  # The boost attribute makes a field more important in the index. That is,
  # you can increase the score of a match for queries that match terms in a
  # boosted field. You may, for example, want to boost a title field so that
  # matches that match in the :title field score more highly than matches that
  # match in the :contents field. 
  #
  # Note: If you'd like to use boosted fields without having to use
  # the Field class you can just include the BoostMixin in the Array class.
  # See BoostMixin.
  class Field < Array
    include BoostMixin

    # Create a new Field object. You can pass data to the field as either a
    # string;
    #
    #    f = Field.new("This is the fields data")
    #
    # or as an array of strings;
    #
    #    f = Field.new(["this", "is", "an", "array", "of", "field", "data"])
    #
    # Of course Fields can also be boosted;
    #
    #    f = Field.new("field data", 1000.0)
    def initialize(data = [], boost = 1.0)
      @boost = boost
      if data.is_a? Array
        data.each {|v| self << v}
      else
        self << data.to_s
      end
    end

    def eql?(o)
      return (o.is_a? Field and (o.boost == @boost) and super(o))
    end
    alias :== :eql?

    def +(o)
      return Field.new(super(o), self.boost)
    end

    def to_s
      buf = %{["#{self.join('", "')}"]}
      buf << "^#@boost" if @boost != 1.0
      return buf
    end
  end
end

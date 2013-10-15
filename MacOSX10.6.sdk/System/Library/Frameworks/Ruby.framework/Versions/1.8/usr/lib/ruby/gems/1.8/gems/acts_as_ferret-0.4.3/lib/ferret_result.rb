module ActsAsFerret

  # mixed into the FerretResult and AR classes calling acts_as_ferret
  module ResultAttributes
    # holds the score this record had when it was found via
    # acts_as_ferret
    attr_accessor :ferret_score

    attr_accessor :ferret_rank
  end

  class FerretResult
    include ResultAttributes
    attr_accessor :id

    def initialize(model, id, score, data = {})
      @model = model.constantize
      @id = id
      @ferret_score = score
      @data = data
    end
    
    def method_missing(method, *args)
      if @ar_record || @data[method].nil?
        ferret_load_record unless @ar_record
        @ar_record.send method, *args
      else
        @data[method]
      end
    end

    def ferret_load_record
      @ar_record = @model.find(id)
    end
  end
end

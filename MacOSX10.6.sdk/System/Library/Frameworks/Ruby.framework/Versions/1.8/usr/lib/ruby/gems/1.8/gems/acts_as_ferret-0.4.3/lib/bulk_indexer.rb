module ActsAsFerret
  class BulkIndexer
    def initialize(args = {})
      @batch_size = args[:batch_size] || 1000
      @logger = args[:logger]
      @model = args[:model]
      @work_done = 0
      @index = args[:index]
      if args[:reindex]
        @reindex = true
        @model_count  = @model.count.to_f
      else
        @model_count = args[:total]
      end
    end

    def index_records(records, offset)
      batch_time = measure_time {
        records.each { |rec| @index << rec.to_doc if rec.ferret_enabled?(true) }
      }.to_f
      @work_done = offset.to_f / @model_count * 100.0 if @model_count > 0
      remaining_time = ( batch_time / @batch_size ) * ( @model_count - offset + @batch_size )
      @logger.info "#{@reindex ? 're' : 'bulk '}index model #{@model.name} : #{'%.2f' % @work_done}% complete : #{'%.2f' % remaining_time} secs to finish"

    end

    def measure_time
      t1 = Time.now
      yield
      Time.now - t1
    end

  end

end

require 'drb'
module ActsAsFerret

  # This index implementation connects to a remote ferret server instance. It
  # basically forwards all calls to the remote server.
  class RemoteIndex < AbstractIndex

    def initialize(config)
      @config = config
      @ferret_config = config[:ferret]
      @server = DRbObject.new(nil, config[:remote])
    end

    def method_missing(method_name, *args)
      args.unshift model_class_name
      @server.send(method_name, *args)
    end

    def find_id_by_contents(q, options = {}, &proc)
      total_hits, results = @server.find_id_by_contents(model_class_name, q, options)
      block_given? ? yield_results(total_hits, results, &proc) : [ total_hits, results ]
    end

    def id_multi_search(query, models, options, &proc)
      total_hits, results = @server.id_multi_search(model_class_name, query, models, options)
      block_given? ? yield_results(total_hits, results, &proc) : [ total_hits, results ]
    end

    # add record to index
    def add(record)
      @server.add record.class.name, record.to_doc
    end
    alias << add

    private

    def yield_results(total_hits, results)
      results.each do |result|
        yield result[:model], result[:id], result[:score], result[:data]
      end
      total_hits
    end

    def model_class_name
      @config[:class_name]
    end

  end

end

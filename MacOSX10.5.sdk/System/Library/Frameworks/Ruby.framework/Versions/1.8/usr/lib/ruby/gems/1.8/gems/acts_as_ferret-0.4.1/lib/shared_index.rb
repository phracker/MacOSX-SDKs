module ActsAsFerret
  
  class SharedIndex < LocalIndex

    # build a ferret query matching only the record with the given id and class
    def query_for_record(id, class_name)
      returning bq = Ferret::Search::BooleanQuery.new do
        bq.add_query(Ferret::Search::TermQuery.new(:id,         id.to_s),    :must)
        bq.add_query(Ferret::Search::TermQuery.new(:class_name, class_name), :must)
      end
    end

  end
end

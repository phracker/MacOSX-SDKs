require 'yaml'

module Ferret::Index
  class FieldInfos
    # Load FieldInfos from a YAML file. The YAML file should look something like
    # this:
    # default:
    #   store: :yes
    #   index: :yes
    #   term_vector: :no
    #
    # fields:
    #   id:
    #     index: :untokenized
    #     term_vector: :no
    # 
    #   title:
    #     boost: 20.0
    #     term_vector: :no
    # 
    #   content:
    #     term_vector: :with_positions_offsets
    #  
    def self.load(yaml_str)
      info = YAML.load(yaml_str)
      convert_strings_to_symbols(info)
      fis = FieldInfos.new(info[:default])
      fields = info[:fields]
      fields.keys.each {|key| fis.add_field(key, fields[key])} if fields
      fis
    end

    private
    def self.convert_strings_to_symbols(hash)
      hash.keys.each do |key|
        convert_strings_to_symbols(hash[key]) if hash[key].is_a?(Hash)
        if key.is_a?(String)
          hash[key.intern] = hash[key]
          hash.delete(key)
        end
      end
    end
  end
end

module RedCloth
  module VERSION
    MAJOR = 4
    MINOR = 1
    TINY  = 1
    RELEASE_CANDIDATE = nil

    STRING = [MAJOR, MINOR, TINY].join('.')
    TAG = "REL_#{[MAJOR, MINOR, TINY, RELEASE_CANDIDATE].compact.join('_')}".upcase.gsub(/\.|-/, '_')
    FULL_VERSION = "#{[MAJOR, MINOR, TINY, RELEASE_CANDIDATE].compact.join('.')}"
    
    class << self
      def to_s
        STRING
      end
      
      def ==(arg)
        STRING == arg
      end
    end
  end
  
  NAME = "RedCloth"
  GEM_NAME = NAME
  URL  = "http://redcloth.org/"

  DESCRIPTION = "#{NAME}-#{VERSION::FULL_VERSION} - Textile parser for Ruby.\n#{URL}"
end
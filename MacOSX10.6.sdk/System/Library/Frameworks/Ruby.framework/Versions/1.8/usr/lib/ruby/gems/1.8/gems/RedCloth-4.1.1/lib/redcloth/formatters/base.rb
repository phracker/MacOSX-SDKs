module RedCloth::Formatters
  module Base
    
    def pba(opts)
      opts.delete(:style) if filter_styles
      opts.delete(:class) if filter_classes
      opts.delete(:id) if filter_ids

      atts = ''
      opts[:"text-align"] = opts.delete(:align)
      opts[:style] += ';' if opts[:style] && (opts[:style][-1..-1] != ';')
      [:float, :"text-align", :"vertical-align"].each do |a|
        opts[:style] = "#{a}:#{opts[a]};#{opts[:style]}" if opts[a]
      end
      [:"padding-right", :"padding-left"].each do |a|
        opts[:style] = "#{a}:#{opts[a]}em;#{opts[:style]}" if opts[a]
      end
      [:style, :class, :lang, :id, :colspan, :rowspan, :title, :start, :align].each do |a|
        atts << " #{a}=\"#{ html_esc(opts[a].to_s, :html_escape_attributes) }\"" if opts[a]
      end
      atts
    end
    
    def ignore(opts)
      opts[:text]
    end
    alias_method :notextile, :ignore
    
    def redcloth_version(opts)
      p(:text => "#{opts[:prefix]}#{RedCloth::VERSION}")
    end

    def inline_redcloth_version(opts)
      RedCloth::VERSION::STRING
    end
    
    [:del_phrase, :sup_phrase, :sub_phrase, :span_phrase].each do |phrase_method|
      method = phrase_method.to_s.split('_')[0]
      define_method(phrase_method) do |opts|
        "#{opts[:beginning_space]}#{self.send(method, opts)}"
      end
    end
    
    def method_missing(method, opts)
      opts[:text] || ""
    end
    
    def before_transform(text)
      
    end
    
    def after_transform(text)
      
    end

  end
end

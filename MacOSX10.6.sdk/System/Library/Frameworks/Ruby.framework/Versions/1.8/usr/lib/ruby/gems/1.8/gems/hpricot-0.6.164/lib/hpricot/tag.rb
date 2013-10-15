module Hpricot
  # :stopdoc:

  class Doc
    attr_accessor :children
    def initialize(children = [], options = {})
      @children = children ? children.each { |c| c.parent = self }  : []
      @options = options
    end
    def output(out, opts = {})
      @children.each do |n|
        n.output(out, opts)
      end
      out
    end
    def make(input = nil, &blk)
      Hpricot.make(input, @options, &blk)
    end
    def altered!; end
  end

  class BaseEle
    attr_accessor :raw_string, :parent
    def html_quote(str)
      "\"" + str.gsub('"', '\\"') + "\""
    end
    def if_output(opts)
      if opts[:preserve] and not @raw_string.nil?
        @raw_string
      else
        yield opts
      end
    end
    def pathname; self.name end
    def altered!
      @raw_string = nil
    end
    def self.alterable(*fields)
      attr_accessor(*fields)
      fields.each do |f|
        define_method("#{f}=") do |v|
          altered!
          instance_variable_set("@#{f}", v)
        end
      end
    end
  end

  class Elem
    attr_accessor :stag, :etag, :children
    def initialize(stag, children=nil, etag=nil)
      @stag, @etag = stag, etag
      @children = children ? children.each { |c| c.parent = self }  : []
    end
    def empty?; @children.empty? end
    [:name, :raw_attributes, :parent, :altered!].each do |m|
      [m, "#{m}="].each { |m2| define_method(m2) { |*a| [@etag, @stag].inject { |_,t| t.send(m2, *a) if t and t.respond_to?(m2) } } }
    end
    def attributes
      if raw_attributes
        raw_attributes.inject({}) do |hsh, (k, v)|
          hsh[k] = Hpricot.uxs(v)
          hsh
        end
      end
    end
    def to_plain_text
      if self.name == 'br'
        "\n"
      elsif self.name == 'p'
        "\n\n" + super + "\n\n"
      elsif self.name == 'a' and self.has_attribute?('href')
        "#{super} [#{self['href']}]"
      elsif self.name == 'img' and self.has_attribute?('src')
        "[img:#{self['src']}]"
      else
        super
      end
    end
    def pathname; self.name end
    def output(out, opts = {})
      if empty? and ElementContent[@stag.name] == :EMPTY
        @stag.output(out, opts.merge(:style => :empty))
      else
        @stag.output(out, opts)
        @children.each { |n| n.output(out, opts) }
        if @etag
          @etag.output(out, opts)
        elsif !opts[:preserve]
          ETag.new(@stag.name).output(out, opts)
        end
      end
      out
    end
  end

  class STag < BaseEle
    def initialize(name, attributes=nil)
      @name = name.to_s
      @raw_attributes = attributes || {}
    end
    alterable :name, :raw_attributes
    def attributes_as_html
      if @raw_attributes
        @raw_attributes.map do |aname, aval|
          " #{aname}" +
            (aval ? "=#{html_quote aval}" : "")
        end.join
      end
    end
    def output(out, opts = {})
      out <<
        if_output(opts) do
          "<#{@name}#{attributes_as_html}" +
            (opts[:style] == :empty ? " /" : "") +
            ">"
        end
    end
  end

  class ETag < BaseEle
    def initialize(qualified_name)
      @name = qualified_name.to_s
    end
    alterable :name
    def output(out, opts = {})
      out <<
        if_output(opts) do
          "</#{@name}>"
        end
    end
  end

  class BogusETag < ETag
    def output(out, opts = {}); out << if_output(opts) { '' }; end
  end

  class Text < BaseEle
    def initialize(text)
      @content = text
    end
    alterable :content
    def pathname; "text()" end
    def to_s
      Hpricot.uxs(@content)
    end
    alias_method :inner_text, :to_s
    alias_method :to_plain_text, :to_s
    def output(out, opts = {})
      out <<
        if_output(opts) do
          @content
        end
    end
  end

  class CData < Text
    alias_method :to_s, :content
    alias_method :to_plain_text, :content
    def output(out, opts = {})
      out <<
        if_output(opts) do
          "<![CDATA[#@content]]>"
        end
    end
  end

  class XMLDecl < BaseEle
    def initialize(version, encoding, standalone)
      @version, @encoding, @standalone = version, encoding, standalone
    end
    alterable :version, :encoding, :standalone
    def pathname; "xmldecl()" end
    def output(out, opts = {})
      out <<
        if_output(opts) do
          "<?xml version=\"#{@version}\"" +
            (@encoding ? " encoding=\"#{encoding}\"" : "") +
            (@standalone != nil ? " standalone=\"#{standalone ? 'yes' : 'no'}\"" : "") +
            "?>"
        end
    end
  end

  class DocType < BaseEle
    def initialize(target, pubid, sysid)
      @target, @public_id, @system_id = target, pubid, sysid
    end
    alterable :target, :public_id, :system_id
    def pathname; "doctype()" end
    def output(out, opts = {})
      out <<
        if_output(opts) do
          "<!DOCTYPE #{@target} " +
            (@public_id ? "PUBLIC \"#{@public_id}\"" : "SYSTEM") +
            (@system_id ? " #{html_quote(@system_id)}" : "") + ">"
        end
    end
  end

  class ProcIns < BaseEle
    def initialize(target, content)
      @target, @content = target, content
    end
    def pathname; "procins()" end
    alterable :target, :content
    def output(out, opts = {})
      out << 
        if_output(opts) do
          "<?#{@target}" +
           (@content ? " #{@content}" : "") +
           "?>"
        end
    end
  end

  class Comment < BaseEle
    def initialize(content)
      @content = content
    end
    def pathname; "comment()" end
    alterable :content
    def output(out, opts = {})
      out <<
        if_output(opts) do
          "<!--#{@content}-->"
        end
    end
  end

  # :startdoc:
end

require 'hpricot/htmlinfo'

def Hpricot(input = nil, opts = {}, &blk)
  Hpricot.parse(input, opts, &blk)
end

module Hpricot
  # Exception class used for any errors related to deficiencies in the system when
  # handling the character encodings of a document.
  class EncodingError < StandardError; end

  # Hpricot.parse parses <i>input</i> and return a document tree.
  # represented by Hpricot::Doc.
  def Hpricot.parse(input = nil, opts = {}, &blk)
    Doc.new(make(input, opts, &blk), opts)
  end

  # Hpricot::XML parses <i>input</i>, disregarding all the HTML rules
  # and returning a document tree.
  def Hpricot.XML(input = nil, opts = {}, &blk)
    opts.merge! :xml => true
    Doc.new(make(input, opts, &blk), opts)
  end

  # :stopdoc:

  def Hpricot.make(input = nil, opts = {}, &blk)
    opts = {:fixup_tags => false}.merge(opts)
    unless input or blk
      raise ArgumentError, "An Hpricot document must be built from an input source (a String) or a block."
    end

    conv = opts[:xml] ? :to_s : :downcase

    fragment =
    if input
      case opts[:encoding]
      when nil
      when 'utf-8'
        unless defined? Encoding::Character::UTF8
          raise EncodingError, "The ruby-character-encodings library could not be found for utf-8 mode."
        end
      else
        raise EncodingError, "No encoding option `#{opts[:encoding]}' is available."
      end

      if opts[:xhtml_strict]
        opts[:fixup_tags] = true
      end

      stack = [[nil, nil, [], [], [], []]]
      Hpricot.scan(input) do |token|
        if stack.last[5] == :CDATA and ![:procins, :comment, :cdata].include?(token[0]) and
            !(token[0] == :etag and token[1].casecmp(stack.last[0]).zero?)
          token[0] = :text
          token[1] = token[3] if token[3]
        end

        if !opts[:xml] and token[0] == :emptytag
          token[1] = token[1].send(conv)
          if ElementContent[token[1].downcase] != :EMPTY
            token[0] = :stag
          end
        end

        # TODO: downcase instead when parsing attributes?
        if !opts[:xml] and token[2].is_a?(Hash)
          token[2] = token[2].inject({}) { |hsh,(k,v)| hsh[k.downcase] = v; hsh }
        end

        case token[0]
        when :stag
          case opts[:encoding] when 'utf-8'
            token.map! { |str| u(str) if str.is_a? String }
          end

          stagname = token[0] = token[1] = token[1].send(conv)
          if ElementContent[stagname] == :EMPTY and !opts[:xml]
            token[0] = :emptytag
            stack.last[2] << token
          else
            unless opts[:xml]
              if opts[:fixup_tags]
                # obey the tag rules set up by the current element
                if ElementContent.has_key? stagname
                  trans = nil
                  (stack.length-1).downto(0) do |i|
                    untags = stack[i][5]
                    break unless untags.include? stagname
                    # puts "** ILLEGAL #{stagname} IN #{stack[i][0]}"
                    trans = i
                  end
                  if trans.to_i > 1
                    eles = stack.slice!(trans..-1)
                    stack.last[2] += eles
                    # puts "** TRANSPLANTED #{stagname} TO #{stack.last[0]}"
                  end
                elsif opts[:xhtml_strict]
                  token[2] = {'class' => stagname}
                  stagname = token[0] = "div"
                end
              end

              # setup tag rules for inside this element
              if ElementContent[stagname] == :CDATA
                uncontainable_tags = :CDATA
              elsif opts[:fixup_tags]
                possible_tags = ElementContent[stagname]
                excluded_tags, included_tags = stack.last[3..4]
                if possible_tags
                  excluded_tags = excluded_tags | (ElementExclusions[stagname] || [])
                  included_tags = included_tags | (ElementInclusions[stagname] || [])
                  containable_tags = (possible_tags | included_tags) - excluded_tags
                  uncontainable_tags = ElementContent.keys - containable_tags
                else
                  # If the tagname is unknown, it is assumed that any element
                  # except excluded can be contained.
                  uncontainable_tags = excluded_tags
                end
              end
            end
            unless opts[:xml]
              case token[2] when Hash
                token[2] = token[2].inject({}) { |hsh,(k,v)| hsh[k.downcase] = v; hsh }
              end
            end
            stack << [stagname, token, [], excluded_tags, included_tags, uncontainable_tags]
          end
        when :etag
          etagname = token[0] = token[1].send(conv)
          if opts[:xhtml_strict] and not ElementContent.has_key? etagname
            etagname = token[0] = "div"
          end
          matched_elem = nil
          (stack.length-1).downto(0) do |i|
            stagname, = stack[i]
            if stagname == etagname
              matched_elem = stack[i]
              stack[i][1] += token
              eles = stack.slice!((i+1)..-1)
              stack.last[2] += eles if eles
              break
            end
          end
          unless matched_elem
            stack.last[2] << [:bogus_etag, token.first, token.last]
          else
            ele = stack.pop
            stack.last[2] << ele
          end
        when :text
          l = stack.last[2].last
          if l and l[0] == :text
            l[1] += token[1]
          else
            stack.last[2] << token
          end
        else
          stack.last[2] << token
        end
      end

      while 1 < stack.length
        ele = stack.pop
        stack.last[2] << ele
      end

      structure_list = stack[0][2]
      structure_list.map {|s| build_node(s, opts) }
    elsif blk
      Hpricot.build(&blk).children
    end
  end

  def Hpricot.build_node(structure, opts = {})
    case structure[0]
    when String
      tagname, _, attrs, sraw, _, _, _, eraw = structure[1]
      children = structure[2]
      etag = eraw && ETag.parse(tagname, eraw)
      stag = STag.parse(tagname, attrs, sraw, true)
      if !children.empty? || etag
        Elem.new(stag,
                  children.map {|c| build_node(c, opts) },
                  etag)
      else
        Elem.new(stag)
      end
    when :text
      Text.parse_pcdata(structure[1])
    when :emptytag
      Elem.new(STag.parse(structure[1], structure[2], structure[3], false))
    when :bogus_etag
      BogusETag.parse(structure[1], structure[2])
    when :xmldecl
      XMLDecl.parse(structure[2], structure[3])
    when :doctype
      if opts[:xhtml_strict]
        structure[2]['system_id'] = "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd"
        structure[2]['public_id'] = "-//W3C//DTD XHTML 1.0 Strict//EN"
      end
      DocType.parse(structure[1], structure[2], structure[3])
    when :procins
      ProcIns.parse(structure[1])
    when :comment
      Comment.parse(structure[1])
    when :cdata_content
      Text.parse_cdata_content(structure[1])
    when :cdata
      Text.parse_cdata_section(structure[1])
    else
      raise "[bug] unknown structure: #{structure.inspect}"
    end
  end

  def STag.parse(qname, attrs, raw_string, is_stag)
    result = STag.new(qname, attrs)
    result.raw_string = raw_string
    result
  end

  def ETag.parse(qname, raw_string)
    result = self.new(qname)
    result.raw_string = raw_string
    result
  end

  def BogusETag.parse(qname, raw_string)
    result = self.new(qname)
    result.raw_string = raw_string
    result
  end

  def Text.parse_pcdata(raw_string)
    result = Text.new(raw_string)
    result
  end

  def Text.parse_cdata_content(raw_string)
    result = CData.new(raw_string)
    result
  end

  def Text.parse_cdata_section(content)
    result = CData.new(content)
    result
  end

  def XMLDecl.parse(attrs, raw_string)
    attrs ||= {}
    version = attrs['version']
    encoding = attrs['encoding']
    case attrs['standalone']
    when 'yes'
      standalone = true
    when 'no'
      standalone = false
    else
      standalone = nil
    end

    result = XMLDecl.new(version, encoding, standalone)
    result.raw_string = raw_string
    result
  end

  def DocType.parse(root_element_name, attrs, raw_string)
    if attrs
      public_identifier = attrs['public_id']
      system_identifier = attrs['system_id']
    end

    root_element_name = root_element_name.downcase

    result = DocType.new(root_element_name, public_identifier, system_identifier)
    result.raw_string = raw_string
    result
  end

  def ProcIns.parse(raw_string)
    _, target, content = *raw_string.match(/\A<\?(\S+)\s+(.+)/m)
    result = ProcIns.new(target, content)
    result
  end

  def Comment.parse(content)
    result = Comment.new(content)
    result
  end

  module Pat
    NameChar = /[-A-Za-z0-9._:]/
    Name = /[A-Za-z_:]#{NameChar}*/
    Nmtoken = /#{NameChar}+/
  end

  # :startdoc:
end

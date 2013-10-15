require "openid/htmltokenizer"

def parse_link_attrs(data)
  parser = HTMLTokenizer.new(data)
  in_head = false
  begin
    while el = parser.getTag("head", "link", "body")
      if el.tag_name == "head"
        in_head = true
      elsif el.tag_name == "link"
        continue unless in_head
        yield el.attr_hash
      elsif el.tag_name == "body"
        return
      end
    end
  rescue
    return
  end  
end

            
            

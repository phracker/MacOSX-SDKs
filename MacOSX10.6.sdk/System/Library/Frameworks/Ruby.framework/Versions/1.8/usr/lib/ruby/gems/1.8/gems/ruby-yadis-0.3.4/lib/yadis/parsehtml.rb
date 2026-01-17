require "yadis/htmltokenizer"

def html_yadis_location(html)
  parser = HTMLTokenizer.new(html)

  # to keep track of whether or not we are in the head element
  in_head = false

  begin
    while el = parser.getTag('head', '/head', 'meta', 'body')
      
      # we are leaving head or have reached body, so we bail
      return nil if ['/head', 'body'].member?(el.tag_name)

      # meta needs to be in head, so we mark it
      in_head = true if el.tag_name == 'head'
      continue unless in_head

      if el.tag_name == 'meta' and (equiv = el.attr_hash['http-equiv'])
        if ['x-xrds-location','x-yadis-location'].member?(equiv.downcase)
          return el.attr_hash['content']
        end
      end
      
    end
  rescue
    return nil
  end

end



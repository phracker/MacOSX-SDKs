module RedCloth::Formatters::HTML
  include RedCloth::Formatters::Base
  
  # escapement for regular HTML (not in PRE tag)
  def escape(text)
    html_esc(text)
  end

  # escapement for HTML in a PRE tag
  def escape_pre(text)
    html_esc(text, :html_escape_preformatted)
  end
  
  # escaping for HTML attributes
  def escape_attribute(text)
    html_esc(text, :html_escape_attributes)
  end
  
  def after_transform(text)
    text.chomp!
  end
    
  [:h1, :h2, :h3, :h4, :h5, :h6, :p, :pre, :div].each do |m|
    define_method(m) do |opts|
      "<#{m}#{pba(opts)}>#{opts[:text]}</#{m}>\n"
    end
  end
  
  [:strong, :code, :em, :i, :b, :ins, :sup, :sub, :span, :cite].each do |m|
    define_method(m) do |opts|
      opts[:block] = true
      "<#{m}#{pba(opts)}>#{opts[:text]}</#{m}>"
    end
  end
  
  def hr(opts)
    "<hr />\n"
  end
  
  def acronym(opts)
    opts[:block] = true
    "<acronym#{pba(opts)}>#{caps(:text => opts[:text])}</acronym>"
  end
  
  def caps(opts)
    if no_span_caps
      opts[:text]
    else
      opts[:class] = 'caps'
      span(opts)
    end
  end
  
  def del(opts)
    opts[:block] = true
    "<del#{pba(opts)}>#{opts[:text]}</del>"
  end
  
  [:ol, :ul].each do |m|
    define_method("#{m}_open") do |opts|
      opts[:block] = true
      "#{"\n" if opts[:nest] > 1}#{"\t" * (opts[:nest] - 1)}<#{m}#{pba(opts)}>\n"
    end
    define_method("#{m}_close") do |opts|
      "#{li_close}#{"\t" * (opts[:nest] - 1)}</#{m}>#{"\n" if opts[:nest] <= 1}"
    end
  end
  
  def li_open(opts)
    "#{li_close unless opts.delete(:first)}#{"\t" * opts[:nest]}<li#{pba(opts)}>#{opts[:text]}"
  end
  
  def li_close(opts=nil)
    "</li>\n"
  end
  
  def dl_open(opts)
    opts[:block] = true
    "<dl#{pba(opts)}>\n"
  end
  
  def dl_close(opts=nil)
    "</dl>\n"
  end
  
  [:dt, :dd].each do |m|
    define_method(m) do |opts|
      "\t<#{m}#{pba(opts)}>#{opts[:text]}</#{m}>\n"
    end
  end
  
  def td(opts)
    tdtype = opts[:th] ? 'th' : 'td'
    "\t\t<#{tdtype}#{pba(opts)}>#{opts[:text]}</#{tdtype}>\n"
  end
  
  def tr_open(opts)
    "\t<tr#{pba(opts)}>\n"
  end
  
  def tr_close(opts)
    "\t</tr>\n"
  end
  
  def table_open(opts)
    "<table#{pba(opts)}>\n"
  end
  
  def table_close(opts)
    "</table>\n"
  end
  
  def bc_open(opts)
    opts[:block] = true
    "<pre#{pba(opts)}>"
  end
  
  def bc_close(opts)
    "</pre>\n"
  end
  
  def bq_open(opts)
    opts[:block] = true
    cite = opts[:cite] ? " cite=\"#{ escape_attribute opts[:cite] }\"" : ''
    "<blockquote#{cite}#{pba(opts)}>\n"
  end
  
  def bq_close(opts)
    "</blockquote>\n"
  end
  
  LINK_TEXT_WITH_TITLE_RE = /
          ([^"]+?)         # $text
          \s?
          \(([^)]+?)\)     # $title
          $
      /x
  def link(opts)
    if opts[:name] =~ LINK_TEXT_WITH_TITLE_RE
      md = LINK_TEXT_WITH_TITLE_RE.match(opts[:name])
      opts[:name] = md[1]
      opts[:title] = md[2]
    end
    "<a href=\"#{escape_attribute opts[:href]}\"#{pba(opts)}>#{opts[:name]}</a>"
  end
  
  def image(opts)
    opts.delete(:align)
    opts[:alt] = opts[:title]
    img = "<img src=\"#{escape_attribute opts[:src]}\"#{pba(opts)} alt=\"#{escape_attribute opts[:alt].to_s}\" />"  
    img = "<a href=\"#{escape_attribute opts[:href]}\">#{img}</a>" if opts[:href]
    img
  end
  
  def footno(opts)
    opts[:id] ||= opts[:text]
    %Q{<sup class="footnote"><a href=\"#fn#{opts[:id]}\">#{opts[:text]}</a></sup>}
  end
  
  def fn(opts)
    no = opts[:id]
    opts[:id] = "fn#{no}"
    opts[:class] = ["footnote", opts[:class]].compact.join(" ")
    "<p#{pba(opts)}><sup>#{no}</sup> #{opts[:text]}</p>\n"
  end
  
  def snip(opts)
    "<pre#{pba(opts)}><code>#{opts[:text]}</code></pre>\n"
  end
  
  def quote1(opts)
    "&#8216;#{opts[:text]}&#8217;"
  end
  
  def quote2(opts)
    "&#8220;#{opts[:text]}&#8221;"
  end
  
  def multi_paragraph_quote(opts)
    "&#8220;#{opts[:text]}"
  end
  
  def ellipsis(opts)
    "#{opts[:text]}&#8230;"
  end
  
  def emdash(opts)
    "&#8212;"
  end
  
  def endash(opts)
    " &#8211; "
  end
  
  def arrow(opts)
    "&#8594;"
  end
  
  def dim(opts)
    opts[:text].gsub!('x', '&#215;')
    opts[:text].gsub!("'", '&#8242;')
    opts[:text].gsub!('"', '&#8243;')
    opts[:text]
  end
  
  def trademark(opts)
    "&#8482;"
  end
  
  def registered(opts)
    "&#174;"
  end
  
  def copyright(opts)
    "&#169;"
  end
  
  def entity(opts)
    "&#{opts[:text]};"
  end
  
  def amp(opts)
    "&amp;"
  end
  
  def gt(opts)
    "&gt;"
  end
  
  def lt(opts)
    "&lt;"
  end
  
  def br(opts)
    if hard_breaks == false
      "\n"
    else
      "<br />\n"
    end
  end
  
  def quot(opts)
    "&quot;"
  end
  
  def squot(opts)
    "&#8217;"
  end
  
  def apos(opts)
    "&#39;"
  end
  
  def html(opts)
    "#{opts[:text]}\n"
  end
  
  def html_block(opts)
    inline_html(:text => "#{opts[:indent_before_start]}#{opts[:start_tag]}#{opts[:indent_after_start]}") + 
    "#{opts[:text]}" +
    inline_html(:text => "#{opts[:indent_before_end]}#{opts[:end_tag]}#{opts[:indent_after_end]}")
  end
  
  def notextile(opts)
    if filter_html
      html_esc(opts[:text], :html_escape_preformatted)
    else
      opts[:text]
    end
  end
  
  def inline_html(opts)
    if filter_html
      html_esc(opts[:text], :html_escape_preformatted)
    else
      "#{opts[:text]}" # nil-safe
    end
  end
  
  def ignored_line(opts)
    opts[:text] + "\n"
  end
  
  def before_transform(text)
    clean_html(text) if sanitize_html
  end
  
  # HTML cleansing stuff
  BASIC_TAGS = {
      'a' => ['href', 'title'],
      'img' => ['src', 'alt', 'title'],
      'br' => [],
      'i' => nil,
      'u' => nil, 
      'b' => nil,
      'pre' => nil,
      'kbd' => nil,
      'code' => ['lang'],
      'cite' => nil,
      'strong' => nil,
      'em' => nil,
      'ins' => nil,
      'sup' => nil,
      'sub' => nil,
      'del' => nil,
      'table' => nil,
      'tr' => nil,
      'td' => ['colspan', 'rowspan'],
      'th' => nil,
      'ol' => ['start'],
      'ul' => nil,
      'li' => nil,
      'p' => nil,
      'h1' => nil,
      'h2' => nil,
      'h3' => nil,
      'h4' => nil,
      'h5' => nil,
      'h6' => nil, 
      'blockquote' => ['cite'],
      'notextile' => nil
  }
  
  # Clean unauthorized tags.
  def clean_html( text, allowed_tags = BASIC_TAGS )
    text.gsub!( /<!\[CDATA\[/, '' )
    text.gsub!( /<(\/*)([A-Za-z]\w*)([^>]*?)(\s?\/?)>/ ) do |m|
      raw = $~
      tag = raw[2].downcase
      if allowed_tags.has_key? tag
        pcs = [tag]
        allowed_tags[tag].each do |prop|
          ['"', "'", ''].each do |q|
            q2 = ( q != '' ? q : '\s' )
            if raw[3] =~ /#{prop}\s*=\s*#{q}([^#{q2}]+)#{q}/i
              attrv = $1
              next if (prop == 'src' or prop == 'href') and not attrv =~ %r{^(http|https|ftp):}
              pcs << "#{prop}=\"#{attrv.gsub('"', '\\"')}\""
              break
            end
          end
        end if allowed_tags[tag]
        "<#{raw[1]}#{pcs.join " "}#{raw[4]}>"
      else # Unauthorized tag
        if block_given?
          yield m
        else
          ''
        end
      end
    end
  end
end

class ERB
  module Util

    #
    # A utility method for transforming Textile in _s_ to HTML.
    # 
    # 	require "erb"
    # 	include ERB::Util
    # 	
    # 	puts textilize("Isn't ERB *great*?")
    # 
    # _Generates_
    # 
    # 	<p>Isn&#8217;t <span class="caps">ERB</span> <strong>great</strong>?</p>
    #
    def textilize( s )
      if s && s.respond_to?(:to_s)
        RedCloth.new( s.to_s ).to_html
      end
    end

    alias t textilize
    module_function :t
    module_function :textilize

  end
end

require 'contest'
require 'tilt'

begin
  require 'bluecloth'

  class BlueClothTemplateTest < Test::Unit::TestCase
    setup do
      Tilt.register('markdown', Tilt::BlueClothTemplate)
      Tilt.register('md', Tilt::BlueClothTemplate)
      Tilt.register('mkd', Tilt::BlueClothTemplate)
    end

    teardown do
      # Need to revert to RDiscount, otherwise the RDiscount test will fail
      Tilt.register('markdown', Tilt::RDiscountTemplate)
      Tilt.register('md', Tilt::RDiscountTemplate)
      Tilt.register('mkd', Tilt::RDiscountTemplate)
    end

    test "registered for '.markdown' files unless RDiscount is loaded" do
      unless defined?(RDiscount)
        assert_equal Tilt::BlueClothTemplate, Tilt['test.markdown']
      end
    end

    test "registered for '.md' files unless RDiscount is loaded" do
      unless defined?(RDiscount)
        assert_equal Tilt::BlueClothTemplate, Tilt['test.md']
      end
    end

    test "registered for '.mkd' files unless RDiscount is loaded" do
      unless defined?(RDiscount)
        assert_equal Tilt::BlueClothTemplate, Tilt['test.mkd']
      end
    end

    test "preparing and evaluating templates on #render" do
      template = Tilt::BlueClothTemplate.new { |t| "# Hello World!" }
      assert_equal "<h1>Hello World!</h1>", template.render
    end

    test "can be rendered more than once" do
      template = Tilt::BlueClothTemplate.new { |t| "# Hello World!" }
      3.times { assert_equal "<h1>Hello World!</h1>", template.render }
    end

    test "smartypants when :smart is set" do
      template = Tilt::BlueClothTemplate.new(:smartypants => true) { |t|
        "OKAY -- 'Smarty Pants'" }
      assert_equal "<p>OKAY &mdash; &lsquo;Smarty Pants&rsquo;</p>",
        template.render
    end

    test "stripping HTML when :filter_html is set" do
      template = Tilt::BlueClothTemplate.new(:escape_html => true) { |t|
        "HELLO <blink>WORLD</blink>" }
      assert_equal "<p>HELLO &lt;blink>WORLD&lt;/blink></p>", template.render
    end
  end
rescue LoadError => boom
  warn "Tilt::BlueClothTemplate (disabled)\n"
end

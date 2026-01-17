require File.expand_path(File.join(File.dirname(__FILE__), 'helper'))

class TestCurbCurlPostfield < Test::Unit::TestCase
  def test_private_new
    assert_raise(NoMethodError) { Curl::PostField.new }  
  end
  
  def test_new_content_01
    pf = Curl::PostField.content('foo', 'bar')
    
    assert_equal 'foo', pf.name
    assert_equal 'bar', pf.content
    assert_nil pf.content_type
    assert_nil pf.local_file
    assert_nil pf.remote_file    
    assert_nil pf.set_content_proc
  end
    
  def test_new_content_02
    pf = Curl::PostField.content('foo', 'bar', 'text/html')
    
    assert_equal 'foo', pf.name
    assert_equal 'bar', pf.content
    assert_equal 'text/html', pf.content_type
    assert_nil pf.local_file
    assert_nil pf.remote_file
    assert_nil pf.set_content_proc    
  end    
  
  def test_new_content_03
    l = lambda { |field| "never gets run" }
    pf = Curl::PostField.content('foo', &l)
    
    assert_equal 'foo', pf.name
    assert_nil pf.content
    assert_nil pf.content_type
    assert_nil pf.local_file
    assert_nil pf.remote_file
    
    # N.B. This doesn't just get the proc, but also removes it.
    assert_equal l, pf.set_content_proc
  end    

  def test_new_content_04
    l = lambda { |field| "never gets run" }
    pf = Curl::PostField.content('foo', 'text/html', &l)
    
    assert_equal 'foo', pf.name
    assert_nil pf.content
    assert_equal 'text/html', pf.content_type
    assert_nil pf.local_file
    assert_nil pf.remote_file
    
    # N.B. This doesn't just get the proc, but also removes it.
    assert_equal l, pf.set_content_proc
  end    


  def test_new_file_01
    pf = Curl::PostField.file('foo', 'localname')
    
    assert_equal 'foo', pf.name
    assert_equal 'localname', pf.local_file
    assert_equal 'localname', pf.remote_file
    assert_nothing_raised { pf.to_s }
    assert_nil pf.content_type
    assert_nil pf.content
    assert_nil pf.set_content_proc
  end
    
  def test_new_file_02
    pf = Curl::PostField.file('foo', 'localname', 'remotename')
    
    assert_equal 'foo', pf.name
    assert_equal 'localname', pf.local_file
    assert_equal 'remotename', pf.remote_file
    assert_nil pf.content_type
    assert_nil pf.content
    assert_nil pf.set_content_proc
  end    
  
  def test_new_file_03
    l = lambda { |field| "never gets run" }
    pf = Curl::PostField.file('foo', 'remotename', &l)
    
    assert_equal 'foo', pf.name
    assert_equal 'remotename', pf.remote_file
    assert_nil pf.local_file
    assert_nil pf.content_type
    assert_nil pf.content
    
    # N.B. This doesn't just get the proc, but also removes it.
    assert_equal l, pf.set_content_proc
  end    

  def test_new_file_04
    assert_raise(ArgumentError) do
      # no local name, no block
      Curl::PostField.file('foo')
    end
    
    assert_raise(ArgumentError) do
      # no remote name with block
      Curl::PostField.file('foo') { |field| "never runs" }
    end
  end
  
  def test_new_file_05
    # local gets ignored when supplying a block, but remote
    # is still set up properly.
    l = lambda { |field| "never runs" }
    pf = Curl::PostField.file('foo', 'local', 'remote', &l)

    assert_equal 'foo', pf.name
    assert_equal 'remote', pf.remote_file
    assert_nil pf.local_file
    assert_nil pf.content_type
    assert_nil pf.content

    assert_equal l, pf.set_content_proc
  end    
  
  def test_to_s_01
    pf = Curl::PostField.content('foo', 'bar')    
    assert_equal "foo=bar", pf.to_s
  end

  def test_to_s_02
    pf = Curl::PostField.content('foo', 'bar ton')    
    assert_equal "foo=bar%20ton", pf.to_s
  end

  def test_to_s_03
    pf = Curl::PostField.content('foo') { |field| field.name.upcase + "BAR" }
    assert_equal "foo=FOOBAR", pf.to_s
  end

  def test_to_s_04
    pf = Curl::PostField.file('foo.file', 'bar.file')
    assert_nothing_raised { pf.to_s }
    #assert_raise(Curl::Err::InvalidPostFieldError) { pf.to_s }
  end
end

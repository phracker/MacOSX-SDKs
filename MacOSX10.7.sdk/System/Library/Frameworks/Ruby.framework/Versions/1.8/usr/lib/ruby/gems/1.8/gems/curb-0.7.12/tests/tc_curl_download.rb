require File.expand_path(File.join(File.dirname(__FILE__), 'helper'))

class TestCurbCurlDownload < Test::Unit::TestCase
  include TestServerMethods 

  def setup
    server_setup
  end
  
  def test_download_url_to_file_via_string
    dl_url = "http://127.0.0.1:9129/ext/curb_easy.c"
    dl_path = File.join(Dir::tmpdir, "dl_url_test.file")

    curb = Curl::Easy.download(dl_url, dl_path)
    assert File.exist?(dl_path)
    assert_equal File.read(File.join(File.dirname(__FILE__), '..','ext','curb_easy.c')), File.read(dl_path)
  ensure
    File.unlink(dl_path) if File.exist?(dl_path)
  end

  def test_download_url_to_file_via_file_io
    dl_url = "http://127.0.0.1:9129/ext/curb_easy.c"
    dl_path = File.join(Dir::tmpdir, "dl_url_test.file")
    io = File.open(dl_path, 'wb')

    curb = Curl::Easy.download(dl_url, io)
    assert io.closed?
    assert File.exist?(dl_path)
    assert_equal File.read(File.join(File.dirname(__FILE__), '..','ext','curb_easy.c')), File.read(dl_path)
  ensure
    File.unlink(dl_path) if File.exist?(dl_path)
  end

  def test_download_url_to_file_via_io
    dl_url = "http://127.0.0.1:9129/ext/curb_easy.c"
    dl_path = File.join(Dir::tmpdir, "dl_url_test.file")
    reader, writer = IO.pipe

    # Write to local file
    fork do
      begin
        writer.close
        File.open(dl_path, 'wb') { |file| file << reader.read }
      ensure
        reader.close rescue IOError # if the stream has already been closed
      end
    end

    # Download remote source
    begin
      reader.close
      curb = Curl::Easy.download(dl_url, writer)
      Process.wait
    ensure
      writer.close rescue IOError # if the stream has already been closed, which occurs in Easy::download
    end

    assert File.exist?(dl_path)
    assert_equal File.read(File.join(File.dirname(__FILE__), '..','ext','curb_easy.c')), File.read(dl_path)
  ensure
    File.unlink(dl_path) if File.exist?(dl_path)
  end

  def test_download_bad_url_gives_404
    dl_url = "http://127.0.0.1:9129/this_file_does_not_exist.html"
    dl_path = File.join(Dir::tmpdir, "dl_url_test.file")

    curb = Curl::Easy.download(dl_url, dl_path)
    assert_equal Curl::Easy, curb.class
    assert_equal 404, curb.response_code
  ensure
    File.unlink(dl_path) if File.exist?(dl_path)
  end

end

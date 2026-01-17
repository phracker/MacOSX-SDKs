require 'fileutils'
include FileUtils

begin
  incflags = File.read('ext/Makefile')[/INCFLAGS\s*=\s*(.*)$/,1]
rescue Errno::ENOENT
  $stderr.puts("No makefile found; run `rake ext/Makefile' first.")
end

pp_srcdir = 'ext'

rm_rf(tmpdir = '.doc-tmp')
mkdir(tmpdir)

begin
  if ARGV.include?('--cpp') 
    begin
      if `cpp --version` =~ /\(GCC\)/
        # gnu cpp
        $stderr.puts "Running GNU cpp over source"
        
        Dir['ext/*.c'].each do |fn|
          system("cpp -DRDOC_NEVER_DEFINED -C #{incflags} -o " +
                 "#{File.join(tmpdir, File.basename(fn))} #{fn}")
        end
        
        pp_srcdir = tmpdir
      else
        $stderr.puts "Not running cpp (non-GNU)"
      end
    rescue
      # no cpp          
      $stderr.puts "No cpp found"
    end
  end
 
  system("rdoc --title='Curb - libcurl bindings for ruby' --main=README #{pp_srcdir}/*.c README LICENSE lib/curb.rb")
ensure
  rm_rf(tmpdir)
end

 

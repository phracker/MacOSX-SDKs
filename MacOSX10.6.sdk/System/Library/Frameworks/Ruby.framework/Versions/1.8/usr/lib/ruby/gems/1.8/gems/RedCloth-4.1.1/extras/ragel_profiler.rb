class RagelProfiler
  MEM_CONVERSION = 1024
  
  COMMANDS =  { :compile => %w(ragel rlgen-cd gcc-4.0 gnumake cc1),
                :test    => %w(ruby) }
                
  FIELDS = %w(compile_time compile_max_rss test_time test_max_rss ext_so_size)
                
  @@results = {}

  def initialize(name)
    @name = name
    @@results[name] = []
  end
  
  def measure(type)
    raise "not a valid type" unless COMMANDS.keys.include?(type)
    regex = COMMANDS[type].map {|c| Regexp.escape(c) }.join("|")
    t = Thread.new do
      Thread.current[:max] = 0
      loop do
        Thread.current[:max] = [run(regex), Thread.current[:max]].max
        sleep 0.5
      end
    end
    begin_time = Time.now
    yield
    total_time = Time.now - begin_time

    t.kill
    store_result(type, "time", total_time)
    store_result(type, "max_rss", t[:max])
  end
  
  def ext_size(ext_so)
    store_result(:ext_so, "size", File.size(ext_so) / MEM_CONVERSION)
  end
  
  def self.results
    out = []
    out << "name\t" + FIELDS.join("\t")
    @@results.each do |name, results|
      out << [name, results ].flatten.join("\t")
    end
    out.join("\n")
  end
  
  private
  
  def store_result(type, metric, value)
    index = FIELDS.index("#{type.to_s}_#{metric}")
    @@results[@name][index] = "%.2f" % value
  end
  
  def run(ps_regex)
    ps_command   = "ps axucww"
    ps_output    = `#{ps_command}`
    fields       = ps_output.to_a.first.downcase.split
    memory_index = fields.index("rss")
    pid_index    = fields.index("pid")
    ppid_index   = fields.index("ppid")
    total        = ps_output.grep(/(#{ps_regex})\s+$/i).map do |com|
                     Float(com.split[memory_index]).abs
                   end.inject(0) { |s,v| s += v }
    if total
      return total/MEM_CONVERSION
    else
      STDERR.puts "Command not found. No processes found matching #{ps_regex}."
    end

  end

end
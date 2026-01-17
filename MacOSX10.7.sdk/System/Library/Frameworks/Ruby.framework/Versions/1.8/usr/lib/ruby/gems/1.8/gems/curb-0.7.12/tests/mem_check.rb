require File.expand_path(File.join(File.dirname(__FILE__), 'helper'))
#require 'rubygems'
#require 'rmem'

#
# Run some tests to measure the memory usage of curb, these tests require fork and ps
#
class TestCurbMemory < Test::Unit::TestCase

  def test_easy_memory
    easy_avg, easy_std = measure_object_memory(Curl::Easy)
    printf "Easy average: %.2f kilobytes +/- %.2f kilobytes\n", easy_avg.to_f, easy_std.to_f

    multi_avg, multi_std = measure_object_memory(Curl::Multi)
    printf "Multi average: %.2f kilobytes +/- %.2f kilobytes\n", multi_avg.to_f, multi_std.to_f

    # now that we have the average size of an easy handle lets see how much a multi request consumes with 10 requests
  end

  def c_avg(report)
    sum = 0
    report.each {|r| sum += r.last }
    (sum.to_f / report.size)
  end

  def c_std(report,avg)
    var = 0
    report.each {|r| var += (r.last-avg)*(r.last-avg) }
    Math.sqrt(var / (report.size-1))
  end

  def measure_object_memory(klass)
    report = []
    200.times do
      res = mem_check do
        obj = klass.new
      end
      report << res
    end
    avg = c_avg(report)
    std = c_std(report,avg)
    [avg,std]
  end

  def mem_check
    # see: http://gist.github.com/264060 for inspiration of ps command line
    rd, wr = IO.pipe
    memory_usage = `ps -o rss= -p #{Process.pid}`.to_i # in kilobytes
    fork do
      before = `ps -o rss= -p #{Process.pid}`.to_i # in kilobytes
      rd.close
      yield
      after = `ps -o rss= -p #{Process.pid}`.to_i # in kilobytes
      wr.write((after - before))
      wr.flush
      wr.close
    end
    wr.close
    total = rd.read.to_i
    rd.close
    Process.wait
    # return the delta and the total
    [memory_usage, total]
  end
end

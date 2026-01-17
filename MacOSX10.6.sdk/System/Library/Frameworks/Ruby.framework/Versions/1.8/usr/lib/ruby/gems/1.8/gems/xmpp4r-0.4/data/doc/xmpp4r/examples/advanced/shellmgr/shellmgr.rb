require 'thread'

class Shell

  PROMPT = "_-=READY=-_"

  def initialize(shell = "/bin/bash", delay = 1, &block)
    @cb = block
    @shell = shell
    @delay = delay
    @parent_to_child_read, @parent_to_child_write = IO.pipe
    @child_to_parent_read, @child_to_parent_write = IO.pipe
    @child_pid = fork do
      @parent_to_child_write.close
      @child_to_parent_read.close
      $stdin.reopen(@parent_to_child_read)
      $stdout.reopen(@child_to_parent_write)
      $stderr.reopen(@child_to_parent_write)
      exec("/bin/bash")
    end
    buffer = ""
    semaphore = Mutex.new
    Thread.new do
      while true
        c = @child_to_parent_read.read(1)
        semaphore.synchronize { buffer += c }
      end
    end
    Thread.new do
      ch = ""
      while true do
        sleep @delay
        semaphore.synchronize {
          if buffer == ch and ch != ""
            @cb.call buffer
            buffer = ""
          end
          ch = buffer
        }
      end
    end
  end

  def puts(str)
    @parent_to_child_write.puts(str)
  end

  def kill
    @child_pid.kill
  end
end

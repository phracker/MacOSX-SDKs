require 'strscan'
require 'net/ssh/transport/ossl/buffer'
require 'net/ssh/util/openssl'

module Net; module SSH
  class KnownHosts
    class <<self
      def canonize(location, port)
        value = location
        value = "[#{value}]:#{port}" if port && port != 22
        value
      end

      def search_for(host)
        search_in(hostfile_locations, host)
      end

      def add(host, key)
        hostfile_locations.each do |file|
          begin
            KnownHosts.new(file).add(host, key)
            return
          rescue SystemCallError
            # try the next hostfile
          end
        end
      end

      def search_in(files, host)
        files.map { |file| KnownHosts.new(file).keys_for(host) }.flatten
      end

      def hostfile_locations
        @hostfile_locations ||= [
          "#{home_directory}/.ssh/known_hosts",
          "#{home_directory}/.ssh/known_hosts2",
          "/etc/ssh/ssh_known_hosts",
          "/etc/ssh/ssh_known_hosts2"
        ]
      end

      def home_directory
        ENV['HOME'] ||
          (ENV['HOMEPATH'] && "#{ENV['HOMEDRIVE']}#{ENV['HOMEPATH']}") ||
          "/"
      end
    end


    attr_reader :source

    def initialize(source)
      @source = source
    end

    def keys_for(host)
      keys = []
      hosts = Array(host)

      File.open(source) do |file|
        scanner = StringScanner.new("")
        file.each_line do |line|
          scanner.string = line

          scanner.skip(/\s*/)
          next if scanner.match?(/$|#/)

          hostlist = scanner.scan(/\S+/)
          next if (hostlist.split(/,/) & hosts).empty?

          scanner.skip(/\s*/)
          type = scanner.scan(/\S+/)
          scanner.skip(/\s*/)
          blob = scanner.rest.unpack("m*").first
          keys << Net::SSH::Transport::OSSL::Buffer.new(blob).read_key
        end
      end

      keys
    rescue SystemCallError
      return []
    end

    def add(host, key)
      dir = File.dirname(source)
      Dir.mkdir(dir, 0700) if !File.exists?(dir)

      File.open(source, "a") do |file|
        buffer = Net::SSH::Transport::OSSL::Buffer.new
        buffer.write_key(key)
        blob = [buffer.to_s].pack("m*").gsub(/\s/, "")
        file.puts "#{Array(host).join(',')} #{key.ssh_type} #{blob}"
      end
    end
  end
end; end
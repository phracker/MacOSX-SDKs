# 1.9.1 fixes


# Make Pathname compatible with 1.8.7 Pathname.
unless Pathname.instance_methods.include?( :=~ )
	class Pathname
		def self::glob( *args ) # :yield: p
			args = args.collect {|p| p.to_s }
			if block_given?
				Dir.glob(*args) {|f| yield self.new(f) }
			else
				Dir.glob(*args).map {|f| self.new(f) }
			end
		end

		def =~( other )
			self.to_s =~ other
		end

		def to_str
			self.to_s
		end
	end
end



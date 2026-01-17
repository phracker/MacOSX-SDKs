#--
# =============================================================================
# Copyright (c) 2004, Jamis Buck (jamis@37signals.com)
# All rights reserved.
#
# This source file is distributed as part of the Needle dependency injection
# library for Ruby. This file (and the library as a whole) may be used only as
# allowed by either the BSD license, or the Ruby license (or, by association
# with the Ruby license, the GPL). See the "doc" subdirectory of the Needle
# distribution for the texts of these licenses.
# -----------------------------------------------------------------------------
# needle website : http://needle.rubyforge.org
# project website: http://rubyforge.org/projects/needle
# =============================================================================
#++

require 'needle/errors'
require 'needle/logger'
require 'thread'

module Needle

  # A factory class that returns Logger instances. Since each registry
  # has its own logger factory, the logger factory must be separately
  # instantiable.
  class LogFactory

    # The default name of the log file to write to.
    DEFAULT_LOG_FILENAME = "./needle.log"

    # The default format of the log messages (see Logger for more info)
    DEFAULT_MESSAGE_FORMAT = "[%-5p] %d -- %C: %m"

    # Translate names of levels to their actual values.
    LEVEL_TRANSLATOR = {
      "DEBUG" => Logger::DEBUG,
      "INFO" => Logger::INFO,
      "WARN" => Logger::WARN,
      "ERROR" => Logger::ERROR,
      "FATAL" => Logger::FATAL,
      "UNKNOWN" => Logger::UNKNOWN
    }

    # The default date format string to use when logging.
    attr_reader :default_date_format

    # The default message format string to use when logging.
    attr_reader :default_message_format

    # The default log level to use for logs that are created.
    attr_reader :default_level

    # The device that logs will write to.
    attr_reader :device

    VALID_OPTIONS = [ :device, :filename, :roll_age, :roll_frequency,
                      :roll_size, :default_date_format,
                      :default_message_format, :default_level, :levels ]

    VALID_LEVEL_OPTIONS = [ :level, :date_format, :message_format ]
                      
    # Create a new LogFactory using the given initialization parameters.
    # The valid options are:
    #
    # * <tt>:device</tt>: the device (pseudo-IO object) to write log
    #   messages to. Either this, or <tt>:filename</tt> must be specified.
    # * <tt>:filename</tt>: the filename of the log to write to.
    # * <tt>:roll_age</tt>: the number of days before the log should be
    #   rolled.
    # * <tt>:roll_frequency</tt>: either 'daily', 'weekly', or 'monthly'.
    # * <tt>:roll_size</tt>: the maximum size of a log file.
    # * <tt>:default_date_format</tt>: the default date format string for
    #   the log.
    # * <tt>:default_message_format</tt>: the default message format string
    #   for  the log.
    # * <tt>:default_level</tt>: the default log level for the log.
    # * <tt>:levels</tt>: a hash of patterns that map to a hash of 'level'
    #   'date_format', and 'message_format' keys, specifying the log level,
    #   date format, and message format for any log whose name matches the key.
    def initialize( opts={} )
      opts = convert_keys_to_symbols( opts )
      bad = opts.keys - VALID_OPTIONS
      raise ArgumentError,
        "invalid option(s) to LogFactory (#{bad.inspect})" unless bad.empty?

      if opts[:device]
        @device = opts[:device]
      else
        filename = opts[:filename] || DEFAULT_LOG_FILENAME
        roll_age = opts[:roll_age ] || opts[:roll_frequency] || 0
        roll_size = opts[:roll_size] || 0
        @device = Logger::LogDevice.new( filename,
          :shift_age=>roll_age, :shift_size=>roll_size )
      end

      @default_date_format = opts[:default_date_format]
      @default_message_format = opts[:default_message_format] ||
        DEFAULT_MESSAGE_FORMAT
      @default_level = opts[:default_level]

      if @default_level.is_a?( String ) || @default_level.is_a?( Symbol )
        @default_level = LEVEL_TRANSLATOR[@default_level.to_s.upcase]
        if @default_level.nil?
          raise ArgumentError,
            "invalid logging level (#{@default_level.inspect})"
        end
      end

      @levels = Hash.new :level => nil, :date_format => nil,
        :message_format => nil

      ( opts[:levels] || {} ).each_pair do |key, value|
        key = Regexp.new( "^" + key.gsub( /\./, "\\." ).gsub( /\*/, ".*" ) )

        if value.is_a?( String ) || value.is_a?( Symbol )
          value = { :level => value.to_s }
        else
          value = convert_keys_to_symbols( value )
        end

        bad = value.keys - VALID_LEVEL_OPTIONS
        raise ArgumentError, 
          "invalid log level option(s) #{bad.inspect}" unless bad.empty?

        value[ :level ] = LEVEL_TRANSLATOR[ value[:level].to_s.upcase ]
        if value[:level].nil?
          raise ArgumentError,
            "invalid logging level (#{value[:level].inspect})"
        end

        @levels[ key ] = value
      end

      @loggers = Hash.new
      @mutex = Mutex.new
      @closed = false
    end

    # Changes the device that the loggers write to. Every log that was created
    # by this log factory will be changed to use the given device.
    def write_to( device, shift_age = 0, shift_size = 1048576 )
      saved_critical = Thread.critical
      Thread.critical = true

      @device.close if @device unless [ $stdout, $stderr ].include?( @device )
      if device.respond_to?( :write ) && device.respond_to?( :close )
        @device = device
      else
        @device = Logger::LogDevice.new( device.to_str,
          :shift_age => shift_age, 
          :shift_size => shift_size )
      end

      @loggers.each_value { |logger| logger.write_to( @device ) }
      device

    ensure
      Thread.critical = saved_critical
    end

    # Searches for a level definition hash that matches the given log
    # name.
    def find_definition( name )
      best_match = { :length => 0, :value => Hash.new }

      @levels.each_pair do |key, value|
        length = key.to_s.length
        if best_match[ :length ] < length && key === name
          best_match[ :length ] = length
          best_match[ :value ] = value
        end
      end

      return best_match[ :value ]
    end
    private :find_definition

    # Retrieves the logger with the given name. If no such log has been
    # created, the log will be created and initialized. Otherwise, the
    # log with the given name is returned.
    #
    # If +name+ responds to either +fullname+ or +name+, then the result
    # of invoking that message on +name+ will be used as the name.
    def get( name )
      name = name.fullname if name.respond_to?( :fullname )
      name = name.name if name.respond_to?( :name )
      name = name.to_s

      # the common case first, outside the synchronize, for speed
      return @loggers[ name ] if @loggers[ name ]

      @mutex.synchronize do
        # check again, inside the synchronize, to avoid race conditions
        return @loggers[ name ] if @loggers[ name ]

        definition = find_definition( name )

        level = definition[ :level ] || @default_level
        date_format = definition[ :date_format ] || @default_date_format
        message_format = definition[ :message_format ] ||
          @default_message_format

        level = LEVEL_TRANSLATOR[ level.to_s.upcase ] || level

        logger = Needle::Logger.new( @device )
        logger.level = level if level
        logger.progname = name
        logger.datetime_format = date_format if date_format
        logger.message_format = message_format if message_format

        @loggers[ name ] = logger
        return logger
      end
    end

    # Closes the logging device and makes this factory invalid for future
    # accesses.
    def close
      @mutex.synchronize do
        return if @closed

        if @device
          @device.close unless [ $stdout, $stderr ].include?( @device )
        end

        @loggers = nil
        @closed = true
      end
    end

    # Returns true if the factory has been closed.
    def closed?
      @closed
    end

    # Converts the keys of the given hash to symbols, and returns a new
    # hash.
    def convert_keys_to_symbols( hash )
      Hash[ *hash.collect { |k,v| [ k.to_s.tr('-','_').to_sym, v ] }.flatten ]
    end
    private :convert_keys_to_symbols

  end

end

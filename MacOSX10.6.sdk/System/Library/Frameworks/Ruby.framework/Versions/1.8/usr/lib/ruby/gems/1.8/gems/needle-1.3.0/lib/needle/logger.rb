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

require 'logger'
require 'strscan'
require 'needle/errors'

module Needle

  # A specialization of the standard Logger class that comes with Ruby. This
  # provides the additional functionality of a fully-customizable message
  # format, whereas the original only provided a customizable date format.
  class Logger < ::Logger

    # The brief name of this logger (derived from #progname).
    attr_reader :name

    # The format string for the message (+nil+ if the default should be used)
    attr_reader :message_format

    # The map of specifier options supported by this class.
    SPECIFIER_OPTIONS = {
      "c" => { :type => "s", :value => "@name" },
      "C" => { :type => "s", :value => "self.progname" },
      "d" => { :type => "s", :value => "opts[:timestamp]" },
      "F" => { :type => "s", :value => "opts[:caller_file]" },
      "l" => { :type => "s", :value => "opts[:caller_info]" },
      "L" => { :type => "d", :value => "opts[:caller_line]" },
      "m" => { :type => "s", :value => "opts[:msg]" },
      "M" => { :type => "s", :value => "opts[:caller_method]" },
      "n" => { :type => "s", :value => "$/" },
      "p" => { :type => "s", :value => "opts[:severity]" },
      "t" => { :type => "d", :value => "Thread.current.__id__" },
      "%" => { :type => "s", :value => "'%'" },
      "P" => { :type => "s", :value => "opts[:progname]" },
      "$" => { :type => "d", :value => "$$" }
    }

    # The regular expression for matching specifier patterns in the
    # format strings.
    SPECIFIER_PATTERN = /(.*?)%(-?\d*(?:\.\d+)?)?([cCdFlLmMnpt%$P])/

    # Extracts the unqualified name from the progname, after setting the
    # progname.
    def progname=( progname )
      super
      @name = progname.split( /\./ ).last
    end

    # Changes the device that the given logger writes to, to be the given
    # device. Does so in a thread-safe manner.
    def write_to( device, shift_age = 0, shift_size = 1048576 )
      saved_critical = Thread.critical
      Thread.critical = true

      if device
        if device.respond_to?( :write ) && device.respond_to?( :close )
          @logdev = device
        else
          @logdev = Logger::LogDevice.new( device,
            :shift_age => shift_age, 
            :shift_size => shift_size )
        end
      end

      device
    ensure
      Thread.critical = saved_critical
    end

    # Set the message format string to the given string. This also pre-parses
    # the format for faster processing.
    #
    # The format string is a printf-formatted string, which supports the following
    # format specifiers:
    #
    # c:: the unqualified name of the logger
    # C:: the fully-qualified name of the logger
    # d:: the date/time string (as formatted by the #datetime_format string)
    # F:: the filename of the calling routine
    # l:: the location of the calling routine
    # L:: the line number of the calling routine
    # m:: the message to log
    # M:: the name of the calling method
    # n:: the newline character
    # p:: the name of the priority (or severity) used to log this method
    # t:: the id of the current thread
    # %:: a percentage character
    # P:: the progname that was passed to the logger method
    # $:: the current process id
    def message_format=( format )
      @message_format = format
      return unless format

      @needs_caller_info = false

      format_string = ""
      format_parameters = []

      @message_format_tokens = []
      format.scan( SPECIFIER_PATTERN ) do |v|
        format_string << v[0] if v[0].length > 0
        opts = SPECIFIER_OPTIONS[ v[2] ]
        format_string << "%#{v[1]}#{opts[:type]}"
        format_parameters << opts[:value]
        @needs_caller_info = true if v[2] =~ /[FlLM]/
      end
      format_string << $' if $'.length > 0
      format_string << "\n"

      definition =
        "proc { |opts| #{format_string.inspect} " +
        "% [ #{format_parameters.join(',')} ] }"
      @message_formatter = eval( definition )
    end

    # Format the message using the given parameters. If a message format has
    # not been given, just call the superclass's implementation. Otherwise,
    # process the tokens from the parsed message format.
    def format_message( severity, timestamp, *args )
      if @message_format.nil?
        super
      else
        msg, progname = args
        
        # check for API change in 1.8.3 and later
        msg, progname = progname, msg if respond_to?(:formatter=)

        opts = {
          :severity => severity,
          :timestamp => timestamp,
          :msg => msg,
          :progname => progname
        }
        
        if @needs_caller_info
          stack = caller
          stack.shift while stack.first =~ /\blogger\.rb/
          opts[:caller_info] = caller_info = stack.first
          match = caller_info.match( /(.*):(\d+)(?::in `(.*)')?/ )
          opts[:caller_file] = match[1]
          opts[:caller_line] = match[2]
          opts[:caller_method] = match[3]
        end

        @message_formatter.call( opts )
      end
    end
    private :format_message

  end

end

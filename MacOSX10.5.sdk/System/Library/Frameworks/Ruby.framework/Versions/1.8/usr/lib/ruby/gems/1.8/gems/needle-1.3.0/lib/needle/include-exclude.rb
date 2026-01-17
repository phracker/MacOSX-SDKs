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

module Needle

  # A simple structure for representing a single include/exclude pattern.
  IncludeExcludePattern = Struct.new( :name, :comparitor, :arity )

  # A module encapsulating the functionality of a service with include/exclude
  # functionality. Such functionality involves a the ability to specify a
  # pair of include and exclude arrays, each of which must be an array of
  # method names that should be included or excluded from some kind of
  # processing.
  module IncludeExclude

    # This is the regular expression for parsing elements in an include or
    # exclude array.
    PATTERN = /^
               (.*?)        (?# this matches the method name pattern)
               (?:          (?# begin optional arity section)
                 \(         (?# begin parenthesized section)
                   ([<=>])? (?# optional comparator character)
                   (\d+)    (?# arity specification)
                 \)         (?# end parenthesized section)
               )?           (?# end optional arity section)
               $/x

    # This is a utility function for converting an array of strings
    # representing method name patterns, into an array of
    # IncludeExcludePattern instances.
    def build_map( array )
      ( array || [] ).map do |pattern|
        unless pattern =~ PATTERN
          raise InterceptorConfigurationError,
            "invalid logging interceptor method pattern: #{pattern.inspect}"
        end

        name = $1
        comparitor = $2
        arity = ( $3 || -1 ).to_i

        comparitor ||= ">" if arity < 0
        comparitor ||= "="
          
        IncludeExcludePattern.new( Regexp.new( "^" + name + "$" ),
                                   comparitor,
                                   arity )
      end
    end
    private :build_map

    # Returns +false+ if the given context object "matches" any of the
    # exclude patterns without matching any of the include patterns.
    # The context object must respond to the <tt>:sym</tt> and
    # <tt>:args</tt> messages, where <tt>:sym</tt> is a symbol identifying
    # the method being matched, and <tt>:args</tt> is an array of
    # arguments that will be sent to that method.
    def match( context )
      match = true

      @excludes.each do |pattern|
        if match_pattern( context, pattern )
          match = false
          break
        end
      end

      unless match
        @includes.each do |pattern|
          if match_pattern( context, pattern )
            match = true
            break
          end
        end
      end

      return match
    end
    private :match

    # Returns +true+ if the given context matches the given pattern, and
    # +false+ otherwise.
    def match_pattern( context, pattern )
      if context.sym.to_s =~ pattern.name
        case pattern.comparitor
          when "<"
            return context.args.length < pattern.arity
          when ">"
            return context.args.length > pattern.arity
          when "="
            return context.args.length == pattern.arity
        end
      end

      return false
    end
    private :match_pattern

  end

end

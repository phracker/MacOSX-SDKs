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

require 'needle/include-exclude'

module Needle

  # A LoggingInterceptor is an interceptor object that logs method
  # invocations and exceptions. It includes the IncludeExclude functionality.
  class LoggingInterceptor
    include IncludeExclude

    # Create a new LoggingInterceptor for the given service point, with the
    # given list of include and exclude patterns. The logger object will be
    # created as well, named with the service point's full name.
    def initialize( point, parms )
      @log = point.container.logs.get( point.fullname )

      @includes = build_map( parms[ :include ] )
      @excludes = build_map( parms[ :exclude ] )
    end

    # Processes a method invocation context. If the current log has debugging
    # activated, and the requested method is not excluded by the
    # interceptor's exclude and include patterns, then a message will be
    # written for the method's invocation, its return code, and any exception
    # that is thrown.
    def process( chain, context )
      if @log.debug? && match( context )
        args = context.args.map { |i| i.inspect } .join( ', ' )
        @log.debug "#{context.sym}( #{args} )"

        begin
          result = chain.process_next( context )
        rescue Exception => e
          @log.debug "#{context.sym} raised #{e.message.inspect} (#{e.class})"
          raise
        end

        @log.debug "#{context.sym} => #{result.inspect}"
        return result
      else
        return chain.process_next( context )
      end
    end

  end

end

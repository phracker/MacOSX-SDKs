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

module Needle

  # The base class for all Needle-specific errors.
  class NeedleError < StandardError; end

  # Raised when a requested service could not be located.
  class ServiceNotFound < NeedleError; end

  # Raised when there was an error configuring an interceptor.
  class InterceptorConfigurationError < NeedleError; end

  # Raised to denote a condition that should never occur. If this gets
  # raised, it is Needle's fault, not the consumer's.
  class Bug < NeedleError; end

end

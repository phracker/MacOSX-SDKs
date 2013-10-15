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

#--
# Documentation Roadmap:
#
# The following items will given you sufficient background to understand how to
# use the Needle API in your own programs.
#
#   1. Start with needle/registry.rb. This describes how to create a new
#      service registry.
#
#   2. Then, read needle/container.rb. This describes the interface of the
#      registry and namespaces.
#
# The following items are only necessary if you want to understand how Needle
# works internally. You will rarely (if ever) need to use these interfaces
# directly in your own programs:
#
#   1. needle/service-point.rb. This describes how services are instantiated.
#
#   2. needle/models.rb and needle/models/*.rb. These describe the service
#      models that are available, which are used to manage the lifecycles of
#      instantiated services.
#
#   3. needle/interceptor.rb. This describes the interface for configuring
#      interceptors on services.
#
#   4. needle/interceptor-builder.rb. This describes the routines for
#      constructing the proxy objects and interceptor chains around services.
#
#   5. needle/log-factory.rb and needle/logger.rb. These define the logging
#      interface for needle.
#
#   6. needle/logging-interceptor.rb. This defines the logging interceptor
#      service, which wraps every method of a service and logs tracing
#      information.
#++

require 'needle/errors'
require 'needle/registry'

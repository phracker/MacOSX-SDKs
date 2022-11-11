/* Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file  ap_config_layout.h
 * @brief Apache Config Layout
 */

#ifndef AP_CONFIG_LAYOUT_H
#define AP_CONFIG_LAYOUT_H

/* Configured Apache directory layout */
#define DEFAULT_PREFIX "/usr"
#define DEFAULT_EXP_EXEC_PREFIX "/usr"
#define DEFAULT_REL_EXEC_PREFIX ""
#define DEFAULT_EXP_BINDIR "/usr/bin"
#define DEFAULT_REL_BINDIR "bin"
#define DEFAULT_EXP_SBINDIR "/usr/sbin"
#define DEFAULT_REL_SBINDIR "sbin"
#define DEFAULT_EXP_LIBEXECDIR "/usr/libexec/apache2"
#define DEFAULT_REL_LIBEXECDIR "libexec/apache2"
#define DEFAULT_EXP_MANDIR "/usr/share/man"
#define DEFAULT_REL_MANDIR "share/man"
#define DEFAULT_EXP_SYSCONFDIR "/private/etc/apache2"
#define DEFAULT_REL_SYSCONFDIR "/private/etc/apache2"
#define DEFAULT_EXP_DATADIR "/Library/WebServer"
#define DEFAULT_REL_DATADIR "/Library/WebServer"
#define DEFAULT_EXP_INSTALLBUILDDIR "/usr/share/httpd/build"
#define DEFAULT_REL_INSTALLBUILDDIR "share/httpd/build"
#define DEFAULT_EXP_ERRORDIR "/usr/share/httpd/error"
#define DEFAULT_REL_ERRORDIR "share/httpd/error"
#define DEFAULT_EXP_ICONSDIR "/usr/share/httpd/icons"
#define DEFAULT_REL_ICONSDIR "share/httpd/icons"
#define DEFAULT_EXP_HTDOCSDIR "/Library/WebServer/Documents"
#define DEFAULT_REL_HTDOCSDIR "/Library/WebServer/Documents"
#define DEFAULT_EXP_MANUALDIR "/Library/WebServer/share/httpd/manual"
#define DEFAULT_REL_MANUALDIR "/Library/WebServer/share/httpd/manual"
#define DEFAULT_EXP_CGIDIR "/Library/WebServer/CGI-Executables"
#define DEFAULT_REL_CGIDIR "/Library/WebServer/CGI-Executables"
#define DEFAULT_EXP_INCLUDEDIR "/usr/include/apache2"
#define DEFAULT_REL_INCLUDEDIR "include/apache2"
#define DEFAULT_EXP_LOCALSTATEDIR "/private/var"
#define DEFAULT_REL_LOCALSTATEDIR "/private/var"
#define DEFAULT_EXP_RUNTIMEDIR "/private/var/run"
#define DEFAULT_REL_RUNTIMEDIR "/private/var/run"
#define DEFAULT_EXP_LOGFILEDIR "/private/var/log/apache2"
#define DEFAULT_REL_LOGFILEDIR "/private/var/log/apache2"
#define DEFAULT_EXP_PROXYCACHEDIR "/private/var/run/proxy"
#define DEFAULT_REL_PROXYCACHEDIR "/private/var/run/proxy"

#endif /* AP_CONFIG_LAYOUT_H */

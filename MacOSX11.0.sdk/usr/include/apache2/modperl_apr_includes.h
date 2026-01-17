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

#ifndef MODPERL_APR_INCLUDES_H
#define MODPERL_APR_INCLUDES_H

/* header files for APR */

#ifndef CORE_PRIVATE
#define CORE_PRIVATE
#endif

#include "apr_version.h"
#include "apr_poll.h"
#include "apr_lib.h"
#include "apr_strings.h"
#include "apr_uri.h"
#include "apr_date.h"
#include "apr_buckets.h"
#include "apr_time.h"
#include "apr_network_io.h"
#include "apr_general.h"
#include "apr_uuid.h"
#include "apr_env.h"
#include "apu_version.h"
#if APU_MAJOR_VERSION > 1 \
    || (APU_MAJOR_VERSION == 1 && APU_MINOR_VERSION > 3)
#include "apu_errno.h"
#endif

#endif /* MODPERL_APR_INCLUDES_H */

/*
 * Local Variables:
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */

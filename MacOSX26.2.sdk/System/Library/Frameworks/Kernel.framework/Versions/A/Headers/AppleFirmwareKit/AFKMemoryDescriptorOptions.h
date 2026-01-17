	/*
 *  Copyright (C) 2021 Apple, Inc. All rights reserved.
 *
 *  This document is the property of Apple Inc.
 *  It is considered confidential and proprietary.
 *
 *  This document may not be reproduced or transmitted in any form,
 *  in whole or in part, without the express written permission of
 *  Apple Inc.
 */

#pragma once

#include <sys/cdefs.h>
#include <string.h>

__BEGIN_DECLS

/*! @typedef  descriptor_options
 *  @abstract Object for specifying options to create AFKMemoryDescriptors
 *  @discussion Methods of AFKMemoryDescriptorManager to create descriptors take this optional options
 *  parameter to specify nonstandard behavior. Initialize it with <code>descriptor_options_init</code> and calling
 *  some number of <code>descriptor_options_set...</code> before passing it to AFKMemoryDescriptorManager.
 */
typedef uint32_t descriptor_options[1];

inline void descriptor_options_init(descriptor_options options)
{
    memset(options, 0, sizeof(descriptor_options));
}

__END_DECLS

//
//  libmanagedconfigurationfiles.h
//  ManagedConfigurationFilesLibrary
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#ifndef libmanagedconfigurationfiles_h
#define libmanagedconfigurationfiles_h

#include <stdio.h>

/**
 * Used to get Managed Service Path for a given service.
 * @param serviceType the reverse domain name of the service
 * @param servicePath Managed service path of serviceType
 * @param servicePathSize Allocated size of servicePath
 * @returns @c 0 in case of any failure or if service is not managed and errno is set
 * @returns @c size of managed configuration file path
 */
 __API_AVAILABLE(macos(14.0)) __API_UNAVAILABLE(ios, watchos, tvos)
size_t mcf_service_path_for_service_type(const char * _Nonnull serviceType, char * _Nonnull servicePath, size_t servicePathSize);

#endif /* libmanagedconfigurationfiles_h */

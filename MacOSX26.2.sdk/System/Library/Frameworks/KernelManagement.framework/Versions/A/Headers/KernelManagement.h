//
//  KernelManagement.h
//  KernelManagement
//
//  Created by jkb on 9/11/19.
//

#import <Foundation/Foundation.h>

#ifndef KERNELMANAGEMENT_HOST
#define KM_AVAILABLE(...) API_AVAILABLE(__VA_ARGS__)
#define KM_ENUM_AVAILABLE(...) NS_ENUM_AVAILABLE_MAC(__VA_ARGS__)
#else
#define KM_AVAILABLE(...)
#define KM_ENUM_AVAILABLE(...)
#endif /* !KERNELMANAGEMENT_HOST */

__BEGIN_DECLS

//! Project version number for KernelManagement.
FOUNDATION_EXPORT double KernelManagementVersionNumber;

//! Project version string for KernelManagement.
FOUNDATION_EXPORT const unsigned char KernelManagementVersionString[];

__END_DECLS

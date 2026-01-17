//
// @header ModelIOExports.h
// @framework ModelIO
//
// @copyright (c) 2015 Apple. All rights reserved.
//
#pragma once

#ifdef __cplusplus
#   define MDL_EXPORT_CPPCLASS __attribute__((visibility ("default")))
#   define MDL_EXPORT extern "C" __attribute__((visibility ("default")))
#else
#   define MDL_EXPORT extern __attribute__((visibility ("default")))
#endif

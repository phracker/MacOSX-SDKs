#ifndef MediaAccessibility_Definitions_h
#define MediaAccessibility_Definitions_h

#include <Availability.h>
#include <AvailabilityMacros.h>
#include <TargetConditionals.h>

#if TARGET_OS_WIN32
#include <MediaAccessibility/MADefinitionsWindows.h>
#endif

#if defined(__cplusplus)
#define MA_EXTERN_C_BEGIN extern "C" {
#define MA_EXTERN_C_END }
#else
#define MA_EXTERN_C_BEGIN
#define MA_EXTERN_C_END
#endif

#if TARGET_OS_WIN32
#if defined(BUILDING_MA)
#define MA_VISIBLE __declspec(dllexport)
#else
#define MA_VISIBLE __declspec(dllimport)
#endif
#else
#define MA_VISIBLE __attribute__((visibility("default")))
#endif

#if defined(__cplusplus)
#define MA_EXTERN extern "C"
#else
#define MA_EXTERN extern
#endif

#define MA_EXPORT MA_EXTERN MA_VISIBLE

#endif

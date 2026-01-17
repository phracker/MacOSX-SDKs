#ifndef MediaAccessibility_Definitions_h
#define MediaAccessibility_Definitions_h

#include <Availability.h>
#include <AvailabilityMacros.h>
#include <TargetConditionals.h>



#if defined(__cplusplus)
#define MA_EXTERN_C_BEGIN extern "C" {
#define MA_EXTERN_C_END }
#else
#define MA_EXTERN_C_BEGIN
#define MA_EXTERN_C_END
#endif


#define MA_VISIBLE __attribute__((visibility("default")))


#if defined(__cplusplus)
#define MA_EXTERN extern "C"
#else
#define MA_EXTERN extern
#endif

#define MA_EXPORT MA_EXTERN MA_VISIBLE

#endif

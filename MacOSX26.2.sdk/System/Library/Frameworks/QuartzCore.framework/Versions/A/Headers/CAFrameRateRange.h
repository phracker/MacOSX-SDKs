/* CoreAnimation - CAFrameRateRange.h

   Copyright (c) 2020-2025, Apple Inc.
   All rights reserved. */

#ifndef CAFRAMERATERANGE_H
#define CAFRAMERATERANGE_H

#include <QuartzCore/CABase.h>
#include <stdbool.h>

struct CAFrameRateRange {
  float minimum;
  float maximum;
  float preferred CF_REFINED_FOR_SWIFT;
} API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos);

typedef struct CAFrameRateRange CAFrameRateRange
  API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos);

CA_EXTERN_C_BEGIN

CA_EXTERN const CAFrameRateRange CAFrameRateRangeDefault
  API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos)
  CF_SWIFT_NAME(CAFrameRateRange.default);

CA_EXTERN CAFrameRateRange CAFrameRateRangeMake(float minimum,
                                                float maximum,
                                                float preferred)
  API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos)
  CF_SWIFT_UNAVAILABLE("Use CAFrameRateRange.init(minimum:maximum:preferred) instead");

CA_EXTERN bool CAFrameRateRangeIsEqualToRange(CAFrameRateRange range,
                                              CAFrameRateRange other)
  API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos)
  CF_REFINED_FOR_SWIFT;

CA_EXTERN_C_END

#endif /* CAFRAMERATERANGE_H */

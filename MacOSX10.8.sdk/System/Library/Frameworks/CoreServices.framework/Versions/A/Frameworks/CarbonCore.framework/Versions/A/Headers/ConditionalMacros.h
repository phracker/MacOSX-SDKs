/*
     File:       CarbonCore/ConditionalMacros.h
 
     Contains:   This header file is deprecated.
                 The contents have been moved to </usr/include/ConditionalMacros.h>.
 
     Copyright:  © 1993-2011 by Apple Inc. All rights reserved.
*/

#ifdef __has_include
#  if __has_include(</usr/include/ConditionalMacros.h>)
#    include </usr/include/ConditionalMacros.h>
#  else
#    include <ConditionalMacros.h>
#  endif
#else
#  include <ConditionalMacros.h>
#endif

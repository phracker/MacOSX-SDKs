//
// MDLUtility.h
// @framework ModelIO
//
// @copyright (c) 2018 Apple. All rights reserved.
//

#ifndef MDLUtility_h
#define MDLUtility_h

#include <ModelIO/ModelIOExports.h>
#include <ModelIO/MDLAsset.h>

API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0))
MDL_EXPORT
@interface MDLUtility : NSObject
+(void)convertToUSDZ:(nonnull NSURL*)inputURL writeToURL:(nonnull NSURL*)outputURL;
@end

#endif /* MDLUtility_h */

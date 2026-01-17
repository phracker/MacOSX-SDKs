//
//  PKInkType.h
//  PencilKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>


typedef NSString * PKInkType NS_TYPED_ENUM API_AVAILABLE(ios(13.0)) NS_REFINED_FOR_SWIFT;
API_AVAILABLE(ios(13.0), macos(10.15)) FOUNDATION_EXPORT PKInkType const PKInkTypePen;
API_AVAILABLE(ios(13.0), macos(10.15)) FOUNDATION_EXPORT PKInkType const PKInkTypePencil;
API_AVAILABLE(ios(13.0), macos(10.15)) FOUNDATION_EXPORT PKInkType const PKInkTypeMarker;
API_AVAILABLE(ios(17.0), macos(14.0))  FOUNDATION_EXPORT PKInkType const PKInkTypeMonoline;
API_AVAILABLE(ios(17.0), macos(14.0))  FOUNDATION_EXPORT PKInkType const PKInkTypeFountainPen;
API_AVAILABLE(ios(17.0), macos(14.0))  FOUNDATION_EXPORT PKInkType const PKInkTypeWatercolor;
API_AVAILABLE(ios(26.0), macos(26.0), visionos(26.0))  FOUNDATION_EXPORT PKInkType const PKInkTypeReed;
API_AVAILABLE(ios(17.0), macos(14.0))  FOUNDATION_EXPORT PKInkType const PKInkTypeCrayon;

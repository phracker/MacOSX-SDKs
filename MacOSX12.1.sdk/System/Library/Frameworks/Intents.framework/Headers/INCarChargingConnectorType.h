//
//  INCarChargingConnectorType.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NSString *INCarChargingConnectorType NS_TYPED_ENUM NS_SWIFT_NAME(INCar.ChargingConnectorType);

INTENTS_EXTERN INCarChargingConnectorType const INCarChargingConnectorTypeJ1772 NS_SWIFT_NAME(INCarChargingConnectorType.j1772) API_AVAILABLE(ios(14.0), watchos(7.0)) API_UNAVAILABLE(macos, tvos);
INTENTS_EXTERN INCarChargingConnectorType const INCarChargingConnectorTypeCCS1 NS_SWIFT_NAME(INCarChargingConnectorType.ccs1) API_AVAILABLE(ios(14.0), watchos(7.0)) API_UNAVAILABLE(macos, tvos);
INTENTS_EXTERN INCarChargingConnectorType const INCarChargingConnectorTypeCCS2 NS_SWIFT_NAME(INCarChargingConnectorType.ccs2) API_AVAILABLE(ios(14.0), watchos(7.0)) API_UNAVAILABLE(macos, tvos);
INTENTS_EXTERN INCarChargingConnectorType const INCarChargingConnectorTypeCHAdeMO NS_SWIFT_NAME(INCarChargingConnectorType.chaDeMo) API_AVAILABLE(ios(14.0), watchos(7.0)) API_UNAVAILABLE(macos, tvos);
INTENTS_EXTERN INCarChargingConnectorType const INCarChargingConnectorTypeGBTAC NS_SWIFT_NAME(INCarChargingConnectorType.gbtAC) API_AVAILABLE(ios(14.0), watchos(7.0)) API_UNAVAILABLE(macos, tvos);
INTENTS_EXTERN INCarChargingConnectorType const INCarChargingConnectorTypeGBTDC NS_SWIFT_NAME(INCarChargingConnectorType.gbtDC) API_AVAILABLE(ios(14.0), watchos(7.0)) API_UNAVAILABLE(macos, tvos);
INTENTS_EXTERN INCarChargingConnectorType const INCarChargingConnectorTypeTesla API_AVAILABLE(ios(14.0), watchos(7.0)) API_UNAVAILABLE(macos, tvos);
INTENTS_EXTERN INCarChargingConnectorType const INCarChargingConnectorTypeMennekes API_AVAILABLE(ios(14.0), watchos(7.0)) API_UNAVAILABLE(macos, tvos);

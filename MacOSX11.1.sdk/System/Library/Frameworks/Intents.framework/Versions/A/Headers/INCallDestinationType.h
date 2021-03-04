//
//  INCallDestinationType.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#ifndef INCallDestinationType_h
#define INCallDestinationType_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INCallDestinationType) {
    INCallDestinationTypeUnknown = 0,
    INCallDestinationTypeNormal,
    INCallDestinationTypeEmergency,
    INCallDestinationTypeVoicemail,
    INCallDestinationTypeRedial,
    INCallDestinationTypeCallBack API_AVAILABLE(ios(13.0), watchos(6.0)) API_UNAVAILABLE(macos),
    INCallDestinationTypeNormalDestination API_DEPRECATED("Use INCallDestinationTypeNormal instead", ios(11.0, 11.0), watchos(4.0, 4.0), macosx(10.13, 10.13), tvos(13.4, 13.4)) = 1,
    INCallDestinationTypeEmergencyDestination API_DEPRECATED("Use INCallDestinationTypeEmergency instead", ios(11.0, 11.0), watchos(4.0, 4.0), macosx(10.13, 10.13), tvos(13.4, 13.4)) = 2,
    INCallDestinationTypeVoicemailDestination API_DEPRECATED("Use INCallDestinationTypeVoicemail instead", ios(11.0, 11.0), watchos(4.0, 4.0), macosx(10.13, 10.13), tvos(13.4, 13.4)) = 3,
    INCallDestinationTypeRedialDestination API_DEPRECATED("Use INCallDestinationTypeRedial instead", ios(11.0, 11.0), watchos(4.0, 4.0), macosx(10.13, 10.13), tvos(13.4, 13.4)) = 4,
} API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macos, tvos);

#endif // INCallDestinationType_h

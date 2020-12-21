//
//  INPersonRelationship.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NSString *INPersonRelationship NS_TYPED_EXTENSIBLE_ENUM;

INTENTS_EXTERN INPersonRelationship const INPersonRelationshipFather NS_SWIFT_NAME(INPersonRelationship.father) API_AVAILABLE(ios(10.2), watchos(3.2)) API_UNAVAILABLE(macos, tvos);
INTENTS_EXTERN INPersonRelationship const INPersonRelationshipMother NS_SWIFT_NAME(INPersonRelationship.mother) API_AVAILABLE(ios(10.2), watchos(3.2)) API_UNAVAILABLE(macos, tvos);
INTENTS_EXTERN INPersonRelationship const INPersonRelationshipParent NS_SWIFT_NAME(INPersonRelationship.parent) API_AVAILABLE(ios(10.2), watchos(3.2)) API_UNAVAILABLE(macos, tvos);
INTENTS_EXTERN INPersonRelationship const INPersonRelationshipBrother NS_SWIFT_NAME(INPersonRelationship.brother) API_AVAILABLE(ios(10.2), watchos(3.2)) API_UNAVAILABLE(macos, tvos);
INTENTS_EXTERN INPersonRelationship const INPersonRelationshipSister NS_SWIFT_NAME(INPersonRelationship.sister) API_AVAILABLE(ios(10.2), watchos(3.2)) API_UNAVAILABLE(macos, tvos);
INTENTS_EXTERN INPersonRelationship const INPersonRelationshipChild NS_SWIFT_NAME(INPersonRelationship.child) API_AVAILABLE(ios(10.2), watchos(3.2)) API_UNAVAILABLE(macos, tvos);
INTENTS_EXTERN INPersonRelationship const INPersonRelationshipFriend NS_SWIFT_NAME(INPersonRelationship.friend) API_AVAILABLE(ios(10.2), watchos(3.2)) API_UNAVAILABLE(macos, tvos);
INTENTS_EXTERN INPersonRelationship const INPersonRelationshipSpouse NS_SWIFT_NAME(INPersonRelationship.spouse) API_AVAILABLE(ios(10.2), watchos(3.2)) API_UNAVAILABLE(macos, tvos);
INTENTS_EXTERN INPersonRelationship const INPersonRelationshipPartner NS_SWIFT_NAME(INPersonRelationship.partner) API_AVAILABLE(ios(10.2), watchos(3.2)) API_UNAVAILABLE(macos, tvos);
INTENTS_EXTERN INPersonRelationship const INPersonRelationshipAssistant NS_SWIFT_NAME(INPersonRelationship.assistant) API_AVAILABLE(ios(10.2), watchos(3.2)) API_UNAVAILABLE(macos, tvos);
INTENTS_EXTERN INPersonRelationship const INPersonRelationshipManager NS_SWIFT_NAME(INPersonRelationship.manager) API_AVAILABLE(ios(10.2), watchos(3.2)) API_UNAVAILABLE(macos, tvos);
INTENTS_EXTERN INPersonRelationship const INPersonRelationshipSon NS_SWIFT_NAME(INPersonRelationship.son) API_AVAILABLE(ios(13.0), macos(10.15), watchos(6.0)) API_UNAVAILABLE(tvos);
INTENTS_EXTERN INPersonRelationship const INPersonRelationshipDaughter NS_SWIFT_NAME(INPersonRelationship.daughter) API_AVAILABLE(ios(13.0), macos(10.15), watchos(6.0)) API_UNAVAILABLE(tvos);

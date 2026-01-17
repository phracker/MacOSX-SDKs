/*!
 @header     MSSession
 @copyright  Copyright (c) 2016 Apple Inc. All rights reserved.
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class MSSession
 @abstract A MSSession establishes a relationship between a sequence of messages within a conversation.
 @discussion Messages created with the same session are represented as a single
 entry in the conversation transcript.
 */
NS_CLASS_AVAILABLE_IOS(10_0)
@interface MSSession : NSObject <NSSecureCoding>
@end

NS_ASSUME_NONNULL_END

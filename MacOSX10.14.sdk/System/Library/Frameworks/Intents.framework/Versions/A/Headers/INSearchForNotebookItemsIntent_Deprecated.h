//
//  INSearchForNotebookItemsIntent_Deprecated.h
//  Intents
//
//  Created by Kyle Zhao on 9/18/17.
//  Copyright © 2017 Apple. All rights reserved.
//

#import <Intents/INSearchForNotebookItemsIntent.h>

NS_ASSUME_NONNULL_BEGIN

@interface INSearchForNotebookItemsIntent (Deprecated)

- (instancetype)initWithTitle:(nullable INSpeakableString *)title
                      content:(nullable NSString *)content
                     itemType:(INNotebookItemType)itemType
                       status:(INTaskStatus)status
                     location:(nullable CLPlacemark *)location
           locationSearchType:(INLocationSearchType)locationSearchType
                     dateTime:(nullable INDateComponentsRange *)dateTime
               dateSearchType:(INDateSearchType)dateSearchType API_DEPRECATED("Use the designated initializer instead", ios(11.0, 11.2), watchos(4.0, 4.2));

@end

NS_ASSUME_NONNULL_END

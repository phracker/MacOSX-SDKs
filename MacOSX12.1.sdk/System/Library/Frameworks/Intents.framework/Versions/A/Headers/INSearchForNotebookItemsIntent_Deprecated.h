//
//  INSearchForNotebookItemsIntent_Deprecated.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
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

- (instancetype)initWithTitle:(nullable INSpeakableString *)title
                      content:(nullable NSString *)content
                     itemType:(INNotebookItemType)itemType
                       status:(INTaskStatus)status
                     location:(nullable CLPlacemark *)location
           locationSearchType:(INLocationSearchType)locationSearchType
                     dateTime:(nullable INDateComponentsRange *)dateTime
               dateSearchType:(INDateSearchType)dateSearchType
       notebookItemIdentifier:(nullable NSString *)notebookItemIdentifier API_DEPRECATED("Use the designated initializer instead", ios(11.2, 13.0), watchos(4.2, 6.0));

@end

NS_ASSUME_NONNULL_END

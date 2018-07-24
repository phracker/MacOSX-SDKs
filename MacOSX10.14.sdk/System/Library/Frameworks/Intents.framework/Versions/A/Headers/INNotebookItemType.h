//
//  INNotebookItemType.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INNotebookItemType_h
#define INNotebookItemType_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INNotebookItemType) {
    INNotebookItemTypeUnknown = 0,
    INNotebookItemTypeNote,
    INNotebookItemTypeTaskList,
    INNotebookItemTypeTask,
} API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macosx);

#endif // INNotebookItemType_h

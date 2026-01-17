/*
	NSPrinter.h
	Application Kit
	Copyright (c) 1994-2001, Apple Computer, Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>

@class NSArray, NSDate;

typedef enum _NSPrinterTableStatus {
    NSPrinterTableOK			= (0),
    NSPrinterTableNotFound		= (1),
    NSPrinterTableError			= (2)
} NSPrinterTableStatus;

@interface NSPrinter:NSObject <NSCopying, NSCoding>
{
    /*All instance variables are private*/
    NSString *_printerName;
    NSString *_hostName;
    NSString *_domainName;
    NSString *_printerType;
    BOOL _ignore;
    BOOL _valid;
    int _creationNum;
    void *_nodes;
    NSDate *_previousValid;
    long _niInstance;
    NSDictionary *_deviceDict;
    void *_priv;
#ifdef WIN32
    NSString *_comment;
    NSMutableDictionary *_papers;
#endif
}

+ (NSPrinter *)printerWithName:(NSString *)name;

#ifndef WIN32
- (NSString *)domain;
+ (NSPrinter *)printerWithName:(NSString *)name domain:(NSString *)domain includeUnavailable:(BOOL)flag;
#endif WIN32

+ (NSArray *)printerNames;
+ (NSPrinter *)printerWithType:(NSString *)type;
+ (NSArray *)printerTypes;

- (NSString *)name;
- (NSString *)host;
- (NSString *)type;
- (NSString *)note;
- (BOOL)isColor;
- (BOOL)acceptsBinary;
- (BOOL)isOutputStackInReverseOrder;
- (NSSize)pageSizeForPaper:(NSString *)paperName;
- (NSRect)imageRectForPaper:(NSString *)paperName;
- (int)languageLevel;
- (BOOL)isFontAvailable:(NSString *)faceName;
- (NSPrinterTableStatus)statusForTable:(NSString *)table;
- (NSDictionary *)deviceDescription;

- (BOOL)isKey:(NSString *)key inTable:(NSString *)table;
- (NSString *)stringForKey:(NSString *)key inTable:(NSString *)table;
- (NSSize)sizeForKey:(NSString *)key inTable:(NSString *)table;
- (NSRect)rectForKey:(NSString *)key inTable:(NSString *)table;
- (int)intForKey:(NSString *)key inTable:(NSString *)table;
- (float)floatForKey:(NSString *)key inTable:(NSString *)table;
- (BOOL)booleanForKey:(NSString *)key inTable:(NSString *)table;
- (NSArray *)stringListForKey:(NSString *)key inTable:(NSString *)table;

@end

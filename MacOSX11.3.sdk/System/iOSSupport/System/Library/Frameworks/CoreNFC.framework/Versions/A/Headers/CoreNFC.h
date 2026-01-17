//
//  CoreNFC.h
//  CoreNFC
//
//  Copyright © 2017 Apple. All rights reserved.
//

#ifndef CoreNFC_H
#define CoreNFC_H

#import <CoreNFC/NFCError.h>
#import <CoreNFC/NFCReaderSession.h>
#import <CoreNFC/NFCTag.h>
#import <CoreNFC/NFCTagReaderSession.h>
#import <CoreNFC/NFCNDEFReaderSession.h>
#import <CoreNFC/NSUserActivity+CoreNFC.h>
#if __has_include(<CoreNFC/NFCISO15693Tag.h>)
#import <CoreNFC/NFCISO15693Tag.h>
#endif
#if __has_include(<CoreNFC/NFCISO15693ReaderSession.h>)
#import <CoreNFC/NFCISO15693ReaderSession.h>
#endif
#import <CoreNFC/NFCFeliCaTag.h>
#import <CoreNFC/NFCISO7816Tag.h>
#import <CoreNFC/NFCMiFareTag.h>
#import <CoreNFC/NFCNDEFTag.h>
#import <CoreNFC/NFCNDEFPayload.h>
#import <CoreNFC/NFCNDEFMessage.h>
#import <CoreNFC/NFCVASReaderSession.h>
#endif

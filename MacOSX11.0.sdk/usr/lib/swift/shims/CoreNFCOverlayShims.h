#ifndef SWIFT_STDLIB_SHIMS_CORENFCSHIMS_H
#define SWIFT_STDLIB_SHIMS_CORENFCSHIMS_H

#import <Foundation/Foundation.h>
@import CoreNFC;


NS_ASSUME_NONNULL_BEGIN

@interface NFCTagReaderSession (CoreNFC_SPI)
// According to the current auto renaming rule, the Swift method will be named "-init(__pollingOption:swiftDelegate:queue:)"
- (nullable instancetype)initWithPollingOption:(NFCPollingOption)pollingOption
                                 swiftDelegate:(id)swiftDelegate
                                         queue:(nullable dispatch_queue_t)queue API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos) NS_REFINED_FOR_SWIFT;
@end

NS_ASSUME_NONNULL_END

#endif

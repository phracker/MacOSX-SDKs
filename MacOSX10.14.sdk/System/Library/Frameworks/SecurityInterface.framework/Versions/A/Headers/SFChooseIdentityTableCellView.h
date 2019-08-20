//
//  SFChooseIdentityTableCellView.h
//  SecurityInterface
//
//  Created by Michiko (Julie) Osakabe on 4/4/17.
//  Copyright (c) 2017 Apple Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface SFChooseIdentityTableCellView : NSTableCellView
{
    IBOutlet NSTextField *issuerTextField;
}
@property(assign) IBOutlet NSTextField *issuerTextField;

@end

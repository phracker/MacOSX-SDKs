//
//  cp_conditionals.h
//  WakeBoard
//
//  Created by Jacob Wilson on 3/14/25.
//  Copyright © 2025 Apple. All rights reserved.
//

#ifndef cp_conditionals_h
#define cp_conditionals_h

#define CP_ARKITCORE_AVAILABLE ((TARGET_OS_VISION && !TARGET_OS_SIMULATOR) || TARGET_OS_OSX)
#define CP_MTL4_AVAILABLE      !TARGET_OS_SIMULATOR

#endif

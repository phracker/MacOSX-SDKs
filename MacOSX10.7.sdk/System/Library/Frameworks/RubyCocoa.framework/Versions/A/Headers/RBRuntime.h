/* 
 * Copyright (c) 2006-2008, The RubyCocoa Project.
 * Copyright (c) 2001-2006, FUJIMOTO Hisakuni.
 * All Rights Reserved.
 *
 * RubyCocoa is free software, covered under either the Ruby's license or the 
 * LGPL. See the COPYRIGHT file for more information.
 */

#ifndef _RBRUNTIME_H_
#define _RBRUNTIME_H_

#import <objc/objc.h>

/** [API] RBBundleInit
 *
 * initialize ruby and rubycocoa for a bundle.
 * return not 0 when something error.
 */
int RBBundleInit (const char* path_to_ruby_program, 
                  Class       objc_class, 
                  id          additional_param);


/** [API] RBApplicationInit
 *
 * initialize ruby and rubycocoa for a command/application
 * return 0 when complete, or return not 0 when error.
 */
int RBApplicationInit (const char* path_to_ruby_program,
                       int         argc,
                       const char* argv[],
                       id          additional_param);


/** [API] RBRubyCocoaInit (for compatibility)
 *
 * initialize rubycocoa for a ruby extention library
 */
void RBRubyCocoaInit (void);


/** [API] RBApplicationMain (for compatibility)
 *
 * launch rubycocoa application
 */
int
RBApplicationMain (const char* path_to_ruby_program, 
                   int         argc, 
                   const char* argv[]);

/** [API] RBIsRubyThreadingSupported
 *
 * verify if this environment supports the Ruby threading
 */
BOOL RBIsRubyThreadingSupported (void);

#endif  // _RBRUNTIME_H_

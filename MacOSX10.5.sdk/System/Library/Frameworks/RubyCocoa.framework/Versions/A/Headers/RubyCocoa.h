/* 
 * Copyright (c) 2006-2007, The RubyCocoa Project.
 * Copyright (c) 2001-2006, FUJIMOTO Hisakuni.
 * All Rights Reserved.
 *
 * RubyCocoa is free software, covered under either the Ruby's license or the 
 * LGPL. See the COPYRIGHT file for more information.
 */

#ifndef _RUBYCOCOA_H_
#define _RUBYCOCOA_H_

#import <RubyCocoa/RBRuntime.h>
#import <Foundation/NSObject.h>

@interface RubyCocoa : NSObject
+ (int) bundleInitWithProgram: (const char*) path_to_ruby_program
			class: (Class) objc_class
			param: (id) additional_param;

+ (int) applicationInitWithProgram: (const char*) path_to_ruby_program
			      argc: (int) argc
			      argv: (const char**) argv
			     param: (id) additional_param;

+ (int) applicationMainWithProgram: (const char*) path_to_ruby_program
			      argc: (int) argc
			      argv: (const char**) argv;
@end

#endif

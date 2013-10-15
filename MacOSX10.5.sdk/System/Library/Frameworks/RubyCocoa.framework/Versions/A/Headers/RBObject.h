/* 
 * Copyright (c) 2006-2007, The RubyCocoa Project.
 * Copyright (c) 2001-2006, FUJIMOTO Hisakuni.
 * All Rights Reserved.
 *
 * RubyCocoa is free software, covered under either the Ruby's license or the 
 * LGPL. See the COPYRIGHT file for more information.
 */

#import <Foundation/NSProxy.h>
#import <RubyCocoa/osx_ruby.h>

@interface RBObject : NSProxy
{
  VALUE m_rbobj;
  BOOL m_rbobj_retained;
  id oc_master;
}

+ RBObjectWithRubyScriptCString: (const char*) cstr;
+ RBObjectWithRubyScriptString: (NSString*) str;

- initWithRubyObject: (VALUE) rbobj; 
- initWithRubyScriptCString: (const char*) cstr;
- initWithRubyScriptString: (NSString*) str;

- (VALUE) __rbobj__;
- (BOOL) isKindOfClass:(Class)aClass;
- (BOOL) isRBObject;

@end

@interface NSProxy (RubyCocoaEx)

- (BOOL) isRBObject;

@end

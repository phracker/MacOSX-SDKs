/*
 *  CTDefines.h
 *  CoreText
 *
 *  Copyright (c) 2010-2016 Apple Inc. All rights reserved.
 *
 */

#ifndef __CTDEFINES__
#define __CTDEFINES__

#include <Availability.h>

#ifndef __has_feature
# define __has_feature(x) 0
#endif

#ifndef __has_attribute
# define __has_attribute(x) 0
#endif

#if defined(CT_BUILDING_CoreText) || TARGET_OS_WIN32
# define CT_AVAILABLE(_mac, _ios)
# define CT_AVAILABLE_MAC(_mac)
# define CT_AVAILABLE_IOS(_ios)
# define CT_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep)
# define CT_DEPRECATED_MAC(_macIntro, _macDep)
# define CT_DEPRECATED_IOS(_iosIntro, _iosDep)
#else /* defined(CT_BUILDING_CoreText) */
# define CT_AVAILABLE(_mac, _ios) __OSX_AVAILABLE_STARTING(__MAC_##_mac, __IPHONE_##_ios)
# define CT_AVAILABLE_MAC(_mac) __OSX_AVAILABLE_STARTING(__MAC_##_mac, __IPHONE_NA)
# define CT_AVAILABLE_IOS(_ios) __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_##_ios)
# define CT_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep) __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_##_macIntro, __MAC_##_macDep, __IPHONE_##_iosIntro, __IPHONE_##_iosDep)
# define CT_DEPRECATED_MAC(_macIntro, _macDep) __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_##_macIntro, __MAC_##_macDep, __IPHONE_NA, __IPHONE_NA)
# define CT_DEPRECATED_IOS(_iosIntro, _iosDep) __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA, __MAC_NA, __IPHONE_##_iosIntro, __IPHONE_##_iosDep)
#endif /* defined(CT_BUILDING_CoreText) */

#if __has_feature(enumerator_attributes) && __has_attribute(availability)
# define CT_ENUM_AVAILABLE(_mac, _ios) CT_AVAILABLE(_mac, _ios)
# define CT_ENUM_AVAILABLE_MAC(_mac) CT_AVAILABLE_MAC(_mac)
# define CT_ENUM_AVAILABLE_IOS(_ios) CT_AVAILABLE_IOS(_ios)
# define CT_ENUM_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep) CT_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep)
# define CT_ENUM_DEPRECATED_MAC(_macIntro, _macDep) CT_DEPRECATED_MAC(_macIntro, _macDep)
# define CT_ENUM_DEPRECATED_IOS(_iosIntro, _iosDep) CT_DEPRECATED_IOS(_iosIntro, _iosDep)
#else
# define CT_ENUM_AVAILABLE(_mac, _ios)
# define CT_ENUM_AVAILABLE_MAC(_mac)
# define CT_ENUM_AVAILABLE_IOS(_ios)
# define CT_ENUM_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep)
# define CT_ENUM_DEPRECATED_MAC(_macIntro, _macDep)
# define CT_ENUM_DEPRECATED_IOS(_iosIntro, _iosDep)
#endif /* __has_feature(enumerator_attributes) && __has_attribute(availability) */

#if __has_attribute(objc_bridge)
# if defined(__OBJC__)
#  if TARGET_OS_IPHONE
@class UIFont;
@class UIFontDescriptor;
#  else
@class NSFont;
@class NSFontCollection;
@class NSFontDescriptor;
@class NSGlyphInfo;
@class NSMutableFontCollection;
#  endif /* TARGET_OS_IPHONE */
@class NSParagraphStyle;
@class NSTextTab;
# endif /* defined(__OBJC__) */
#endif /*  __has_attribute(objc_bridge) */

#if TARGET_OS_WIN32
#define __nullable

#define CF_BRIDGED_TYPE(T)
#define CF_BRIDGED_MUTABLE_TYPE(T)
#define CF_RELATED_TYPE(T,C,I)

#define CF_ASSUME_NONNULL_BEGIN
#define CF_ASSUME_NONNULL_END

# if defined(CT_BUILDING_CoreText) && defined(__cplusplus)
#  define CT_EXPORT extern "C" __declspec(dllexport)
# elif defined(CT_BUILDING_CoreText) && !defined(__cplusplus)
#  define CT_EXPORT extern __declspec(dllexport)
# elif defined(__cplusplus)
#  define CT_EXPORT extern "C" __declspec(dllimport)
# else
#  define CT_EXPORT extern __declspec(dllimport)
# endif
#else
# define CT_EXPORT extern
#endif

#endif

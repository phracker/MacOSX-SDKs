/*
	Copyright:	(c) 2003-2018 by Apple, Inc., all rights reserved.
*/

// GL Deprecation
#ifdef QC_SILENCE_GL_DEPRECATION
#define QC_GL_DEPRECATED(from, to) NS_AVAILABLE_MAC(from)
#define QC_GL_CLASS_DEPRECATED(from, to) NS_CLASS_AVAILABLE_MAC(from)
#else
#define QC_GL_DEPRECATED(from, to) NS_DEPRECATED_MAC(from, to, "Quartz Composer OpenGL API deprecated. (Define QC_SILENCE_GL_DEPRECATION to silence these warnings)")
#define QC_GL_CLASS_DEPRECATED(from, to) NS_CLASS_DEPRECATED_MAC(from, to, "Quartz Composer OpenGL API deprecated. (Define QC_SILENCE_GL_DEPRECATION to silence these warnings)")
#endif

#ifdef QC_SILENCE_DEPRECATION
#define QC_DEPRECATED_MAC(to)  NS_AVAILABLE_MAC(10_4)
#define QC_CLASS_DEPRECATED_MAC(to)  NS_CLASS_AVAILABLE_MAC(10_4)
#else
#define QC_DEPRECATED_MAC(to)  NS_DEPRECATED_MAC(10_4, to, "QuartzComposer API deprecated. (Define QC_SILENCE_DEPRECATION to silence these warnings)")
#define QC_CLASS_DEPRECATED_MAC(to)  NS_CLASS_DEPRECATED_MAC(10_4, to, "QuartzComposer API deprecated. (Define QC_SILENCE_DEPRECATION to silence these warnings)")
#endif

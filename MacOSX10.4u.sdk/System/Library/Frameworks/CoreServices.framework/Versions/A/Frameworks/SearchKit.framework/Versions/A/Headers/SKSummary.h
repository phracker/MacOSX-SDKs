/*
     File:       SearchKit/SKSummary.h
 
     Contains:   SearchKit Interfaces.
 
     Version:    SearchKit-147.2~771
 
     Copyright:  © 2004-2006 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __SKSUMMARY__
#define __SKSUMMARY__

#ifndef __CFBASE__
#include <CoreFoundation/CFBase.h>
#endif

#ifndef __CFSTRING__
#include <CoreFoundation/CFString.h>
#endif


/*
 * Summarization API
 */

#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif


/*
 *  SKSummaryRef
 *  
 *  Summary:
 *    An opaque data type representing summary information.
 *  
 *  Discussion:
 *    A summary reference contains summary information, from which
 *    summary text can be obtained.
 */
typedef struct __SKSummary*             SKSummaryRef;
/*
 *  SKSummaryGetTypeID()
 *  
 *  Summary:
 *    Returns the type identifier of the SKSummaryRef type.
 *  
 *  Result:
 *    Returns a CFTypeID object, or <tt>NULL</tt> on failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFTypeID 
SKSummaryGetTypeID(void)                                      AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  SKSummaryCreateWithString()
 *  
 *  Summary:
 *    Creates a summary reference with text string.
 *  
 *  Discussion:
 *    Creates a summary reference that pre-computes what is needed for
 *    fast summarization. This function must be balanced with a call at
 *    a later time to CFRelease.
 *  
 *  Parameters:
 *    
 *    inString:
 *      the text string.
 *  
 *  Result:
 *    Returns a summary reference, or <tt>NULL</tt> on failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern SKSummaryRef 
SKSummaryCreateWithString(CFStringRef inString)               AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  SKSummaryGetSentenceCount()
 *  
 *  Summary:
 *    Gets the number of sentences available.
 *  
 *  Parameters:
 *    
 *    summary:
 *      A reference to the summary object
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFIndex 
SKSummaryGetSentenceCount(SKSummaryRef summary)               AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  SKSummaryGetParagraphCount()
 *  
 *  Summary:
 *    Gets the number of paragraphs available.
 *  
 *  Parameters:
 *    
 *    summary:
 *      A reference to the summary object
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFIndex 
SKSummaryGetParagraphCount(SKSummaryRef summary)              AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  SKSummaryCopySentenceAtIndex()
 *  
 *  Summary:
 *    Gets the ith sentence from the original text.
 *  
 *  Parameters:
 *    
 *    summary:
 *      A reference to the summary object
 *    
 *    i:
 *      zero-based index
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef 
SKSummaryCopySentenceAtIndex(
  SKSummaryRef   summary,
  CFIndex        i)                                           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  SKSummaryCopyParagraphAtIndex()
 *  
 *  Summary:
 *    Gets the ith paragraph from the original text.
 *  
 *  Parameters:
 *    
 *    summary:
 *      A reference to the summary object
 *    
 *    i:
 *      zero-based index
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef 
SKSummaryCopyParagraphAtIndex(
  SKSummaryRef   summary,
  CFIndex        i)                                           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  SKSummaryCopySentenceSummaryString()
 *  
 *  Summary:
 *    Gets a summary string that includes at most the requested number
 *    of sentences.
 *  
 *  Parameters:
 *    
 *    summary:
 *      A reference to the summary object
 *    
 *    numSentences:
 *      the number of sentences desired
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef 
SKSummaryCopySentenceSummaryString(
  SKSummaryRef   summary,
  CFIndex        numSentences)                                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  SKSummaryCopyParagraphSummaryString()
 *  
 *  Summary:
 *    Gets a summary string that includes at most the requested number
 *    of paragraphs.
 *  
 *  Parameters:
 *    
 *    summary:
 *      A reference to the summary object
 *    
 *    numParagraphs:
 *      the number of paragraphs desired
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef 
SKSummaryCopyParagraphSummaryString(
  SKSummaryRef   summary,
  CFIndex        numParagraphs)                               AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  SKSummaryGetSentenceSummaryInfo()
 *  
 *  Summary:
 *    Get detailed information about a sentence-based summary. Useful
 *    for constructing your own summary string. Arrays must be of size
 *    numSentences or they can be nil. Return value is the number of
 *    sentences actually returned. Sentences are returned in text order
 *    via outSentenceIndexOfSentences.
 *  
 *  Parameters:
 *    
 *    summary:
 *      A reference to the summary object
 *    
 *    numSentencesInSummary:
 *      the number of sentences desired
 *    
 *    outRankOrderOfSentences:
 *      array for returning the rank of each sentence; most important
 *      sentence is rank 1
 *    
 *    outSentenceIndexOfSentences:
 *      array for returning the index of each sentence; use
 *      SKSummaryCopySentenceAtIndex to get sentence
 *    
 *    outParagraphIndexOfSentences:
 *      array for returning the index of the paragraph in which
 *      sentence occured
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFIndex 
SKSummaryGetSentenceSummaryInfo(
  SKSummaryRef   summary,
  CFIndex        numSentencesInSummary,
  CFIndex *      outRankOrderOfSentences,
  CFIndex *      outSentenceIndexOfSentences,
  CFIndex *      outParagraphIndexOfSentences)                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  SKSummaryGetParagraphSummaryInfo()
 *  
 *  Summary:
 *    Get detailed information about a paragraph-based summary. Useful
 *    for constructing your own summary string. Arrays must be of size
 *    numParagraphs or they can be nil. Return value is the number of
 *    paragraphs actually returned. Paragraphs are returned in text
 *    order via outParagraphIndexOfParagraphs.
 *  
 *  Parameters:
 *    
 *    summary:
 *      A reference to the summary object
 *    
 *    numParagraphsInSummary:
 *      the number of sentences desired
 *    
 *    outRankOrderOfParagraphs:
 *      array for returning the rank of each paragraph; most important
 *      paragraph is rank 1
 *    
 *    outParagraphIndexOfParagraphs:
 *      array for returning the index of each paragraph; use
 *      SKSummaryCopyParagraphAtIndex to get paragraph
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFIndex 
SKSummaryGetParagraphSummaryInfo(
  SKSummaryRef   summary,
  CFIndex        numParagraphsInSummary,
  CFIndex *      outRankOrderOfParagraphs,
  CFIndex *      outParagraphIndexOfParagraphs)               AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



#ifdef __cplusplus
}
#endif

#endif /* __SKSUMMARY__ */


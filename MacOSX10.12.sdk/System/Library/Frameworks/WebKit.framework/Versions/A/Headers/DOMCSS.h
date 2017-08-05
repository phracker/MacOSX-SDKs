/*
 * Copyright (C) 2004 Apple Inc.  All rights reserved.
 * Copyright (C) 2006 Samuel Weinig <sam.weinig@gmail.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

#import <WebKit/DOMCore.h>
#import <WebKit/DOMDocument.h>
#import <WebKit/DOMElement.h>
#import <WebKit/DOMObject.h>
#import <WebKit/DOMStylesheets.h>

#import <WebKit/DOMCSSCharsetRule.h>
#import <WebKit/DOMCSSFontFaceRule.h>
#import <WebKit/DOMCSSImportRule.h>
#import <WebKit/DOMCSSMediaRule.h>
#import <WebKit/DOMCSSPageRule.h>
#import <WebKit/DOMCSSPrimitiveValue.h>
#import <WebKit/DOMCSSRule.h>
#import <WebKit/DOMCSSRuleList.h>
#import <WebKit/DOMCSSStyleDeclaration.h>
#import <WebKit/DOMCSSStyleRule.h>
#import <WebKit/DOMCSSStyleSheet.h>
#import <WebKit/DOMCSSUnknownRule.h>
#import <WebKit/DOMCSSValue.h>
#import <WebKit/DOMCSSValueList.h>
#import <WebKit/DOMCounter.h>
#import <WebKit/DOMRGBColor.h>
#import <WebKit/DOMRect.h>

@interface DOMCSSStyleDeclaration (DOMCSS2Properties)
- (NSString *)azimuth NS_AVAILABLE_MAC(10_4);
- (void)setAzimuth:(NSString *)azimuth NS_AVAILABLE_MAC(10_4);
- (NSString *)background NS_AVAILABLE_MAC(10_4);
- (void)setBackground:(NSString *)background NS_AVAILABLE_MAC(10_4);
- (NSString *)backgroundAttachment NS_AVAILABLE_MAC(10_4);
- (void)setBackgroundAttachment:(NSString *)backgroundAttachment NS_AVAILABLE_MAC(10_4);
- (NSString *)backgroundColor NS_AVAILABLE_MAC(10_4);
- (void)setBackgroundColor:(NSString *)backgroundColor NS_AVAILABLE_MAC(10_4);
- (NSString *)backgroundImage NS_AVAILABLE_MAC(10_4);
- (void)setBackgroundImage:(NSString *)backgroundImage NS_AVAILABLE_MAC(10_4);
- (NSString *)backgroundPosition NS_AVAILABLE_MAC(10_4);
- (void)setBackgroundPosition:(NSString *)backgroundPosition NS_AVAILABLE_MAC(10_4);
- (NSString *)backgroundRepeat NS_AVAILABLE_MAC(10_4);
- (void)setBackgroundRepeat:(NSString *)backgroundRepeat NS_AVAILABLE_MAC(10_4);
- (NSString *)border NS_AVAILABLE_MAC(10_4);
- (void)setBorder:(NSString *)border NS_AVAILABLE_MAC(10_4);
- (NSString *)borderCollapse NS_AVAILABLE_MAC(10_4);
- (void)setBorderCollapse:(NSString *)borderCollapse NS_AVAILABLE_MAC(10_4);
- (NSString *)borderColor NS_AVAILABLE_MAC(10_4);
- (void)setBorderColor:(NSString *)borderColor NS_AVAILABLE_MAC(10_4);
- (NSString *)borderSpacing NS_AVAILABLE_MAC(10_4);
- (void)setBorderSpacing:(NSString *)borderSpacing NS_AVAILABLE_MAC(10_4);
- (NSString *)borderStyle NS_AVAILABLE_MAC(10_4);
- (void)setBorderStyle:(NSString *)borderStyle NS_AVAILABLE_MAC(10_4);
- (NSString *)borderTop NS_AVAILABLE_MAC(10_4);
- (void)setBorderTop:(NSString *)borderTop NS_AVAILABLE_MAC(10_4);
- (NSString *)borderRight NS_AVAILABLE_MAC(10_4);
- (void)setBorderRight:(NSString *)borderRight NS_AVAILABLE_MAC(10_4);
- (NSString *)borderBottom NS_AVAILABLE_MAC(10_4);
- (void)setBorderBottom:(NSString *)borderBottom NS_AVAILABLE_MAC(10_4);
- (NSString *)borderLeft NS_AVAILABLE_MAC(10_4);
- (void)setBorderLeft:(NSString *)borderLeft NS_AVAILABLE_MAC(10_4);
- (NSString *)borderTopColor NS_AVAILABLE_MAC(10_4);
- (void)setBorderTopColor:(NSString *)borderTopColor NS_AVAILABLE_MAC(10_4);
- (NSString *)borderRightColor NS_AVAILABLE_MAC(10_4);
- (void)setBorderRightColor:(NSString *)borderRightColor NS_AVAILABLE_MAC(10_4);
- (NSString *)borderBottomColor NS_AVAILABLE_MAC(10_4);
- (void)setBorderBottomColor:(NSString *)borderBottomColor NS_AVAILABLE_MAC(10_4);
- (NSString *)borderLeftColor NS_AVAILABLE_MAC(10_4);
- (void)setBorderLeftColor:(NSString *)borderLeftColor NS_AVAILABLE_MAC(10_4);
- (NSString *)borderTopStyle NS_AVAILABLE_MAC(10_4);
- (void)setBorderTopStyle:(NSString *)borderTopStyle NS_AVAILABLE_MAC(10_4);
- (NSString *)borderRightStyle NS_AVAILABLE_MAC(10_4);
- (void)setBorderRightStyle:(NSString *)borderRightStyle NS_AVAILABLE_MAC(10_4);
- (NSString *)borderBottomStyle NS_AVAILABLE_MAC(10_4);
- (void)setBorderBottomStyle:(NSString *)borderBottomStyle NS_AVAILABLE_MAC(10_4);
- (NSString *)borderLeftStyle NS_AVAILABLE_MAC(10_4);
- (void)setBorderLeftStyle:(NSString *)borderLeftStyle NS_AVAILABLE_MAC(10_4);
- (NSString *)borderTopWidth NS_AVAILABLE_MAC(10_4);
- (void)setBorderTopWidth:(NSString *)borderTopWidth NS_AVAILABLE_MAC(10_4);
- (NSString *)borderRightWidth NS_AVAILABLE_MAC(10_4);
- (void)setBorderRightWidth:(NSString *)borderRightWidth NS_AVAILABLE_MAC(10_4);
- (NSString *)borderBottomWidth NS_AVAILABLE_MAC(10_4);
- (void)setBorderBottomWidth:(NSString *)borderBottomWidth NS_AVAILABLE_MAC(10_4);
- (NSString *)borderLeftWidth NS_AVAILABLE_MAC(10_4);
- (void)setBorderLeftWidth:(NSString *)borderLeftWidth NS_AVAILABLE_MAC(10_4);
- (NSString *)borderWidth NS_AVAILABLE_MAC(10_4);
- (void)setBorderWidth:(NSString *)borderWidth NS_AVAILABLE_MAC(10_4);
- (NSString *)bottom NS_AVAILABLE_MAC(10_4);
- (void)setBottom:(NSString *)bottom NS_AVAILABLE_MAC(10_4);
- (NSString *)captionSide NS_AVAILABLE_MAC(10_4);
- (void)setCaptionSide:(NSString *)captionSide NS_AVAILABLE_MAC(10_4);
- (NSString *)clear NS_AVAILABLE_MAC(10_4);
- (void)setClear:(NSString *)clear NS_AVAILABLE_MAC(10_4);
- (NSString *)clip NS_AVAILABLE_MAC(10_4);
- (void)setClip:(NSString *)clip NS_AVAILABLE_MAC(10_4);
- (NSString *)color NS_AVAILABLE_MAC(10_4);
- (void)setColor:(NSString *)color NS_AVAILABLE_MAC(10_4);
- (NSString *)content NS_AVAILABLE_MAC(10_4);
- (void)setContent:(NSString *)content NS_AVAILABLE_MAC(10_4);
- (NSString *)counterIncrement NS_AVAILABLE_MAC(10_4);
- (void)setCounterIncrement:(NSString *)counterIncrement NS_AVAILABLE_MAC(10_4);
- (NSString *)counterReset NS_AVAILABLE_MAC(10_4);
- (void)setCounterReset:(NSString *)counterReset NS_AVAILABLE_MAC(10_4);
- (NSString *)cue NS_AVAILABLE_MAC(10_4);
- (void)setCue:(NSString *)cue NS_AVAILABLE_MAC(10_4);
- (NSString *)cueAfter NS_AVAILABLE_MAC(10_4);
- (void)setCueAfter:(NSString *)cueAfter NS_AVAILABLE_MAC(10_4);
- (NSString *)cueBefore NS_AVAILABLE_MAC(10_4);
- (void)setCueBefore:(NSString *)cueBefore NS_AVAILABLE_MAC(10_4);
- (NSString *)cursor NS_AVAILABLE_MAC(10_4);
- (void)setCursor:(NSString *)cursor NS_AVAILABLE_MAC(10_4);
- (NSString *)direction NS_AVAILABLE_MAC(10_4);
- (void)setDirection:(NSString *)direction NS_AVAILABLE_MAC(10_4);
- (NSString *)display NS_AVAILABLE_MAC(10_4);
- (void)setDisplay:(NSString *)display NS_AVAILABLE_MAC(10_4);
- (NSString *)elevation NS_AVAILABLE_MAC(10_4);
- (void)setElevation:(NSString *)elevation NS_AVAILABLE_MAC(10_4);
- (NSString *)emptyCells NS_AVAILABLE_MAC(10_4);
- (void)setEmptyCells:(NSString *)emptyCells NS_AVAILABLE_MAC(10_4);
- (NSString *)cssFloat NS_AVAILABLE_MAC(10_4);
- (void)setCssFloat:(NSString *)cssFloat NS_AVAILABLE_MAC(10_4);
- (NSString *)font NS_AVAILABLE_MAC(10_4);
- (void)setFont:(NSString *)font NS_AVAILABLE_MAC(10_4);
- (NSString *)fontFamily NS_AVAILABLE_MAC(10_4);
- (void)setFontFamily:(NSString *)fontFamily NS_AVAILABLE_MAC(10_4);
- (NSString *)fontSize NS_AVAILABLE_MAC(10_4);
- (void)setFontSize:(NSString *)fontSize NS_AVAILABLE_MAC(10_4);
- (NSString *)fontSizeAdjust NS_AVAILABLE_MAC(10_4);
- (void)setFontSizeAdjust:(NSString *)fontSizeAdjust NS_AVAILABLE_MAC(10_4);
- (NSString *)fontStretch NS_AVAILABLE_MAC(10_4);
- (void)setFontStretch:(NSString *)fontStretch NS_AVAILABLE_MAC(10_4);
- (NSString *)fontStyle NS_AVAILABLE_MAC(10_4);
- (void)setFontStyle:(NSString *)fontStyle NS_AVAILABLE_MAC(10_4);
- (NSString *)fontVariant NS_AVAILABLE_MAC(10_4);
- (void)setFontVariant:(NSString *)fontVariant NS_AVAILABLE_MAC(10_4);
- (NSString *)fontWeight NS_AVAILABLE_MAC(10_4);
- (void)setFontWeight:(NSString *)fontWeight NS_AVAILABLE_MAC(10_4);
- (NSString *)height NS_AVAILABLE_MAC(10_4);
- (void)setHeight:(NSString *)height NS_AVAILABLE_MAC(10_4);
- (NSString *)left NS_AVAILABLE_MAC(10_4);
- (void)setLeft:(NSString *)left NS_AVAILABLE_MAC(10_4);
- (NSString *)letterSpacing NS_AVAILABLE_MAC(10_4);
- (void)setLetterSpacing:(NSString *)letterSpacing NS_AVAILABLE_MAC(10_4);
- (NSString *)lineHeight NS_AVAILABLE_MAC(10_4);
- (void)setLineHeight:(NSString *)lineHeight NS_AVAILABLE_MAC(10_4);
- (NSString *)listStyle NS_AVAILABLE_MAC(10_4);
- (void)setListStyle:(NSString *)listStyle NS_AVAILABLE_MAC(10_4);
- (NSString *)listStyleImage NS_AVAILABLE_MAC(10_4);
- (void)setListStyleImage:(NSString *)listStyleImage NS_AVAILABLE_MAC(10_4);
- (NSString *)listStylePosition NS_AVAILABLE_MAC(10_4);
- (void)setListStylePosition:(NSString *)listStylePosition NS_AVAILABLE_MAC(10_4);
- (NSString *)listStyleType NS_AVAILABLE_MAC(10_4);
- (void)setListStyleType:(NSString *)listStyleType NS_AVAILABLE_MAC(10_4);
- (NSString *)margin NS_AVAILABLE_MAC(10_4);
- (void)setMargin:(NSString *)margin NS_AVAILABLE_MAC(10_4);
- (NSString *)marginTop NS_AVAILABLE_MAC(10_4);
- (void)setMarginTop:(NSString *)marginTop NS_AVAILABLE_MAC(10_4);
- (NSString *)marginRight NS_AVAILABLE_MAC(10_4);
- (void)setMarginRight:(NSString *)marginRight NS_AVAILABLE_MAC(10_4);
- (NSString *)marginBottom NS_AVAILABLE_MAC(10_4);
- (void)setMarginBottom:(NSString *)marginBottom NS_AVAILABLE_MAC(10_4);
- (NSString *)marginLeft NS_AVAILABLE_MAC(10_4);
- (void)setMarginLeft:(NSString *)marginLeft NS_AVAILABLE_MAC(10_4);
- (NSString *)markerOffset NS_AVAILABLE_MAC(10_4);
- (void)setMarkerOffset:(NSString *)markerOffset NS_AVAILABLE_MAC(10_4);
- (NSString *)marks NS_AVAILABLE_MAC(10_4);
- (void)setMarks:(NSString *)marks NS_AVAILABLE_MAC(10_4);
- (NSString *)maxHeight NS_AVAILABLE_MAC(10_4);
- (void)setMaxHeight:(NSString *)maxHeight NS_AVAILABLE_MAC(10_4);
- (NSString *)maxWidth NS_AVAILABLE_MAC(10_4);
- (void)setMaxWidth:(NSString *)maxWidth NS_AVAILABLE_MAC(10_4);
- (NSString *)minHeight NS_AVAILABLE_MAC(10_4);
- (void)setMinHeight:(NSString *)minHeight NS_AVAILABLE_MAC(10_4);
- (NSString *)minWidth NS_AVAILABLE_MAC(10_4);
- (void)setMinWidth:(NSString *)minWidth NS_AVAILABLE_MAC(10_4);
- (NSString *)orphans NS_AVAILABLE_MAC(10_4);
- (void)setOrphans:(NSString *)orphans NS_AVAILABLE_MAC(10_4);
- (NSString *)outline NS_AVAILABLE_MAC(10_4);
- (void)setOutline:(NSString *)outline NS_AVAILABLE_MAC(10_4);
- (NSString *)outlineColor NS_AVAILABLE_MAC(10_4);
- (void)setOutlineColor:(NSString *)outlineColor NS_AVAILABLE_MAC(10_4);
- (NSString *)outlineStyle NS_AVAILABLE_MAC(10_4);
- (void)setOutlineStyle:(NSString *)outlineStyle NS_AVAILABLE_MAC(10_4);
- (NSString *)outlineWidth NS_AVAILABLE_MAC(10_4);
- (void)setOutlineWidth:(NSString *)outlineWidth NS_AVAILABLE_MAC(10_4);
- (NSString *)overflow NS_AVAILABLE_MAC(10_4);
- (void)setOverflow:(NSString *)overflow NS_AVAILABLE_MAC(10_4);
- (NSString *)padding NS_AVAILABLE_MAC(10_4);
- (void)setPadding:(NSString *)padding NS_AVAILABLE_MAC(10_4);
- (NSString *)paddingTop NS_AVAILABLE_MAC(10_4);
- (void)setPaddingTop:(NSString *)paddingTop NS_AVAILABLE_MAC(10_4);
- (NSString *)paddingRight NS_AVAILABLE_MAC(10_4);
- (void)setPaddingRight:(NSString *)paddingRight NS_AVAILABLE_MAC(10_4);
- (NSString *)paddingBottom NS_AVAILABLE_MAC(10_4);
- (void)setPaddingBottom:(NSString *)paddingBottom NS_AVAILABLE_MAC(10_4);
- (NSString *)paddingLeft NS_AVAILABLE_MAC(10_4);
- (void)setPaddingLeft:(NSString *)paddingLeft NS_AVAILABLE_MAC(10_4);
- (NSString *)page NS_AVAILABLE_MAC(10_4);
- (void)setPage:(NSString *)page NS_AVAILABLE_MAC(10_4);
- (NSString *)pageBreakAfter NS_AVAILABLE_MAC(10_4);
- (void)setPageBreakAfter:(NSString *)pageBreakAfter NS_AVAILABLE_MAC(10_4);
- (NSString *)pageBreakBefore NS_AVAILABLE_MAC(10_4);
- (void)setPageBreakBefore:(NSString *)pageBreakBefore NS_AVAILABLE_MAC(10_4);
- (NSString *)pageBreakInside NS_AVAILABLE_MAC(10_4);
- (void)setPageBreakInside:(NSString *)pageBreakInside NS_AVAILABLE_MAC(10_4);
- (NSString *)pause NS_AVAILABLE_MAC(10_4);
- (void)setPause:(NSString *)pause NS_AVAILABLE_MAC(10_4);
- (NSString *)pauseAfter NS_AVAILABLE_MAC(10_4);
- (void)setPauseAfter:(NSString *)pauseAfter NS_AVAILABLE_MAC(10_4);
- (NSString *)pauseBefore NS_AVAILABLE_MAC(10_4);
- (void)setPauseBefore:(NSString *)pauseBefore NS_AVAILABLE_MAC(10_4);
- (NSString *)pitch NS_AVAILABLE_MAC(10_4);
- (void)setPitch:(NSString *)pitch NS_AVAILABLE_MAC(10_4);
- (NSString *)pitchRange NS_AVAILABLE_MAC(10_4);
- (void)setPitchRange:(NSString *)pitchRange NS_AVAILABLE_MAC(10_4);
- (NSString *)playDuring NS_AVAILABLE_MAC(10_4);
- (void)setPlayDuring:(NSString *)playDuring NS_AVAILABLE_MAC(10_4);
- (NSString *)position NS_AVAILABLE_MAC(10_4);
- (void)setPosition:(NSString *)position NS_AVAILABLE_MAC(10_4);
- (NSString *)quotes NS_AVAILABLE_MAC(10_4);
- (void)setQuotes:(NSString *)quotes NS_AVAILABLE_MAC(10_4);
- (NSString *)richness NS_AVAILABLE_MAC(10_4);
- (void)setRichness:(NSString *)richness NS_AVAILABLE_MAC(10_4);
- (NSString *)right NS_AVAILABLE_MAC(10_4);
- (void)setRight:(NSString *)right NS_AVAILABLE_MAC(10_4);
- (NSString *)size NS_AVAILABLE_MAC(10_4);
- (void)setSize:(NSString *)size NS_AVAILABLE_MAC(10_4);
- (NSString *)speak NS_AVAILABLE_MAC(10_4);
- (void)setSpeak:(NSString *)speak NS_AVAILABLE_MAC(10_4);
- (NSString *)speakHeader NS_AVAILABLE_MAC(10_4);
- (void)setSpeakHeader:(NSString *)speakHeader NS_AVAILABLE_MAC(10_4);
- (NSString *)speakNumeral NS_AVAILABLE_MAC(10_4);
- (void)setSpeakNumeral:(NSString *)speakNumeral NS_AVAILABLE_MAC(10_4);
- (NSString *)speakPunctuation NS_AVAILABLE_MAC(10_4);
- (void)setSpeakPunctuation:(NSString *)speakPunctuation NS_AVAILABLE_MAC(10_4);
- (NSString *)speechRate NS_AVAILABLE_MAC(10_4);
- (void)setSpeechRate:(NSString *)speechRate NS_AVAILABLE_MAC(10_4);
- (NSString *)stress NS_AVAILABLE_MAC(10_4);
- (void)setStress:(NSString *)stress NS_AVAILABLE_MAC(10_4);
- (NSString *)tableLayout NS_AVAILABLE_MAC(10_4);
- (void)setTableLayout:(NSString *)tableLayout NS_AVAILABLE_MAC(10_4);
- (NSString *)textAlign NS_AVAILABLE_MAC(10_4);
- (void)setTextAlign:(NSString *)textAlign NS_AVAILABLE_MAC(10_4);
- (NSString *)textDecoration NS_AVAILABLE_MAC(10_4);
- (void)setTextDecoration:(NSString *)textDecoration NS_AVAILABLE_MAC(10_4);
- (NSString *)textIndent NS_AVAILABLE_MAC(10_4);
- (void)setTextIndent:(NSString *)textIndent NS_AVAILABLE_MAC(10_4);
- (NSString *)textShadow NS_AVAILABLE_MAC(10_4);
- (void)setTextShadow:(NSString *)textShadow NS_AVAILABLE_MAC(10_4);
- (NSString *)textTransform NS_AVAILABLE_MAC(10_4);
- (void)setTextTransform:(NSString *)textTransform NS_AVAILABLE_MAC(10_4);
- (NSString *)top NS_AVAILABLE_MAC(10_4);
- (void)setTop:(NSString *)top NS_AVAILABLE_MAC(10_4);
- (NSString *)unicodeBidi NS_AVAILABLE_MAC(10_4);
- (void)setUnicodeBidi:(NSString *)unicodeBidi NS_AVAILABLE_MAC(10_4);
- (NSString *)verticalAlign NS_AVAILABLE_MAC(10_4);
- (void)setVerticalAlign:(NSString *)verticalAlign NS_AVAILABLE_MAC(10_4);
- (NSString *)visibility NS_AVAILABLE_MAC(10_4);
- (void)setVisibility:(NSString *)visibility NS_AVAILABLE_MAC(10_4);
- (NSString *)voiceFamily NS_AVAILABLE_MAC(10_4);
- (void)setVoiceFamily:(NSString *)voiceFamily NS_AVAILABLE_MAC(10_4);
- (NSString *)volume NS_AVAILABLE_MAC(10_4);
- (void)setVolume:(NSString *)volume NS_AVAILABLE_MAC(10_4);
- (NSString *)whiteSpace NS_AVAILABLE_MAC(10_4);
- (void)setWhiteSpace:(NSString *)whiteSpace NS_AVAILABLE_MAC(10_4);
- (NSString *)widows NS_AVAILABLE_MAC(10_4);
- (void)setWidows:(NSString *)widows NS_AVAILABLE_MAC(10_4);
- (NSString *)width NS_AVAILABLE_MAC(10_4);
- (void)setWidth:(NSString *)width NS_AVAILABLE_MAC(10_4);
- (NSString *)wordSpacing NS_AVAILABLE_MAC(10_4);
- (void)setWordSpacing:(NSString *)wordSpacing NS_AVAILABLE_MAC(10_4);
- (NSString *)zIndex NS_AVAILABLE_MAC(10_4);
- (void)setZIndex:(NSString *)zIndex NS_AVAILABLE_MAC(10_4);
@end

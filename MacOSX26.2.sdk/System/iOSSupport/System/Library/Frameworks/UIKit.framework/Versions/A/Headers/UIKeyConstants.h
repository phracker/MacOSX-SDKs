#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIKeyConstants.h>)
//
//  UIKeyConstants.h
//  UIKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <UIKit/UIKitDefines.h>

#pragma once

/**
 * This file defines a table of standardized key codes, called "HID usages" used by USB keyboards to identify individual keys.
 *
 * A general note on Usages and languages: Due to the variation of keyboards from language to language, it is not feasible
 * to specify exact key mappings for every language. Where this list is not specific for a key function in a language, the
 * closest equivalent key position should be used, so that a keyboard may be modified for a different language by simply printing
 * different keycaps. One example is the Y key on a North American keyboard. In Germany this is typically Z. Rather than changing
 * the keyboard firmware to put the Z Usage into that place in the descriptor list, the vendor uses the Y Usage on both the North
 * American and German keyboards. This continues to be the existing practice in the industry, in order to minimize the number of
 * changes to the electronics to accommodate other languages.
 *
 * The following constants are from the USB 'HID Usage Tables' specification, revision 1.1rc3.
 */

API_AVAILABLE(ios(13.4), tvos(13.4)) API_UNAVAILABLE(watchos) typedef NS_ENUM(CFIndex, UIKeyboardHIDUsage)
{
    UIKeyboardHIDUsageKeyboardErrorRollOver   = 0x01,    /* ErrorRollOver */
    UIKeyboardHIDUsageKeyboardPOSTFail        = 0x02,    /* POSTFail */
    UIKeyboardHIDUsageKeyboardErrorUndefined  = 0x03,    /* ErrorUndefined */
    
    UIKeyboardHIDUsageKeyboardA    = 0x04,    /* a or A */
    UIKeyboardHIDUsageKeyboardB    = 0x05,    /* b or B */
    UIKeyboardHIDUsageKeyboardC    = 0x06,    /* c or C */
    UIKeyboardHIDUsageKeyboardD    = 0x07,    /* d or D */
    UIKeyboardHIDUsageKeyboardE    = 0x08,    /* e or E */
    UIKeyboardHIDUsageKeyboardF    = 0x09,    /* f or F */
    UIKeyboardHIDUsageKeyboardG    = 0x0A,    /* g or G */
    UIKeyboardHIDUsageKeyboardH    = 0x0B,    /* h or H */
    UIKeyboardHIDUsageKeyboardI    = 0x0C,    /* i or I */
    UIKeyboardHIDUsageKeyboardJ    = 0x0D,    /* j or J */
    UIKeyboardHIDUsageKeyboardK    = 0x0E,    /* k or K */
    UIKeyboardHIDUsageKeyboardL    = 0x0F,    /* l or L */
    UIKeyboardHIDUsageKeyboardM    = 0x10,    /* m or M */
    UIKeyboardHIDUsageKeyboardN    = 0x11,    /* n or N */
    UIKeyboardHIDUsageKeyboardO    = 0x12,    /* o or O */
    UIKeyboardHIDUsageKeyboardP    = 0x13,    /* p or P */
    UIKeyboardHIDUsageKeyboardQ    = 0x14,    /* q or Q */
    UIKeyboardHIDUsageKeyboardR    = 0x15,    /* r or R */
    UIKeyboardHIDUsageKeyboardS    = 0x16,    /* s or S */
    UIKeyboardHIDUsageKeyboardT    = 0x17,    /* t or T */
    UIKeyboardHIDUsageKeyboardU    = 0x18,    /* u or U */
    UIKeyboardHIDUsageKeyboardV    = 0x19,    /* v or V */
    UIKeyboardHIDUsageKeyboardW    = 0x1A,    /* w or W */
    UIKeyboardHIDUsageKeyboardX    = 0x1B,    /* x or X */
    UIKeyboardHIDUsageKeyboardY    = 0x1C,    /* y or Y */
    UIKeyboardHIDUsageKeyboardZ    = 0x1D,    /* z or Z */
    UIKeyboardHIDUsageKeyboard1    = 0x1E,    /* 1 or ! */
    UIKeyboardHIDUsageKeyboard2    = 0x1F,    /* 2 or @ */
    UIKeyboardHIDUsageKeyboard3    = 0x20,    /* 3 or # */
    UIKeyboardHIDUsageKeyboard4    = 0x21,    /* 4 or $ */
    UIKeyboardHIDUsageKeyboard5    = 0x22,    /* 5 or % */
    UIKeyboardHIDUsageKeyboard6    = 0x23,    /* 6 or ^ */
    UIKeyboardHIDUsageKeyboard7    = 0x24,    /* 7 or & */
    UIKeyboardHIDUsageKeyboard8    = 0x25,    /* 8 or * */
    UIKeyboardHIDUsageKeyboard9    = 0x26,    /* 9 or ( */
    UIKeyboardHIDUsageKeyboard0    = 0x27,    /* 0 or ) */
    
    UIKeyboardHIDUsageKeyboardReturnOrEnter       = 0x28,    /* Return (Enter) */
    UIKeyboardHIDUsageKeyboardEscape              = 0x29,    /* Escape */
    UIKeyboardHIDUsageKeyboardDeleteOrBackspace   = 0x2A,    /* Delete (Backspace) */
    UIKeyboardHIDUsageKeyboardTab                 = 0x2B,    /* Tab */
    UIKeyboardHIDUsageKeyboardSpacebar            = 0x2C,    /* Spacebar */
    UIKeyboardHIDUsageKeyboardHyphen              = 0x2D,    /* - or _ */
    UIKeyboardHIDUsageKeyboardEqualSign           = 0x2E,    /* = or + */
    UIKeyboardHIDUsageKeyboardOpenBracket         = 0x2F,    /* [ or { */
    UIKeyboardHIDUsageKeyboardCloseBracket        = 0x30,    /* ] or } */
    UIKeyboardHIDUsageKeyboardBackslash           = 0x31,    /* \ or | */
    UIKeyboardHIDUsageKeyboardNonUSPound          = 0x32,    /* Non-US # or _ */
                                                             /* Typical language mappings: US: \| Belg: μ`£ FrCa: <}> Dan:’* Dutch: <> Fren:*μ
                                                                                           Ger: #’ Ital: ù§ LatAm: }`] Nor:,* Span: }Ç Swed: ,*
                                                                                           Swiss: $£ UK: #~. */
    UIKeyboardHIDUsageKeyboardSemicolon           = 0x33,    /* ; or : */
    UIKeyboardHIDUsageKeyboardQuote               = 0x34,    /* ' or " */
    UIKeyboardHIDUsageKeyboardGraveAccentAndTilde = 0x35,    /* Grave Accent and Tilde */
    UIKeyboardHIDUsageKeyboardComma               = 0x36,    /* , or < */
    UIKeyboardHIDUsageKeyboardPeriod              = 0x37,    /* . or > */
    UIKeyboardHIDUsageKeyboardSlash               = 0x38,    /* / or ? */
    UIKeyboardHIDUsageKeyboardCapsLock            = 0x39,    /* Caps Lock */
    
    /* Function keys */
    UIKeyboardHIDUsageKeyboardF1             = 0x3A,    /* F1 */
    UIKeyboardHIDUsageKeyboardF2             = 0x3B,    /* F2 */
    UIKeyboardHIDUsageKeyboardF3             = 0x3C,    /* F3 */
    UIKeyboardHIDUsageKeyboardF4             = 0x3D,    /* F4 */
    UIKeyboardHIDUsageKeyboardF5             = 0x3E,    /* F5 */
    UIKeyboardHIDUsageKeyboardF6             = 0x3F,    /* F6 */
    UIKeyboardHIDUsageKeyboardF7             = 0x40,    /* F7 */
    UIKeyboardHIDUsageKeyboardF8             = 0x41,    /* F8 */
    UIKeyboardHIDUsageKeyboardF9             = 0x42,    /* F9 */
    UIKeyboardHIDUsageKeyboardF10            = 0x43,    /* F10 */
    UIKeyboardHIDUsageKeyboardF11            = 0x44,    /* F11 */
    UIKeyboardHIDUsageKeyboardF12            = 0x45,    /* F12 */
    UIKeyboardHIDUsageKeyboardPrintScreen    = 0x46,    /* Print Screen */
    UIKeyboardHIDUsageKeyboardScrollLock     = 0x47,    /* Scroll Lock */
    UIKeyboardHIDUsageKeyboardPause          = 0x48,    /* Pause */
    UIKeyboardHIDUsageKeyboardInsert         = 0x49,    /* Insert */
    UIKeyboardHIDUsageKeyboardHome           = 0x4A,    /* Home */
    UIKeyboardHIDUsageKeyboardPageUp         = 0x4B,    /* Page Up */
    UIKeyboardHIDUsageKeyboardDeleteForward  = 0x4C,    /* Delete Forward */
    UIKeyboardHIDUsageKeyboardEnd            = 0x4D,    /* End */
    UIKeyboardHIDUsageKeyboardPageDown       = 0x4E,    /* Page Down */
    UIKeyboardHIDUsageKeyboardRightArrow     = 0x4F,    /* Right Arrow */
    UIKeyboardHIDUsageKeyboardLeftArrow      = 0x50,    /* Left Arrow */
    UIKeyboardHIDUsageKeyboardDownArrow      = 0x51,    /* Down Arrow */
    UIKeyboardHIDUsageKeyboardUpArrow        = 0x52,    /* Up Arrow */
    
    /* Keypad (numpad) keys */
    UIKeyboardHIDUsageKeypadNumLock              = 0x53,    /* Keypad NumLock or Clear */
    UIKeyboardHIDUsageKeypadSlash                = 0x54,    /* Keypad / */
    UIKeyboardHIDUsageKeypadAsterisk             = 0x55,    /* Keypad * */
    UIKeyboardHIDUsageKeypadHyphen               = 0x56,    /* Keypad - */
    UIKeyboardHIDUsageKeypadPlus                 = 0x57,    /* Keypad + */
    UIKeyboardHIDUsageKeypadEnter                = 0x58,    /* Keypad Enter */
    UIKeyboardHIDUsageKeypad1                    = 0x59,    /* Keypad 1 or End */
    UIKeyboardHIDUsageKeypad2                    = 0x5A,    /* Keypad 2 or Down Arrow */
    UIKeyboardHIDUsageKeypad3                    = 0x5B,    /* Keypad 3 or Page Down */
    UIKeyboardHIDUsageKeypad4                    = 0x5C,    /* Keypad 4 or Left Arrow */
    UIKeyboardHIDUsageKeypad5                    = 0x5D,    /* Keypad 5 */
    UIKeyboardHIDUsageKeypad6                    = 0x5E,    /* Keypad 6 or Right Arrow */
    UIKeyboardHIDUsageKeypad7                    = 0x5F,    /* Keypad 7 or Home */
    UIKeyboardHIDUsageKeypad8                    = 0x60,    /* Keypad 8 or Up Arrow */
    UIKeyboardHIDUsageKeypad9                    = 0x61,    /* Keypad 9 or Page Up */
    UIKeyboardHIDUsageKeypad0                    = 0x62,    /* Keypad 0 or Insert */
    UIKeyboardHIDUsageKeypadPeriod               = 0x63,    /* Keypad . or Delete */
    UIKeyboardHIDUsageKeyboardNonUSBackslash     = 0x64,    /* Non-US \ or | */
                                                            /* On Apple ISO keyboards, this is the section symbol (§/±) */
                                                            /* Typical language mappings: Belg:<\> FrCa:«°» Dan:<\> Dutch:]|[ Fren:<> Ger:<|>
                                                                                          Ital:<> LatAm:<> Nor:<> Span:<> Swed:<|> Swiss:<\>
                                                                                          UK:\| Brazil: \|. */
    UIKeyboardHIDUsageKeyboardApplication        = 0x65,    /* Application */
    UIKeyboardHIDUsageKeyboardPower              = 0x66,    /* Power */
    UIKeyboardHIDUsageKeypadEqualSign            = 0x67,    /* Keypad = */
    
    /* Additional keys */
    UIKeyboardHIDUsageKeyboardF13        = 0x68,    /* F13 */
    UIKeyboardHIDUsageKeyboardF14        = 0x69,    /* F14 */
    UIKeyboardHIDUsageKeyboardF15        = 0x6A,    /* F15 */
    UIKeyboardHIDUsageKeyboardF16        = 0x6B,    /* F16 */
    UIKeyboardHIDUsageKeyboardF17        = 0x6C,    /* F17 */
    UIKeyboardHIDUsageKeyboardF18        = 0x6D,    /* F18 */
    UIKeyboardHIDUsageKeyboardF19        = 0x6E,    /* F19 */
    UIKeyboardHIDUsageKeyboardF20        = 0x6F,    /* F20 */
    UIKeyboardHIDUsageKeyboardF21        = 0x70,    /* F21 */
    UIKeyboardHIDUsageKeyboardF22        = 0x71,    /* F22 */
    UIKeyboardHIDUsageKeyboardF23        = 0x72,    /* F23 */
    UIKeyboardHIDUsageKeyboardF24        = 0x73,    /* F24 */
    UIKeyboardHIDUsageKeyboardExecute    = 0x74,    /* Execute */
    UIKeyboardHIDUsageKeyboardHelp       = 0x75,    /* Help */
    UIKeyboardHIDUsageKeyboardMenu       = 0x76,    /* Menu */
    UIKeyboardHIDUsageKeyboardSelect     = 0x77,    /* Select */
    UIKeyboardHIDUsageKeyboardStop       = 0x78,    /* Stop */
    UIKeyboardHIDUsageKeyboardAgain      = 0x79,    /* Again */
    UIKeyboardHIDUsageKeyboardUndo       = 0x7A,    /* Undo */
    UIKeyboardHIDUsageKeyboardCut        = 0x7B,    /* Cut */
    UIKeyboardHIDUsageKeyboardCopy       = 0x7C,    /* Copy */
    UIKeyboardHIDUsageKeyboardPaste      = 0x7D,    /* Paste */
    UIKeyboardHIDUsageKeyboardFind       = 0x7E,    /* Find */
    UIKeyboardHIDUsageKeyboardMute       = 0x7F,    /* Mute */
    UIKeyboardHIDUsageKeyboardVolumeUp   = 0x80,    /* Volume Up */
    UIKeyboardHIDUsageKeyboardVolumeDown = 0x81,    /* Volume Down */
    
    UIKeyboardHIDUsageKeyboardLockingCapsLock   = 0x82,    /* Locking Caps Lock */
    UIKeyboardHIDUsageKeyboardLockingNumLock    = 0x83,    /* Locking Num Lock */
                                                           /* Implemented as a locking key; sent as a toggle button. Available for legacy support;
                                                              however, most systems should use the non-locking version of this key. */
    UIKeyboardHIDUsageKeyboardLockingScrollLock = 0x84,    /* Locking Scroll Lock */
    UIKeyboardHIDUsageKeypadComma               = 0x85,    /* Keypad Comma */
    UIKeyboardHIDUsageKeypadEqualSignAS400      = 0x86,    /* Keypad Equal Sign for AS/400 */
    
    /* See the footnotes in the USB specification for what keys these are commonly mapped to.
     * https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf */
    UIKeyboardHIDUsageKeyboardInternational1    = 0x87,    /* International1 */
    UIKeyboardHIDUsageKeyboardInternational2    = 0x88,    /* International2 */
    UIKeyboardHIDUsageKeyboardInternational3    = 0x89,    /* International3 */
    UIKeyboardHIDUsageKeyboardInternational4    = 0x8A,    /* International4 */
    UIKeyboardHIDUsageKeyboardInternational5    = 0x8B,    /* International5 */
    UIKeyboardHIDUsageKeyboardInternational6    = 0x8C,    /* International6 */
    UIKeyboardHIDUsageKeyboardInternational7    = 0x8D,    /* International7 */
    UIKeyboardHIDUsageKeyboardInternational8    = 0x8E,    /* International8 */
    UIKeyboardHIDUsageKeyboardInternational9    = 0x8F,    /* International9 */
    
    /* LANG1: On Apple keyboard for Japanese, this is the kana switch (かな) key */
    /* On Korean keyboards, this is the Hangul/English toggle key. */
    UIKeyboardHIDUsageKeyboardLANG1    = 0x90,    /* LANG1 */
    
    /* LANG2: On Apple keyboards for Japanese, this is the alphanumeric (英数) key */
    /* On Korean keyboards, this is the Hanja conversion key. */
    UIKeyboardHIDUsageKeyboardLANG2    = 0x91,    /* LANG2 */
    
    /* LANG3: Defines the Katakana key for Japanese USB word-processing keyboards. */
    UIKeyboardHIDUsageKeyboardLANG3    = 0x92,    /* LANG3 */
    
    /* LANG4: Defines the Hiragana key for Japanese USB word-processing keyboards. */
    UIKeyboardHIDUsageKeyboardLANG4    = 0x93,    /* LANG4 */
    
    /* LANG5: Defines the Zenkaku/Hankaku key for Japanese USB word-processing keyboards. */
    UIKeyboardHIDUsageKeyboardLANG5    = 0x94,    /* LANG5 */
    
    /* LANG6-9: Reserved for language-specific functions, such as Front End Processors and Input Method Editors. */
    UIKeyboardHIDUsageKeyboardLANG6    = 0x95,    /* LANG6 */
    UIKeyboardHIDUsageKeyboardLANG7    = 0x96,    /* LANG7 */
    UIKeyboardHIDUsageKeyboardLANG8    = 0x97,    /* LANG8 */
    UIKeyboardHIDUsageKeyboardLANG9    = 0x98,    /* LANG9 */
    
    UIKeyboardHIDUsageKeyboardAlternateErase       = 0x99,    /* AlternateErase */
    UIKeyboardHIDUsageKeyboardSysReqOrAttention    = 0x9A,    /* SysReq/Attention */
    UIKeyboardHIDUsageKeyboardCancel               = 0x9B,    /* Cancel */
    UIKeyboardHIDUsageKeyboardClear                = 0x9C,    /* Clear */
    UIKeyboardHIDUsageKeyboardPrior                = 0x9D,    /* Prior */
    UIKeyboardHIDUsageKeyboardReturn               = 0x9E,    /* Return */
    UIKeyboardHIDUsageKeyboardSeparator            = 0x9F,    /* Separator */
    UIKeyboardHIDUsageKeyboardOut                  = 0xA0,    /* Out */
    UIKeyboardHIDUsageKeyboardOper                 = 0xA1,    /* Oper */
    UIKeyboardHIDUsageKeyboardClearOrAgain         = 0xA2,    /* Clear/Again */
    UIKeyboardHIDUsageKeyboardCrSelOrProps         = 0xA3,    /* CrSel/Props */
    UIKeyboardHIDUsageKeyboardExSel                = 0xA4,    /* ExSel */
    
    /* 0xA5-0xDF: Reserved */
    
    UIKeyboardHIDUsageKeyboardLeftControl  = 0xE0,    /* Left Control */
    UIKeyboardHIDUsageKeyboardLeftShift    = 0xE1,    /* Left Shift */
    UIKeyboardHIDUsageKeyboardLeftAlt      = 0xE2,    /* Left Alt */
    UIKeyboardHIDUsageKeyboardLeftGUI      = 0xE3,    /* Left GUI */
    UIKeyboardHIDUsageKeyboardRightControl = 0xE4,    /* Right Control */
    UIKeyboardHIDUsageKeyboardRightShift   = 0xE5,    /* Right Shift */
    UIKeyboardHIDUsageKeyboardRightAlt     = 0xE6,    /* Right Alt */
    UIKeyboardHIDUsageKeyboardRightGUI     = 0xE7,    /* Right GUI */
    
    /* 0xE8-0xFFFF: Reserved */
    UIKeyboardHIDUsageKeyboard_Reserved = 0xFFFF,
    
    
    /* Helpful aliases */
    UIKeyboardHIDUsageKeyboardHangul = UIKeyboardHIDUsageKeyboardLANG1,
    UIKeyboardHIDUsageKeyboardHanja  = UIKeyboardHIDUsageKeyboardLANG2,
    
    UIKeyboardHIDUsageKeyboardKanaSwitch = UIKeyboardHIDUsageKeyboardLANG1,
    UIKeyboardHIDUsageKeyboardAlphanumericSwitch = UIKeyboardHIDUsageKeyboardLANG2,
    UIKeyboardHIDUsageKeyboardKatakana = UIKeyboardHIDUsageKeyboardLANG3,
    UIKeyboardHIDUsageKeyboardHiragana = UIKeyboardHIDUsageKeyboardLANG4,
    UIKeyboardHIDUsageKeyboardZenkakuHankakuKanji = UIKeyboardHIDUsageKeyboardLANG5,
} API_UNAVAILABLE(watchos);



#else
#import <UIKitCore/UIKeyConstants.h>
#endif

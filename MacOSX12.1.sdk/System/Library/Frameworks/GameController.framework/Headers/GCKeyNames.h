//
//  GCKeys.h
//  GameController
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//
#import <GameController/GCExtern.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
A set of strings that can be used to access keyboard buttons
 
 @example keyboard.physicalInputProfile.buttons[GCKeySpacebar]
 
@see GCKeyboardInput.h
@see GCPhysicalInputProfile.h
*/

GAMECONTROLLER_EXTERN NSString *const GCKeyA API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                           /* a or A */
GAMECONTROLLER_EXTERN NSString *const GCKeyB API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                           /* b or B */
GAMECONTROLLER_EXTERN NSString *const GCKeyC API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                           /* c or C */
GAMECONTROLLER_EXTERN NSString *const GCKeyD API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                           /* d or D */
GAMECONTROLLER_EXTERN NSString *const GCKeyE API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                           /* e or E */
GAMECONTROLLER_EXTERN NSString *const GCKeyF API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                           /* f or F */
GAMECONTROLLER_EXTERN NSString *const GCKeyG API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                           /* g or G */
GAMECONTROLLER_EXTERN NSString *const GCKeyH API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                           /* h or H */
GAMECONTROLLER_EXTERN NSString *const GCKeyI API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                           /* i or I */
GAMECONTROLLER_EXTERN NSString *const GCKeyJ API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                           /* j or J */
GAMECONTROLLER_EXTERN NSString *const GCKeyK API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                           /* k or K */
GAMECONTROLLER_EXTERN NSString *const GCKeyL API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                           /* l or L */
GAMECONTROLLER_EXTERN NSString *const GCKeyM API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                           /* m or M */
GAMECONTROLLER_EXTERN NSString *const GCKeyN API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                           /* n or N */
GAMECONTROLLER_EXTERN NSString *const GCKeyO API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                           /* o or O */
GAMECONTROLLER_EXTERN NSString *const GCKeyP API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                           /* p or P */
GAMECONTROLLER_EXTERN NSString *const GCKeyQ API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                           /* q or Q */
GAMECONTROLLER_EXTERN NSString *const GCKeyR API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                           /* r or R */
GAMECONTROLLER_EXTERN NSString *const GCKeyS API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                           /* s or S */
GAMECONTROLLER_EXTERN NSString *const GCKeyT API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                           /* t or T */
GAMECONTROLLER_EXTERN NSString *const GCKeyU API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                           /* u or U */
GAMECONTROLLER_EXTERN NSString *const GCKeyV API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                           /* v or V */
GAMECONTROLLER_EXTERN NSString *const GCKeyW API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                           /* w or W */
GAMECONTROLLER_EXTERN NSString *const GCKeyX API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                           /* x or X */
GAMECONTROLLER_EXTERN NSString *const GCKeyY API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                           /* y or Y */
GAMECONTROLLER_EXTERN NSString *const GCKeyZ API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                           /* z or Z */
GAMECONTROLLER_EXTERN NSString *const GCKeyOne API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                         /* 1 or ! */
GAMECONTROLLER_EXTERN NSString *const GCKeyTwo API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                         /* 2 or @ */
GAMECONTROLLER_EXTERN NSString *const GCKeyThree API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* 3 or # */
GAMECONTROLLER_EXTERN NSString *const GCKeyFour API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* 4 or $ */
GAMECONTROLLER_EXTERN NSString *const GCKeyFive API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* 5 or % */
GAMECONTROLLER_EXTERN NSString *const GCKeySix API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                         /* 6 or ^ */
GAMECONTROLLER_EXTERN NSString *const GCKeySeven API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* 7 or & */
GAMECONTROLLER_EXTERN NSString *const GCKeyEight API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* 8 or * */
GAMECONTROLLER_EXTERN NSString *const GCKeyNine API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* 9 or ( */
GAMECONTROLLER_EXTERN NSString *const GCKeyZero API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* 0 or ) */
GAMECONTROLLER_EXTERN NSString *const GCKeyReturnOrEnter API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));               /* Return (Enter) */
GAMECONTROLLER_EXTERN NSString *const GCKeyEscape API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                      /* Escape */
GAMECONTROLLER_EXTERN NSString *const GCKeyDeleteOrBackspace API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));           /* Delete (Backspace) */
GAMECONTROLLER_EXTERN NSString *const GCKeyTab API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                         /* Tab */
GAMECONTROLLER_EXTERN NSString *const GCKeySpacebar API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                    /* Spacebar */
GAMECONTROLLER_EXTERN NSString *const GCKeyHyphen API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                      /* - or _ */
GAMECONTROLLER_EXTERN NSString *const GCKeyEqualSign API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                   /* = or + */
GAMECONTROLLER_EXTERN NSString *const GCKeyOpenBracket API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                 /* [ or { */
GAMECONTROLLER_EXTERN NSString *const GCKeyCloseBracket API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                /* ] or } */
GAMECONTROLLER_EXTERN NSString *const GCKeyBackslash API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                   /* \ or | */
GAMECONTROLLER_EXTERN NSString *const GCKeyNonUSPound API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                  /* Non-US # or _ */
GAMECONTROLLER_EXTERN NSString *const GCKeySemicolon API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                   /* ; or : */
GAMECONTROLLER_EXTERN NSString *const GCKeyQuote API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* ' or " */
GAMECONTROLLER_EXTERN NSString *const GCKeyGraveAccentAndTilde API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));         /* Grave Accent and Tilde */
GAMECONTROLLER_EXTERN NSString *const GCKeyComma API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* , or < */
GAMECONTROLLER_EXTERN NSString *const GCKeyPeriod API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                      /* . or > */
GAMECONTROLLER_EXTERN NSString *const GCKeySlash API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* / or ? */
GAMECONTROLLER_EXTERN NSString *const GCKeyCapsLock API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                    /* Caps Lock */

/* Function keys */
GAMECONTROLLER_EXTERN NSString *const GCKeyF1 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                          /* F1 */
GAMECONTROLLER_EXTERN NSString *const GCKeyF2 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                          /* F2 */
GAMECONTROLLER_EXTERN NSString *const GCKeyF3 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                          /* F3 */
GAMECONTROLLER_EXTERN NSString *const GCKeyF4 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                          /* F4 */
GAMECONTROLLER_EXTERN NSString *const GCKeyF5 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                          /* F5 */
GAMECONTROLLER_EXTERN NSString *const GCKeyF6 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                          /* F6 */
GAMECONTROLLER_EXTERN NSString *const GCKeyF7 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                          /* F7 */
GAMECONTROLLER_EXTERN NSString *const GCKeyF8 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                          /* F8 */
GAMECONTROLLER_EXTERN NSString *const GCKeyF9 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                          /* F9 */
GAMECONTROLLER_EXTERN NSString *const GCKeyF10 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                         /* F10 */
GAMECONTROLLER_EXTERN NSString *const GCKeyF11 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                         /* F11 */
GAMECONTROLLER_EXTERN NSString *const GCKeyF12 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                         /* F12 */
GAMECONTROLLER_EXTERN NSString *const GCKeyF13 API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));                         /* F13 */
GAMECONTROLLER_EXTERN NSString *const GCKeyF14 API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));                         /* F14 */
GAMECONTROLLER_EXTERN NSString *const GCKeyF15 API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));                         /* F15 */
GAMECONTROLLER_EXTERN NSString *const GCKeyF16 API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));                         /* F16 */
GAMECONTROLLER_EXTERN NSString *const GCKeyF17 API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));                         /* F17 */
GAMECONTROLLER_EXTERN NSString *const GCKeyF18 API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));                         /* F18 */
GAMECONTROLLER_EXTERN NSString *const GCKeyF19 API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));                         /* F19 */
GAMECONTROLLER_EXTERN NSString *const GCKeyF20 API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));                         /* F20 */
GAMECONTROLLER_EXTERN NSString *const GCKeyPrintScreen API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                 /* Print Screen */
GAMECONTROLLER_EXTERN NSString *const GCKeyScrollLock API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                  /* Scroll Lock */
GAMECONTROLLER_EXTERN NSString *const GCKeyPause API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* Pause */
GAMECONTROLLER_EXTERN NSString *const GCKeyInsert API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                      /* Insert */
GAMECONTROLLER_EXTERN NSString *const GCKeyHome API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* Home */
GAMECONTROLLER_EXTERN NSString *const GCKeyPageUp API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                      /* Page Up */
GAMECONTROLLER_EXTERN NSString *const GCKeyDeleteForward API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));               /* Delete Forward */
GAMECONTROLLER_EXTERN NSString *const GCKeyEnd API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                         /* End */
GAMECONTROLLER_EXTERN NSString *const GCKeyPageDown API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                    /* Page Down */
GAMECONTROLLER_EXTERN NSString *const GCKeyRightArrow API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                  /* Right Arrow */
GAMECONTROLLER_EXTERN NSString *const GCKeyLeftArrow API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                   /* Left Arrow */
GAMECONTROLLER_EXTERN NSString *const GCKeyDownArrow API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                   /* Down Arrow */
GAMECONTROLLER_EXTERN NSString *const GCKeyUpArrow API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                     /* Up Arrow */

/* Keypad (numpad) keys */
GAMECONTROLLER_EXTERN NSString *const GCKeyKeypadNumLock API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));               /* Keypad NumLock or Clear */
GAMECONTROLLER_EXTERN NSString *const GCKeyKeypadSlash API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                 /* Keypad / */
GAMECONTROLLER_EXTERN NSString *const GCKeyKeypadAsterisk API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));              /* Keypad * */
GAMECONTROLLER_EXTERN NSString *const GCKeyKeypadHyphen API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                /* Keypad - */
GAMECONTROLLER_EXTERN NSString *const GCKeyKeypadPlus API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                  /* Keypad + */
GAMECONTROLLER_EXTERN NSString *const GCKeyKeypadEnter API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                 /* Keypad Enter */
GAMECONTROLLER_EXTERN NSString *const GCKeyKeypad1 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                     /* Keypad 1 or End */
GAMECONTROLLER_EXTERN NSString *const GCKeyKeypad2 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                     /* Keypad 2 or Down Arrow */
GAMECONTROLLER_EXTERN NSString *const GCKeyKeypad3 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                     /* Keypad 3 or Page Down */
GAMECONTROLLER_EXTERN NSString *const GCKeyKeypad4 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                     /* Keypad 4 or Left Arrow */
GAMECONTROLLER_EXTERN NSString *const GCKeyKeypad5 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                     /* Keypad 5 */
GAMECONTROLLER_EXTERN NSString *const GCKeyKeypad6 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                     /* Keypad 6 or Right Arrow */
GAMECONTROLLER_EXTERN NSString *const GCKeyKeypad7 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                     /* Keypad 7 or Home */
GAMECONTROLLER_EXTERN NSString *const GCKeyKeypad8 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                     /* Keypad 8 or Up Arrow */
GAMECONTROLLER_EXTERN NSString *const GCKeyKeypad9 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                     /* Keypad 9 or Page Up */
GAMECONTROLLER_EXTERN NSString *const GCKeyKeypad0 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                     /* Keypad 0 or Insert */
GAMECONTROLLER_EXTERN NSString *const GCKeyKeypadPeriod API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                /* Keypad . or Delete */
GAMECONTROLLER_EXTERN NSString *const GCKeyKeypadEqualSign API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));             /* Keypad = */
GAMECONTROLLER_EXTERN NSString *const GCKeyNonUSBackslash API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));              /* Non-US \ or | */

GAMECONTROLLER_EXTERN NSString *const GCKeyApplication API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                 /* Application */
GAMECONTROLLER_EXTERN NSString *const GCKeyPower API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* Power */

GAMECONTROLLER_EXTERN NSString *const GCKeyInternational1 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));              /* International1 */
GAMECONTROLLER_EXTERN NSString *const GCKeyInternational2 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));              /* International2 */
GAMECONTROLLER_EXTERN NSString *const GCKeyInternational3 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));              /* International3 */
GAMECONTROLLER_EXTERN NSString *const GCKeyInternational4 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));              /* International4 */
GAMECONTROLLER_EXTERN NSString *const GCKeyInternational5 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));              /* International5 */
GAMECONTROLLER_EXTERN NSString *const GCKeyInternational6 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));              /* International6 */
GAMECONTROLLER_EXTERN NSString *const GCKeyInternational7 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));              /* International7 */
GAMECONTROLLER_EXTERN NSString *const GCKeyInternational8 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));              /* International8 */
GAMECONTROLLER_EXTERN NSString *const GCKeyInternational9 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));              /* International9 */

/* LANG1: On Apple keyboard for Japanese, this is the kana switch (かな) key */
/* On Korean keyboards, this is the Hangul/English toggle key. */
GAMECONTROLLER_EXTERN NSString *const GCKeyLANG1 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* LANG1 */

/* LANG2: On Apple keyboards for Japanese, this is the alphanumeric (英数) key */
/* On Korean keyboards, this is the Hanja conversion key. */
GAMECONTROLLER_EXTERN NSString *const GCKeyLANG2 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* LANG2 */

/* LANG3: Defines the Katakana key for Japanese USB word-processing keyboards. */
GAMECONTROLLER_EXTERN NSString *const GCKeyLANG3 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* LANG3 */

/* LANG4: Defines the Hiragana key for Japanese USB word-processing keyboards. */
GAMECONTROLLER_EXTERN NSString *const GCKeyLANG4 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* LANG4 */

/* LANG5: Defines the Zenkaku/Hankaku key for Japanese USB word-processing keyboards. */
GAMECONTROLLER_EXTERN NSString *const GCKeyLANG5 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* LANG5 */

/* LANG6-9: Reserved for language-specific functions, such as Front End Processors and Input Method Editors. */
GAMECONTROLLER_EXTERN NSString *const GCKeyLANG6 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* LANG6 */
GAMECONTROLLER_EXTERN NSString *const GCKeyLANG7 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* LANG7 */
GAMECONTROLLER_EXTERN NSString *const GCKeyLANG8 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* LANG8 */
GAMECONTROLLER_EXTERN NSString *const GCKeyLANG9 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* LANG9 */

GAMECONTROLLER_EXTERN NSString *const GCKeyLeftControl API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                 /* Left Control */
GAMECONTROLLER_EXTERN NSString *const GCKeyLeftShift API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                   /* Left Shift */
GAMECONTROLLER_EXTERN NSString *const GCKeyLeftAlt API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                     /* Left Alt */
GAMECONTROLLER_EXTERN NSString *const GCKeyLeftGUI API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                     /* Left GUI */
GAMECONTROLLER_EXTERN NSString *const GCKeyRightControl API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                /* Right Control */
GAMECONTROLLER_EXTERN NSString *const GCKeyRightShift API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                  /* Right Shift */
GAMECONTROLLER_EXTERN NSString *const GCKeyRightAlt API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                    /* Right Alt */
GAMECONTROLLER_EXTERN NSString *const GCKeyRightGUI API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                    /* Right GUI */

NS_ASSUME_NONNULL_END

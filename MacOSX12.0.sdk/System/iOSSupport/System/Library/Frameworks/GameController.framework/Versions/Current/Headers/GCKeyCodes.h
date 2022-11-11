//
//  GCKeyCodes.h
//  GameController
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <GameController/GCExtern.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
/**
 A set of low level key codes that can be used to access keyboard buttons
 
 @example [keyboard.keyboardInput buttonForKeyCode:GCKeyCodeSpacebar]
 
 @see GCKeyboardInput.h
 */

typedef CFIndex GCKeyCode NS_TYPED_ENUM API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeyA API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* a or A */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeyB API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* b or B */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeyC API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* c or C */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeyD API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* d or D */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeyE API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* e or E */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeyF API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* f or F */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeyG API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* g or G */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeyH API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* h or H */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeyI API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* i or I */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeyJ API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* j or J */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeyK API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* k or K */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeyL API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* l or L */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeyM API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* m or M */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeyN API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* n or N */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeyO API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* o or O */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeyP API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* p or P */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeyQ API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* q or Q */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeyR API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* r or R */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeyS API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* s or S */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeyT API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* t or T */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeyU API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* u or U */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeyV API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* v or V */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeyW API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* w or W */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeyX API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* x or X */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeyY API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* y or Y */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeyZ API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* z or Z */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeOne API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                         /* 1 or ! */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeTwo API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                         /* 2 or @ */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeThree API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* 3 or # */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeFour API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* 4 or $ */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeFive API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* 5 or % */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeSix API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                         /* 6 or ^ */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeSeven API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* 7 or & */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeEight API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* 8 or * */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeNine API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* 9 or ( */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeZero API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* 0 or ) */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeReturnOrEnter API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));               /* Return (Enter) */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeEscape API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                      /* Escape */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeDeleteOrBackspace API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));           /* Delete (Backspace) */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeTab API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                         /* Tab */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeSpacebar API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                    /* Spacebar */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeHyphen API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                      /* - or _ */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeEqualSign API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                   /* = or + */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeOpenBracket API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                 /* [ or { */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeCloseBracket API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                /* ] or } */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeBackslash API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                   /* \ or | */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeNonUSPound API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                  /* Non-US # or _ */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeSemicolon API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                   /* ; or : */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeQuote API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* ' or " */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeGraveAccentAndTilde API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));         /* Grave Accent and Tilde */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeComma API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* , or < */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodePeriod API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                      /* . or > */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeSlash API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* / or ? */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeCapsLock API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                    /* Caps Lock */

/* Function keys */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeF1 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                          /* F1 */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeF2 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                          /* F2 */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeF3 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                          /* F3 */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeF4 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                          /* F4 */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeF5 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                          /* F5 */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeF6 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                          /* F6 */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeF7 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                          /* F7 */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeF8 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                          /* F8 */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeF9 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                          /* F9 */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeF10 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                         /* F10 */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeF11 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                         /* F11 */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeF12 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                         /* F12 */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeF13 API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));                         /* F13 */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeF14 API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));                         /* F14 */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeF15 API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));                         /* F15 */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeF16 API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));                         /* F16 */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeF17 API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));                         /* F17 */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeF18 API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));                         /* F18 */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeF19 API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));                         /* F19 */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeF20 API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));                         /* F20 */

GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodePrintScreen API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                 /* Print Screen */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeScrollLock API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                  /* Scroll Lock */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodePause API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* Pause */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeInsert API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                      /* Insert */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeHome API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* Home */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodePageUp API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                      /* Page Up */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeDeleteForward API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));               /* Delete Forward */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeEnd API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                         /* End */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodePageDown API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                    /* Page Down */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeRightArrow API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                  /* Right Arrow */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeLeftArrow API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                   /* Left Arrow */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeDownArrow API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                   /* Down Arrow */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeUpArrow API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                     /* Up Arrow */

/* Keypad (numpad) keys */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeypadNumLock API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));               /* Keypad NumLock or Clear */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeypadSlash API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                 /* Keypad / */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeypadAsterisk API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));              /* Keypad * */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeypadHyphen API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                /* Keypad - */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeypadPlus API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                  /* Keypad + */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeypadEnter API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                 /* Keypad Enter */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeypad1 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                     /* Keypad 1 or End */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeypad2 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                     /* Keypad 2 or Down Arrow */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeypad3 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                     /* Keypad 3 or Page Down */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeypad4 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                     /* Keypad 4 or Left Arrow */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeypad5 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                     /* Keypad 5 */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeypad6 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                     /* Keypad 6 or Right Arrow */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeypad7 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                     /* Keypad 7 or Home */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeypad8 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                     /* Keypad 8 or Up Arrow */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeypad9 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                     /* Keypad 9 or Page Up */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeypad0 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                     /* Keypad 0 or Insert */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeypadPeriod API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                /* Keypad . or Delete */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeKeypadEqualSign API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));             /* Keypad = */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeNonUSBackslash API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));              /* Non-US \ or | */

GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeApplication API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                 /* Application */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodePower API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* Power */

GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeInternational1 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));              /* International1 */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeInternational2 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));              /* International2 */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeInternational3 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));              /* International3 */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeInternational4 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));              /* International4 */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeInternational5 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));              /* International5 */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeInternational6 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));              /* International6 */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeInternational7 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));              /* International7 */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeInternational8 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));              /* International8 */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeInternational9 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));              /* International9 */

/* LANG1: On Apple keyboard for Japanese, this is the kana switch (かな) key */
/* On Korean keyboards, this is the Hangul/English toggle key. */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeLANG1 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* LANG1 */

/* LANG2: On Apple keyboards for Japanese, this is the alphanumeric (英数) key */
/* On Korean keyboards, this is the Hanja conversion key. */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeLANG2 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* LANG2 */

/* LANG3: Defines the Katakana key for Japanese USB word-processing keyboards. */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeLANG3 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* LANG3 */

/* LANG4: Defines the Hiragana key for Japanese USB word-processing keyboards. */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeLANG4 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* LANG4 */

/* LANG5: Defines the Zenkaku/Hankaku key for Japanese USB word-processing keyboards. */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeLANG5 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* LANG5 */

/* LANG6-9: Reserved for language-specific functions, such as Front End Processors and Input Method Editors. */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeLANG6 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* LANG6 */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeLANG7 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* LANG7 */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeLANG8 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* LANG8 */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeLANG9 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* LANG9 */

GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeLeftControl API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                 /* Left Control */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeLeftShift API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                   /* Left Shift */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeLeftAlt API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                     /* Left Alt */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeLeftGUI API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                     /* Left GUI */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeRightControl API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                /* Right Control */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeRightShift API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                  /* Right Shift */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeRightAlt API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                    /* Right Alt */
GAMECONTROLLER_EXTERN GCKeyCode const GCKeyCodeRightGUI API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                    /* Right GUI */

NS_ASSUME_NONNULL_END

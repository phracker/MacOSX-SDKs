//
//  GCKeyCodes.h
//  GameController
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameController/GCExtern.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A set of low level key codes that can be used to access keyboard buttons
 
 @example [keyboard.keyboardInput buttonForKeyCode:GCKeyCodeSpacebar]
 
 @see GCKeyboardInput.h
 */

typedef CFIndex GCKeyCode NS_TYPED_ENUM API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeyA API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* a or A */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeyB API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* b or B */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeyC API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* c or C */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeyD API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* d or D */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeyE API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* e or E */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeyF API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* f or F */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeyG API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* g or G */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeyH API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* h or H */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeyI API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* i or I */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeyJ API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* j or J */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeyK API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* k or K */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeyL API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* l or L */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeyM API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* m or M */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeyN API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* n or N */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeyO API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* o or O */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeyP API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* p or P */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeyQ API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* q or Q */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeyR API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* r or R */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeyS API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* s or S */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeyT API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* t or T */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeyU API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* u or U */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeyV API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* v or V */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeyW API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* w or W */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeyX API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* x or X */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeyY API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* y or Y */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeyZ API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* z or Z */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeOne API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                         /* 1 or ! */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeTwo API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                         /* 2 or @ */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeThree API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* 3 or # */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeFour API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* 4 or $ */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeFive API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* 5 or % */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeSix API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                         /* 6 or ^ */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeSeven API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* 7 or & */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeEight API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* 8 or * */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeNine API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* 9 or ( */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeZero API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* 0 or ) */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeReturnOrEnter API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));               /* Return (Enter) */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeEscape API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                      /* Escape */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeDeleteOrBackspace API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));           /* Delete (Backspace) */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeTab API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                         /* Tab */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeSpacebar API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                    /* Spacebar */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeHyphen API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                      /* - or _ */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeEqualSign API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                   /* = or + */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeOpenBracket API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                 /* [ or { */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeCloseBracket API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                /* ] or } */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeBackslash API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                   /* \ or | */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeNonUSPound API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                  /* Non-US # or _ */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeSemicolon API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                   /* ; or : */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeQuote API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* ' or " */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeGraveAccentAndTilde API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));         /* Grave Accent and Tilde */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeComma API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* , or < */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodePeriod API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                      /* . or > */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeSlash API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* / or ? */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeCapsLock API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                    /* Caps Lock */

/* Function keys */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeF1 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                          /* F1 */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeF2 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                          /* F2 */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeF3 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                          /* F3 */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeF4 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                          /* F4 */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeF5 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                          /* F5 */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeF6 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                          /* F6 */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeF7 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                          /* F7 */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeF8 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                          /* F8 */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeF9 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                          /* F9 */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeF10 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                         /* F10 */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeF11 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                         /* F11 */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeF12 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                         /* F12 */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeF13 API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));                         /* F13 */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeF14 API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));                         /* F14 */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeF15 API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));                         /* F15 */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeF16 API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));                         /* F16 */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeF17 API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));                         /* F17 */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeF18 API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));                         /* F18 */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeF19 API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));                         /* F19 */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeF20 API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));                         /* F20 */

GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodePrintScreen API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                 /* Print Screen */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeScrollLock API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                  /* Scroll Lock */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodePause API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* Pause */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeInsert API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                      /* Insert */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeHome API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                        /* Home */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodePageUp API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                      /* Page Up */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeDeleteForward API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));               /* Delete Forward */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeEnd API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                         /* End */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodePageDown API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                    /* Page Down */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeRightArrow API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                  /* Right Arrow */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeLeftArrow API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                   /* Left Arrow */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeDownArrow API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                   /* Down Arrow */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeUpArrow API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                     /* Up Arrow */

/* Keypad (numpad) keys */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeypadNumLock API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));               /* Keypad NumLock or Clear */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeypadSlash API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                 /* Keypad / */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeypadAsterisk API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));              /* Keypad * */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeypadHyphen API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                /* Keypad - */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeypadPlus API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                  /* Keypad + */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeypadEnter API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                 /* Keypad Enter */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeypad1 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                     /* Keypad 1 or End */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeypad2 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                     /* Keypad 2 or Down Arrow */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeypad3 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                     /* Keypad 3 or Page Down */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeypad4 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                     /* Keypad 4 or Left Arrow */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeypad5 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                     /* Keypad 5 */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeypad6 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                     /* Keypad 6 or Right Arrow */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeypad7 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                     /* Keypad 7 or Home */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeypad8 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                     /* Keypad 8 or Up Arrow */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeypad9 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                     /* Keypad 9 or Page Up */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeypad0 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                     /* Keypad 0 or Insert */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeypadPeriod API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                /* Keypad . or Delete */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeKeypadEqualSign API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));             /* Keypad = */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeNonUSBackslash API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));              /* Non-US \ or | */

GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeApplication API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                 /* Application */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodePower API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* Power */

GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeInternational1 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));              /* International1 */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeInternational2 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));              /* International2 */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeInternational3 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));              /* International3 */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeInternational4 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));              /* International4 */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeInternational5 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));              /* International5 */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeInternational6 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));              /* International6 */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeInternational7 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));              /* International7 */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeInternational8 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));              /* International8 */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeInternational9 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));              /* International9 */

/* LANG1: On Apple keyboard for Japanese, this is the kana switch (かな) key */
/* On Korean keyboards, this is the Hangul/English toggle key. */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeLANG1 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* LANG1 */

/* LANG2: On Apple keyboards for Japanese, this is the alphanumeric (英数) key */
/* On Korean keyboards, this is the Hanja conversion key. */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeLANG2 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* LANG2 */

/* LANG3: Defines the Katakana key for Japanese USB word-processing keyboards. */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeLANG3 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* LANG3 */

/* LANG4: Defines the Hiragana key for Japanese USB word-processing keyboards. */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeLANG4 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* LANG4 */

/* LANG5: Defines the Zenkaku/Hankaku key for Japanese USB word-processing keyboards. */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeLANG5 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* LANG5 */

/* LANG6-9: Reserved for language-specific functions, such as Front End Processors and Input Method Editors. */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeLANG6 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* LANG6 */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeLANG7 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* LANG7 */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeLANG8 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* LANG8 */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeLANG9 API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                       /* LANG9 */

GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeLeftControl API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                 /* Left Control */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeLeftShift API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                   /* Left Shift */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeLeftAlt API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                     /* Left Alt */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeLeftGUI API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                     /* Left GUI */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeRightControl API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                /* Right Control */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeRightShift API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                  /* Right Shift */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeRightAlt API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                    /* Right Alt */
GAMECONTROLLER_EXPORT GCKeyCode const GCKeyCodeRightGUI API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));                    /* Right GUI */

NS_ASSUME_NONNULL_END

#pragma once

namespace nano {

// MOUSE BUTTON MACROS
#define 	NANO_MOUSE_BUTTON_1   0
#define 	NANO_MOUSE_BUTTON_2   1
#define 	NANO_MOUSE_BUTTON_3   2
#define 	NANO_MOUSE_BUTTON_4   3
#define 	NANO_MOUSE_BUTTON_5   4
#define 	NANO_MOUSE_BUTTON_6   5
#define 	NANO_MOUSE_BUTTON_7   6
#define 	NANO_MOUSE_BUTTON_8   7
#define 	NANO_MOUSE_BUTTON_LAST   NANO_MOUSE_BUTTON_8
#define 	NANO_MOUSE_BUTTON_LEFT   NANO_MOUSE_BUTTON_1
#define 	NANO_MOUSE_BUTTON_RIGHT   NANO_MOUSE_BUTTON_2
#define 	NANO_MOUSE_BUTTON_MIDDLE   NANO_MOUSE_BUTTON_3

// KEYBOARD MACROS
#define 	NANO_KEY_UNKNOWN   -1
#define 	NANO_KEY_SPACE   32
#define 	NANO_KEY_APOSTROPHE   39 /* ' */
#define 	NANO_KEY_COMMA   44 /* , */
#define 	NANO_KEY_MINUS   45 /* - */
#define 	NANO_KEY_PERIOD   46 /* . */
#define 	NANO_KEY_SLASH   47 /* / */
#define 	NANO_KEY_0   48
#define 	NANO_KEY_1   49
#define 	NANO_KEY_2   50
#define 	NANO_KEY_3   51
#define 	NANO_KEY_4   52
#define 	NANO_KEY_5   53
#define 	NANO_KEY_6   54
#define 	NANO_KEY_7   55
#define 	NANO_KEY_8   56
#define 	NANO_KEY_9   57
#define 	NANO_KEY_SEMICOLON   59 /* ; */
#define 	NANO_KEY_EQUAL   61 /* = */
#define 	NANO_KEY_A   65
#define 	NANO_KEY_B   66
#define 	NANO_KEY_C   67
#define 	NANO_KEY_D   68
#define 	NANO_KEY_E   69
#define 	NANO_KEY_F   70
#define 	NANO_KEY_G   71
#define 	NANO_KEY_H   72
#define 	NANO_KEY_I   73
#define 	NANO_KEY_J   74
#define 	NANO_KEY_K   75
#define 	NANO_KEY_L   76
#define 	NANO_KEY_M   77
#define 	NANO_KEY_N   78
#define 	NANO_KEY_O   79
#define 	NANO_KEY_P   80
#define 	NANO_KEY_Q   81
#define 	NANO_KEY_R   82
#define 	NANO_KEY_S   83
#define 	NANO_KEY_T   84
#define 	NANO_KEY_U   85
#define 	NANO_KEY_V   86
#define 	NANO_KEY_W   87
#define 	NANO_KEY_X   88
#define 	NANO_KEY_Y   89
#define 	NANO_KEY_Z   90
#define 	NANO_KEY_LEFT_BRACKET   91 /* [ */
#define 	NANO_KEY_BACKSLASH   92 /* \ */
#define 	NANO_KEY_RIGHT_BRACKET   93 /* ] */
#define 	NANO_KEY_GRAVE_ACCENT   96 /* ` */
#define 	NANO_KEY_WORLD_1   161 /* non-US #1 */
#define 	NANO_KEY_WORLD_2   162 /* non-US #2 */
#define 	NANO_KEY_ESCAPE   256
#define 	NANO_KEY_ENTER   257
#define 	NANO_KEY_TAB   258
#define 	NANO_KEY_BACKSPACE   259
#define 	NANO_KEY_INSERT   260
#define 	NANO_KEY_DELETE   261
#define 	NANO_KEY_RIGHT   262
#define 	NANO_KEY_LEFT   263 
#define 	NANO_KEY_DOWN   264
#define 	NANO_KEY_UP   265
#define 	NANO_KEY_PAGE_UP   266
#define 	NANO_KEY_PAGE_DOWN   267
#define 	NANO_KEY_HOME   268
#define 	NANO_KEY_END   269
#define 	NANO_KEY_CAPS_LOCK   280
#define 	NANO_KEY_SCROLL_LOCK   281
#define 	NANO_KEY_NUM_LOCK   282
#define 	NANO_KEY_PRINT_SCREEN   283
#define 	NANO_KEY_PAUSE   284
#define 	NANO_KEY_F1   290
#define 	NANO_KEY_F2   291
#define 	NANO_KEY_F3   292
#define 	NANO_KEY_F4   293
#define 	NANO_KEY_F5   294
#define 	NANO_KEY_F6   295
#define 	NANO_KEY_F7   296
#define 	NANO_KEY_F8   297
#define 	NANO_KEY_F9   298
#define 	NANO_KEY_F10   299
#define 	NANO_KEY_F11   300
#define 	NANO_KEY_F12   301
#define 	NANO_KEY_F13   302
#define 	NANO_KEY_F14   303
#define 	NANO_KEY_F15   304
#define 	NANO_KEY_F16   305
#define 	NANO_KEY_F17   306
#define 	NANO_KEY_F18   307
#define 	NANO_KEY_F19   308
#define 	NANO_KEY_F20   309
#define 	NANO_KEY_F21   310
#define 	NANO_KEY_F22   311
#define 	NANO_KEY_F23   312
#define 	NANO_KEY_F24   313
#define 	NANO_KEY_F25   314
#define 	NANO_KEY_KP_0   320
#define 	NANO_KEY_KP_1   321
#define 	NANO_KEY_KP_2   322
#define 	NANO_KEY_KP_3   323
#define 	NANO_KEY_KP_4   324
#define 	NANO_KEY_KP_5   325
#define 	NANO_KEY_KP_6   326
#define 	NANO_KEY_KP_7   327
#define 	NANO_KEY_KP_8   328
#define 	NANO_KEY_KP_9   329
#define 	NANO_KEY_KP_DECIMAL   330
#define 	NANO_KEY_KP_DIVIDE   331
#define 	NANO_KEY_KP_MULTIPLY   332
#define 	NANO_KEY_KP_SUBTRACT   333
#define 	NANO_KEY_KP_ADD   334
#define 	NANO_KEY_KP_ENTER   335
#define 	NANO_KEY_KP_EQUAL   336
#define 	NANO_KEY_LEFT_SHIFT   340
#define 	NANO_KEY_LEFT_CONTROL   341
#define 	NANO_KEY_LEFT_ALT   342
#define 	NANO_KEY_LEFT_SUPER   343
#define 	NANO_KEY_RIGHT_SHIFT   344
#define 	NANO_KEY_RIGHT_CONTROL   345
#define 	NANO_KEY_RIGHT_ALT   346
#define 	NANO_KEY_RIGHT_SUPER   347
#define 	NANO_KEY_MENU   348
#define 	NANO_KEY_LAST   NANO_KEY_MENU

}
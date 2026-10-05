#pragma once

//from glfw3.h

namespace Dark {

	enum class KeyState : uint8_t
	{
		TTRUE   =   1,
		FFALSE  =   0,
		RELEASE =   0,
		PRESS   =   1,
		REPEAT  =   2,
	};

	enum class KeyCode : uint16_t
	{
		KEY_SPACE = 32,
		KEY_APOSTROPHE = 39, /* ' */
		KEY_COMMA = 44, /* , */
		KEY_MINUS = 45, /* - */
		KEY_PERIOD = 46, /* . */
		KEY_SLASH = 47, /* / */
		KEY_0 = 48,
		KEY_1 = 49,
		KEY_2 = 50,
		KEY_3 = 51,
		KEY_4 = 52,
		KEY_5 = 53,
		KEY_6 = 54,
		KEY_7 = 55,
		KEY_8 = 56,
		KEY_9 = 57,
		KEY_SEMICOLON = 59, /* ; */
		KEY_EQUAL = 61, /* = */
		KEY_A = 65,
		KEY_B = 66,
		KEY_C = 67,
		KEY_D = 68,
		KEY_E = 69,
		KEY_F = 70,
		KEY_G = 71,
		KEY_H = 72,
		KEY_I = 73,
		KEY_J = 74,
		KEY_K = 75,
		KEY_L = 76,
		KEY_M = 77,
		KEY_N = 78,
		KEY_O = 79,
		KEY_P = 80,
		KEY_Q = 81,
		KEY_R = 82,
		KEY_S = 83,
		KEY_T = 84,
		KEY_U = 85,
		KEY_V = 86,
		KEY_W = 87,
		KEY_X = 88,
		KEY_Y = 89,
		KEY_Z = 90,
		KEY_LEFT_BRACKET = 91, /* [ */
		KEY_BACKSLASH = 92, /* \ */
		KEY_RIGHT_BRACKET = 93, /* ] */
		KEY_GRAVE_ACCENT = 96, /* ` */
		KEY_WORLD_1 = 161, /* non-US #1 */
		KEY_WORLD_2 = 162, /* non-US #2 */
		KEY_ESCAPE = 256,
		KEY_ENTER = 257,
		KEY_TAB = 258,
		KEY_BACKSPACE = 259,
		KEY_INSERT = 260,
		KEY_DELETE = 261,
		KEY_RIGHT = 262,
		KEY_LEFT = 263,
		KEY_DOWN = 264,
		KEY_UP = 265,
		KEY_PAGE_UP = 266,
		KEY_PAGE_DOWN = 267,
		KEY_HOME = 268,
		KEY_END = 269,
		KEY_CAPS_LOCK = 280,
		KEY_SCROLL_LOCK = 281,
		KEY_NUM_LOCK = 282,
		KEY_PRINT_SCREEN = 283,
		KEY_PAUSE = 284,
		KEY_F1 = 290,
		KEY_F2 = 291,
		KEY_F3 = 292,
		KEY_F4 = 293,
		KEY_F5 = 294,
		KEY_F6 = 295,
		KEY_F7 = 296,
		KEY_F8 = 297,
		KEY_F9 = 298,
		KEY_F10 = 299,
		KEY_F11 = 300,
		KEY_F12 = 301,
		KEY_F13 = 302,
		KEY_F14 = 303,
		KEY_F15 = 304,
		KEY_F16 = 305,
		KEY_F17 = 306,
		KEY_F18 = 307,
		KEY_F19 = 308,
		KEY_F20 = 309,
		KEY_F21 = 310,
		KEY_F22 = 311,
		KEY_F23 = 312,
		KEY_F24 = 313,
		KEY_F25 = 314,
		KEY_KP_0 = 320,
		KEY_KP_1 = 321,
		KEY_KP_2 = 322,
		KEY_KP_3 = 323,
		KEY_KP_4 = 324,
		KEY_KP_5 = 325,
		KEY_KP_6 = 326,
		KEY_KP_7 = 327,
		KEY_KP_8 = 328,
		KEY_KP_9 = 329,
		KEY_KP_DECIMAL = 330,
		KEY_KP_DIVIDE = 331,
		KEY_KP_MULTIPLY = 332,
		KEY_KP_SUBTRACT = 333,
		KEY_KP_ADD = 334,
		KEY_KP_ENTER = 335,
		KEY_KP_EQUAL = 336,
		KEY_LEFT_SHIFT = 340,
		KEY_LEFT_CONTROL = 341,
		KEY_LEFT_ALT = 342,
		KEY_LEFT_SUPER = 343,
		KEY_RIGHT_SHIFT = 344,
		KEY_RIGHT_CONTROL = 345,
		KEY_RIGHT_ALT = 346,
		KEY_RIGHT_SUPER = 347,
		KEY_MENU = 348,
		KEY_LAST = KEY_MENU
	};

}

//From glfw3.h

#define DK_TRUE                 ::Dark::KeyState::TTRUE
#define DK_FALSE                ::Dark::KeyState::FFALSE
#define DK_RELEASE              ::Dark::KeyState::RELEASE
#define DK_PRESS                ::Dark::KeyState::PRESS
#define DK_REPEAT               ::Dark::KeyState::REPEAT

#define DK_KEY_SPACE			::Dark::KeyCode::KEY_SPACE      
#define DK_KEY_APOSTROPHE       ::Dark::KeyCode::KEY_APOSTROPHE 
#define DK_KEY_COMMA            ::Dark::KeyCode::KEY_COMMA      
#define DK_KEY_MINUS            ::Dark::KeyCode::KEY_MINUS      
#define DK_KEY_PERIOD           ::Dark::KeyCode::KEY_PERIOD     
#define DK_KEY_SLASH            ::Dark::KeyCode::KEY_SLASH      
#define DK_KEY_0                ::Dark::KeyCode::KEY_0          
#define DK_KEY_1                ::Dark::KeyCode::KEY_1          
#define DK_KEY_2                ::Dark::KeyCode::KEY_2          
#define DK_KEY_3                ::Dark::KeyCode::KEY_3          
#define DK_KEY_4                ::Dark::KeyCode::KEY_4          
#define DK_KEY_5                ::Dark::KeyCode::KEY_5          
#define DK_KEY_6                ::Dark::KeyCode::KEY_6          
#define DK_KEY_7                ::Dark::KeyCode::KEY_7          
#define DK_KEY_8                ::Dark::KeyCode::KEY_8          
#define DK_KEY_9                ::Dark::KeyCode::KEY_9          
#define DK_KEY_SEMICOLON        ::Dark::KeyCode::KEY_SEMICOLON  
#define DK_KEY_EQUAL            ::Dark::KeyCode::KEY_EQUAL      
#define DK_KEY_A                ::Dark::KeyCode::KEY_A
#define DK_KEY_B                ::Dark::KeyCode::KEY_B
#define DK_KEY_C                ::Dark::KeyCode::KEY_C
#define DK_KEY_D                ::Dark::KeyCode::KEY_D
#define DK_KEY_E                ::Dark::KeyCode::KEY_E
#define DK_KEY_F                ::Dark::KeyCode::KEY_F
#define DK_KEY_G                ::Dark::KeyCode::KEY_G
#define DK_KEY_H                ::Dark::KeyCode::KEY_H
#define DK_KEY_I                ::Dark::KeyCode::KEY_I
#define DK_KEY_J                ::Dark::KeyCode::KEY_J
#define DK_KEY_K                ::Dark::KeyCode::KEY_K
#define DK_KEY_L                ::Dark::KeyCode::KEY_L
#define DK_KEY_M                ::Dark::KeyCode::KEY_M
#define DK_KEY_N                ::Dark::KeyCode::KEY_N
#define DK_KEY_O                ::Dark::KeyCode::KEY_O
#define DK_KEY_P                ::Dark::KeyCode::KEY_P
#define DK_KEY_Q                ::Dark::KeyCode::KEY_Q
#define DK_KEY_R                ::Dark::KeyCode::KEY_R
#define DK_KEY_S                ::Dark::KeyCode::KEY_S
#define DK_KEY_T                ::Dark::KeyCode::KEY_T
#define DK_KEY_U                ::Dark::KeyCode::KEY_U
#define DK_KEY_V                ::Dark::KeyCode::KEY_V
#define DK_KEY_W                ::Dark::KeyCode::KEY_W
#define DK_KEY_X                ::Dark::KeyCode::KEY_X
#define DK_KEY_Y                ::Dark::KeyCode::KEY_Y
#define DK_KEY_Z                ::Dark::KeyCode::KEY_Z
#define DK_KEY_LEFT_BRACKET     ::Dark::KeyCode::KEY_LEFT_BRACKET
#define DK_KEY_BACKSLASH        ::Dark::KeyCode::KEY_BACKSLASH
#define DK_KEY_RIGHT_BRACKET    ::Dark::KeyCode::KEY_RIGHT_BRACKET
#define DK_KEY_GRAVE_ACCENT     ::Dark::KeyCode::KEY_GRAVE_ACCENT
#define DK_KEY_WORLD_1          ::Dark::KeyCode::KEY_WORLD_1
#define DK_KEY_WORLD_2          ::Dark::KeyCode::KEY_WORLD_2

/* Function keys */
#define DK_KEY_ESCAPE           ::Dark::KeyCode::KEY_ESCAPE
#define DK_KEY_ENTER            ::Dark::KeyCode::KEY_ENTER
#define DK_KEY_TAB              ::Dark::KeyCode::KEY_TAB
#define DK_KEY_BACKSPACE        ::Dark::KeyCode::KEY_BACKSPACE
#define DK_KEY_INSERT           ::Dark::KeyCode::KEY_INSERT
#define DK_KEY_DELETE           ::Dark::KeyCode::KEY_DELETE
#define DK_KEY_RIGHT            ::Dark::KeyCode::KEY_RIGHT
#define DK_KEY_LEFT             ::Dark::KeyCode::KEY_LEFT
#define DK_KEY_DOWN             ::Dark::KeyCode::KEY_DOWN
#define DK_KEY_UP               ::Dark::KeyCode::KEY_UP
#define DK_KEY_PAGE_UP          ::Dark::KeyCode::KEY_PAGE_UP
#define DK_KEY_PAGE_DOWN        ::Dark::KeyCode::KEY_PAGE_DOWN
#define DK_KEY_HOME             ::Dark::KeyCode::KEY_HOME
#define DK_KEY_END              ::Dark::KeyCode::KEY_END
#define DK_KEY_CAPS_LOCK        ::Dark::KeyCode::KEY_CAPS_LOCK
#define DK_KEY_SCROLL_LOCK      ::Dark::KeyCode::KEY_SCROLL_LOCK
#define DK_KEY_NUM_LOCK         ::Dark::KeyCode::KEY_NUM_LOCK
#define DK_KEY_PRINT_SCREEN     ::Dark::KeyCode::KEY_PRINT_SCREEN
#define DK_KEY_PAUSE            ::Dark::KeyCode::KEY_PAUSE
#define DK_KEY_F1               ::Dark::KeyCode::KEY_F1
#define DK_KEY_F2               ::Dark::KeyCode::KEY_F2
#define DK_KEY_F3               ::Dark::KeyCode::KEY_F3
#define DK_KEY_F4               ::Dark::KeyCode::KEY_F4
#define DK_KEY_F5               ::Dark::KeyCode::KEY_F5
#define DK_KEY_F6               ::Dark::KeyCode::KEY_F6
#define DK_KEY_F7               ::Dark::KeyCode::KEY_F7
#define DK_KEY_F8               ::Dark::KeyCode::KEY_F8
#define DK_KEY_F9               ::Dark::KeyCode::KEY_F9
#define DK_KEY_F10              ::Dark::KeyCode::KEY_F10 
#define DK_KEY_F11              ::Dark::KeyCode::KEY_F11 
#define DK_KEY_F12              ::Dark::KeyCode::KEY_F12 
#define DK_KEY_F13              ::Dark::KeyCode::KEY_F13 
#define DK_KEY_F14              ::Dark::KeyCode::KEY_F14 
#define DK_KEY_F15              ::Dark::KeyCode::KEY_F15 
#define DK_KEY_F16              ::Dark::KeyCode::KEY_F16 
#define DK_KEY_F17              ::Dark::KeyCode::KEY_F17 
#define DK_KEY_F18              ::Dark::KeyCode::KEY_F18 
#define DK_KEY_F19              ::Dark::KeyCode::KEY_F19 
#define DK_KEY_F20              ::Dark::KeyCode::KEY_F20 
#define DK_KEY_F21              ::Dark::KeyCode::KEY_F21 
#define DK_KEY_F22              ::Dark::KeyCode::KEY_F22 
#define DK_KEY_F23              ::Dark::KeyCode::KEY_F23 
#define DK_KEY_F24              ::Dark::KeyCode::KEY_F24 
#define DK_KEY_F25              ::Dark::KeyCode::KEY_F25 
#define DK_KEY_KP_0             ::Dark::KeyCode::KEY_KP_0
#define DK_KEY_KP_1             ::Dark::KeyCode::KEY_KP_1
#define DK_KEY_KP_2             ::Dark::KeyCode::KEY_KP_2
#define DK_KEY_KP_3             ::Dark::KeyCode::KEY_KP_3
#define DK_KEY_KP_4             ::Dark::KeyCode::KEY_KP_4
#define DK_KEY_KP_5             ::Dark::KeyCode::KEY_KP_5
#define DK_KEY_KP_6             ::Dark::KeyCode::KEY_KP_6
#define DK_KEY_KP_7             ::Dark::KeyCode::KEY_KP_7
#define DK_KEY_KP_8             ::Dark::KeyCode::KEY_KP_8
#define DK_KEY_KP_9             ::Dark::KeyCode::KEY_KP_9
#define DK_KEY_KP_DECIMAL       ::Dark::KeyCode::KEY_KP_DECIMAL
#define DK_KEY_KP_DIVIDE        ::Dark::KeyCode::KEY_KP_DIVIDE
#define DK_KEY_KP_MULTIPLY      ::Dark::KeyCode::KEY_KP_MULTIPLY
#define DK_KEY_KP_SUBTRACT      ::Dark::KeyCode::KEY_KP_SUBTRACT
#define DK_KEY_KP_ADD           ::Dark::KeyCode::KEY_KP_ADD
#define DK_KEY_KP_ENTER         ::Dark::KeyCode::KEY_KP_ENTER
#define DK_KEY_KP_EQUAL         ::Dark::KeyCode::KEY_KP_EQUAL
#define DK_KEY_LEFT_SHIFT       ::Dark::KeyCode::KEY_LEFT_SHIFT
#define DK_KEY_LEFT_CONTROL     ::Dark::KeyCode::KEY_LEFT_CONTROL
#define DK_KEY_LEFT_ALT         ::Dark::KeyCode::KEY_LEFT_ALT
#define DK_KEY_LEFT_SUPER       ::Dark::KeyCode::KEY_LEFT_SUPER
#define DK_KEY_RIGHT_SHIFT      ::Dark::KeyCode::KEY_RIGHT_SHIFT
#define DK_KEY_RIGHT_CONTROL    ::Dark::KeyCode::KEY_RIGHT_CONTROL
#define DK_KEY_RIGHT_ALT        ::Dark::KeyCode::KEY_RIGHT_ALT
#define DK_KEY_RIGHT_SUPER      ::Dark::KeyCode::KEY_RIGHT_SUPER
#define DK_KEY_MENU             ::Dark::KeyCode::KEY_MENU

#define DK_KEY_LAST             ::Dark::KeyCode::KEY_LAST
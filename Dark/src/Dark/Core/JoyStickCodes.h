#pragma once

namespace Dark
{
	enum class JoyStickCode : uint8_t
	{
		JOYSTICK_1      =       0 ,
		JOYSTICK_2      =       1 ,
		JOYSTICK_3      =       2 ,
		JOYSTICK_4      =       3 ,
		JOYSTICK_5      =       4 ,
		JOYSTICK_6      =       5 ,
		JOYSTICK_7      =       6 ,
		JOYSTICK_8      =       7 ,
		JOYSTICK_9      =       8 ,
		JOYSTICK_10     =       9 ,
		JOYSTICK_11     =       10,
		JOYSTICK_12     =       11,
		JOYSTICK_13     =       12,
		JOYSTICK_14     =       13,
		JOYSTICK_15     =       14,
		JOYSTICK_16     =       15,
		JOYSTICK_LAST   =       JOYSTICK_16
	};
}

#define DK_JOYSTICK_1           ::Dark::JoyStickCode::JOYSTICK_1
#define DK_JOYSTICK_2           ::Dark::JoyStickCode::JOYSTICK_2
#define DK_JOYSTICK_3           ::Dark::JoyStickCode::JOYSTICK_3
#define DK_JOYSTICK_4           ::Dark::JoyStickCode::JOYSTICK_4
#define DK_JOYSTICK_5           ::Dark::JoyStickCode::JOYSTICK_5
#define DK_JOYSTICK_6           ::Dark::JoyStickCode::JOYSTICK_6
#define DK_JOYSTICK_7           ::Dark::JoyStickCode::JOYSTICK_7
#define DK_JOYSTICK_8           ::Dark::JoyStickCode::JOYSTICK_8
#define DK_JOYSTICK_9           ::Dark::JoyStickCode::JOYSTICK_9
#define DK_JOYSTICK_10          ::Dark::JoyStickCode::JOYSTICK_1
#define DK_JOYSTICK_11          ::Dark::JoyStickCode::JOYSTICK_11  
#define DK_JOYSTICK_12          ::Dark::JoyStickCode::JOYSTICK_12  
#define DK_JOYSTICK_13          ::Dark::JoyStickCode::JOYSTICK_13  
#define DK_JOYSTICK_14          ::Dark::JoyStickCode::JOYSTICK_14  
#define DK_JOYSTICK_15          ::Dark::JoyStickCode::JOYSTICK_15  
#define DK_JOYSTICK_16          ::Dark::JoyStickCode::JOYSTICK_16  
#define DK_JOYSTICK_LAST        ::Dark::JoyStickCode::JOYSTICK_LAST
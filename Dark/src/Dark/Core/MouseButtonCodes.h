#pragma once

namespace Dark {

	enum class MouseCode : uint8_t
	{
		MOUSE_BUTTON_1      =    0,
		MOUSE_BUTTON_2      =    1,
		MOUSE_BUTTON_3      =    2,
		MOUSE_BUTTON_4      =    3,
		MOUSE_BUTTON_5      =    4,
		MOUSE_BUTTON_6      =    5,
		MOUSE_BUTTON_7      =    6,
		MOUSE_BUTTON_8      =    7,
		MOUSE_BUTTON_LAST   =    MOUSE_BUTTON_8,
		MOUSE_BUTTON_LEFT   =    MOUSE_BUTTON_1,
		MOUSE_BUTTON_RIGHT  =    MOUSE_BUTTON_2,
		MOUSE_BUTTON_MIDDLE =    MOUSE_BUTTON_3,
	};

}

#define DK_MOUSE_BUTTON_1         ::Dark::MouseCode::MOUSE_BUTTON_1     
#define DK_MOUSE_BUTTON_2         ::Dark::MouseCode::MOUSE_BUTTON_2     
#define DK_MOUSE_BUTTON_3         ::Dark::MouseCode::MOUSE_BUTTON_3     
#define DK_MOUSE_BUTTON_4         ::Dark::MouseCode::MOUSE_BUTTON_4     
#define DK_MOUSE_BUTTON_5         ::Dark::MouseCode::MOUSE_BUTTON_5     
#define DK_MOUSE_BUTTON_6         ::Dark::MouseCode::MOUSE_BUTTON_6     
#define DK_MOUSE_BUTTON_7         ::Dark::MouseCode::MOUSE_BUTTON_7     
#define DK_MOUSE_BUTTON_8         ::Dark::MouseCode::MOUSE_BUTTON_8     
#define DK_MOUSE_BUTTON_LAST      ::Dark::MouseCode::MOUSE_BUTTON_LAST  
#define DK_MOUSE_BUTTON_LEFT      ::Dark::MouseCode::MOUSE_BUTTON_LEFT  
#define DK_MOUSE_BUTTON_RIGHT     ::Dark::MouseCode::MOUSE_BUTTON_RIGHT 
#define DK_MOUSE_BUTTON_MIDDLE    ::Dark::MouseCode::MOUSE_BUTTON_MIDDLE
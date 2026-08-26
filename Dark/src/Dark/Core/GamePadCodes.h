#pragma once

#define DK_GAMEPAD_BUTTON_A               0
#define DK_GAMEPAD_BUTTON_B               1
#define DK_GAMEPAD_BUTTON_X               2
#define DK_GAMEPAD_BUTTON_Y               3
#define DK_GAMEPAD_BUTTON_LEFT_BUMPER     4
#define DK_GAMEPAD_BUTTON_RIGHT_BUMPER    5
#define DK_GAMEPAD_BUTTON_BACK            6
#define DK_GAMEPAD_BUTTON_START           7
#define DK_GAMEPAD_BUTTON_GUIDE           8
#define DK_GAMEPAD_BUTTON_LEFT_THUMB      9
#define DK_GAMEPAD_BUTTON_RIGHT_THUMB     10
#define DK_GAMEPAD_BUTTON_DPAD_UP         11
#define DK_GAMEPAD_BUTTON_DPAD_RIGHT      12
#define DK_GAMEPAD_BUTTON_DPAD_DOWN       13
#define DK_GAMEPAD_BUTTON_DPAD_LEFT       14
#define DK_GAMEPAD_BUTTON_LAST            DK_GAMEPAD_BUTTON_DPAD_LEFT

#define DK_GAMEPAD_BUTTON_CROSS       DK_GAMEPAD_BUTTON_A
#define DK_GAMEPAD_BUTTON_CIRCLE      DK_GAMEPAD_BUTTON_B
#define DK_GAMEPAD_BUTTON_SQUARE      DK_GAMEPAD_BUTTON_X
#define DK_GAMEPAD_BUTTON_TRIANGLE    DK_GAMEPAD_BUTTON_Y
/*! @} */

/*! @defgroup gamepad_axes Gamepad axes
 *  @brief Gamepad axes.
 *
 *  See @ref gamepad for how these are used.
 *
 *  @ingroup input
 *  @{ */
#define DK_GAMEPAD_AXIS_LEFT_X        0
#define DK_GAMEPAD_AXIS_LEFT_Y        1
#define DK_GAMEPAD_AXIS_RIGHT_X       2
#define DK_GAMEPAD_AXIS_RIGHT_Y       3
#define DK_GAMEPAD_AXIS_LEFT_TRIGGER  4
#define DK_GAMEPAD_AXIS_RIGHT_TRIGGER 5
#define DK_GAMEPAD_AXIS_LAST          DK_GAMEPAD_AXIS_RIGHT_TRIGGER
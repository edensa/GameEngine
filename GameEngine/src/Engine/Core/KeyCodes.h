#pragma once

namespace engine
{
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space               = 32,
		Apostrophe          = 39, /* ' */
		Comma               = 44, /* , */
		Minus               = 45, /* - */
		Period              = 46, /* . */
		Slash               = 47, /* / */

		D0                  = 48, /* 0 */
		D1                  = 49, /* 1 */
		D2                  = 50, /* 2 */
		D3                  = 51, /* 3 */
		D4                  = 52, /* 4 */
		D5                  = 53, /* 5 */
		D6                  = 54, /* 6 */
		D7                  = 55, /* 7 */
		D8                  = 56, /* 8 */
		D9                  = 57, /* 9 */

		Semicolon           = 59, /* ; */
		Equal               = 61, /* = */

		A                   = 65,
		B                   = 66,
		C                   = 67,
		D                   = 68,
		E                   = 69,
		F                   = 70,
		G                   = 71,
		H                   = 72,
		I                   = 73,
		J                   = 74,
		K                   = 75,
		L                   = 76,
		M                   = 77,
		N                   = 78,
		O                   = 79,
		P                   = 80,
		Q                   = 81,
		R                   = 82,
		S                   = 83,
		T                   = 84,
		U                   = 85,
		V                   = 86,
		W                   = 87,
		X                   = 88,
		Y                   = 89,
		Z                   = 90,

		LeftBracket         = 91,  /* [ */
		Backslash           = 92,  /* \ */
		RightBracket        = 93,  /* ] */
		GraveAccent         = 96,  /* ` */

		World1              = 161, /* non-US #1 */
		World2              = 162, /* non-US #2 */

		/* Function keys */
		Escape              = 256,
		Enter               = 257,
		Tab                 = 258,
		Backspace           = 259,
		Insert              = 260,
		Delete              = 261,
		Right               = 262,
		Left                = 263,
		Down                = 264,
		Up                  = 265,
		PageUp              = 266,
		PageDown            = 267,
		Home                = 268,
		End                 = 269,
		CapsLock            = 280,
		ScrollLock          = 281,
		NumLock             = 282,
		PrintScreen         = 283,
		Pause               = 284,
		F1                  = 290,
		F2                  = 291,
		F3                  = 292,
		F4                  = 293,
		F5                  = 294,
		F6                  = 295,
		F7                  = 296,
		F8                  = 297,
		F9                  = 298,
		F10                 = 299,
		F11                 = 300,
		F12                 = 301,
		F13                 = 302,
		F14                 = 303,
		F15                 = 304,
		F16                 = 305,
		F17                 = 306,
		F18                 = 307,
		F19                 = 308,
		F20                 = 309,
		F21                 = 310,
		F22                 = 311,
		F23                 = 312,
		F24                 = 313,
		F25                 = 314,

		/* Keypad */
		KP0                 = 320,
		KP1                 = 321,
		KP2                 = 322,
		KP3                 = 323,
		KP4                 = 324,
		KP5                 = 325,
		KP6                 = 326,
		KP7                 = 327,
		KP8                 = 328,
		KP9                 = 329,
		KPDecimal           = 330,
		KPDivide            = 331,
		KPMultiply          = 332,
		KPSubtract          = 333,
		KPAdd               = 334,
		KPEnter             = 335,
		KPEqual             = 336,

		LeftShift           = 340,
		LeftControl         = 341,
		LeftAlt             = 342,
		LeftSuper           = 343,
		RightShift          = 344,
		RightControl        = 345,
		RightAlt            = 346,
		RightSuper          = 347,
		Menu                = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
	
}

#define ENGINE_KEY_SPACE           ::engine::Key::Space
#define ENGINE_KEY_APOSTROPHE      ::engine::Key::Apostrophe    /* ' */
#define ENGINE_KEY_COMMA           ::engine::Key::Comma         /* , */
#define ENGINE_KEY_MINUS           ::engine::Key::Minus         /* - */
#define ENGINE_KEY_PERIOD          ::engine::Key::Period        /* . */
#define ENGINE_KEY_SLASH           ::engine::Key::Slash         /* / */
#define ENGINE_KEY_0               ::engine::Key::D0
#define ENGINE_KEY_1               ::engine::Key::D1
#define ENGINE_KEY_2               ::engine::Key::D2
#define ENGINE_KEY_3               ::engine::Key::D3
#define ENGINE_KEY_4               ::engine::Key::D4
#define ENGINE_KEY_5               ::engine::Key::D5
#define ENGINE_KEY_6               ::engine::Key::D6
#define ENGINE_KEY_7               ::engine::Key::D7
#define ENGINE_KEY_8               ::engine::Key::D8
#define ENGINE_KEY_9               ::engine::Key::D9
#define ENGINE_KEY_SEMICOLON       ::engine::Key::Semicolon     /* ; */
#define ENGINE_KEY_EQUAL           ::engine::Key::Equal         /* = */
#define ENGINE_KEY_A               ::engine::Key::A
#define ENGINE_KEY_B               ::engine::Key::B
#define ENGINE_KEY_C               ::engine::Key::C
#define ENGINE_KEY_D               ::engine::Key::D
#define ENGINE_KEY_E               ::engine::Key::E
#define ENGINE_KEY_F               ::engine::Key::F
#define ENGINE_KEY_G               ::engine::Key::G
#define ENGINE_KEY_H               ::engine::Key::H
#define ENGINE_KEY_I               ::engine::Key::I
#define ENGINE_KEY_J               ::engine::Key::J
#define ENGINE_KEY_K               ::engine::Key::K
#define ENGINE_KEY_L               ::engine::Key::L
#define ENGINE_KEY_M               ::engine::Key::M
#define ENGINE_KEY_N               ::engine::Key::N
#define ENGINE_KEY_O               ::engine::Key::O
#define ENGINE_KEY_P               ::engine::Key::P
#define ENGINE_KEY_Q               ::engine::Key::Q
#define ENGINE_KEY_R               ::engine::Key::R
#define ENGINE_KEY_S               ::engine::Key::S
#define ENGINE_KEY_T               ::engine::Key::T
#define ENGINE_KEY_U               ::engine::Key::U
#define ENGINE_KEY_V               ::engine::Key::V
#define ENGINE_KEY_W               ::engine::Key::W
#define ENGINE_KEY_X               ::engine::Key::X
#define ENGINE_KEY_Y               ::engine::Key::Y
#define ENGINE_KEY_Z               ::engine::Key::Z
#define ENGINE_KEY_LEFT_BRACKET    ::engine::Key::LeftBracket   /* [ */
#define ENGINE_KEY_BACKSLASH       ::engine::Key::Backslash     /* \ */
#define ENGINE_KEY_RIGHT_BRACKET   ::engine::Key::RightBracket  /* ] */
#define ENGINE_KEY_GRAVE_ACCENT    ::engine::Key::GraveAccent   /* ` */
#define ENGINE_KEY_WORLD_1         ::engine::Key::World1        /* non-US #1 */
#define ENGINE_KEY_WORLD_2         ::engine::Key::World2        /* non-US #2 */

/* Function keys */
#define ENGINE_KEY_ESCAPE          ::engine::Key::Escape
#define ENGINE_KEY_ENTER           ::engine::Key::Enter
#define ENGINE_KEY_TAB             ::engine::Key::Tab
#define ENGINE_KEY_BACKSPACE       ::engine::Key::Backspace
#define ENGINE_KEY_INSERT          ::engine::Key::Insert
#define ENGINE_KEY_DELETE          ::engine::Key::Delete
#define ENGINE_KEY_RIGHT           ::engine::Key::Right
#define ENGINE_KEY_LEFT            ::engine::Key::Left
#define ENGINE_KEY_DOWN            ::engine::Key::Down
#define ENGINE_KEY_UP              ::engine::Key::Up
#define ENGINE_KEY_PAGE_UP         ::engine::Key::PageUp
#define ENGINE_KEY_PAGE_DOWN       ::engine::Key::PageDown
#define ENGINE_KEY_HOME            ::engine::Key::Home
#define ENGINE_KEY_END             ::engine::Key::End
#define ENGINE_KEY_CAPS_LOCK       ::engine::Key::CapsLock
#define ENGINE_KEY_SCROLL_LOCK     ::engine::Key::ScrollLock
#define ENGINE_KEY_NUM_LOCK        ::engine::Key::NumLock
#define ENGINE_KEY_PRINT_SCREEN    ::engine::Key::PrintScreen
#define ENGINE_KEY_PAUSE           ::engine::Key::Pause
#define ENGINE_KEY_F1              ::engine::Key::F1
#define ENGINE_KEY_F2              ::engine::Key::F2
#define ENGINE_KEY_F3              ::engine::Key::F3
#define ENGINE_KEY_F4              ::engine::Key::F4
#define ENGINE_KEY_F5              ::engine::Key::F5
#define ENGINE_KEY_F6              ::engine::Key::F6
#define ENGINE_KEY_F7              ::engine::Key::F7
#define ENGINE_KEY_F8              ::engine::Key::F8
#define ENGINE_KEY_F9              ::engine::Key::F9
#define ENGINE_KEY_F10             ::engine::Key::F10
#define ENGINE_KEY_F11             ::engine::Key::F11
#define ENGINE_KEY_F12             ::engine::Key::F12
#define ENGINE_KEY_F13             ::engine::Key::F13
#define ENGINE_KEY_F14             ::engine::Key::F14
#define ENGINE_KEY_F15             ::engine::Key::F15
#define ENGINE_KEY_F16             ::engine::Key::F16
#define ENGINE_KEY_F17             ::engine::Key::F17
#define ENGINE_KEY_F18             ::engine::Key::F18
#define ENGINE_KEY_F19             ::engine::Key::F19
#define ENGINE_KEY_F20             ::engine::Key::F20
#define ENGINE_KEY_F21             ::engine::Key::F21
#define ENGINE_KEY_F22             ::engine::Key::F22
#define ENGINE_KEY_F23             ::engine::Key::F23
#define ENGINE_KEY_F24             ::engine::Key::F24
#define ENGINE_KEY_F25             ::engine::Key::F25

/* Keypad */
#define ENGINE_KEY_KP_0            ::engine::Key::KP0
#define ENGINE_KEY_KP_1            ::engine::Key::KP1
#define ENGINE_KEY_KP_2            ::engine::Key::KP2
#define ENGINE_KEY_KP_3            ::engine::Key::KP3
#define ENGINE_KEY_KP_4            ::engine::Key::KP4
#define ENGINE_KEY_KP_5            ::engine::Key::KP5
#define ENGINE_KEY_KP_6            ::engine::Key::KP6
#define ENGINE_KEY_KP_7            ::engine::Key::KP7
#define ENGINE_KEY_KP_8            ::engine::Key::KP8
#define ENGINE_KEY_KP_9            ::engine::Key::KP9
#define ENGINE_KEY_KP_DECIMAL      ::engine::Key::KPDecimal
#define ENGINE_KEY_KP_DIVIDE       ::engine::Key::KPDivide
#define ENGINE_KEY_KP_MULTIPLY     ::engine::Key::KPMultiply
#define ENGINE_KEY_KP_SUBTRACT     ::engine::Key::KPSubtract
#define ENGINE_KEY_KP_ADD          ::engine::Key::KPAdd
#define ENGINE_KEY_KP_ENTER        ::engine::Key::KPEnter
#define ENGINE_KEY_KP_EQUAL        ::engine::Key::KPEqual

#define ENGINE_KEY_LEFT_SHIFT      ::engine::Key::LeftShift
#define ENGINE_KEY_LEFT_CONTROL    ::engine::Key::LeftControl
#define ENGINE_KEY_LEFT_ALT        ::engine::Key::LeftAlt
#define ENGINE_KEY_LEFT_SUPER      ::engine::Key::LeftSuper
#define ENGINE_KEY_RIGHT_SHIFT     ::engine::Key::RightShift
#define ENGINE_KEY_RIGHT_CONTROL   ::engine::Key::RightControl
#define ENGINE_KEY_RIGHT_ALT       ::engine::Key::RightAlt
#define ENGINE_KEY_RIGHT_SUPER     ::engine::Key::RightSuper
#define ENGINE_KEY_MENU            ::engine::Key::Menu
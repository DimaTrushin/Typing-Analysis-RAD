//---------------------------------------------------------------------------

#ifndef UnitKeyboardRelatedDefinitionsH
#define UnitKeyboardRelatedDefinitionsH
// ---------------------------------------------------------------------------
// Define
// ---------------------------------------------------------------------------

// Symbols for system keys
// Needed for a "raw" output of a captured text
#define SMB_ENTER     L'\u2BA0'
#define SMB_CTRL      L'\u2353'
#define SMB_LCTRL     L'\u2343'
#define SMB_RCTRL     L'\u2344'
#define SMB_ALT       L'\u2338'
#define SMB_LALT      L'\u2347'
#define SMB_RALT      L'\u2348'
#define SMB_SHIFT     L'\u21E7'
#define SMB_LSHIFT    L'\u2B01'
#define SMB_RSHIFT    L'\u2B00'
#define SMB_BACKSPACE L'\u232B'
#define SMB_CAPSLOCK  L'\u2B89'


// Aliases for keys are based on the standard
// QWERTY layout

// VKCode for numbers
#define VK_0 0x30
#define VK_1 0x31
#define VK_2 0x32
#define VK_3 0x33
#define VK_4 0x34
#define VK_5 0x35
#define VK_6 0x36
#define VK_7 0x37
#define VK_8 0x38
#define VK_9 0x39

// VKCode for english letters
#define VK_A 0x41
#define VK_B 0x42
#define VK_C 0x43
#define VK_D 0x44
#define VK_E 0x45
#define VK_F 0x46
#define VK_G 0x47
#define VK_H 0x48
#define VK_I 0x49
#define VK_J 0x4A
#define VK_K 0x4B
#define VK_L 0x4C
#define VK_M 0x4D
#define VK_N 0x4E
#define VK_O 0x4F
#define VK_P 0x50
#define VK_Q 0x51
#define VK_R 0x52
#define VK_S 0x53
#define VK_T 0x54
#define VK_U 0x55
#define VK_V 0x56
#define VK_W 0x57
#define VK_X 0x58
#define VK_Y 0x59
#define VK_Z 0x5A

// REDEFINE
// VKCodes from 0xBA to 0xBF
#define VK_ENG_SEMICOLON      VK_OEM_1
#define VK_ENG_PLUS           VK_OEM_PLUS
#define VK_ENG_COMMA          VK_OEM_COMMA
#define VK_ENG_MINUS          VK_OEM_MINUS
#define VK_ENG_PERIOD         VK_OEM_PERIOD
#define VK_ENG_SLASH_QUESTION VK_OEM_2

// REDEFINE
// VKCodes from 0xDB to 0xDE
#define VK_ENG_LEFT_BRACE     VK_OEM_4
#define VK_ENG_BACKSLASH      VK_OEM_5
#define VK_ENG_RIGHT_BRACE    VK_OEM_6
#define VK_ENG_QUOTE          VK_OEM_7

// REDEFINE
// VKCode for 0xC0
#define VK_ENG_TILDE          VK_OEM_3

// ---------------------------------------------------------------------------
// VKCodes information
// ---------------------------------------------------------------------------

// VKCode от 0xBA до 0xBF
// VK_OEM_1       0xBA    ;:
// VK_OEM_PLUS    0xBB    =+
// VK_OEM_COMMA   0xBC    ,<
// VK_OEM_MINUS   0xBD    -_
// VK_OEM_PERIOD  0xBE    .>
// VK_OEM_2       0xBF    /?

// VKCode от 0xDB до 0xDE
// VK_OEM_4       0xDB    [{
// VK_OEM_5       0xDC    \|
// VK_OEM_6       0xDD    ]}
// VK_OEM_7       0xDE    '"

// VKCode для 0xC0
// VK_OEM_3       0xC0    `~
//---------------------------------------------------------------------------
#endif

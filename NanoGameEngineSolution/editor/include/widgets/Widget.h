#pragma once

namespace nano { namespace editor {
		
#define MAIN_MENU_BAR_HEIGHT 19

// Entity Select Widget
// Position: upper left 
#define ENTITY_SELECT_WIDTH 200
#define ENTITY_SELECT_HEIGHT_RATIO 5/10 // Ratio of realestate the widgets height take of the window height

// Utility Select Widget
// Position: middle left
#define UNNAMED_WIDGET_HEIGHT_RATIO 3/10 // --||--
#define UNNAMED_WIDGET_WIDTH 200

// Utility Widget
// Position: bottom left
#define UTILITY_HEIGHT_RATIO 2/10
#define UTILITY_WIDTH_RATIO 5/10 // This will be ratio~based on screen width

// Entity Inspector Widget
// Position: upper right
#define ENTITY_INSPECTOR_HEIGHT_RATIO 8/10 // --||..
#define ENTITY_INSPECTOR_WIDTH 235

// Console Widget
// Position: bottom right
#define CONSOLE_WIDTH_RATIO 5/10
#define CONSOLE_HEIGHT_RATIO 2/10

} }
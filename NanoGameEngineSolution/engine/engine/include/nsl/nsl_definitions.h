#pragma once

namespace nano { namespace engine {
		static std::string cmdExpressions[] = { "move", "destroy", "create", "setPosition", "setSize", };

		static std::string passiveLogicExpressions[] = { "keyPressed", "keyReleased", "mousePressed", "mouseReleased" };
		static std::string logicExpressions[] = { "keyDown", "keyPressed", "keyReleased", "mousePressed", "mouseReleased" };

		static std::string parserTokens[] = { "if", "then", "var" };
		
		static char identifierSplit = ',';  
} }
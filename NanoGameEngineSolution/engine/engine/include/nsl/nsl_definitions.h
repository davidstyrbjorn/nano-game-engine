#pragma once

namespace nano { namespace engine {
		static std::string cmdExpressions[] = { "move", "destroy", "create" };
		static std::string logicExpressions[] = { "keyDown" };
		static std::string parserTokens[] = { "if", "then", "var" };
		
		static char identifierSplit = ',';  
} }
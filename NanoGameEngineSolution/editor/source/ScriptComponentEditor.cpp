#include"../include/components/ScriptComponentEditor.h"

#include"../include/systems/EditorConfig.h"

#include<Windows.h>
#include<StringHelp.h>
#include<fstream>

namespace nano { namespace editor {

	ScriptComponent::ScriptComponent()
	{
		m_scriptHndl = "none";
	}

	void ScriptComponent::Start()
	{
	}

	void ScriptComponent::Update()
	{
	}

	void ScriptComponent::setScriptHndl()
	{
		OPENFILENAME ofn;       // common dialog box structure
		HWND hwnd;				// owner window
		hwnd = GetActiveWindow();
		HANDLE hf;              // file handle
		char fileNameBuffer[256];
								// Initialize OPENFILENAME
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = hwnd;
		ofn.lpstrFile = fileNameBuffer;
		// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
		// use the contents of szFile to initialize itself.
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = sizeof(fileNameBuffer);
		ofn.lpstrFilter = "All\0*.nsl\0Text\0*.TXT\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (GetOpenFileName(&ofn) == TRUE)
		{
			m_scriptHndl = getFileName(fileNameBuffer);
			// @TODO: Check for correct file extension (nsl)
		}
	}

	std::string ScriptComponent::getScriptHndl()
	{
		return m_scriptHndl;
	}
	
} }
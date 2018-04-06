#include"../include/components/ScriptComponentEditor.h"

#include"../include/systems/EditorConfig.h"

#include<Windows.h>
#include<StringHelp.h>
#include<fstream>

namespace nano { namespace editor {

	ScriptComponent::ScriptComponent(std::string a_hndl)
	{
		m_scriptHndl = a_hndl;
	}

	void ScriptComponent::Start()
	{
	}

	void ScriptComponent::Update()
	{
	}

	void ScriptComponent::setScriptHndl(const std::string &a_hndl)
	{
		m_scriptHndl = a_hndl;
	}

	std::string ScriptComponent::getScriptHndl()
	{
		return m_scriptHndl;
	}
	
} }
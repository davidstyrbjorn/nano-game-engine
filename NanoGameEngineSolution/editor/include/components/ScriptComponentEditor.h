#pragma once

#include<ecs\Component.h>

namespace nano { namespace editor {

	class ScriptComponent : public ecs::Component {
	public:
		ScriptComponent(std::string a_hndl = "none");
		virtual void Start() override;
		virtual void Update() override;

		void setScriptHndl(const std::string &a_hndl);
		std::string getScriptHndl();

	private:
		std::string m_scriptHndl;
	};
	
} }
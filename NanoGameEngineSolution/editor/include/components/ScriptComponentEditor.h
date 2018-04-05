#pragma once

#include<ecs\Component.h>

namespace nano { namespace editor {

	class ScriptComponent : public ecs::Component {
	public:
		ScriptComponent();
		virtual void Start() override;
		virtual void Update() override;

		void setScriptHndl();
		std::string getScriptHndl();

	private:
		std::string m_scriptHndl;
	};
	
} }
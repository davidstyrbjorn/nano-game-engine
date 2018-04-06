#pragma once

#include<ecs\Component.h>

namespace nano { namespace engine { 

	class ScriptComponent : public ecs::Component {
	public:
		ScriptComponent(std::string a_hndl);
		void Start() override;
		void Update() override;

	private:
		ScriptFile *m_scriptFile;
	};

}} 
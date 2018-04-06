#pragma once

#include<ecs\Component.h>

#include"../nsl/ScriptFile.h"

namespace nano { namespace engine { 

	class ScriptFile;

	class ScriptComponent : public ecs::Component {
	public:
		ScriptComponent(std::string a_hndl);
		void Init() override;
		void Update() override;

	private:
		ScriptFile *m_scriptFile;
	};

}} 
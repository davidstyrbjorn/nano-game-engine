#pragma once

#include<ecs\Component.h>

#include"../nsl/ScriptFile.h"

namespace nano { namespace engine { 

	class ScriptFile;

	class ScriptComponent : public ecs::Component {
	public:
		ScriptComponent(std::string a_hndl);
		~ScriptComponent();
		
		void Init() override;
		void Update() override;
		void FixedUpdate() override;

	private:
		std::string m_hndl;
		ScriptFile *m_scriptFile;
	};

}} 
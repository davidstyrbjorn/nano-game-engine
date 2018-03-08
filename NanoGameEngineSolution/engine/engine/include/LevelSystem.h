#pragma once

#include"EngineSystemBase.h"

namespace nano { namespace engine {

	class LevelSystem : public EngineSystemBase<LevelSystem> {
	friend class EngineSystemBase<LevelSystem>;

	private:
		LevelSystem() { }

	public:
		void start() override;
		void update() override;
		void shutdown() override;
	};

} }
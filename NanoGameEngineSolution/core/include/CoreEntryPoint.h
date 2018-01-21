#pragma once

namespace nano {

	class CoreEntryPoint {
	public:
		// Virtual destructor
		virtual ~CoreEntryPoint();

		// Initalize 
		void CoreInit();
	};

}
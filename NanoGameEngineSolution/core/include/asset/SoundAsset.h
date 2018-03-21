#pragma once

#include"Asset.h"

namespace nano { namespace asset {

	// @TODO: use stb to load sound files instead of doing it manually you fucking idiot

	struct SoundAssetInfo {
		AssetInfo file;

	};

	class SoundAsset : public Asset {
	public:
		SoundAsset();

	};


} }
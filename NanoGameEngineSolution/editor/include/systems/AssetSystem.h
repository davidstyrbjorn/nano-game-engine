#pragma once

#include"EditorSystem.h"
#include<vector>

namespace nano {
	namespace asset {
		class Asset;
		class ImageAsset;
} }

namespace nano { namespace editor {  

	class AssetSystem : public EditorSystem<AssetSystem> {
		friend class EditorSystem<AssetSystem>;
	private:
		AssetSystem() { }

		std::vector<asset::Asset*> m_assetContainer;
		asset::ImageAsset *m_highlightTextureAsset;

		// Helper
		void ReadDirectory(const std::string& name, std::vector<std::string>& v);

	public:
		void Start() override;
		void Update() override;
		void Quit() override;

		std::vector<asset::Asset*>& getAssetContainer();
		asset::ImageAsset* getHighlightAsset();
	};

} }
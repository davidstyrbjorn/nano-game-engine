#include"../include/widgets/Widgets.h"

#include<asset\Asset.h>
#include<asset\ImageAsset.h>
#include<asset\SoundAsset.h>
#include<math\Vector2.h>

#include"../include/systems/EditorConfig.h"
#include"../include/systems/AssetSystem.h"

#include"../include/DearImGui/imgui.h"

namespace nano { namespace editor {

	AssetBrowserWidget::AssetBrowserWidget()
	{

	}

	void AssetBrowserWidget::Start()
	{

	}

	void AssetBrowserWidget::Update()
	{

	}

	void AssetBrowserWidget::Render()
	{
		static AssetSystem* assetSystem = AssetSystem::getInstance();

		math::Vector2 _windowSize = EditorConfig::Instance()->getWindowSize();

		// Calculate size
		ImVec2 size;
		size.y = (_windowSize.y * ASSET_WIDGET_HEIGHT_RATIO); // Make sure height is the ratio based on the current window height
		size.x = ASSET_WIDGET_WIDTH;

		// Calculate position
		ImVec2 pos;
		pos.x = 0;
		pos.y = MAIN_MENU_BAR_HEIGHT + (_windowSize.y * ENTITY_SELECT_HEIGHT_RATIO);

		ImGui::SetNextWindowPos(pos);
		ImGui::SetNextWindowSize(size);
		ImGui::Begin("Asset Browser", false, size, 1.0f,
			ImGuiWindowFlags_::ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_::ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse
		);

		for (asset::Asset *asset : assetSystem->getAssetContainer()) {
			ImGui::Text(asset->getFileName().c_str());
		}

		ImGui::End();
	}

} }
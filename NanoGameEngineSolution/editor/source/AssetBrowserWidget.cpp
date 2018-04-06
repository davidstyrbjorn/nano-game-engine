#include"../include/widgets/Widgets.h"

#include<asset\Asset.h>
#include<asset\ImageAsset.h>
#include<asset\SoundAsset.h>
#include<math\Vector2.h>

#include"../include/systems/EditorConfig.h"
#include"../include/systems/AssetSystem.h"

#include"../include/DearImGui/imgui.h"

#include<Windows.h>
#include<fstream>

#include<FileHelp.h>
#include<StringHelp.h>
#include<asset\AssetUtility.h>

#include<opengl\Texture.h>

namespace nano { namespace editor {

	std::string ExePath() {
		char buffer[MAX_PATH];
		GetModuleFileName(NULL, buffer, MAX_PATH);
		size_t pos = std::string(buffer).find_last_of("\\/");
		return std::string(buffer).substr(0, pos);
	}

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
		static asset::ASSET_TYPE currentAssetType = asset::ASSET_TYPE::IMAGE;
		static AssetSystem* assetSystem = AssetSystem::getInstance();
		static asset::ImageAsset* currentHoveringImageAsset = nullptr;
		static opengl::Texture* currentImageTexture = new opengl::Texture(nullptr, 0, 0, GL_RGB);

		math::Vector2 _windowSize = EditorConfig::Instance()->getWindowSize();

		// Calculate size
		static ImVec2 size;
		size.y = (_windowSize.y * ASSET_WIDGET_HEIGHT_RATIO); // Make sure height is the ratio based on the current window height
		size.x = ASSET_WIDGET_WIDTH;

		// Calculate position
		static ImVec2 pos;
		pos.x = 0;
		pos.y = MAIN_MENU_BAR_HEIGHT + (_windowSize.y * ENTITY_SELECT_HEIGHT_RATIO);

		ImGui::SetNextWindowPos(pos);
		ImGui::SetNextWindowSize(size);
		ImGui::Begin("Asset Browser", false, size, 1.0f,
			ImGuiWindowFlags_::ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_::ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse
		);

		if (ImGui::Button("Refresh")) {
			AssetSystem::getInstance()->refresh();
		}
		ImGui::SameLine(100);
		std::string temp = asset::asset_type_to_strig(currentAssetType);
		if (ImGui::Button(temp.c_str())) {
			ImGui::OpenPopup("asset_type_dropdown");
		}
		if (ImGui::BeginPopup("asset_type_dropdown")) {
			if (ImGui::Selectable("Image"))
				currentAssetType = asset::ASSET_TYPE::IMAGE;
			else if (ImGui::Selectable("Sound"))
				currentAssetType = asset::ASSET_TYPE::SOUND;

			ImGui::EndPopup();
		}

		if (currentAssetType == asset::ASSET_TYPE::IMAGE) {
			ImGui::Text("Image Assets");
			ImGui::Separator();
			// List image assets
			for (asset::ImageAsset *asset : assetSystem->getImageAssetContainer()) {
				ImGui::Text(asset->getFileName().c_str());
				if (ImGui::IsItemHovered()) {
					if (currentHoveringImageAsset != asset) {
						currentHoveringImageAsset = asset;
						currentImageTexture->Bind();
						currentImageTexture->SetTextureData(currentHoveringImageAsset->getImageData(), 100, 100, currentHoveringImageAsset->getAssetInfo().format);
						currentImageTexture->Unbind();
					}
				}
			}
		}
		else if (currentAssetType == asset::ASSET_TYPE::SOUND) {
			// List sound assets
			ImGui::Text("Sounds Assets");
			ImGui::Separator();
			for (asset::SoundAsset *asset : assetSystem->getSoundAssetContainer()) {
				ImGui::Text(asset->getFileName().c_str());
			}
		}

		ImGui::End();
	}

} }
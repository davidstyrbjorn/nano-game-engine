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

#include<opengl\Texture.h>

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
		static std::string currentImageFileName = "";
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

		if (ImGui::Button("Import")) {
			OpenExplorerWindow();
		}

		for (asset::Asset *asset : assetSystem->getAssetContainer()) {
			ImGui::Text(asset->getFileName().c_str());
			if (ImGui::IsItemHovered()) {
				if (asset->getFileName() != currentImageFileName) {
					currentImageFileName = asset->getFileName();
					//currentImageTexture->SetTextureData()
				}
			}
		}

		ImGui::End();
	}

	void AssetBrowserWidget::OpenExplorerWindow()
	{
		OPENFILENAME ofn;       // common dialog box structure
		HWND hwnd;				// owner window
		hwnd = GetActiveWindow();
		HANDLE hf;              // file handle

		// Initialize OPENFILENAME
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = hwnd;
		ofn.lpstrFile = m_fileNameBuffer;
		// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
		// use the contents of szFile to initialize itself.
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = sizeof(m_fileNameBuffer);
		ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
		
		if (GetOpenFileName(&ofn) == TRUE) 
		{
			std::string fileName = getFileName(m_fileNameBuffer);
			std::string temp = EditorConfig::Instance()->getProjectInfo().localPath + "\\resources\\assets\\" + fileName;
			std::string temp2 = m_fileNameBuffer;
			std::string newThing = "";

			// Format m_fileNameBuffer
			for (int i = 0; i < temp2.length(); i++) {
				newThing += temp2.at(i);
				if (temp2.at(i) == '\\') {
					newThing += "\\";
				}
			}

			// Copy happends here
			std::ifstream src(newThing, std::ios::binary);
			std::ofstream dst(temp, std::ios::binary);			   
			dst << src.rdbuf();

			// Tell asset system what happend
			AssetSystem::getInstance()->newAssetImported(fileName);
		}
		else {
			// Cancel in dialogue box (getting file failed)
		}
	}

} }
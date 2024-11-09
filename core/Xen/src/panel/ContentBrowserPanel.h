#pragma once

#include <Core.h>
#include <imgui.h>
#include <imgui/IconsFontAwesome.h>

#include <core/renderer/Texture.h>
#include <core/app/GameApplication.h>

#include <core/asset/AssetManagerUtil.h>

#include "StringValues.h"

class ContentBrowserPanel 
{
public:
	ContentBrowserPanel() {}
	ContentBrowserPanel(const std::filesystem::path& assetsDirectory) 
		:m_AssetsPath(assetsDirectory) 
	{
		m_CurrentPath = m_AssetsPath;
	}

	~ContentBrowserPanel() {}

	void OnImGuiRender()
	{
		// Load Textures of the icons here:
		if (!m_LoadedTextures)
		{
			m_FileTexture = Xen::Texture2D::CreateTexture2D(std::string(EDITOR_RESOURCES) + "/textures/file.png", false);
			m_FolderTexture = Xen::Texture2D::CreateTexture2D(std::string(EDITOR_RESOURCES) + "/textures/folder.png", false);
			m_PngTexture = Xen::Texture2D::CreateTexture2D(std::string(EDITOR_RESOURCES) + "/textures/png.png", false);
			
			m_FileTexture->LoadTexture();
			m_FolderTexture->LoadTexture();
			m_PngTexture->LoadTexture();

			m_LoadedTextures = true;
		}

		// The header part of the panel -------------------------------------
		ImGui::Begin(m_PanelTitle.c_str());

		bool up_button_disabled = false;

		if (m_CurrentPath != m_AssetsPath)
			up_button_disabled = true;

		ImGui::BeginDisabled(!up_button_disabled);
		if(ImGui::Button(m_BackIcon.c_str()))
			m_CurrentPath = m_CurrentPath.parent_path();
		ImGui::EndDisabled();

		ImGui::SameLine();

		float windowWidth = ImGui::GetContentRegionAvail().x;
		float textFieldWidth = 375.0f;

		ImGui::SetCursorPosX(windowWidth - textFieldWidth);

		ImGui::PushItemWidth(textFieldWidth);
		ImGui::InputTextWithHint(m_SearchIcon.c_str(), "Search in assets", m_SearchBuf, 40);
		ImGui::PopItemWidth();
		// -------------------------------------------------------------------

		ImGui::Separator();

		uint32_t panel_width = ImGui::GetContentRegionAvail().x;
		uint32_t cell_size = m_IconSize + m_IconPadding;

		uint32_t column_count = (uint32_t)(panel_width / cell_size);
		if (column_count < 1)
			column_count = 1;

		ImGui::Columns(column_count, "##FileColumns", false);

		Xen::AssetPtrRegistry assetRegistry = Xen::AssetManagerUtil::GetEditorAssetManager()->GetLoadedAssetRegistry();

		for (auto&& assetPair : assetRegistry)
		{
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));

			Xen::Ref<Xen::Texture2D> texture = Xen::AssetManagerUtil::GetAsset<Xen::Texture2D>(assetPair.first);

			ImGui::PushID(assetPair.first);
			ImGui::ImageButton((ImTextureID)(texture->GetNativeTextureID()), { (float)m_IconSize, (float)m_IconSize });

			ImGui::PopID();

			ImGui::TextWrapped("%u", assetPair.first);
			ImGui::PopStyleColor();
			ImGui::NextColumn();
		}

#if 0
		for (auto& p : std::filesystem::directory_iterator{ m_CurrentPath })
		{
			const auto& path = p.path();
			std::string pathString = p.path().string();
			std::string fileName = p.path().filename().string();

			Xen::Ref<Xen::Texture2D> icon_to_show = p.is_directory() ? m_FolderTexture : m_FileTexture;

			// Temporary. Load the Texture and display that as the icon instead!
			if (path.extension().string() == ".png")
				icon_to_show = m_PngTexture;

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));

			ImGui::PushID(pathString.c_str());
			ImGui::ImageButton((ImTextureID)(icon_to_show->GetNativeTextureID()), { (float)m_IconSize, (float)m_IconSize });

			if (ImGui::BeginDragDropSource())
			{
				const char* payload_data = pathString.c_str();
				if (path.extension().string() == ".xen")
					ImGui::SetDragDropPayload(m_SceneLoadDropType.c_str(), payload_data, pathString.size() + 1);

				else if (path.extension().string() == ".lua" && Xen::GetApplicationInstance()->GetScriptLang() == Xen::ScriptLang::Lua)
					ImGui::SetDragDropPayload(m_ScriptLoadDropType.c_str(), payload_data, pathString.size() + 1);

				// TODO: make sure to support all the texture formats:
				else if (path.extension().string() == ".png")
					ImGui::SetDragDropPayload(m_TextureLoadDropType.c_str(), payload_data, pathString.size() + 1);

				ImGui::EndDragDropSource();
			}

			ImGui::PopID();

			if(ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left) && p.is_directory())
				m_CurrentPath /= path.filename();

			ImGui::TextWrapped(fileName.c_str());
			ImGui::PopStyleColor();
			ImGui::NextColumn();

		}
#endif
		ImGui::Columns(1);
		ImGui::End();
	}

	inline const std::string& GetPanelTitle() { return m_PanelTitle; }

	inline const std::string& GetSceneLoadDropType()	{ return m_SceneLoadDropType; }
	inline const std::string& GetTextureLoadDropType()	{ return m_TextureLoadDropType; }
	inline const std::string& GetScriptLoadDropType()	{ return m_ScriptLoadDropType; }

private:
	std::string m_PanelTitle = Xen::StringValues::PANEL_TITLE_CONTENT_BROWSER;
	std::string m_BackIcon = std::string(ICON_FA_ARROW_UP);
	std::string m_SearchIcon = std::string(ICON_FA_MAGNIFYING_GLASS);
	
	std::filesystem::path m_AssetsPath;
	std::filesystem::path m_CurrentPath;

	// Drag drop types:
	std::string m_SceneLoadDropType    = "XEN_CONTENT_BROWSER_SCENE_LOAD";
	std::string m_TextureLoadDropType  = "XEN_CONTENT_BROWSER_TEXTURE_LOAD";
	std::string m_ScriptLoadDropType   = "XEN_CONTENT_BROWSER_SCRIPT_LOAD";

	Xen::Ref<Xen::Texture2D> m_FolderTexture;
	Xen::Ref<Xen::Texture2D> m_FileTexture;

	// Temporary:
	Xen::Ref<Xen::Texture2D> m_PngTexture;

	uint32_t m_IconSize = 80;
	uint32_t m_IconPadding = 25;

	char m_SearchBuf[40] = "";

	bool m_LoadedTextures = false;
};
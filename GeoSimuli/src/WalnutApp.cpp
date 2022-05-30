#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include "Walnut/Image.h"

using namespace Walnut;

class ExampleLayer : public Walnut::Layer
{
public:
	virtual void OnUIRender() override
	{
		// ImGui::ShowDemoWindow();

		// ImGui::Begin("Menu");
		ImGui::BeginMainMenuBar();
		if (ImGui::BeginMenu("File"))
		{
			ImGui::MenuItem("Save File", "Ctrl+S");
			ImGui::MenuItem("Load File", "Ctrl+O");
			ImGui::MenuItem("Export", "Ctrl+E");
			ImGui::MenuItem("Import Topology", "Ctrl+Alt+E", &m_importWindowEnabled);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("View"))
		{
			if (ImGui::MenuItem("Toolbar"))
			{
				m_toolbarEnabled = !m_toolbarEnabled;
			}
			if (ImGui::MenuItem("Project Menu"))
			{
				m_projectEnabled = !m_projectEnabled;
			}
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
		//ImGui::End();

		if (m_importWindowEnabled)
			ImGui::OpenPopup("Import");
		
		if (ImGui::BeginPopup("Import"))
		{
			ImGui::BeginTabBar("Import...");
			ImGui::TabItemButton("Import...");
			ImGui::EndTabBar();
			ImGui::Text("Import Topology");
			ImGui::RadioButton("Scan", true);
			ImGui::SameLine(200.0f, -1.0f);
			ImGui::RadioButton("GIS format", false);
			ImGui::SameLine(400.0f, -1.0f);
			ImGui::RadioButton("Map", false);
			ImGui::InputInt("Number", m_IntPtr, 1, 100);
			if (ImGui::Button("Cancel"))
			{
				m_importWindowEnabled = false;
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine(400.0f, -1.0f);
			if (ImGui::Button("Import"))
			{
				m_importWindowEnabled = false;
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
		

		ImGui::Begin("TopBar");

		if (ImGui::Button("Run"))
		{
			Render();
		}
		// ImGui::SameLine(100.0f, -1.0f);
		// ImGui::Button("Test");

		ImGui::End();

		if (m_toolbarEnabled)
		{
			ImGui::Begin("Toolbar");
			ImGui::SmallButton("Trees");
			ImGui::SmallButton("Bushes");
			ImGui::SmallButton("Ground");
			ImGui::End();
		}

		if (m_projectEnabled)
		{
			ImGui::Begin("Project");

			m_ProjectWidth = ImGui::GetContentRegionAvail().x;
			m_ProjectHeight = ImGui::GetContentRegionAvail().y;

			ImGui::BeginChild("Items", { (float)m_ProjectWidth , (float)(m_ProjectHeight / 2) });
			ImGui::Text("This will hold items \n that have been added \n to the project");
			ImGui::EndChild();

			ImGui::Separator();

			ImGui::BeginChild("Settings");
			ImGui::Text("Settings information will \nbe here \n \n Example: \n");
			ImGui::InputInt("Number", m_IntPtr, 1, 100);
			ImGui::EndChild();

			ImGui::End();
		}

		// Viewport, where image shows up
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("Viewport");

		m_ViewportWidth = ImGui::GetContentRegionAvail().x;
		m_ViewportHeight = ImGui::GetContentRegionAvail().y;

		if(m_Image)
			ImGui::Image(m_Image->GetDescriptorSet(), { (float)m_Image->GetWidth(), (float)m_Image->GetHeight() });

		ImGui::End();
		ImGui::PopStyleVar();
	}

	// Method used to generate and render the image
	void Render()
	{
		if (!m_Image || m_ViewportWidth != m_Image->GetWidth() || m_ViewportHeight != m_Image ->GetHeight())
		{
			m_Image = std::make_shared<Image>(m_ViewportWidth, m_ViewportHeight, ImageFormat::RGBA);
			delete[] m_ImageData;
			m_ImageData = new uint32_t[m_ViewportWidth * m_ViewportHeight];
		}

		for (uint32_t i = 0; i < m_ViewportWidth * m_ViewportHeight; i++)
		{
			m_ImageData[i] = 0xffff00ff;
		}

		m_Image->SetData(m_ImageData);
	}

	// private declarations
private:
	std::shared_ptr<Image> m_Image;
	uint32_t* m_ImageData = nullptr;
	uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

	uint32_t m_ProjectWidth = 0, m_ProjectHeight = 0;
	int* m_IntPtr = new int(1);
	bool m_toolbarEnabled = true;
	bool m_projectEnabled = true;
	bool m_importWindowEnabled = false;
};

Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "GeoSimuli";

	Walnut::Application* app = new Walnut::Application(spec);
	app->PushLayer<ExampleLayer>();
	// app->SetMenubarCallback([app]()
	// {
	// 	if (ImGui::BeginMenu("File"))
	// 	{
	// 		if (ImGui::MenuItem("Exit", "Ctrl+Q"))
	// 		{
	// 			app->Close();
	// 		}
	// 		ImGui::MenuItem("Save File", "Ctrl+S");
	// 		ImGui::MenuItem("Load File", "Ctrl+O");
	// 		ImGui::MenuItem("Export", "Ctrl+E");
	// 		ImGui::MenuItem("Import Topology", "Ctrl+Alt+E");
	// 		ImGui::EndMenu();
	// 	}
	// 	if (ImGui::BeginMenu("View"))
	// 	{
	// 		ImGui::MenuItem("Test");
	// 		ImGui::EndMenu();
	// 	}
	// });
	return app;
}
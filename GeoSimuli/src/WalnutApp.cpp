#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include "Walnut/Image.h"

using namespace Walnut;

class ExampleLayer : public Walnut::Layer
{
public:
	virtual void OnUIRender() override
	{
		ImGui::Begin("TopBar");
		if (ImGui::Button("Run"))
		{
			Render();
		}
		ImGui::End();


		ImGui::Begin("Project");

		m_ProjectWidth = ImGui::GetContentRegionAvail().x;
		m_ProjectHeight = ImGui::GetContentRegionAvail().y;

		ImGui::BeginChild("Items", { (float)m_ProjectWidth , (float)(m_ProjectHeight / 2) });
		ImGui::Text("This will hold items \n that have been added \n to the project");
		ImGui::EndChild();

		ImGui::Separator();

		ImGui::BeginChild("Settings");
		ImGui::Text("Settings information will \n also be here \n \n Example: \n");
		ImGui::InputInt("Number", m_IntPtr, 1, 100);
		ImGui::EndChild();
		
		ImGui::End();

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
};

Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "GeoSimuli";

	Walnut::Application* app = new Walnut::Application(spec);
	app->PushLayer<ExampleLayer>();
	app->SetMenubarCallback([app]()
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit", "Ctrl+Q"))
			{
				app->Close();
			}
			ImGui::MenuItem("Save File", "Ctrl+S");
			ImGui::MenuItem("Load File", "Ctrl+O");
			ImGui::MenuItem("Export", "Ctrl+E");
			ImGui::MenuItem("Import Topology", "Ctrl+Alt+E");
			ImGui::EndMenu();
		}
	});
	return app;
}
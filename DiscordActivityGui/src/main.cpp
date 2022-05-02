#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include "discord.h"
#include <sstream>

class DiscordLayer : public Walnut::Layer
{
public:
	virtual void OnAttach() {
		memcpy(id			, data.id			, sizeof(char)*128);
		memcpy(state		, data.state		, sizeof(char)*128);
		memcpy(details		, data.details		, sizeof(char)*128);
		memcpy(starttime	, data.starttime	, sizeof(char)*128);
		memcpy(endtime		, data.endtime		, sizeof(char)*128);
		memcpy(large_image	, data.large_image	, sizeof(char)*128);
		memcpy(large_text	, data.large_text	, sizeof(char)*128);
		memcpy(small_text	, data.small_text	, sizeof(char)*128);
		memcpy(small_image	, data.small_image	, sizeof(char)*128);
	}

	virtual void OnUIRender() override
	{
		ImGui::Begin("Discord activity manager");


		//ImGui::Text("id:");
		//ImGui::InputText("##id", id, sizeof(char) * 128);

		ImGui::Text("state:");
		ImGui::InputText("##state", state, sizeof(char) * 128);

		ImGui::Text("details:");
		ImGui::InputText("##details", details, sizeof(char) * 128);

		ImGui::Text("starttime:");
		ImGui::InputText("##starttime", starttime, sizeof(char) * 128);

		ImGui::Text("endtime:");
		ImGui::InputText("##endtime", endtime, sizeof(char) * 128);

		ImGui::Text("large image:");
		ImGui::InputText("##largeimage", large_image, sizeof(char) * 128);

		ImGui::Text("large text:");
		ImGui::InputText("##dlargetext", large_text, sizeof(char) * 128);

		ImGui::Text("small image:");
		ImGui::InputText("##smallimage", small_image, sizeof(char) * 128);

		ImGui::Text("small text:");
		ImGui::InputText("##smalltext", small_text, sizeof(char) * 128);

		ImGui::LabelText("##paddingbutton","");

		if (ImGui::Button("send")) {
			data.id = id;
			data.state = state;
			data.details = details;
			data.starttime = starttime;
			data.endtime = endtime;
			data.large_image = large_image;
			data.large_text = large_text;
			data.small_image = small_image;
			data.small_text = small_text;
			dis.UpdateActivity(data);
		}


		ImGui::End();

		dis.RunCallbacks();
	}
private:
	char id[128];
	char state[128];
	char details[128];
	char starttime[128];
	char endtime[128];
	char large_image[128];
	char large_text[128];
	char small_image[128];
	char small_text[128];
};

Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "Walnut Example";

	Walnut::Application* app = new Walnut::Application(spec);
	app->PushLayer<DiscordLayer>();
	//app->SetMenubarCallback([app]()
	//	{
	//		if (ImGui::BeginMenu("File"))
	//		{
	//			if (ImGui::MenuItem("Exit"))
	//			{
	//				app->Close();
	//			}
	//			ImGui::EndMenu();
	//		}
	//	});
	return app;
}
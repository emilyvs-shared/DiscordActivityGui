#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include <sstream>
#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>

#include "discord.h"
#include <json/json.h>

class DiscordLayer : public Walnut::Layer
{
public:
	virtual void OnAttach() override{
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


		ImGui::Text("id:");
		ImGui::BeginDisabled(true);
		ImGui::InputText("##id", id, sizeof(char) * 128);
		ImGui::EndDisabled();

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
	Discord::activityData ReadConfig() {
		Discord::activityData dat{};
		Discord::activityData da{};
		

		if (!std::filesystem::exists("id.json")) {
			std::fstream FileOut("id.json", std::fstream::out);
			Json::StreamWriterBuilder wBuilder;
			wBuilder["indentation"] = "\t";
			Json::Value root;
			root["activity"]["id"] = "965996061711822888";
			root["activity"]["state"] = "making a discord activity(rpc) gui app";
			root["activity"]["details"] = "making a discord activity(rpc) gui app with c++";
			root["activity"]["starttime"] = "0";
			root["activity"]["endtime"] = "0";
			root["activity"]["large_image"] = "visual_studio";
			root["activity"]["large_text"] = "visual studio";
			root["activity"]["small_image"] = "cpp";
			root["activity"]["small_text"] = "c++ programing language";
			std::string document = Json::writeString(wBuilder, root);
			FileOut << document;
			FileOut.close();
		}

		Json::CharReaderBuilder rBuilder;

		std::fstream FileIn("id.json", std::fstream::in);

		Json::Value root;
		std::string err;
		bool ok = Json::parseFromStream(rBuilder, FileIn, &root, &err);

		if (!ok) {
			std::cerr << "config error: " << err << std::endl;
		}


		dat.id = (char *)root["activity"]["id"].asCString();
		dat.state = (char *)root["activity"]["state"].asCString();
		dat.details = (char *)root["activity"]["details"].asCString();
		dat.starttime = (char *)root["activity"]["starttime"].asCString();
		dat.endtime = (char *)root["activity"]["endtime"].asCString();
		dat.large_image = (char *)root["activity"]["large_image"].asCString();
		dat.large_text = (char *)root["activity"]["large_text"].asCString();
		dat.small_image = (char *)root["activity"]["small_image"].asCString();
		dat.small_text = (char *)root["activity"]["small_text"].asCString();
		strcpy_s(id, dat.id);
		strcpy_s(state, dat.state);
		strcpy_s(details, dat.details);
		strcpy_s(starttime, dat.starttime);
		strcpy_s(endtime, dat.endtime);
		strcpy_s(large_image, dat.large_image);
		strcpy_s(large_text, dat.large_text);
		strcpy_s(small_image, dat.small_image);
		strcpy_s(small_text, dat.small_text);

		dat.id = id;
		dat.state = state;
		dat.details = details;
		dat.starttime = starttime;
		dat.endtime = endtime;
		dat.large_image = large_image;
		dat.large_text = large_text;
		dat.small_image = small_image;
		dat.small_text = small_text;

		FileIn.close();

		return dat;
	}
	Discord::activityData data = ReadConfig();
	Discord dis = Discord(data);
};

Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "Discord activity manager";

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
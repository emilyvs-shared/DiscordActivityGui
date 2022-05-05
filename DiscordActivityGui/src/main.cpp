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
	virtual void OnDetach() override {
		dis.ClearActivity();
	}

	virtual void OnUIRender() override
	{
		ImGui::Begin("Discord activity manager");

		ImGui::Text("Id:");
		ImGui::BeginDisabled(true);
		ImGui::InputText("##id", id, sizeof(char) * 128);
		ImGui::EndDisabled();

		ImGui::Text("presets: ");
		ImGui::BeginListBox("##presets", ImVec2(0,100));
		
		for (std::vector<std::string>::iterator it = presets.begin(); it != presets.end(); ++it) {
			Json::String m = *it;
			if (ImGui::Selectable(m.c_str(), selected == m)) {
				selected = m;
				strcpy(state, root[m]["state"].asCString());
				strcpy(details, root[m]["details"].asCString());
				strcpy(starttime, root[m]["starttime"].asCString());
				strcpy(endtime, root[m]["endtime"].asCString());
				strcpy(large_image, root[m]["large_image"].asCString());
				strcpy(large_text, root[m]["large_text"].asCString());
				strcpy(small_image, root[m]["small_image"].asCString());
				strcpy(small_text, root[m]["small_text"].asCString());
			}
		}

		ImGui::EndListBox();

		ImGui::Text("Starttime:");
		ImGui::InputText("##starttime", starttime, sizeof(char) * 128);

		ImGui::Text("Endtime:");
		ImGui::InputText("##endtime", endtime, sizeof(char) * 128);

		ImGui::Text("Details:");
		ImGui::InputText("##details", details, sizeof(char) * 128);

		ImGui::Text("State:");
		ImGui::InputText("##state", state, sizeof(char) * 128);

		ImGui::Text("Large image:");
		ImGui::InputText("##largeimage", large_image, sizeof(char) * 128);

		ImGui::Text("Large text:");
		ImGui::InputText("##dlargetext", large_text, sizeof(char) * 128);

		ImGui::Text("Small image:");
		ImGui::InputText("##smallimage", small_image, sizeof(char) * 128);

		ImGui::Text("Small text:");
		ImGui::InputText("##smalltext", small_text, sizeof(char) * 128);

		ImGui::LabelText("##paddingbutton","");

		sec = std::time(nullptr) - time;
		if (!doneUpdate) {
			sec = 0;
			time = std::time(nullptr);
		}
		check = sec <= 5 && doneUpdate;
		//std::cout << sec << ":" << check << " = " << doneUpdate << ":" << count << std::endl;
		ImGui::BeginDisabled(check);
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
			doneUpdate = true;
			count++;
		}
		ImGui::EndDisabled();
		if (sec > 5) {
			sec = 0;
			time = std::time(nullptr);
			doneUpdate = false;
		}


		ImGui::End();

		dis.RunCallbacks();
	}
private:
	int time = std::time(nullptr);
	int sec;
	int count;
	bool doneUpdate;
	bool check;
	bool test;
	std::vector<std::string> presets;
	std::string selected = "default";
	char id[128];
	char state[128];
	char details[128];
	char starttime[128];
	char endtime[128];
	char large_image[128];
	char large_text[128];
	char small_image[128];
	char small_text[128];
	Json::Value root;
	Discord::activityData ReadConfig() {
		Discord::activityData dat{};
		
		if (!std::filesystem::exists("config.json")) {
			std::fstream FileOut("config.json", std::fstream::out);
			Json::StreamWriterBuilder wBuilder;
			wBuilder["indentation"] = "\t";
			Json::Value root;
			root["id"] = "965996061711822888";
			root["presets"]["default"]["state"] = "making a discord activity(rpc) gui app";
			root["presets"]["default"]["details"] = "making a discord activity(rpc) gui app with c++";
			root["presets"]["default"]["starttime"] = "0";
			root["presets"]["default"]["endtime"] = "0";
			root["presets"]["default"]["large_image"] = "visual_studio";
			root["presets"]["default"]["large_text"] = "visual studio";
			root["presets"]["default"]["small_image"] = "cpp";
			root["presets"]["default"]["small_text"] = "c++ programing language";
			std::cout << root["presets"];
			std::string document = Json::writeString(wBuilder, root);
			FileOut << document;
			FileOut.close();
		}

		Json::CharReaderBuilder rBuilder;

		std::fstream FileIn("config.json", std::fstream::in);

		Json::Value root;
		std::string err;
		bool ok = Json::parseFromStream(rBuilder, FileIn, &root, &err);

		if (!ok) {
			std::cerr << "config error: " << err << std::endl;
		}

		dat.id = (char *)root["id"].asCString();
		dat.state = (char *)root["presets"]["default"]["state"].asCString();
		dat.details = (char *)root["presets"]["default"]["details"].asCString();
		dat.starttime = (char *)root["presets"]["default"]["starttime"].asCString();
		dat.endtime = (char *)root["presets"]["default"]["endtime"].asCString();
		dat.large_image = (char *)root["presets"]["default"]["large_image"].asCString();
		dat.large_text = (char *)root["presets"]["default"]["large_text"].asCString();
		dat.small_image = (char *)root["presets"]["default"]["small_image"].asCString();
		dat.small_text = (char *)root["presets"]["default"]["small_text"].asCString();

		Json::Value::Members members = root["presets"].getMemberNames();

		for (Json::Value::Members::iterator it = members.begin(); it != members.end(); ++it) {
			Json::String m = *it;
			presets.push_back(m);
		}

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
		this->root = root["presets"];

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
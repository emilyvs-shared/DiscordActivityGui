#pragma once
#include <discord/discord.h>
#include "config.h"


class Discord {
public:
	struct activityData {
		discord::ActivityType type;
		char* id = "965996061711822888";
		char* state = "making a discord activity(rpc) gui app";
		char* details = "making a discord activity(rpc) gui app with c++";
		char* starttime = "0";
		char* endtime = "0";
		char* large_image = "visual_studio";
		char* large_text = "visual studio";
		char* small_image = "cpp";
		char* small_text = "c++ programing language";
		discord::Activity ToActivity();
	};
	Discord(activityData data);
	void UpdateActivity(activityData data);
	void RunCallbacks();
private:
	static uint64_t CurrentTimeInSeconds();
	void SetActivity(activityData data);
	discord::Core* core;
};


extern Discord dis;
extern Discord::activityData data;


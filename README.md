# Discord activity gui
a gui for customizing your discord activity status.
## customization
change the id in the config to your discord app's client id.
in the presets object you can change the default or add a new preset by adding a new object to the presets object
example:
```json
{
	"id" : "965996061711822888",
	"presets": {
		"default": {
			"details": "making a discord activity(rpc) gui app with c++",
			"endtime": "0",
			"large_image": "visual_studio",
			"large_text": "visual studio",
			"small_image": "cpp",
			"small_text": "c++ programing language",
			"starttime": "0",
			"state": "making a discord activity(rpc) gui app"
		},
		"test": {
			"details": "making a discord activity(rpc) gui app",
			"endtime": "0",
			"large_image": "visual_studio",
			"large_text": "visual studio",
			"small_image": "cpp",
			"small_text": "c++ programing language",
			"starttime": "0",
			"state": "making a discord activity(rpc) gui app"
		}
	}
}
```

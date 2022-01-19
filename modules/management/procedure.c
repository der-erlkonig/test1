#include "procedure.h"
struct HookSection{
	int scope;
	int num;
	function* hooks;
};

struct Hooks{
	int sectionnum;
	struct HookSection* sections;
};

struct CameraUnit{
	char* xaddrs;
	int ptz_support;
	float pan;
	float tilt;
	float zoom;
	int switcher;
	int running;
	char* imgpath;
	char* streamuri;
	struct Hooks* hook;
};
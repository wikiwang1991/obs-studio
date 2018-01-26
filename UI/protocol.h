#pragma once

#pragma warning(disable : 4200)

namespace ObsRpc {

enum Function : char {
	Configure,
	StartStreaming,
	StopStreaming,
};

struct Msg {
	Function function;
	char params[];
};

struct String {
	unsigned char size;
	char data[];
};

struct ConfigParam {
	int moniter;
	int fpsNum;
	int fpsDen;
	int width;
	int height;
	String url;
};

}

#pragma warning(default : 4200)

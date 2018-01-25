#pragma once

#pragma warning(disable : 4200)

namespace ObsRpc {

enum Function : char {
	SetUrl,
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

}

#pragma warning(default : 4200)

#pragma once
#include <string>
#include <iostream>
#include "game_sdk/interfaces/engine/v_engine_client.h"


enum LoggerMethod
{
	external_method,
	game_method
};

typedef const std::string& ready_message;

class CLogger
{
	int log_method;
	VEngineClient* engine;
public:
	void init(int method = LoggerMethod::external_method);

	void message(ready_message msg, ready_message endl = "\n\0");
	void error(ready_message msg, ready_message endl = "\n\0");
};

extern CLogger* Logger;
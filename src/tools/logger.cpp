#include "logger.h"
#include <assert.h>
#include <interfaces.h>


CLogger* Logger = new CLogger();

void CLogger::init(int method)
{
	log_method = method;

	assert(Interfaces->engine);
	engine = Interfaces->engine;
}

void CLogger::message(ready_message msg, ready_message endl)
{
	if (log_method == LoggerMethod::external_method)
		std::cout << "|L|\t" << msg << endl;
	//else
		//engine->execute_client_cmd(("echo |L|\t" + msg + endl).c_str());
}

void CLogger::error(ready_message msg, ready_message endl)
{
	if (log_method == LoggerMethod::external_method)
		std::cout << "|E|\t" << msg << endl;
	//else
		//engine->execute_client_cmd(("|E|\t" + msg + endl).c_str());
}

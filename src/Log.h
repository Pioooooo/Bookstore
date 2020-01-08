#ifndef BOOKSTORE_LOG_H
#define BOOKSTORE_LOG_H


#include <fstream>
#include <iomanip>
#include <ctime>
#include <vector>
#include <string>
#include <sstream>
#include "Config.h"
#include "Basic.h"
#include "Account.h"

class Log
{
private:
	bool init();

	bool logFinance(const double &turnover);

	const std::string currentTime();

public:
	Log();

	~Log();

	bool log(const LOG_TYPE &type, const std::vector<std::string> &content);

};

extern Log logger;


#endif //BOOKSTORE_LOG_H
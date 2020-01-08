#include "Log.h"

Log::Log()
{
	if(!exists(Config::finLoc))
	{
		init();
	}
}

Log::~Log() = default;

bool Log::log(const LOG_TYPE &type, const std::vector<std::string> &content)
{
	std::ofstream logFile(Config::logLoc, std::ios::app);

	switch(type)
	{
	case LOG_FINANCE:    //[string] [turnover]
		logFile << "[FINANCE] " << currentTime() << content[0] << std::endl;
		logFinance(stod(content[1]));
		break;
	case LOG_EMPLOYEE:
		logFile << "[EMPLOYEE] <" << account.curID << "> " << currentTime() << content[0] << std::endl;
		break;
	case LOG_ERROR:
		logFile << "[ERROR] " << currentTime() << content[0] << std::endl;
		break;
	case LOG_INFO:
		logFile << "[INFO] " << currentTime() << content[0] << std::endl;
		break;
	}
	logFile.close();
	return true;
}

bool Log::init()
{
	std::ofstream file(Config::finLoc, std::ios::trunc | std::ios::binary);
	double tmp = 0;
	file.write((char *)&tmp, 8).write((char *)&tmp, 8);
	return true;
}

bool Log::logFinance(const double &turnover)
{
	std::fstream finFile(Config::finLoc, std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
	if(turnover >= 0)
	{
		double revenue;
		finFile.seekg(-16, std::ios::end);
		finFile.read((char*)&revenue, 8);
		revenue += turnover;
		finFile.write((char*)&revenue, 8);
	}
	else
	{
		double expenditure;
		finFile.seekg(-19, std::ios::end);
		finFile.read((char*)&expenditure, 8);
		expenditure += turnover;
		finFile.write((char*)&expenditure, 8);
	}
	return true;
}

const std::string Log::currentTime()
{
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d %X ", &tstruct);
	return buf;
}
Log logger;
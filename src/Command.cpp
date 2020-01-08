#include "Command.h"

Command::Command()
{
	map_init(cmdToEnum)("login", CMD_USER_LOGIN)("logout", CMD_USER_LOGOUT)("useradd", CMD_USER_ADD)("register", CMD_USER_REG)("delete", CMD_USER_DEL)("passwd", CMD_USER_PASS)("select", CMD_SELECT)("modify", CMD_MODIFY)("import", CMD_IMPORT)("show", CMD_SHOW)("buy", CMD_BUY)("report", CMD_REPORT)("lot", CMD_REPORT_LOG)("load", CMD_LOAD)("exit", CMD_EXIT);
}

Command::~Command() = default;

Command::CMD_TYPE Command::parseInput(const std::string &cmdLine, std::vector<std::string> &params)
{
	std::string cmdType, paramTmp;
	std::stringstream cmd(cmdLine);
	cmd >> cmdType;
	while(cmd >> paramTmp)
	{
		params.push_back(paramTmp);
	}
	return cmdToEnum[cmdType];
}

bool Command::fun(const CMD_TYPE &type, const std::vector<std::string> &params)
{
	switch(type)
	{
	case CMD_USER_LOGIN:
		break;
	case CMD_USER_LOGOUT:
		break;
	case CMD_USER_ADD:
		break;
	case CMD_USER_DEL:
		break;
	case CMD_USER_REG:
		break;
	case CMD_USER_PASS:
		break;
	case CMD_SELECT:
		break;
	case CMD_MODIFY:
		break;
	case CMD_IMPORT:
		break;
	case CMD_SHOW:
		break;
	case CMD_BUY:
		break;
	case CMD_REPORT:
		break;
	case CMD_REPORT_LOG:
		break;
	case CMD_LOAD:
		load(params[0]);
		break;
	case CMD_EXIT:
		exit(0);
	case CMD_INVALID:
		std::cout << "Invalid" << std::endl;
		return false;
	}
	return true;
}

bool Command::fun(std::istream &is)
{
	std::string cmdLine;
	getline(is, cmdLine);
	return Command::fun(parseInput(cmdLine, paramBuffer), paramBuffer);
}

void Command::doCommandLoop(std::istream &is)
{
	while(!is.eof())
	{
		fun(is);
	}
}

bool Command::load(const std::string &fileName)
{
	try
	{
		std::ifstream fileInput(fileName);
		if(!fileInput)
		{
			return false;
		}
		doCommandLoop(fileInput);
		return true;
	}
	catch(std::exception &e)
	{
		return false;
	}
}

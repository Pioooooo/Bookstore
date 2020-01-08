#include "Command.h"

Command::Command()
{
	map_init(cmdToEnum)
		("su", CMD_USER_LOGIN)
		("logout", CMD_USER_LOGOUT)
		("useradd", CMD_USER_ADD)
		("register", CMD_USER_REG)
		("delete", CMD_USER_DEL)
		("passwd", CMD_USER_PASS)
		("select", CMD_SELECT)
		("modify", CMD_MODIFY)
		("import", CMD_IMPORT)
		("show", CMD_SHOW)
		("buy", CMD_BUY)
		("report", CMD_REPORT)
		("lot", CMD_REPORT_LOG)
		("load", CMD_LOAD)
		("exit", CMD_EXIT);
	map_init(userToEnum)
		("0", USER_NULL)
		("1", USER_CLIENT)
		("3", USER_STAFF)
		("7", USER_ROOT);
}

Command::~Command() = default;

Command::CMD_TYPE Command::parseInput(const std::string &cmdLine, std::vector<std::string> &params)
{
	std::string cmdType, paramTmp;
	std::stringstream cmd(cmdLine);
	cmd >> cmdType;
	params.clear();
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
		if(params.size() == 2)
		{
			return account.login(params[0], params[1]);
		}
		else if(params.size() == 1)
		{
			return account.login(params[0]);
		}
		return false;
	case CMD_USER_LOGOUT:
		if(params.empty())
		{
			return account.logout();
		}
		return false;
	case CMD_USER_ADD:
		if(params.size() == 4)
		{
			return account.add(params[0], params[1], userToEnum[params[2]], params[3]);
		}
		return false;
	case CMD_USER_DEL:
		if(params.size() == 1)
		{
			return account.del(params[0]);
		}
		return false;
	case CMD_USER_REG:
		if(params.size() == 3)
		{
			return account.reg(params[0], params[1], params[2]);
		}
		return false;
	case CMD_USER_PASS:
		if(params.size() == 3)
		{
			return account.pswd(params[0], params[1], params[2]);
		}
		else if(params.size() == 2)
		{
			return account.pswdR(params[0], params[1]);
		}
		return false;
	case CMD_SELECT:
		if(params.size() == 1)
		{
			return data.select(params[0]);
		}
		return false;
	case CMD_MODIFY:
		if(!params.empty())
		{
			return data.modify(params);
		}
		return false;
	case CMD_IMPORT:
		if(params.size() == 2)
		{
			return data.import(std::stoi(params[0]), std::stod(params[1]));
		}
		return false;
	case CMD_SHOW:
		if(params.empty())
		{
			return data.show();
		}
		else if(params.size() == 1)
		{
			return data.show(params[0]);
		}
		else if(params.size() == 2)
		{
			return data.showFinance(std::stoi(params[1]));
		}
		return false;
	case CMD_BUY:
		if(params.size() == 2)
		{
			return data.buy(params[0], std::stoi(params[1]));
		}
		return false;
	case CMD_REPORT:
		break;
	case CMD_REPORT_LOG:
		break;
	case CMD_LOAD:
		if(params.size() != 1)
		{
			return false;
		}
		return load(params[0]);
	case CMD_EXIT:
		exit(0);
	case CMD_INVALID:
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
	std::vector<std::string> inv;
	inv.push_back("Invalid.");
	while(!is.eof())
	{
		if(!fun(is))
		{
			std::cout << "Invalid" << std::endl;
			logger.log(LOG_INFO, inv);
		}
	}
}

bool Command::load(const std::string &fileName)
{
	if(account.curType != USER_ROOT)
	{
		return false;
	}
	std::ifstream fileInput(fileName);
	if(!fileInput)
	{
		return false;
	}
	doCommandLoop(fileInput);
	return true;
}

Command cmd;
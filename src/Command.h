#ifndef BOOKSTORE_COMMAND_H
#define BOOKSTORE_COMMAND_H

#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include "MapInit.h"
#include "Data.h"
#include "Account.h"
#include "Log.h"

class Command
{
private:
	enum CMD_TYPE
	{
		CMD_INVALID = 0,		//无效指令
		CMD_USER_LOGIN = 1,		//登录或切换用户
		CMD_USER_LOGOUT = 2,		//注销用户
		CMD_USER_ADD = 3,		//添加用户
		CMD_USER_REG = 4,		//注册用户
		CMD_USER_DEL = 5,		//删除用户
		CMD_USER_PASS = 6,		//修改密码

		CMD_SELECT = 10,	//选定或添加book
		CMD_MODIFY = 11,	//修改book信息
		CMD_IMPORT = 12,	//采购
		CMD_SHOW = 13,	//查询
		CMD_BUY = 14,	//购买

		CMD_REPORT = 20,	//报表
		CMD_REPORT_LOG = 22,	//日志记录报表

		CMD_LOAD = 50,
		CMD_EXIT = 51,
	};
	std::unordered_map<std::string, CMD_TYPE> cmdToEnum;
	std::unordered_map<std::string, USER_TYPE> userToEnum;
	std::vector<std::string> paramBuffer;

public:
	Command();

	~Command();

	bool load(const std::string &fileName);

	void doCommandLoop(std::istream &is);

private:
	CMD_TYPE parseInput(const std::string &cmdLine, std::vector<std::string> &params);

	bool fun(const CMD_TYPE &type, const std::vector<std::string> &params);

	bool fun(std::istream &is);
};

extern Command cmd;

#endif // !BOOKSTORE_COMMAND_H
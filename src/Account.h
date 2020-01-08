#ifndef BOOKSTORE_ACCOUNT_H
#define BOOKSTORE_ACCOUNT_H


#include <fstream>
#include <iomanip>
#include <sstream>
#include <streambuf>
#include <cstdio>
#include "Config.h"
#include "Log.h"
#include "Basic.h"
#include "MD5.h"

class Account
{
private:

	bool init();

	bool userAdd(const std::string &id, const std::string &password, const USER_TYPE &type, const std::string &name);

	bool setPassword(std::string id, std::string passwordOld, std::string password);

public:
	USER_TYPE curType;
	char curID[30];
	char curName[20];

public:
	Account();

	~Account();

	bool login(const std::string &id, const std::string &password = "");

	bool logout();

	bool add(const std::string &id, const std::string &password, const USER_TYPE &type, const std::string &name);

	bool reg(const std::string &id, const std::string &password, const std::string &name);

	bool del(std::string id);

	bool pswd(std::string id, std::string passwordOld, std::string password);

	bool pswdR(std::string id, std::string password);
};

extern Account account;


#endif //BOOKSTORE_ACCOUNT_H

#include "Account.h"

bool Account::init()
{
	std::ofstream rootFile(std::string(Config::defaultAccount) + Config::accountTrailer, std::ios::binary);
	rootFile << '\7';
	rootFile.write(MD5::encode(Config::defaultPswd).c_str(), 32);
	char tmpname[20] = {0};
	std::strcpy(tmpname, Config::defaultName);
	rootFile.write(tmpname, 20);
	rootFile.close();
	return true;
}

Account::Account()
{
	curType = USER_ROOT;
	std::memset(curID, 0, 20);
	std::memset(curName, 0, 20);
	std::strcpy(curID, "root");
	std::strcpy(curName, "root");
	if(!exists(std::string(Config::defaultAccount) + Config::accountTrailer))
	{
		init();
	}
}

bool Account::login(const std::string &id, const std::string &password)
{
	if(!exists(id + Config::accountTrailer))
	{
		return false;
	}
	std::ifstream file(id + Config::accountTrailer, std::ios::binary);
	char tmptype;
	file.read(&tmptype, 1);
	if(tmptype < curType)
	{
		curType = static_cast<USER_TYPE>(tmptype);
		std::memset(curID, 0, 30 * sizeof(char));
		std::strcpy(curID, id.c_str());
		file.seekg(32, std::ios::cur);
		file.read(curName, 20 * sizeof(char));
		file.close();
		std::vector<std::string> tmp;
		tmp.push_back(std::string("<") + curID + "> logged in.");
		logger.log(LOG_INFO, tmp);
		return true;
	}
	std::string pswd = MD5::encode(password);
	char tmppswd[33] = {0};
	file.read(reinterpret_cast<char *>(tmppswd), 32 * sizeof(char));
	if(tmppswd == pswd)
	{
		curType = static_cast<USER_TYPE>(tmptype);
		file.read(curName, 20 * sizeof(char));
		file.close();
		std::memset(curID, 0, 30 * sizeof(char));
		std::strcpy(curID, id.c_str());
		std::vector<std::string> tmp;
		tmp.push_back(std::string("<") + curID + "> logged in.");
		logger.log(LOG_INFO, tmp);
		return true;
	}
	else
	{
		file.close();
		return false;
	}
}

bool Account::logout()
{
	if(curType == USER_NULL)
	{
		return false;
	}
	std::vector<std::string> tmp;
	tmp.push_back(std::string("<") + curID + "> logged out.");
	logger.log(LOG_INFO, tmp);
	curType = USER_NULL;
	std::memset(curID, 0, 20);
	std::memset(curName, 0, 20);
	return true;
}

bool Account::userAdd(const std::string &id, const std::string &password, const USER_TYPE &type, const std::string &name)
{
	if(exists(id + Config::accountTrailer))
	{
		return false;
	}
	std::ofstream file(id + Config::accountTrailer, std::ios::binary);
	char tmptype = type;
	file.write(&tmptype, 1).write(MD5::encode(password).c_str(), 32);
	char tmpname[21] = {0};
	std::strcpy(tmpname, name.c_str());
	file.write(tmpname, 20);
	file.close();

	std::vector<std::string> tmp;
	if(curType == USER_NULL)
	{
		tmp.push_back("<" + id + "> registered.");
	}
	else
	{
		tmp.push_back("<" + std::string(curID) + "> added user <" + id + ">.");//TODO: user specification
	}
	logger.log(LOG_INFO, tmp);

	return true;
}

bool Account::setPassword(std::string id, std::string passwordOld, std::string password)
{
	if(!exists(id + Config::accountTrailer))
	{
		return false;
	}

	std::fstream file(id + Config::accountTrailer, std::ios::in | std::ios::out | std::ios::binary);
	if(curType < USER_ROOT)
	{
		char tmppswd[33] = {0};
		file.seekg(1);
		file.read(tmppswd, 32);
		if(MD5::encode(passwordOld) != tmppswd)
		{
			return false;
		}
	}
	file.seekp(1);
	file.write(MD5::encode(password).c_str(), 32);
	file.close();

	std::vector<std::string> tmp;
	tmp.push_back("<" + std::string(id) + "> reset password.");
	logger.log(LOG_INFO, tmp);
	return true;
}

bool Account::add(const std::string &id, const std::string &password, const USER_TYPE &type, const std::string &name)
{
	if(curType >= USER_STAFF && curType > type)
	{
		return userAdd(id, password, type, name);
	}
	return false;
}

bool Account::reg(const std::string &id, const std::string &password, const std::string &name)
{
	return userAdd(id, password, USER_CLIENT, name);
}

bool Account::del(std::string id)
{
	if(curType < USER_ROOT || !exists(id + Config::accountTrailer))
	{
		return false;
	}

	std::remove((id + Config::accountTrailer).c_str());

	std::vector<std::string> tmp;
	tmp.push_back("<" + std::string(id) + "> deleted.");
	logger.log(LOG_INFO, tmp);
	return true;
}

bool Account::pswd(std::string id, std::string passwordOld, std::string password)
{
	if(curType < USER_CLIENT)
	{
		return false;
	}
	return setPassword(id, passwordOld, password);
}

bool Account::pswdR(std::string id, std::string password)
{
	if(curType < USER_ROOT)
	{
		return false;
	}
	return setPassword(id, "", password);
}

Account::~Account() = default;

Account account;
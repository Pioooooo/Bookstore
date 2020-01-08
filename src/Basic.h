#ifndef BOOKSTORE_BASIC_H
#define BOOKSTORE_BASIC_H

#include <fstream>
#include <string>

enum LOG_TYPE
{
	LOG_FINANCE,
	LOG_EMPLOYEE,
	LOG_ERROR,
	LOG_INFO
};

enum USER_TYPE
{
	USER_NULL = 0,
	USER_CLIENT = 1,
	USER_STAFF = 3,
	USER_ROOT = 7,
};

inline bool exists(std::string fileName)
{
	std::fstream file(fileName.c_str());
	if(file)
	{
		file.close();
		return true;
	}
	file.close();
	return false;
}

#endif // !BOOKSTORE_BASIC_H

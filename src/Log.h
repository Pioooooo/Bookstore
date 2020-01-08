#ifndef BOOKSTORE_LOG_H
#define BOOKSTORE_LOG_H


#include <fstream>

class Log
{
private:
	std::ofstream logFile;
public:
	Log();

	~Log();
};


#endif //BOOKSTORE_LOG_H

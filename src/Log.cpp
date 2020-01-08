#include "Report.h"

Log::Log()
{
	logFile.open("bookstore.log");
}

Log::~Log()
{
	logFile.close();
}


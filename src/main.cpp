#include <iostream>
#include <fstream>
#include "Command.h"
#include "MD5.h"
#include <cstring>

int main()
{
	std::ifstream fin("tmp/command.txt");
	if(fin)
	{
		cmd.doCommandLoop(fin);
	}
	fin.close();
	cmd.doCommandLoop(std::cin);
	return 0;
}
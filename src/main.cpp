#include <iostream>
#include <fstream>
#include "Command.h"

int main()
{
	std::ifstream fin("command.txt");
	if(fin)
	{
		cmd.doCommandLoop(fin);
	}
	fin.close();
	cmd.doCommandLoop(std::cin);
	return 0;
}
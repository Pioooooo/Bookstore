#ifndef BOOKSTORE_MD5_H
#define BOOKSTORE_MD5_H



#include <iostream>
#include <utility>
#include <vector>
#include <cstdlib>
#include <string>

class MD5
{
private:
	static const unsigned int A, B, C, D;

	static const char str16[];

	static const unsigned int T[];

	static const unsigned int s[];

	static unsigned int F(unsigned int b, unsigned int c, unsigned int d);

	static unsigned int G(unsigned int b, unsigned int c, unsigned int d);

	static unsigned int H(unsigned int b, unsigned int c, unsigned int d);

	static unsigned int I(unsigned int b, unsigned int c, unsigned int d);

	static unsigned int shift(unsigned int a, unsigned int n);

	static std::string format(unsigned int num);

public:
	static std::string encode(std::string src);
};


#endif // !BOOKSTORE_MD5_H
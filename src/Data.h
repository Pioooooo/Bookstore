#ifndef BOOKSTORE_DATA_H
#define BOOKSTORE_DATA_H


#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "Config.h"
#include "MapInit.h"
#include "Account.h"

class Data
{
private:
	enum DATA_TYPE
	{
		DATA_ISBN,
		DATA_NAME,
		DATA_AUTHOR,
		DATA_KEYWORD,
		DATA_PRICE
	};
	std::unordered_map<std::string, DATA_TYPE> dataToEnum;

	char curISBN[20];

	bool init();

	bool add(const std::string &key, const std::string &trailer, const std::string &isbn);

	bool del(const std::string &key, const std::string &trailer, const std::string &isbn);

	bool addISBN(const std::string &isbn);

	bool delISBN(const std::string &isbn);

	bool modISBN(const std::string &isbn);

	bool mod(const std::string &key, const std::string &trailer, const int &off);

	bool modKeywords(const std::string &keywords);

	bool modPrice(const double &price);

	bool showBook(const std::string &isbn);

	bool show(const DATA_TYPE &type, const std::string &keyword);

public:
	Data();

	~Data();

	bool select(const std::string &isbn);

	bool modify(const std::vector<std::string> &info);

	bool import(const int &quantity, const double &price);

	bool show();

	bool show(const std::string &param);

	bool showFinance(const int &time);

	bool showFinance();

	bool buy(const std::string &isbn, const int &quantity);
};

extern Data data;


#endif //BOOKSTORE_DATA_H

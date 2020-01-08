#include "Data.h"

Data data;

bool Data::init()
{
	std::ofstream file(Config::isbnCont, std::ios::trunc);
	file.close();
	char t[32] = {0};
	file.open(Config::isbnInfo, std::ios::trunc);
	file.write(t, 32);
	file.close();
	return true;
}

bool Data::add(const std::string &key, const std::string &trailer, const std::string &isbn)
{
	if(key == "")
	{
		return false;
	}
	if(!exists(std::string(key) + trailer))
	{
		std::ofstream File(std::string(key) + trailer, std::ios::out | std::ios::binary);
		char tmpisbn[20] = {0};
		std::strcpy(tmpisbn, isbn.c_str());
		File.write(tmpisbn, 20);
		File.close();
		return true;
	}

	std::ifstream File(std::string(key) + trailer, std::ios::binary);
	std::ofstream FileN(std::string(key) + trailer + Config::tmpTrailer, std::ios::binary);
	while(File)
	{
		char tmpISBN[21] = {0};
		File.read(tmpISBN, 20);
		if(isbn < tmpISBN)
		{
			char tmpisbn[20] = {0};
			std::strcpy(tmpisbn, isbn.c_str());
			FileN.write(tmpisbn, 20);
		}
		FileN.write(tmpISBN, 20);
	}
	File.close();
	FileN.close();

	std::remove((std::string(key) + trailer).c_str());
	std::rename((std::string(key) + trailer + Config::tmpTrailer).c_str(), (std::string(key) + trailer).c_str());
	return true;
}

bool Data::del(const std::string &key, const std::string &trailer, const std::string &isbn)
{
	if(key == "")
	{
		return false;
	}
	if(!exists(std::string(key) + trailer))
	{
		return false;
	}

	std::ifstream File(std::string(key) + trailer, std::ios::binary);
	std::ofstream FileN(std::string(key) + trailer + Config::tmpTrailer, std::ios::in | std::ios::out | std::ios::binary);
	while(File)
	{
		char tmpISBN[21] = {0};
		File.read(tmpISBN, 20);
		if(isbn == tmpISBN)
		{
			continue;
		}
		FileN.write(tmpISBN, 20);
	}
	File.close();
	FileN.close();

	std::remove((std::string(key) + trailer).c_str());
	std::rename((std::string(key) + trailer + Config::tmpTrailer).c_str(), (std::string(key) + trailer).c_str());
	return true;
}

bool Data::addISBN(const std::string &isbn)
{
	std::fstream isbnInfo(Config::isbnInfo, std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
	char tmpISBN[21] = {0};
	int i = 0, cnt, size = isbnInfo.tellg() / 32;
	isbnInfo.seekg(0);
	long long off;
	for(i = 0; i < size; i++)
	{
		isbnInfo.read(tmpISBN, 20);
		if(tmpISBN > isbn)
		{
			break;
		}
	}
	if(i == size)
	{
		i--;
	}
	isbnInfo.seekg(i * 32 + 20);
	isbnInfo.read((char *)&off, 8).read((char *)&cnt, 4);

	std::fstream isbnCont(Config::isbnCont, std::ios::in | std::ios::out | std::ios::binary);
	if(cnt < Config::isbnBCnt)
	{
		int tmp = cnt + 1;
		isbnInfo.seekp(i * 32 + 28);
		isbnInfo.write((char *)&tmp, 4);

		long long off1 = off, off2 = off;
		int j;
		bool fl = 1;
		for(j = 0; j < cnt; j++)
		{

			isbnCont.seekg(off1);
			isbnCont.read(tmpISBN, 20);
			off1 += 20;
			if(tmpISBN > isbn)
			{
				char tmpISBN[20] = {0};
				std::strcpy(tmpISBN, isbn.c_str());
				isbnCont.seekg(off2);
				isbnCont.write(tmpISBN, 20);
				off2 += 20;
				fl = 0;
			}
			isbnCont.seekg(off2);
			isbnCont.write(tmpISBN, 20);
			off2 += 20;
		}
		if(fl)
		{
			char tmpISBN[20] = {0};
			std::strcpy(tmpISBN, isbn.c_str());
			isbnCont.seekg(off2);
			isbnCont.write(tmpISBN, 20);
		}
		isbnCont.seekg(off);
		isbnCont.read(tmpISBN, 20);
		isbnCont.close();
		isbnInfo.seekp(i * 32);
		isbnInfo.write(tmpISBN, 20);
		isbnInfo.close();
	}
	else
	{
		int half = (cnt + 1) / 2, newoff;
		int tmp = cnt + 1 - half;
		isbnInfo.seekp(i * 32 + 28);
		isbnInfo.write((char *)&half, 4);
		for(int j = size - 1; j > i; j--)
		{
			isbnInfo.seekg((j + 1) * 32);
			isbnInfo.seekp(j * 32);
			char buf[32];
			isbnInfo.read(buf, 32);
			isbnInfo.write(buf, 32);
		}

		long long off1 = off, off2 = off;
		int j;
		bool fl = 1;
		for(j = 0; j < cnt; j++)
		{
			isbnCont.seekg(off1);
			isbnCont.read(tmpISBN, 20);
			off1 += 20;
			if(j == half)
			{
				isbnCont.seekp(0, std::ios::end);
				off2 = newoff = isbnCont.tellp();
			}
			if(tmpISBN > isbn)
			{
				char tmpISBN[20] = {0};
				std::strcpy(tmpISBN, isbn.c_str());
				isbnCont.seekp(off2);
				isbnCont.write(tmpISBN, 20);
				off2 += 20;
				fl = 0;
			}
			isbnCont.seekp(off2);
			isbnCont.write(tmpISBN, 20);
			off2 += 20;
		}
		if(fl)
		{
			char tmpISBN[20] = {0};
			isbnCont.seekp(off2);
			isbnCont.write(tmpISBN, 20);
		}
		char tmpstr[20] = {0};
		for(int k = 0; k < half - 1; k++)
		{
			isbnCont.write(tmpstr, 20);
		}
		isbnCont.seekg(off + half * 20);
		isbnCont.read(tmpstr, 20);
		isbnCont.seekg(off);
		isbnCont.read(tmpISBN, 20);
		isbnCont.close();

		isbnInfo.seekp(i * 32);
		isbnInfo.write(tmpISBN, 20);
		isbnInfo.seekp((i + 1) * 32);
		isbnInfo.write(tmpstr, 20);
		isbnInfo.write((char *)&newoff, 8);
		isbnInfo.write((char *)&tmp, 4);
		isbnInfo.close();
	}
	return true;
}

bool Data::delISBN(const std::string &isbn)
{
	std::fstream isbnInfo(Config::isbnInfo, std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
	char tmpISBN[21] = {0};
	int i = 0, cnt, size = isbnInfo.tellg() / 32;
	long long off;
	for(i = 0; i < size; i++)
	{
		isbnInfo.read(tmpISBN, 20);
		if(tmpISBN > isbn)
		{
			break;
		}
	}
	if(i == size)
	{
		i--;
	}
	isbnInfo.clear();
	isbnInfo.seekg(i * 32 + 20);
	isbnInfo.read((char *)&off, 8);
	isbnInfo.read((char *)&cnt, 4);

	std::fstream isbnCont(Config::isbnCont, std::ios::in | std::ios::out | std::ios::binary);
	

	int tmp = cnt - 1;
	isbnInfo.seekp(i * 32 + 28);
	isbnInfo.write((char *)&tmp, 4);

	isbnCont.seekg(off);
	isbnCont.seekp(off);
	int j;
	for(j = 0; j < cnt; j++)
	{
		isbnCont.read(tmpISBN, 20);
		if(tmpISBN == isbn)
		{
			continue;
		}
		isbnCont.write(tmpISBN, 20);
	}
	isbnCont.seekg(off);
	isbnCont.read(tmpISBN, 20);
	isbnCont.close();
	isbnInfo.seekp(i * 32);
	isbnInfo.write(tmpISBN, 20);
		
	return true;
}


bool Data::modISBN(const std::string &isbn)
{
	if(exists(isbn + Config::bookTrailer))
	{
		return false;
	}
	std::ifstream curFile(std::string(curISBN) + Config::bookTrailer);
	char name[41] = {0}, author[41] = {0}, keyword[41] = {0};
	curFile.read(name, 40).read(author, 40).read(keyword, 40);
	curFile.close();

	add(name, Config::nameTrailer, isbn);
	del(name, Config::nameTrailer, curISBN);
	add(author, Config::authorTrailer, isbn);
	del(author, Config::authorTrailer, curISBN);
	std::vector<std::string> keywords;
	int p1 = 0, p2 = 0;
	while((p2 = std::string(keyword).find('|', p1)) != std::string::npos)
	{
		keywords.push_back(std::string(keyword).substr(p1, p2 - p1));
		p1 = p2 + 1;
	}
	keywords.push_back(std::string(keyword).substr(p1));
	for(auto keyword : keywords)
	{
		add(keyword, Config::keywordTrailer, isbn);
		del(keyword, Config::keywordTrailer, curISBN);
	}

	delISBN(curISBN);
	addISBN(isbn);

	std::rename((std::string(curISBN) + Config::bookTrailer).c_str(), (isbn + Config::bookTrailer).c_str());
	std::memset(curISBN, 0, 20);
	std::strcpy(curISBN, isbn.c_str());


	return true;
}

bool Data::mod(const std::string &key, const std::string &trailer, const int &off)
{
	add(key, trailer, curISBN);

	char curKey[41] = {0};
	std::fstream curFile(std::string(curISBN) + Config::bookTrailer, std::ios::in | std::ios::out | std::ios::binary);
	curFile.seekg(off);
	curFile.read(curKey, 40);
	curFile.seekp(off);
	char tmp[40] = {0};
	std::strcpy(tmp, key.c_str());
	curFile.write(tmp, 40);
	curFile.close();
	if(curKey == std::string(""))
	{
		return true;
	}

	std::ifstream File(std::string(curKey) + trailer, std::ios::binary);
	std::ofstream FileN(std::string(curKey) + trailer + Config::tmpTrailer, std::ios::in | std::ios::out | std::ios::binary);
	while(File)
	{
		char tmpISBN[21] = {0};
		File.read(tmpISBN, 20);
		if(std::string(curISBN) == tmpISBN)
		{
			continue;
		}
		FileN.write(tmpISBN, 20);
	}

	File.close();
	FileN.close();

	std::remove((std::string(curKey) + trailer).c_str());
	std::rename((std::string(curKey) + trailer + Config::tmpTrailer).c_str(), (std::string(curKey) + trailer).c_str());
	return true;
}

bool Data::modKeywords(const std::string &keywords)
{
	std::vector<std::string> keys;
	int p1 = 0, p2 = 0;
	while((p2 = keywords.find('|', p1)) != std::string::npos)
	{
		keys.push_back(keywords.substr(p1, p2 - p1));
		p1 = p2 + 1;
	}
	keys.push_back(keywords.substr(p1));
	for(std::string key : keys)
	{
		add(key, Config::keywordTrailer, curISBN);
	}

	char curKey[41] = {0};
	std::fstream curFile(std::string(curISBN) + Config::bookTrailer, std::ios::in | std::ios::out | std::ios::binary);
	curFile.seekg(80);
	curFile.read(curKey, 40);
	curFile.seekp(80);
	char tmp[40] = {0};
	std::strcpy(tmp, keywords.c_str());
	curFile.write(tmp, 40);
	curFile.close();
	if(curKey == std::string(""))
	{
		return true;
	}


	keys.empty();
	p1 = 0, p2 = 0;
	while((p2 = std::string(curKey).find('|', p1)) != std::string::npos)
	{
		keys.push_back(std::string(curKey).substr(p1, p2 - p1));
		p1 = p2 + 1;
	}
	keys.push_back(std::string(curKey).substr(p1));
	for(std::string key : keys)
	{
		std::ifstream File(key + Config::keywordTrailer, std::ios::binary);
		std::ofstream FileN(key + Config::keywordTrailer + Config::tmpTrailer, std::ios::in | std::ios::out | std::ios::binary);
		while(File)
		{
			char tmpISBN[21] = {0};
			File.read(tmpISBN, 20);
			if(std::string(curISBN) == tmpISBN)
			{
				continue;
			}
			FileN.write(tmpISBN, 20);
		}

		File.close();
		FileN.close();

		std::remove((key + Config::keywordTrailer).c_str());
		std::rename((key + Config::keywordTrailer + Config::tmpTrailer).c_str(), (key + Config::keywordTrailer).c_str());
	}
	return true;
}

bool Data::modPrice(const double &price)
{
	std::fstream curFile(std::string(curISBN) + Config::bookTrailer, std::ios::in | std::ios::out | std::ios::binary);
	curFile.seekp(120);
	curFile.write(reinterpret_cast<const char *>(&price), 8);
	curFile.close();
	return true;
}

bool Data::showBook(const std::string &isbn)
{
	std::ifstream file(isbn + Config::bookTrailer);
	if(!file)
	{
		file.close();
		return false;
	}
	char name[41] = {0}, author[41] = {0}, keyword[41] = {0};
	double price;
	int quantity;
	file.read(name, 40).read(author, 40).read(keyword, 40).read((char *)&price, 8).read((char *)&quantity, 4);
	std::cout << isbn << '\t' << name << '\t' << author << '\t' << keyword << '\t' << std::fixed << std::setprecision(2) << price << '\t' << std::setprecision(0) << quantity << "±¾\n";
	file.close();
	return true;
}

Data::Data()
{
	if(!exists(Config::isbnCont) || !exists(Config::isbnInfo))
	{
		init();
	}

	std::memset(curISBN, 0, 20);
	map_init(dataToEnum)
		("ISBN", DATA_ISBN)
		("name", DATA_NAME)
		("author", DATA_AUTHOR)
		("keyword", DATA_KEYWORD)
		("price", DATA_PRICE);
}

Data::~Data() = default;

bool Data::select(const std::string &isbn)
{
	if(account.curType < USER_STAFF)
	{
		return false;
	}
	std::memset(curISBN, 0, 20);
	std::strcpy(curISBN, isbn.c_str());

	if(!exists(isbn + Config::bookTrailer))
	{
		char tmp[120] = {0};
		double tmpp = 0;
		int tmpcnt = 0;
		std::ofstream file(isbn + Config::bookTrailer, std::ios::binary);
		file.write(tmp, 120).write((char *)&tmpp, 8).write((char *)&tmpcnt, 4);
		file.close();
		addISBN(isbn);
	}

	std::vector<std::string> msg;
	msg.push_back(std::string("<") + account.curID + "> selected {" + isbn + "}.");
	logger.log(LOG_INFO, msg);

	return true;
}

bool Data::modify(const std::vector<std::string> &info)
{
	if(account.curType < USER_STAFF || curISBN == std::string(""))
	{
		return false;
	}
	std::vector<std::string> msg;
	msg.push_back(std::string("<") + account.curID + "> modified book {" + curISBN + "}.");
	logger.log(LOG_INFO, msg);

	std::string p[5];
	for(std::string param : info)
	{
		int spl = param.find('=');
		std::string inf = param.substr(1, spl - 1);
		switch(dataToEnum[inf])
		{
			case DATA_ISBN:
				p[0] = param.substr(spl + 1);
				break;
			case DATA_NAME:
				p[1] = param.substr(spl + 2, param.size() - spl - 3);
				break;
			case DATA_AUTHOR:
				p[2] = param.substr(spl + 2, param.size() - spl - 3);
				break;
			case DATA_KEYWORD:
				p[3] = param.substr(spl + 2, param.size() - spl - 3);
				break;
			case DATA_PRICE:
				p[4] = param.substr(spl + 1);
				break;
		}
	}
	if(!p[0].empty() && !modISBN(p[0]))
	{
		return false;
	}
	if(!p[1].empty())
	{
		mod(p[1], Config::nameTrailer, 0);
	}
	if(!p[2].empty())
	{
		mod(p[2], Config::authorTrailer, 40);
	}
	if(!p[3].empty())
	{
		modKeywords(p[3]);
	}
	if(!p[4].empty())
	{
		modPrice(std::stod(p[4]));
	}
	return true;
}

bool Data::import(const int &quantity, const double &price)
{
	if(account.curType < USER_STAFF || curISBN == std::string(""))
	{
		return false;
	}

	int qua;
	std::fstream curFile(std::string(curISBN) + Config::bookTrailer, std::ios::in | std::ios::out | std::ios::binary);
	curFile.seekg(128);
	curFile.read((char *)&qua, 4);
	qua += quantity;
	curFile.seekp(128);
	curFile.write((char *)&qua, 4);
	curFile.close();

	std::vector<std::string> msg;
	msg.push_back(std::string("<") + account.curID + "> imported book {" + curISBN + "} * " + std::to_string(quantity) + ".");
	msg.push_back(std::to_string(-price));
	logger.log(LOG_FINANCE, msg);
	return true;
}

bool Data::show()
{
	if(account.curType < USER_CLIENT)
	{
		return false;
	}
	std::ifstream file(Config::isbnInfo);
	char tmpisbn[21];
	while(file)
	{
		std::memset(tmpisbn, 0, 21);
		file.read(tmpisbn, 20);
		showBook(tmpisbn);
	}
	file.close();

	std::vector<std::string> msg;
	msg.push_back(std::string("<") + account.curID + "> showed books.");
	logger.log(LOG_INFO, msg);

	return true;
}

bool Data::show(const std::string &param)
{
	if(param == "finance")
	{
		if(account.curType < USER_ROOT)
		{
			return false;
		}
		return showFinance();
	}
	if(account.curType < USER_CLIENT)
	{
		return false;
	}
	return show(dataToEnum[param.substr(1, param.find('=') - 1)], param.substr(param.find('=') + 1));
}

bool Data::showFinance(const int &time)
{
	return false;
}

bool Data::showFinance()
{
	return false;
}

bool Data::show(const DATA_TYPE &type, const std::string &keyword)
{
	if(account.curType < USER_CLIENT)
	{
		return false;
	}
	std::ifstream file;
	char tmpisbn[21];
	switch(type)
	{
		case DATA_ISBN:
			showBook(keyword);
			break;
		case DATA_NAME:
			file.open(keyword.substr(1, keyword.length() - 2) + Config::nameTrailer);
			while(file)
			{
				std::memset(tmpisbn, 0, 21);
				file.read(tmpisbn, 20);
				showBook(tmpisbn);
			}
			break;
		case DATA_AUTHOR:
			file.open(keyword.substr(1, keyword.length() - 2) + Config::authorTrailer);
			while(file)
			{
				std::memset(tmpisbn, 0, 21);
				file.read(tmpisbn, 20);
				showBook(tmpisbn);
			}
			break;
		case DATA_KEYWORD:
			file.open(keyword.substr(1, keyword.length() - 2) + Config::keywordTrailer);
			while(file)
			{
				std::memset(tmpisbn, 0, 21);
				file.read(tmpisbn, 20);
				showBook(tmpisbn);
			}
			break;
	}
	file.close();

	std::vector<std::string> msg;
	msg.push_back(std::string("<") + account.curID + "> showed books.");
	logger.log(LOG_INFO, msg);

	return true;
}

bool Data::buy(const std::string &isbn, const int &quantity)
{
	if(account.curType < USER_CLIENT)
	{
		return false;
	}

	double price;
	int qua;
	std::fstream curFile(isbn + Config::bookTrailer, std::ios::in | std::ios::out | std::ios::binary);
	curFile.seekg(120);
	curFile.read((char *)&price, 8).read((char *)&qua, 4);
	qua -= quantity;
	if(qua < 0)
	{
		curFile.close();
		return false;
	}
	curFile.seekp(128);
	curFile.write((char *)&qua, 4);
	curFile.close();

	std::vector<std::string> msg;
	msg.push_back(std::string("<") + account.curID + "> bought book {" + isbn + "} * " + std::to_string(quantity) + ".");
	msg.push_back(std::to_string(quantity * price));
	logger.log(LOG_FINANCE, msg);
	return true;
}

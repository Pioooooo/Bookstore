#include "Config.h"

const char Config::logLoc[] = "bookstore.log",
Config::finLoc[] = "finance",
Config::dataLoc[] = "data",
Config::isbnCont[] = "isbn.con",
Config::nameCont[] = "name.con",
Config::authCont[] = "author.con",
Config::keyCont[] = "keyword.con",
Config::isbnInfo[] = "isbn.info",
Config::nameInfo[] = "name.info",
Config::authInfo[] = "author.info",
Config::keyInfo[] = "keyword.info",
Config::accountLoc[] = "account",
Config::accCont[] = "account.con",
Config::defaultAccount[] = "root",
Config::defaultPswd[] = "sjtu",
Config::defaultName[] = "root",
Config::accountTrailer[] = ".account",
Config::bookTrailer[] = ".book",
Config::isbnTrailer[] = ".isbn",
Config::nameTrailer[] = ".name",
Config::authorTrailer[] = ".author",
Config::keywordTrailer[] = ".keyword",
Config::tmpTrailer[] = ".tmp";

const int Config::isbnBCnt = 100,
Config::nameBCnt = 100,
Config::authBCnt = 100,
Config::keyBCnt = 100;
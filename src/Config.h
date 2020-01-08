#ifndef BOOKSTORE_CONFIG_H
#define BOOKSTORE_CONFIG_H


class Config
{
public:
	static const char logLoc[], finLoc[], dataLoc[], isbnCont[], nameCont[], authCont[], keyCont[], isbnInfo[], nameInfo[], authInfo[], keyInfo[], accountLoc[], accCont[], defaultAccount[], defaultPswd[], defaultName[], accountTrailer[], bookTrailer[], isbnTrailer[], nameTrailer[], authorTrailer[], keywordTrailer[], tmpTrailer[];
	static const int isbnBCnt, nameBCnt, authBCnt, keyBCnt;
};


#endif //BOOKSTORE_CONFIG_H

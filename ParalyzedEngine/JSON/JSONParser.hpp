#ifndef __PE_JSONPARSER_H_
#define __PE_JSONPARSER_H_
 #include <string>
 #include <iostream>
#include "../PEDictionary.hpp"
//need to redo this in C
class JSONParser {
public:
static PEDictionary * parseJson(std::string data);
static std::vector<PEDictionaryItem> getSubItems(std::string data, int *index);
 static std::string getValue(std::string data, int index);
};

 
#endif 
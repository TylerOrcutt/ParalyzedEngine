#ifndef __PARALYZED_MAP_H
#define __PARALYZED_MAP_H
#include <stdio.h>
#include <vector>
#include <fstream>
#include <string>
#include "../JSON/JSONParser.hpp"
#include "../PEDictionary.hpp"
struct PEBlock{
float x=0;
float y=0;;
float width=32;
float height=32;
float imgx=0;
float imgy=0;
float imgw=32;
float imgh=32;

};
class PEMap{
private:
std::vector<PEBlock>blocks;

public:
PEMap(){

}
PEMap(const char * file){
    load_map(file);
}
std::string load_map(const char *);
 

std::vector <PEBlock>* getBlocks(){
    return &blocks;
}

};



#endif
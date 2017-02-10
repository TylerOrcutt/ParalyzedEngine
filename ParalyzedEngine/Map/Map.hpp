#ifndef __PARALYZED_MAP_H
#define __PARALYZED_MAP_H
#include <stdio.h>
#include <vector>
#include <fstream>
#include "../Texture.h"
#include <string>
#include "../JSON/JSONParser.hpp"
#include "../PEDictionary.hpp"
#include "../GameObjects/PEProp.hpp"
#include "../Camera/PETwoDCamera.hpp"
#include "../SpriteRenderer.h"
#include "../Texture.h"
#include <map>
#ifndef MAP_SCALE
#define MAP_SCALE 1
#endif
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
	PEBlock **blocks;
	//std::vector<PETexture*> spritesheets;
	std::vector<PEGameObject*> props;
	int width,height;
	std::vector<PETexture *> spritesheets;
	std::vector<PEGameObjectData *>dataObjects;

public:
	PEMap(){
	}
	
	PEMap(const char * file){
	       	load_map(file);
	}
	
	std::string load_map(const char *);
	void parseMap(std::string map);
	void Update();
	void Draw(PETwoDCamera *);
PEBlock ** getBlocks(){
    return blocks;
}
int getWidth(){
    return width;
}
int getHeight(){
    return height;
}

};



#endif

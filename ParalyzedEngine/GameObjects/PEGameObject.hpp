#ifndef __PE_GAMEOBJECT__H_
#define __PE_GAMEOBJECT__H_
#include <stdio.h>
#include <string>
#include <lua.hpp>
#include <fstream>
#include <map>
#include <typeinfo>
#include "PEGameObjectController.hpp"
#include "../JSON/JSONParser.hpp"
#include "../PEDictionary.hpp"
#include "../Memory/PEalloc/PEalloc.h"
#include "../LUA/PELuaFunctions.hpp"
struct PEGameObjectBlock{
	int spriteSheet=0;
	int imgx,imgy;
};
struct PEGameObjectData{
	float zline=0;
	std::string name;
	int width=0,height=0;
	PEGameObjectBlock**blocks=nullptr;

	~PEGameObjectData(){
		delete []blocks;
	}

	void allocate(int _width,int _height){
		width=_width;
		height=_height;
	//	name=_name;
		blocks = (PEGameObjectBlock**) PE_malloc(sizeof(PEGameObjectBlock)*width);
		for(int x=0;x<width;x++){
			for(int y=0;y<height;y++){
				blocks[x] =(PEGameObjectBlock*)PE_malloc(sizeof(PEGameObjectBlock)*height);
			}
		}
	}

	PEGameObjectData(std::string _name,std::string file){
		name = _name;
		//load file here
		std::fstream f;
		f.open(file.c_str(),std::ios::in);
		std::string data="";
		if(!f.is_open()){
			printf("failed to load prop\n");
			return;
		}
		while(!f.eof()){
			char buf;
			f.read(&buf,1);
			data+=buf;
		}
		f.close();
		parseProp(data);
	}

	bool parseProp(std::string data){
		PEDictionary *dic = JSONParser::parseJson(data);
		PEDictionaryItem * propData = dic->get(0);
		PEDictionaryItem * propinfo = propData->getItem("Prop");
		if(propinfo==nullptr){
			delete dic;
			return false;
		}

		int w = atoi(propinfo->getItem("width")->value.c_str());
		int h = atoi(propinfo->getItem("height")->value.c_str());
		zline = atof(propinfo->getItem("Zbar")->value.c_str());
		printf("Prop Name:%s\n    Width:%d\n     Height:%d\n",
				name.c_str(),w,h);
		allocate(w,h);

		PEDictionaryItem * blockinfo = propData->getItem("Blocks");
		if(blockinfo == nullptr){
			delete dic;
			return false;
		}
		for(int i=0;i<blockinfo->items.size();i++){
			PEDictionaryItem *blk = blockinfo->getItem(i);
			int x = atoi(blk->getItem("x")->value.c_str());
			int y = atoi(blk->getItem("y")->value.c_str());
			int imgx = atoi(blk->getItem("imgx")->value.c_str());
			int imgy = atoi(blk->getItem("imgy")->value.c_str());
			blocks[x][y].imgx = imgx;
			blocks[x][y].imgy=imgy;
		}

		delete dic;
		return true;
	}
};

 typedef PEGameObjectController * (*controllerType)();

class PEGameObject{
	
	
	private:

	protected:

	
	public: 
	static 	std::map<std::string,  controllerType > objectTypes;
	static std::string a;

	static void addMap(std::string test,controllerType a){
		 
		objectTypes.insert(std::pair<std::string,controllerType>(test,a));
		printf("Total Object types: %i \n",objectTypes.size());
	}
	
		PEGameObjectController * controller=NULL;
		//float x,y;
		int width,height;
		std::string name="";
		lua_State *script = luaL_newstate();
		PEGameObjectData * object;
	
		PEGameObject(){}
		

		PEGameObject(std::string _name, PEGameObjectData * _object){
	//		width=_width;
	//		height=_height;

	    controller =  objectTypes[_name]();
	
			name =_name;
			object = _object;
		//	init_script(std::string("Props/"+_name+"/"+name+".lua").c_str());

		}


		void init_script(std::string file){
 
  
		lua_pushliteral(script, "this"); 
    lua_pushlightuserdata(script, (void *)this); 
    lua_settable(script, LUA_REGISTRYINDEX);
			

			pelua::register_lua_funcs(script);
			
			int res=luaL_loadfile(script,file.c_str());
		
			if(res !=LUA_OK){
				printf("failed to load %s script\n", file.c_str());
				return;
			}

		//	printf("testing LUA script\n");
			//try calling update function;
			
			lua_pcall(script,0,0,0);
			lua_getglobal(script,"onLoad");
			if(lua_pcall(script,0,0,0)!=LUA_OK){
				printf("error running update script %s\n",lua_tostring(script,-1));
			}



		}
		
		virtual void Load(const char *){}
		virtual void Update(){
		if(controller!=NULL){
			controller->Update();
		}
		/*	lua_getglobal(script,"onUpdate");
			if(lua_pcall(script,0,0,0)!=LUA_OK){
		//		printf("failed updating object bush\n");
			}*/
		}
		virtual void Draw(){}
		

		int getWidth(){
			return width;
		}
		int getHeight(){
			return height;
		}

		std::string getName(){
			return name;
		}

		
};
#endif

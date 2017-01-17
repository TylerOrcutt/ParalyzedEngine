#ifndef __PE_GAMEOBJECT__H_
#define __PE_GAMEOBJECT__H_
#include <stdio.h>
#include <string>
#include <lua.hpp>


class PEGameObject{
	
	
	private:

	protected:

	
	public: 
		static int println(lua_State *s){
			printf("%s\n",lua_tostring(s,1));
			return LUA_OK;
		}

		int width,height;
		std::string name="";
		lua_State *script = luaL_newstate();

		
		PEGameObject(){}
		

		PEGameObject(std::string _name, int _width,int _height){
			width=_width;
			height=_height;
			name =_name;
			init_script("Props/bush/bush.lua");
		}


		void init_script(std::string file){
			
			lua_register(script,"println",PEGameObject::println);
			
			int res=luaL_loadfile(script,file.c_str());
			if(res !=LUA_OK){
				printf("failed to load %s script\n", file.c_str());
				return;
			}

			printf("testing LUA script\n");
			//try calling update function;
			
			lua_pcall(script,0,0,0);
			lua_getglobal(script,"onUpdate");
			if(lua_pcall(script,0,0,0)!=LUA_OK){
				printf("error running update script %s\n",lua_tostring(script,-1));
			}



		}
		
		virtual void Load(const char *){}
		virtual void Update(){
			lua_getglobal(script,"onUpdate");
			if(lua_pcall(script,0,0,0)!=LUA_OK){
				printf("failed updating object bush\n");
			}
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

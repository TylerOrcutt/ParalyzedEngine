#include "PELuaFunctions.hpp"
#include "../GameObjects/PEGameObject.hpp"
#include <stdio.h>
#include <lua.hpp>
//using namespace pelua;

PEGameObject* pelua::getObject(lua_State *scpt){
 lua_pushliteral(scpt, "this"); 
       lua_gettable(scpt, LUA_REGISTRYINDEX);
	PEGameObject *obj = (PEGameObject*)lua_touserdata(scpt,-1);
    return obj;
}
int pelua::moveLeft(lua_State *scpt){

	PEGameObject *obj = getObject(scpt);
	obj->x--;

	return LUA_OK;
}
int pelua::moveRight(lua_State *scpt){

	PEGameObject *obj = getObject(scpt);
	obj->x++;

	return LUA_OK;
}

int pelua::rotateObject(lua_State *scpt){
	PEGameObject *obj = getObject(scpt);
	int rot = lua_tointeger(scpt,1);
	obj->rotation+=rot;
	if(obj->rotation>360){
		obj->rotation=obj->rotation/360;
	}
 
 

	return LUA_OK;
}
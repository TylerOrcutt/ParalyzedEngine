#ifndef __PE_LUA_FUNCTIONS_H_
#define __PE_LUA_FUNCTIONS_H_

#include <stdio.h>
#include <lua.hpp>
//#include "../GameObjects/PEGameObject.hpp"
class PEGameObject;
namespace pelua{
inline int println(lua_State *s){
	printf("%s\n",lua_tostring(s,1));
	return LUA_OK;
}
extern PEGameObject * getObject(lua_State *);
extern int moveLeft(lua_State *);
extern int moveRight(lua_State *);
inline void register_lua_funcs(lua_State *state){
	lua_register(state,"println",println);
		lua_register(state,"moveLeft",moveLeft);
			lua_register(state,"moveRight",moveRight);
}
}

#endif

#ifndef __PE_LUA_FUNCTIONS_H_
#define __PE_LUA_FUNCTIONS_H_

#include <stdio.h>
#include <lua.hpp>
namespace pelua{
inline int println(lua_State *s){
	printf("%s\n",lua_tostring(s,1));
	return LUA_OK;
}

inline void register_lua_funcs(lua_State *state){
	lua_register(state,"println",println);
}
}

#endif

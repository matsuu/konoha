#include <stdio.h>     // stdin, stderr, fprintf(), fgets()
#include <string.h>    // strlen()
#include <lua.h>       // lua_pcall(), lua_pop(), lua_close()
#include <lauxlib.h>   // LuaL_newstate(), luaL_loadbuffer()
#include <lualib.h>    // luaL_openlibs()
#include <konoha.h>

void knh_lua_gfree(Ctx *ctx,knh_Glue_t *g){
    lua_State* L = (lua_State*)g->ptr;
    lua_close(L);
}

METHOD Lua_new(Ctx *ctx,knh_sfp_t *sfp){
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    knh_Glue_init(ctx,sfp[0].glue,L,knh_lua_gfree);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

METHOD Lua_doString(Ctx *ctx,knh_sfp_t *sfp){
    lua_State* L = (lua_State*) p_cptr(sfp[0]);
    char* string = p_char(sfp[1]);
    int error;
    error = luaL_dostring(L, string);
    if (error) {
        fprintf(stderr, "%s", lua_tostring(L, -1));
        lua_pop(L, 1);
    }
    KNH_RETURN(ctx,sfp,sfp[0].o);
}
METHOD Lua_doFile(Ctx *ctx,knh_sfp_t *sfp){
    lua_State* L = (lua_State*) p_cptr(sfp[0]);
    char* filename = p_char(sfp[1]);
    int error;
    error = luaL_dofile(L, filename);
    if (error) {
        fprintf(stderr, "%s", lua_tostring(L, -1));
        lua_pop(L, 1);
    }
    KNH_RETURN(ctx,sfp,sfp[0].o);
}
/*
METHOD Lua_close(
METHOD Lua_execute(Ctx *ctx,knh_sfp_t *sfp){
    lua_close(L);
    return 0;
}
*/

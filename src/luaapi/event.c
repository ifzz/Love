#include "event.h"
#include "tools.h"

static int l_event_quit(lua_State* state){
        l_running = 0;
        lua_pushinteger(state, l_running);
        return 1;
}

static luaL_Reg const regFuncs[] = {
        {"quit", l_event_quit},
        {NULL,NULL}
};

int l_event_running()
{
        return l_running;
}

int l_event_register(lua_State* state)
{
        l_running = 1;
        l_tools_registerModule(state, "event", regFuncs);
        return 0;
}

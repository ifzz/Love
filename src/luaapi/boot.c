#include <lauxlib.h>
#include "boot.h"

static char const bootScript[] =
  "package.path = '?.lua;?/init.lua'\n"
  "love.update = function(dt) end\n"
  "love.draw = function() end\n"
  "love.load = function() end\n"
  "love.keypressed = function() end\n"
  "love.keyreleased = function() end\n"
  "love.textinput = function() end\n"
  "local conf = {\n"
  "  window = {\n"
  "    width = 600,\n"
  "    height = 600\n"
  "  }\n"
  "}\n"
  "local confFunc = loadfile(\"conf.lua\")\n"
  "if confFunc then\n"
  "  confFunc()\n"
  "  love.conf(conf)\n"
  "end\n"
  "return conf\n"
;

int l_boot(lua_State* state, bonding_Config *config) {
  if(luaL_dostring(state, bootScript)) {
    return 1;
  }

  lua_pushstring(state, "window");
  lua_rawget(state, -2);

  lua_pushstring(state, "width");
  lua_rawget(state, -2);

  config->window.width = lua_tointeger(state, -1);
  lua_pop(state, 1);
  
  lua_pushstring(state, "height");
  lua_rawget(state, -2);
  config->window.height = lua_tointeger(state, -1);

  lua_pop(state, 3);

  return 0;

}

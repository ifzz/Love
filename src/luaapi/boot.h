#pragma once

#include <lualib.h>
#include "../bonding_config.h"

int l_boot(lua_State* state, bonding_Config *config);

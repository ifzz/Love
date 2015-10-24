#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>

// TODO:
// moduleData.getRelativeMode()
// moduleData.getSystemCursor()
// moduleData.isGrabbed()
// moduleData.newCursor()
// moduleData.setCursor()
// moduleData.setGrabbed()
// moduleData.setRelativeMode()

#ifndef EMSCRIPTEN
extern SDL_Window* graphics_getWindow(void);
#endif

static struct {
  int x, y;
  int dx, dy;
  int visible;
  int buttons[256];
} moduleData;


static const char *buttonStr(int x) {
  switch (x) {
    case SDL_BUTTON_LEFT:
      return "l";

    case SDL_BUTTON_RIGHT:
      return "r";

    case SDL_BUTTON_MIDDLE:
      return "m";

/*
    case SDL_BUTTON_WHEELDOWN:
      return "wd";

    case SDL_BUTTON_WHEELUP:
      return "wu";
*/
  }
  return "?";
}


static int buttonEnum(const char *str) {
  int res;
  switch (*str) {
    case 'l':
      res = SDL_BUTTON_LEFT;
      break;

    case 'r':
      res = SDL_BUTTON_RIGHT;
      break;

    case 'm':
      res = SDL_BUTTON_MIDDLE;
      break;
/*
    case 'w':
      str++;
      switch (*str) {
        case 'd':
          res = SDL_BUTTON_WHEELDOWN;
          break; 

        case 'u':
          res = SDL_BUTTON_WHEELUP;
          break;
        default:
          break;
      }
      break;
*/

    default:
      return -1;
  }

  if(str[1] != '\0') {
    return -1;
  }

  return res;
}


void mouse_mousemoved(int x, int y) {
  if(moduleData.x == x && moduleData.y == y) {
    return;
  }

  moduleData.dx = x - moduleData.x;
  moduleData.dy = y - moduleData.y;
  moduleData.x = x;
  moduleData.y = y;
  // TODO : Do lua callback
}



void mouse_mousepressed(int x, int y, int button) {
  mouse_mousemoved(x, y);
  moduleData.buttons[button] = 1;
  printf("%s: %d, %d, %s\n", __func__, x, y, buttonStr(button)); // TODO: remove me
  // TODO : Do lua callback
}


void mouse_mousereleased(int x, int y, int button) {
  mouse_mousemoved(x, y);
  moduleData.buttons[button] = 0;
  printf("%s: %d, %d, %s\n", __func__, x, y, buttonStr(button)); // TODO: remove me
  // TODO : Do lua callback
}


void mouse_getPosition(int *x, int *y) {
  *x = moduleData.x;
  *y = moduleData.y;
}


int mouse_isDown(const char *str) {
  int x = buttonEnum(str);
  if(x < 0) {
    return -1;
  }

  return moduleData.buttons[x];
}


int mouse_isVisible(void) {
  return moduleData.visible;
}


int mouse_getX(void) {
  return moduleData.x;
}


int mouse_getY(void) {
  return moduleData.y;
}


void mouse_setPosition(int x, int y) {
#ifdef EMSCRIPTEN
  SDL_WarpMouse(x, y);
#else
  SDL_WarpMouseInWindow(graphics_getWindow(), x, y);
#endif
}


void mouse_setVisible(int b) {
  moduleData.visible = !!b;
  SDL_ShowCursor(b ? SDL_ENABLE : SDL_DISABLE);
}


void mouse_setX(int x) {
#ifdef EMSCRIPTEN
  SDL_WarpMouse(x, moduleData.y);
#else
  SDL_WarpMouseInWindow(graphics_getWindow(), x, moduleData.y);
#endif
}


void mouse_setY(int y) {
#ifdef EMSCRIPTEN
  SDL_WarpMouse(moduleData.x, y);
#else
  SDL_WarpMouseInWindow(graphics_getWindow(), moduleData.x, y);
#endif
}

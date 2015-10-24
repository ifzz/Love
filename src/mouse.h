#pragma once

void mouse_mousemoved(int x, int y);
void mouse_mousepressed(int x, int y, int button);
void mouse_mousereleased(int x, int y, int button);
int mouse_isDown(const char *str);
int mouse_isVisible(void);
void mouse_getPosition(int *x, int *y);
int mouse_getX(void);
int mouse_getY(void);
void mouse_setPosition(int x, int y);
void mouse_setVisible(int b);
void mouse_setX(int x);
void mouse_setY(int y);

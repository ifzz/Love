#pragma once

void filesystem_init(void);

int filesystem_read(char const* filename, char** output);
int filesystem_write(const char* name, const char* data);
int filesystem_exists(const char* name);

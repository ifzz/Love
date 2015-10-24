#pragma once

void filesystem_init(void);

int filesystem_read(char const* filename, char** output);

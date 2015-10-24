#pragma once

typedef struct {
  int major;
  int minor;
  int revision;
  char const * codename;
} bonding_Version;

bonding_Version const * bonding_getVersion(void);

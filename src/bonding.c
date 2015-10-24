#include "bonding.h"

bonding_Version const * bonding_getVersion(void) {
  static const bonding_Version version = {
    .major = 0,
    .minor = 0,
    .revision = 2,
    .codename = "Happy cake"
  };

  return &version;
}

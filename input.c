#include "grouper.h"
int getInt(int *pointed) {
  char rolled[11];
  if (fgets(rolled, sizeof(rolled), stdin) == NULL) {
    return 1;
  }
  *pointed = (int)strtol(rolled, NULL, 10);
  return 0;
}

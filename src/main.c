#include "fs_tools.h"
#include "stdio.h"
#include "stdlib.h"

#define CONFIG_FILE "quickbuild"

int main(int argc, char **argv) {
  printf("= quickbuild beta\n");

  // get file system tree
  struct FsObject *fs_object;
  int ret = get_fs_object(".", fs_object);
  if (0 > ret) {
    printf("= error: failed to get filesystem information. consider submitting a bug report");
    return EXIT_FAILURE;
  }

  // load config file
  printf("- \n");

  return EXIT_SUCCESS;
}

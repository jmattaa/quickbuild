#include "fs_tools.h"
#include "stdio.h"
#include "stdlib.h"

#define CONFIG_FILE "quickbuild"

int main(int argc, char **argv) {
  printf("= quickbuild beta\n");

  // get file system tree
  struct FsObject *fs_object = calloc(1, sizeof(struct FsObject));
  int ret = get_fs_object(".", fs_object);
  if (0 > ret) {
    printf("= error: failed to get filesystem information. consider submitting a bug report");
    return EXIT_FAILURE;
  }

  // debug: print all paths
  while(1) {
    printf("path `%s` is file `%s`\n", fs_object->path, fs_object->name);
    if(!(fs_object = fs_object->child)) break;
  }

  // load config file
  




  
  // clean up and exit
  // free_fs_object(fs_object);
  printf("= done\n");
  return EXIT_SUCCESS;
}

// main.c
#include "filesystem.h"
#include <stdio.h>

int main() {
    file_system_t fs;
    init_file_system(&fs);

    int inode = create_file(&fs, "test.txt");
    write_file(&fs, inode, "Hello, Tiny FS!");
    read_file(&fs, inode);

    return 0;
}
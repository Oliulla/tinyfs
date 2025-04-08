// test_filesystem.c
#include <assert.h>
#include "filesystem.h"

void test_create_file() {
    file_system_t fs;
    init_file_system(&fs);

    int inode = create_file(&fs, "testfile.txt");
    assert(inode != -1);

    read_file(&fs, inode);  // Check file content (should be empty)
}

void test_write_file() {
    file_system_t fs;
    init_file_system(&fs);

    int inode = create_file(&fs, "testfile.txt");
    write_file(&fs, inode, "Testing write.");
    read_file(&fs, inode);  // Should print "Testing write."
}

int main() {
    test_create_file();
    test_write_file();
    printf("All tests passed!\n");
    return 0;
}
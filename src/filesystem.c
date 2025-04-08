// filesystem.c
#include "filesystem.h"
#include <stdio.h>
#include <string.h>

directory_entry_t directory[MAX_FILES];
int dir_count = 0;

void init_file_system(file_system_t *fs) {
    for (int i = 0; i < NUM_BLOCKS; i++) {
        fs->free_blocks[i] = 1;  // Mark all blocks as free
    }

    for (int i = 0; i < MAX_FILES; i++) {
        fs->inodes[i].size = 0;  // Initialize inodes as empty
        fs->inodes[i].block_start = -1;
    }

    printf("File system initialized\n");
}

int allocate_block(file_system_t *fs) {
    for (int i = 0; i < NUM_BLOCKS; i++) {
        if (fs->free_blocks[i] == 1) {
            fs->free_blocks[i] = 0;
            return i;
        }
    }
    return -1;
}

int create_file(file_system_t *fs, const char *filename) {
    if (dir_count >= MAX_FILES) {
        printf("Directory full\n");
        return -1;
    }

    for (int i = 0; i < dir_count; i++) {
        if (strcmp(directory[i].filename, filename) == 0) {
            printf("File already exists\n");
            return -1;
        }
    }

    int inode_index = -1;
    for (int i = 0; i < MAX_FILES; i++) {
        if (fs->inodes[i].size == 0) {
            inode_index = i;
            break;
        }
    }

    if (inode_index == -1) {
        printf("No free inodes\n");
        return -1;
    }

    int block_index = allocate_block(fs);
    if (block_index == -1) {
        printf("No free blocks\n");
        return -1;
    }

    fs->inodes[inode_index].size = 0;
    fs->inodes[inode_index].block_start = block_index;

    strcpy(directory[dir_count].filename, filename);
    directory[dir_count].inode_index = inode_index;
    dir_count++;

    printf("File '%s' created successfully\n", filename);
    return inode_index;
}

void write_file(file_system_t *fs, int inode_index, const char *data) {
    inode_t *inode = &fs->inodes[inode_index];
    int block_index = inode->block_start;
    if (block_index != -1) {
        strncpy(fs->blocks[block_index].data, data, BLOCK_SIZE);
        inode->size = strlen(data);
        printf("Data written to file\n");
    } else {
        printf("Invalid block\n");
    }
}

void read_file(file_system_t *fs, int inode_index) {
    inode_t *inode = &fs->inodes[inode_index];
    int block_index = inode->block_start;

    if (block_index != -1) {
        printf("File Data: %s\n", fs->blocks[block_index].data);
    } else {
        printf("File not found\n");
    }
}
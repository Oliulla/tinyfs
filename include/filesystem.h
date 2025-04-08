// filesystem.h
#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#define MAX_FILES 10
#define BLOCK_SIZE 256
#define MAX_FILE_NAME 32
#define NUM_BLOCKS 100

typedef struct inode {
    int size;                // File size
    int block_start;         // Starting block for file data
} inode_t;

typedef struct block {
    char data[BLOCK_SIZE];   // Data in the block
} block_t;

typedef struct file_system {
    block_t blocks[NUM_BLOCKS];  // Array of data blocks
    inode_t inodes[MAX_FILES];   // Array of inodes
    int free_blocks[NUM_BLOCKS]; // Free block list
} file_system_t;

typedef struct directory {
    char filename[MAX_FILE_NAME]; // Filename
    int inode_index;              // Associated inode index
} directory_entry_t;

extern directory_entry_t directory[MAX_FILES];
extern int dir_count;

// Function declarations
void init_file_system(file_system_t *fs);
int allocate_block(file_system_t *fs);
int create_file(file_system_t *fs, const char *filename);
void write_file(file_system_t *fs, int inode_index, const char *data);
void read_file(file_system_t *fs, int inode_index);

#endif
# **Tiny File System (TinyFS)**

## **Project Overview**

TinyFS is a simple, in-memory file system implementation written in C. It simulates the creation, writing, and reading of files within a limited set of blocks, mimicking the core concepts of a file system. This project is designed to help understand basic file system operations like block allocation, managing inodes, file creation, and file data storage.

## **Features**

- **File Creation**: Create a new file with a specified name.
- **File Writing**: Write data to a file within the file system.
- **File Reading**: Read the data stored in a file.
- **Block Management**: Manage a limited number of data blocks and allocate them when needed.
- **Inode Management**: Keep track of file metadata including size and associated data block.
- **Directory Management**: Manage a directory where files are listed, storing filenames and their associated inode.

## **Project Structure**

```
tiny_fs/
│
├── build/                  # Directory containing compiled object files and executable
│   ├── tinyfs              # Executable file
│   ├── main.o              # Object file for main.c
│   └── filesystem.o        # Object file for filesystem.c
│
├── include/                # Header files for defining structures and functions
│   ├── filesystem.h        # File system structures and function declarations
│   └── utils.h             # Utility functions like memory allocation, etc.
│
├── src/                    # Source code
│   ├── filesystem.c        # Core file system operations (e.g., create, read, write files)
│   └── main.c              # Entry point, tests file system operations
│
├── tests/                  # Unit tests for core file system features
│   └── test_filesystem.c   # Test cases to validate file system operations
│
├── Makefile                # Makefile for build automation
└── README.md               # Project overview and instructions
```

---

## **Getting Started**

### **Prerequisites**

To build and run the project, you need to have the following installed:

- **C Compiler**: GCC (or any other C compiler)
- **Make**: Make tool to automate the build process

### **Installation Steps**

1. **Clone the Repository**

   If you haven't already, clone the repository to your local machine:

   ```bash
   git clone https://github.com/yourusername/tinyfs.git
   cd tinyfs
   ```

2. **Build the Project**

   The project uses a `Makefile` for easy compilation. To build the project, simply run:

   ```bash
   make
   ```

   This will generate an executable file called `tinyfs` in the `build/` directory.

3. **Run the Program**

   After building, you can run the program by executing:

   ```bash
   ./build/tinyfs
   ```

   This will create a file called `test.txt`, write some data into it, and print the file contents.

4. **Run Unit Tests (Optional)**

   To run the unit tests, navigate to the `tests` directory and compile the test code:

   ```bash
   gcc -Wall -g tests/test_filesystem.c src/filesystem.c -o build/test_fs
   ./build/test_fs
   ```

   This will compile and run the test cases, printing `All tests passed!` if everything works as expected.

5. **Clean Up**

   If you want to clean up the compiled files (object files and executables), you can run:

   ```bash
   make clean
   ```

   This will remove the `*.o` files and the `tinyfs` executable in the `build/` directory.

---

## **Usage**

The program simulates the creation of a file system, allowing you to create files, write to them, and read them back. Here's how you interact with the system:

1. **File Creation**:

   When you run the program, it creates a file called `test.txt` in the file system with the following command in `main.c`:

   ```c
   int inode = create_file(&fs, "test.txt");
   ```

   If a file already exists with the same name, the program will not create a duplicate and will print an error message.

2. **Write Data to File**:

   Once the file is created, data can be written to it using the `write_file` function. In the program, this happens with the following code:

   ```c
   write_file(&fs, inode, "Hello, Tiny FS!");
   ```

   The `inode` is used to identify which file you're writing data to.

3. **Read File Data**:

   After writing data to the file, you can read it back using the `read_file` function:

   ```c
   read_file(&fs, inode);
   ```

   This will print the content of the file to the console.

---

## **Code Explanation**

### **Core Components**

1. **File System Structure (`file_system_t`)**

   - **Blocks**: An array of blocks (`block_t blocks[NUM_BLOCKS]`), each capable of holding `BLOCK_SIZE` bytes of data.
   - **Inodes**: An array of inodes (`inode_t inodes[MAX_FILES]`), which stores file metadata such as file size and starting block index.
   - **Free Block List**: An array (`int free_blocks[NUM_BLOCKS]`) that keeps track of which blocks are free to use.

2. **Directory Entries (`directory_entry_t`)**

   The directory contains a simple file system directory with entries (`directory_entry_t`), storing the filename and corresponding inode index.

3. **File System Operations**:
   - **`init_file_system`**: Initializes the file system, setting all blocks as free and inodes as empty.
   - **`allocate_block`**: Allocates a free block for data storage.
   - **`create_file`**: Creates a new file, assigns an inode, and allocates a data block.
   - **`write_file`**: Writes data to a specific file using its inode.
   - **`read_file`**: Reads and prints the data stored in the file.

---

## **Testing**

Unit tests are included in the `tests/test_filesystem.c` file to ensure that the file system functions as expected. The tests include:

- **Creating a File**: Verifying that a file is created successfully.
- **Writing to a File**: Ensuring that data can be written to a file.
- **Reading a File**: Verifying that the file contents can be read back correctly.

---

## **Makefile Explanation**

The project includes a `Makefile` that automates the build process. Here's a quick breakdown of its contents:

- **`CC = gcc`**: Specifies that GCC is used as the C compiler.
- **`CFLAGS = -Wall -g`**: Includes compiler flags for all warnings and debugging symbols.
- **`SRCS`**: Lists the source files to be compiled.
- **`OBJS`**: The object files generated from the source files.
- **`EXEC = tinyfs`**: Specifies the output executable file name.
- **`all`**: The default target to build the executable.
- **`clean`**: A target to remove object files and the executable, cleaning up the project.

---

## **Future Improvements**

While this is a simple file system implementation, there are many areas where you can extend and improve:

- **Directory Structure**: Implement nested directories and subdirectories.
- **File Deletion**: Add the ability to delete files and reclaim their blocks.
- **File Size**: Support files that span multiple blocks.
- **Error Handling**: Improve error handling with more specific messages.
- **Disk Persistence**: Implement saving the file system to disk so that data persists between program runs.

---

# **Tiny File System (TinyFS) Makefile**

# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Directories
SRCDIR = src
INCDIR = include
BUILDDIR = build
TESTDIR = tests

# Source files
SRCS = $(SRCDIR)/filesystem.c $(SRCDIR)/main.c
OBJS = $(SRCS:$(SRCDIR)/%.c=$(BUILDDIR)/%.o)

# Test files
TEST_SRCS = $(TESTDIR)/test_filesystem.c $(SRCDIR)/filesystem.c
TEST_OBJS = $(TEST_SRCS:$(SRCDIR)/%.c=$(BUILDDIR)/%.o)
TEST_EXEC = $(BUILDDIR)/test_fs

# Output executable
EXEC = $(BUILDDIR)/tinyfs

# Targets

# Default target to build the executable
all: $(EXEC)

# Build the TinyFS executable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Build the object files for the source code
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

# Target to build and run unit tests
test: $(TEST_EXEC)
	$(TEST_EXEC)

# Build the object files for the tests
$(TEST_EXEC): $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Clean up the project
clean:
	rm -rf $(BUILDDIR)

# Run the program (optional, to execute the project directly)
run: $(EXEC)
	./$(EXEC)

# Phony targets
.PHONY: all clean test run

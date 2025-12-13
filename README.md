# TheLinuxProgrammingInterface_MK

A comprehensive collection of C programs and utilities from "The Linux Programming Interface" book. This repository contains educational examples demonstrating Linux system programming concepts, with a focus on file I/O operations and system library functions.

## Repository Structure

```
TheLinuxProgrammingInterface_MK/
├── examples/              # Example programs organized by topic
│   ├── fileio/           # File I/O operations
│   │   ├── copy.c        # Basic file copying program
│   │   ├── copyholes.c   # File copy handling sparse files
│   │   ├── seek_io.c     # File seeking and positioning
│   │   └── tee.c         # Tee utility implementation
│   └── lib/              # Shared library code and utilities
│       ├── error_functions.c/h    # Error handling utilities
│       ├── get_num.c/h            # Numeric input parsing
│       ├── ename.c.inc            # Error name definitions
│       ├── tlpi_hdr.h             # Common header definitions
│       └── Build_ename.sh         # Build script for error names
├── BUILDING              # Detailed build instructions
└── README.md             # This file
```

## Building the Programs

### Prerequisites

Before building, ensure you have the necessary development libraries installed:

**Debian/Ubuntu:**
```bash
sudo apt-get install libcap-dev libacl1-dev libselinux1-dev libseccomp-dev
```

**RPM-based (Fedora, OpenSUSE, CentOS):**
```bash
sudo dnf install libcap-devel libacl-devel libselinux-devel libseccomp-devel
```

### Building All Programs

Navigate to the root directory and run make to build all programs:

```bash
cd TheLinuxProgrammingInterface_MK
make
```

### Building Individual Programs

First, build the shared library in the lib directory:

```bash
cd examples/lib
make
```

Then build individual programs in their respective directories:

```bash
cd examples/fileio
make copy          # Build a specific program
make all          # Build all programs in the directory
make clean        # Clean build artifacts
```

## File I/O Examples (`examples/fileio/`)

The fileio directory contains practical examples of file input/output operations:

- **copy.c** - Basic file copying with open, read, and write operations
- **copyholes.c** - Demonstrates handling sparse files with holes during copying
- **seek_io.c** - Examples of file positioning and seeking operations
- **tee.c** - Implementation of the standard tee utility

## Shared Library (`examples/lib/`)

Common utilities and header files used across all example programs:

- **error_functions.c/h** - Comprehensive error handling and reporting functions
- **get_num.c/h** - Functions for parsing and validating numeric input
- **tlpi_hdr.h** - Common header with standard includes and macro definitions
- **ename.c.inc** - Error number to name mappings for system errors

## Building on Non-Linux UNIX Systems

The code is designed to be portable across UNIX implementations where possible. Some programs are Linux-specific and noted in the Makefiles as `LINUX_EXE`, while portable programs are listed as `GEN_EXE`.

To build on other UNIX systems:

1. Edit `Makefile.inc` in the root directory to adjust `CFLAGS` and `LDLIBS` for your system
2. Run `make -k allgen` to build portable programs only

## Features

- Clean, well-documented C code for learning Linux system programming
- Covers fundamental concepts like file descriptors, buffering, and seek operations
- Proper error handling and reporting
- Portable design considerations for multiple UNIX implementations
- Build system supporting individual program compilation and system-wide builds

## Troubleshooting

If you encounter build issues:

1. Verify all required libraries are installed (see Prerequisites)
2. Check that your Linux kernel and glibc versions support required features
3. Consult the [online FAQ](http://man7.org/tlpi/code/faq.html) for common issues
4. Try building on a different system to isolate configuration problems

Refer to the `BUILDING` file for more detailed build instructions and system-specific guidance.

## License

These examples are from "The Linux Programming Interface" by Michael Kerrisk. Please refer to the original source for licensing information.

## Reference

For more information about the concepts covered in these examples, refer to:
- "The Linux Programming Interface" by Michael Kerrisk
- Linux man pages (e.g., `man 2 open`, `man 2 read`, `man 2 write`)
- [man7.org TLPI resources](http://man7.org/tlpi/)
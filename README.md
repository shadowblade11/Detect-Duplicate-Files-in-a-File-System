# Detect-Duplicate-Files-in-a-File-System
CITS2002 (System Programming) project


This project was part of the CITS2002 unit and was written in C, worked together with a partner.

## Authors
Sunny Lac - [shadowblade11](https://github.com/shadowblade11)
Tony Nguyen - [Tony-Nguyen0](https://github.com/Tony-Nguyen0)

A description of the project is shown below.

**Background**
In recent years, computer disk sizes and densities have increased dramatically, with costs dropping to 4c/gigabyte (HDD) and 14c/gigabyte (SSD). As a consequence, we store files on our computers' disks in very different ways and, because we typically have a huge amount of free space available, we end up having multiple copies of many files on our disks. This presents few problems, until we eventually run out of disk space, or need to transfer files to more expensive cloud-storage, perhaps over a network with limited bandwidth. At that time we'd like to locate all duplicate files, and only make one copy of them to our backup destination.

The **goal** of this project is to design and develop a command-line utility program, named duplicates, to locate and report duplicate files in, and below, a named directory.
 
Successful completion of the project will develop and enhance your understanding of advanced features of the C11 programming language, and core Linux operating system system-calls and POSIX function calls.

There are two parts to the project:

- The basic version requires you to develop a working program with a restricted set of features. It is possible to receive full marks for the project by only completing the basic version.
- 🌶 If you would like a greater challenge, you may like to attempt the advanced version of this project. Undertaking and completing significant parts of the advanced tasks provides the opportunity to recover any marks not awarded for the basic version of the project.


**Program invocation**
Your implementation of duplicates will be invoked with zero or more valid command-line options, and one directory name. With no command-line options (i.e. only a directory name is provided) duplicates will simply list 4 things (with just one integer per line):
1. the total number of files found,
2. the total size (in bytes) of all files found,
3. the total number of unique files (i.e. any duplicate is only counted once), and
4. the possible minimum total size of all files found (i.e. the sizes of duplicated files are only counted once).

Files and directories (other than the "starting" directory indicated on the command-line) which cannot be read should be silently ignored (no error messages should be printed).
For the basic project, the "starting" directory will only contain regular files and sub-directories. In particular, there will be no hard- or symbolic-links. Your project is required to support the following command-line options and, if attempting the advanced version of the project, command-line options marked with a chili 🌶.

**-a** By default, hidden and configuration files (conventionally those beginning with a '.' character) are not considered by duplicates. Providing the -a option requests that all files be considered. This is similar to the standard Linux utility ls.

**-A**	This option indicates if the program attempts the advanced version of the project.
duplicates -A produces no output at all, simply terminating with EXIT_SUCCESS (for advanced) or with EXIT_FAILURE (for basic).

**-f** **filename**	find and list, one per line, the relative pathnames of all files whose SHA2 hash matches that of the indicated file. The name of the indicated file is not listed.
duplicates -f terminates with EXIT_SUCCESS if any matching files are found, or with EXIT_FAILURE otherwise.

**-h** **hash**	find and list, one per line, the relative pathnames of all files with the indicated SHA2 hash.
duplicates -h terminates with EXIT_SUCCESS if any matching files are found, or with EXIT_FAILURE otherwise.

**-l**	duplicates lists all duplicate files found. Each line of output consists of the relative pathnames of two or more files that are duplicates of each other. The pathnames of duplicate files (on the same line line) must be separated by the TAB character.

**-m**	🌶 duplicates minimizes the total number of bytes required to store all files' data by modifying the directory structure being considered.

**-q**	duplicates executes quietly, simply testing if the named directory contains any duplicate files.
duplicates -q produces no output at all, simply terminating with EXIT_SUCCESS if there are no duplicates (i.e. storage is already minimized), or with EXIT_FAILURE otherwise.


**Detecting duplicate files**
- Two or more files are defined to be duplicates iff their contents are identical. Duplicate files will thus have the same size but, when determining if two files are duplicates of each other, their filenames and modification times are not considered.
- A file is defined to be unique iff no other file has the same contents.

To detect duplicate files we'll employ a cryptographic hash function named SHA2 (pronounced 'shar-2'). SHA2 examines the contents of a file and produces a fixed-length summary of its contents. Cryptographic hash functions are designed by mathematicians and those developing encryption and security software.

Here is an implementation of the function strSHA2.c which you may (should) use without attribution.

Two or more files are considered identical if their cryptographic hashes are identical. For this project, we'll use a C11 string to store this representation, and two files will be considered identical if their SHA2 string representations are identical. The function strSHA2(), with the following prototype:

    char *strSHA2(char *filename);
is provided for this project (it is not a standard C11 function). If strSHA2 can read the indicated file, it will return a dynamically allocated string holding the SHA2 string representation of the file's contents. If the indicated file cannot be read, strSHA2 will return NULL. Note that you do not have to understand the SHA2 algorithm or its strSHA2() implementation for this project.

**Getting started**
There is no required sequence of steps to undertake the project, and no sequence of steps will guarantee success. However, the following sequence is strongly recommended (and this is how the sample solution was built). It is assumed (considered essential for success!) that each step:
is extensively tested before you proceed to the next step, and
reports any errors to stderr as they are found. Serious errors may require the whole program to terminate.

It is anticipated that a successful project will use (some of) the following Linux system-calls, and standard C11 & POSIX functions: 

getopt(), malloc(), realloc(), free(), opendir(), readdir(), closedir(), stat(), and perror();   link()🌶, and unlink();🌶,   strdup(), and strSHA2() (neither are part of the C11 standard).

**Advanced tasks**
If you would like a greater challenge, you may like to attempt to an advanced version of this project. Undertaking and completing significant parts of the advanced tasks provides the opportunity to recover any marks not awarded for the basic version of the project.
There are 3 additional tasks in the advanced section:

- 🌶 support duplicate detection in and below two or more directories provided on the command-line. For example, if four directory names are provided, then all files in all four directories should be considered.
- 🌶 support the presence of hard-links (but not symbolic-links) in the directories being considered. When counting the total number of bytes occupied by all files, the "contents" of all files hard-linked together are counted only once.
- 🌶 support the -m command-line option.
This task requires you to identify duplicate files and to then store only one instance of each (with possibly different names). The Linux link() system call (see man 2 link) provides this facility for us, by creating hard-links between two or more files. The actual file contents will only be stored only once, and multiple relative pathnames will refer to that single copy.
WARNING: until you are very confident that your duplicates program is working correctly, you are strongly advised NOT to use your duplicates program with its -m option to minimize the storage of important files and directories! Test with an unimportant temporary directory.

**Project requirements**
- Your project must be developed in multiple C11 source files and (at least one) header file.
- Your submission will be compiled with the C11 compiler arguments -std=c11 -Wall -Werror -pedantic, and marks will not be awarded if your submission does not compile.
- Compilation and linking of your project must be supported by a Makefile, containing approriate variable definitions and automatic variables.
- The default target of your Makefile must be named duplicates, and invocation of the make command must produce an executable program named duplicates.
- Your project must employ sound programming practices, including the use of meaningful comments, well chosen identifier names; appropriate choice of basic data-structures, data-types, and functions; and appropriate choice of control-flow constructs.

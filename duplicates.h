#include  <stdio.h>
#include  <stdbool.h>
#include  <stdlib.h>
#include  <string.h>
#include <stdint.h>

//HASHTABLE_SIZE is defined
#define HASHTABLE_SIZE     999983

//  A HELPFUL PREPROCESSOR MACRO TO CHECK IF ALLOCATIONS WERE SUCCESSFUL
#define	CHECK_ALLOC(p) if(p == NULL) { perror(__func__); exit(EXIT_FAILURE); }

//Allows us to get the strdup function
#if     defined(__linux__)
extern         char *strdup(const char *s);
#endif



//FILES struct is being defined
typedef struct _file {
    char        **listOfName; //stores the list of pathnames
    int         totalNumberOfFiles; //stores the total number of files
    char        *strshaHash; //stores the strSHA value
    struct _file *nextValue; // creates another struct in case of linked list
} FILES;


typedef	FILES * HASHTABLE;


//global functions
//These functions are declared here, and defined in output.c:
extern void stat_print(void);
extern void command_f(char *filename, HASHTABLE *hashtable);
extern void command_h(char *hashValue, HASHTABLE *hashtable);
extern void command_l(HASHTABLE *hashtable, int *indexlist);
extern void usage(void);

//These functions are declared here, and defined in scanDirectory.c:
extern void scan_directory(char *dirname,HASHTABLE *hashtable, int *indexList, int *inodeList, bool hidden);
extern bool does_Exist_Inode(int *inodeList, int value);

//These functions are declared here, and defined in strSHA2.c:
extern char *strSHA2(char *filename);

//These functions are declared here, and defined in alterHashtable.c:
extern void add_to_hashtable(HASHTABLE *hashtable, char* pathname, int *indexList);
extern uint32_t hash_String(char *string);


//global variables are declared
extern FILES            *files;
extern HASHTABLE        *hashtable;
extern int              *indexList;
extern int              *inodeList;
extern int               totalNumberOfIndexes;
extern int               totalNumberOfInodes;
extern int               total_number_of_files;
extern int               total_number_of_files_unique;
extern size_t               total_size_unique;
extern size_t               total_size_all;



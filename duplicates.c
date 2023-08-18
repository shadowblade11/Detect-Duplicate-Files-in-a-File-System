//  CITS2002 Project 2 2021
//  Name(s):             Sunny Lac (, Tony Nguyen)
//  Student number(s):   23119307 (, 23090585)


//Libraries to include in this file
#include <getopt.h>
#define OPTLIST "aA:f:h:lq:m"

//Reference header file
#include "duplicates.h"


//Initialise int variables
int totalNumberOfIndexes = 0;
int totalNumberOfInodes = 0;
int total_number_of_files = 0;
int total_number_of_files_unique = 0;
size_t total_size_all = 0;
size_t total_size_unique = 0;

//Initialise bool variables
bool aFlag = false,fFlag = false,hFlag = false,lFlag = false,qFlag = false;


//Main function where input is taken as parameters
int main(int argc, char *argv[]){

    //Create hashtable variable and assign memory
    HASHTABLE *hashtable = malloc((HASHTABLE_SIZE+1) * sizeof(*hashtable));

    //Checks hashtable memory is valid
    CHECK_ALLOC(hashtable);

    //Create an int pointer to list for indexes and assign memory
    int *indexList = malloc( (HASHTABLE_SIZE+1) * sizeof(*indexList) );

    //Checks indexList memory is valid
    CHECK_ALLOC(indexList);

    //Create an int pointer to list for inodes and assign memory
    int *inodeList = malloc((HASHTABLE_SIZE+1) * sizeof(*inodeList) );

    //Checks indexList memory is valid
    CHECK_ALLOC(inodeList);

    //Declare variable opt;
    int opt;

    //Declare a character pointer variable for the file name
    char *fileName;

    //Declare a character pointer variable for the hash value
    char *optHashValue;

    //Iterates through input to check for every command
    while((opt = getopt(argc, argv, OPTLIST)) != -1) {
        
        //switch case to activate depending on what command is seen in the input
        switch (opt)
        {
        case 'a':
            aFlag = true;
            break;
        case 'A':
            exit(EXIT_SUCCESS);
            break;
        case 'f':
            fFlag = true;
            fileName = optarg;
            break;
        case 'h':
            hFlag = true;
            optHashValue = optarg;
            break;
        case 'l':
            lFlag = true;
            break;
        case 'q':
            qFlag = true;
            break;

        //In case of invalid command print out its proper usage and exit program with EXIT_FAILURE
        default:
            usage();
            exit(EXIT_FAILURE);
        }
    }
    //taking multiple directory inputs
    for (; optind<argc;optind++){
        //scan directory for each directory input
        scan_directory(argv[optind],hashtable,indexList,inodeList,aFlag);
    }

    //if -f command is used run -f command code
    if (fFlag){
        command_f(fileName,hashtable);
    }

    //if -h command is used run -h command code
    if(hFlag){
        command_h(optHashValue, hashtable);
    }

    //if -l command is used run -l command code
    if(lFlag){
        command_l(hashtable, indexList);
        exit(EXIT_SUCCESS);
    }

    //if -q command is used, checks if the numbers of files in directory equates
    // to number of unique files and exit with EXIT_SUCCESS if equal otherwise
    // EXIT_FAILURE
    if(qFlag){
        if (total_number_of_files == total_number_of_files_unique){
            exit(EXIT_SUCCESS);
        }
        exit(EXIT_FAILURE);
    }


    //Print out the relevant statistics for this project
    stat_print();

    //Ends main function
    return 0;
    }
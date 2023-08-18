//Libraries to include in this file
#include <stdio.h>
//Reference header file
#include "duplicates.h"

/*This c source file contains functions that print out the statistics
of the hashtable or the pathnames of the structs within the hashtable
when called*/

//Prints out the following statistics for the directory:
//it's total number of files and unique files
//and it's total byte size of all files and all unique files
void stat_print(void){
    printf("%i\n", total_number_of_files);
    printf("%li\n", total_size_all);
    printf("%i\n", total_number_of_files_unique);
    printf("%li\n", total_size_unique);
}

//-f command code that takes a character pointer to the file name and a pointer to a hashtable 
void command_f(char *filename, HASHTABLE *hashtable){

    //Intialise strValue pointer with the hash value of filename
    char *strValue = strSHA2(filename);

    //Checks if an existing filename was used to initialise strValue
    //If not, exit with EXIT_FAILURE
    if (strValue == NULL){
        exit(EXIT_FAILURE);
    }

    //If strValue has a value, finds the same hash value as filename in hashtable and print its directory
    else{
    
    //Get index from modulating hashvalue with the hashtable size
    int key = hash_String(strValue)%HASHTABLE_SIZE;
    
    //Initialise FILES pointer variable with the hashtable values at key index
    FILES *object = hashtable[key];

    //Iterates through object variable while it is not empty
    while (object != NULL){

    //compares the hashvalue in object with the current hashvalue we're looking for
    if (strcmp(object->strshaHash,strValue) == 0){

        //If hash values matches, iterates through the list of path names until
        //we reach the total number of files
        for (int x = 0; x< object->totalNumberOfFiles;x++){
            
            //Checks if the filename is not the same as the one in the index
            //of listOfName list
            if (strcmp(filename,object->listOfName[x]) != 0){
                
                //prints the pathname in listOfName at index x
                printf("%s\n",object->listOfName[x]);
            }
        }
        
        //Exits out of the program with EXIT_SUCCESS
        exit(EXIT_SUCCESS);
    }

    //Re-initialise variable with the struct in the nextValue variable
    object = object->nextValue;
    }

    //Checks if the object is NULL, if so, then exits out of the program with EXIT_FAILURE
    if (object == NULL){
        exit(EXIT_FAILURE);
    }
    }
    
}
//-h command code that takes a character pointer to the hash value and a pointer to a hashtable 
void command_h(char *hashValue, HASHTABLE *hashtable){
    //Checks if a value has been inputted
    if(hashValue == NULL){
        exit(EXIT_FAILURE);
    }
    else{
        //Get index from modulating hashvalue with the hashtable size
        int key = hash_String(hashValue)%HASHTABLE_SIZE;

        //Initialise FILES pointer variable with the hashtable values at key index
        FILES *object = hashtable[key];

        //Iterates through object variable while it is not empty
        while (object != NULL){
            
            //Compares the hashvalue in object with the current hashvalue we're looking for
            if (strcmp(object->strshaHash, hashValue) != 0){

                //If the hashvalues don't match, re-initialise variable with the struct in the nextValue variable
                object = object->nextValue;
            }
            else{
                //If the hashvalues do match, break the while statement
                break;
            }
        }
        //Checks if the object is NULL, if so, then exits out of the program with EXIT_FAILURE
        if (object ==NULL){
            exit(EXIT_FAILURE);
        }

        //If the object isn't NULL, iterate through the listOfName, printing out the pathname
        int length = object->totalNumberOfFiles;
        for(int x = 0; x < length; x++){
            printf("%s\n",object->listOfName[x]);
        }
    }

    //Exits out of the program with EXIT_SUCCESS
    exit(EXIT_SUCCESS);
}

//Void function that prints an error message and what commands are available
// in the case of invalid inputs
void usage(void){
    printf("Invalid use of command\n");
    printf("Available commands are:\n");
    printf("\t-a\n");
    printf("\t-f filename\n");
    printf("\t-h hash\n");
    printf("\t-l\n");
    printf("\t-q\n");
}

//-l command code that takes a pointer to a hashtable and a pointer to a list of index
void command_l(HASHTABLE *hashtable, int *indexList){

    //Iterates through a number of times equal to the number of indexes in the indexList
    for (int x = 0; x<totalNumberOfIndexes;x++){

        //Initialise FILES object pointer variable with hashtable value at
        //index of indexList value at index x
        FILES *object = hashtable[indexList[x]];

        //Iterates through object variable while it is not empty
        while (object != NULL){

            //If the totalNumberOfFiles is less than 2, re-initialise variable with the struct in the nextValue variable
            if (object->totalNumberOfFiles < 2){
                object = object->nextValue;
            }
            else{

                //Iterate through the listOfName, printing out the pathname
                for (int i =0; i<object->totalNumberOfFiles;i++){
                    printf("%s\t",object->listOfName[i]);
                }
                printf("\n");

                //re-initialise variable with the struct in the nextValue variable
                object=object->nextValue;
            }
        }
    }
}
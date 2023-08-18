//Libraries to include in this file
#include  <sys/stat.h>
//Reference header file
#include "duplicates.h"

/*This c source file contains functions that make changes to the hashtable,
either altering structs within the hashtable or creating structs inside it*/

//Turns hash string into an integer value
//Takes a string paramter and returns a 32-bit integer
uint32_t hash_String(char *string)
{

    //Initialise 32-bit integer variable 'hash' with 0
    uint32_t hash = 0;

    //Checks that pointer to string is not pointer to a null byte
    while(*string != '\0') {

        //Hash value is re-inisitalise as hashvalue multiple by 33 plus
        //the ASCII value of the character at string pointer
        hash = hash*33 + *string;

        //Moves string pointer to the next character
        ++string;
    }

    //returns the hash 32-bit integer value
    return hash;
}

//Function to create a struct
//Function takes a 2 char pointer and returns a struct
FILES* create_Struct(char *hashvalue, char *pathname){

    //Allocates size for struct variable pointer 'ptr'
    //Size allocated is the byte size of FILES struct plus 1
    FILES *ptr = malloc(sizeof(*ptr)+1);

    //Checks that memory has been allocated properly for ptr
    CHECK_ALLOC(ptr);

    //Allocates memory for strshaHash value in ptr struct
    //size allocated is the byte size of char tiems 65, the length
    //of a hash value
    ptr->strshaHash = malloc(65*sizeof(char));

    //Copy the hashvalue into ptr struct variable strshaHash
    strcpy(ptr->strshaHash,hashvalue);

    //Initialise int variable length with string length of pathname
    int length = strlen(pathname);

    //Allocates memory for ptr struct variable listOfName
    ptr->listOfName = malloc(((length+1)*sizeof(char*)));

    //Initialise listOfName at index 0 in ptr struct with a duplicate
    // of pathname string
    ptr->listOfName[0] = strdup(pathname);

    //Initialise totalNumerOfFiles variable in ptr struct with 1
    ptr->totalNumberOfFiles = 1;

    //Initialise nextValue struct variable in ptr struct as NULL
    ptr->nextValue = NULL;

    //Increase global variable total_numer_of_files_unique by 1.
    total_number_of_files_unique++;

    //Declare a struct stat with all the stat info of directory
    struct stat     stat_info;

    //Grabs the statistical information of pathname directory
    stat(pathname, &stat_info);

    //Adds the byte size of the file at the end of the pathname
    //directory to global variable total_size_unique
    total_size_unique += stat_info.st_size;

    //Returns the ptr struct
    return ptr;
}

//Function to add the pathname to ptr struct's listOfName variable
//Takes the struct ptr and pathanme string as parameters
void add_Pathname(FILES *ptr, char* pathname){

    //Initialise integer variable fileNumber with value of totalNumberOfFIles
    // in ptr struct
    int fileNumber = ptr->totalNumberOfFiles;
    
    //Increase totalNumberOfFiles in ptr struct by 1
    ptr->totalNumberOfFiles++;
    
    //Duplicates the pathname string value to fileNumber infex of listOfName in
    //ptr struct
    ptr->listOfName[fileNumber] =  strdup(pathname);
}

//Function to check if the value exists in the indexList already
bool does_Exist(int *indexList,int value){
    int x = 0;
    //Iterates through the indexList
    while (x != totalNumberOfIndexes){
        //If there is a value in the indexList that equals the value in the parameter, return true
        if(indexList[x] == value){
            return true;
        }
        x++;
    }
    //if the while loop has finished, return false
    return false;
}

//Function to add hash index to a list
//Takes index list pointer and integer variable as parameter
void add_to_indexList(int *indexList, int value){
    
    //Checks if value is not in indexList
    if (!does_Exist(indexList, value)){

        //Adds the value to the indexList at index totalNumerOfIndexes
        indexList[totalNumberOfIndexes] = value;

        //Increase global variable totalNumberOfIndexes by 1
        totalNumberOfIndexes++;   
    }
}


//Adds the relevant values to the hashtable
//Takes parameters: pointer to hashtable, pathname string and index list
void add_to_hashtable(HASHTABLE *hashtable, char* pathname, int *indexList){

    //Initialise string strValue with string of the hashValue of pathname directory
    char *strValue = strSHA2(pathname);
     //gets the key using hash_String and the strValue
    int key = hash_String(strValue)%HASHTABLE_SIZE;

    //Checks if the index 'key' in hashtable is NULL
    if (hashtable[key] == NULL){
        
        //If NULL, creates a struct and adds it to the hashtable at index 'key'
        hashtable[key] = create_Struct(strValue,pathname);

        //Adds the index to the list of index in indexist
        add_to_indexList(indexList, key);
    }
    else{

        //Initialise a pointer to a struct variable called tempPtr with the hashtable struct at index 'key'
        FILES *tempPtr = hashtable[key];
        while (true){
            //Checks if the struct has the same hash value
            if (strcmp(tempPtr->strshaHash,strValue) == 0){
                //Adds pathname to listOfName list in file struct
                add_Pathname(tempPtr,pathname);
                //Stops the function
                break;
            }
            //Checks if the nextValue struct is NULL
            else if (tempPtr->nextValue != NULL) {
                //If nextValue isn't NULL, re-initialise variable with the struct in the nextValue variable
                tempPtr = tempPtr->nextValue; 
            }
            //If nextValue is NULL, create a struct for nextValue
            else{
                tempPtr->nextValue = create_Struct(strValue,pathname);
                break;
            }
        }
    }
}
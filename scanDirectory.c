//Libraries to include in this file
#include  <sys/stat.h>
#include  <dirent.h>


//Reference header file
#include "duplicates.h"

/*This c source file contains functions to open directories and
get the needed information from the files*/


//Function that checks if the value exists in the inodeList
bool does_Exist_Inode(int *inodeList, int value){
    int x = 0;
    //Iterates through the inodeList
    while (x != totalNumberOfInodes){
        //If there is a value in the inodeList that equals the value in the parameter, return true
        if(inodeList[x] == value){
            return true;
        }
        x++;
    }
    //if the while loop has finished, return false
    return false;
}

//Function that adds the inode the to inodeList
void add_to_inodeList(int *inodeList, int value){
        //Adds the value to the indexList at index totalNumerOfInodes
        inodeList[totalNumberOfInodes] = value;

        //Increase global variable totalNumberOfInodes by 1
        totalNumberOfInodes++;   
}

//Function that opens a directory and gets the attributes of the files within
void scan_directory(char *dirname,HASHTABLE *hashtable, int *indexList, int *inodeList,bool hidden)
{
    DIR             *dirp;
    struct dirent   *dp;
    bool runnable = true;

//Ensure that we can open (read-only) the required directory
    dirp       = opendir(dirname);
    if(dirp == NULL) {
        perror( dirname );
        exit(EXIT_FAILURE);
    }
//Read from the required directory, until we reach its end
    while((dp = readdir(dirp)) != NULL) {
        //Ignore the "." and ".."
        if (strcmp(dp->d_name,".") != 0 && strcmp(dp->d_name,"..") != 0) {
        struct stat     stat_info;
        char            *pathname = calloc(strlen(dirname)+1+strlen(dp->d_name)+1, sizeof(char));

        //Joins the dirname and dp->d_name together as the variable pathname
        sprintf(pathname, "%s/%s", dirname, dp->d_name);

        //Determines attributes of this directory entry

        //Checks if the file can be used in stat(), if not, then it's corrupted and runnable is false
        if(stat(pathname, &stat_info) != 0) {
            runnable = false;
        }

        //Checks if the file is symbolic or hardlinked, if's it symbolic then runnable is false
        if (S_ISLNK(stat_info.st_mode) && runnable == true){
            runnable = false;
        }

        //If it's a directory, then recursion will occur, opening the directory
        if (S_ISDIR(stat_info.st_mode) != 0 ){ 
            if ((dp->d_name[0] == '.' && hidden) || dp->d_name[0] != '.'){
                scan_directory(pathname, hashtable, indexList,inodeList,hidden);
                
            }
        }
        //if its a regular file, and that it is a hardlinked and uncorrupted file
        if (S_ISREG(stat_info.st_mode) && runnable == true){
            
            //Checks if the file is a hidden file or not and whether to add to the hashtable
            if(((dp->d_name[0] == '.' && hidden) || dp->d_name[0] != '.') && runnable == true){
                //Adds the pathname to the hashtable through add_to_hashtable
                add_to_hashtable(hashtable,pathname,indexList);

                //Gets the inode from stat_info
                int inode = stat_info.st_ino;

                //Checks if the inode already exists within the inodeList
                if (!does_Exist_Inode(inodeList,inode)){

                //Add the inode to the inodeList
                add_to_inodeList(inodeList,inode);
                //Adds the byte size of the file to the total byte size of all files
                total_size_all += stat_info.st_size;

                //increment the total number of files
                total_number_of_files++;
                }
                

                
            }
            
        }
    }
    }
    

    //Close the directory
    closedir(dirp);
}
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<time.h>
#include<dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<stdlib.h>
#include <stddef.h>
int cmd_cnt;// number of compilation commands available in makefile cnt
int dir_file_cnt;//file count available in directory
void * read_cmd(char *);  // all compilation related CMD 
int check_exe(FILE *,DIR *); // it read the executable file name and send to check file()
//int check_file(DIR *,char *);// it check given file present in current direcory or not
char * read_file(FILE *); // it store makefile into a buffer 

void * read_dir(DIR *); // read the directory and store all filename into arry
int check_file(char (*)[50],char *); // it read the executable file name and send to check file
void get_exe_fname(FILE *);// get makefile executable filename

long int file_Lastmodif_time(char *filename); // return last modified time

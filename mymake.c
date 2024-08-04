
//#define CMD 4
#include"myheader.h"
#include"myheader.c"

char *file_name(char *ptr)
{
	int cnt=0;
	char *line=ptr;

	while(line=strchr(line,' '))
	{
		cnt++;
		if(cnt==2)
		{
			return (line+1);
		}
		line++;
	}
	return NULL;
}

int main()
{
	//const char *path="/home/devesh8928/linux/make/";  // for specified directory
	const char *path="./";    // for opening Current working directory

	FILE *fp;
	char * str=NULL;
	char (*cmd)[100]=NULL;  // ptr to all executable / compilation CMD
	char (*file)[50]=NULL;			



	DIR *dir = opendir(path);
	if(dir==NULL)
	{
		perror("Directory : ");
		exit(0);
	}
        file=read_dir(dir);//  Read directory and store in array
	if(check_file(file,"makefile")==0)   // Read directory and check whether makefile is present or not
	{
		printf("Makefile Not Present In Directory\n");
		exit(0);
	}

	fp=fopen("makefile","r");
	if(fp==NULL)
	{
		perror("File");  // printf("Makefile Not opended\n");
		exit(0);
	}

	get_exe_fname(fp);//executable filename store in "exe_name" array

#ifdef	CMD
	printf("Reading makefile\n");
#endif
	str=read_file(fp);
#ifdef	CMD
	printf("Reading makefile success\n");
#endif

#ifdef	CMD
	printf("Reading CMD in buffer\n");
#endif
	cmd=read_cmd(str);
#ifdef	CMD
	printf("Reading CMD success\n");
#endif

	if(check_file(file,exe_name))  
		// Checking is executable file is present in working directory or Not
	{
		// check time stamp of each object file ".c" with last
		// mofication time with "executable" file time
		// if any ".c" file executable diffrent then execute its 
		// related Instruction "cc -c file.o" for all files
		// then execute "Executable file command" 
		// "cc file1.o file2.o"


		int flag=0;  // for checking all file compilation status 

              long int exe_time;
	      exe_time=file_Lastmodif_time(exe_name);// finding executable last modificational time
#ifdef	CMD
	printf("Executable time found : %ld\n",exe_time);
#endif

#ifdef	CMD
	printf("Dir_file_cnt : %d",cmd_cnt);
#endif
	      for(int i=1;i<cmd_cnt;i++) // -1 b/c enter at last of makefile also being save in CMD array 
	      {
		     long int file_time=0;
	      	     char *ptr=file_name(cmd[i]);
		     if(ptr==NULL)
		     {
  			printf("file error : %s\n",cmd[i]);
		      printf("File name Not Supplyed\n");
		      exit(0);
		     }
#ifdef	CMD
	printf("file name last modif time : %s\n",ptr);
#endif
		         
	     		 file_time=file_Lastmodif_time(ptr);// each file last modification time finding
#ifdef	CMD
	printf("file time found : %ld\n",file_time);
#endif

			 if(exe_time<file_time)//  comparing it executable file Last Modf time not equal to File Last Modif 
			 {
			      system(cmd[i]);          // executing the file
			      printf("%s\n",cmd[i]);
			      flag=1;
			 }


	      }

	      if(flag==0)
	      {
	      printf("All Files are Upto date\n");
	      }

	}


	else
	{
		// first execute all ".c" file related CMD of Compilation
		// then execute main executable CMD "cc .o .o"
#ifdef	CMD
	printf("In side loop to compile all CMD\n");
#endif
//		for(int i=0;i<cnt;i++)
//			printf("%s\n",cmd[i]);

		strcat(cmd[0]," -o "); // adding new executable name in cmd 
		strcat(cmd[0],exe_name);

		for(int i=1;i<cmd_cnt;i++)
		{
			printf("%s\n",cmd[i]);
			if(system(cmd[i])==-1)
			{
				perror("system");
				exit(0);
			}
		}
		if(system(cmd[0])==-1)
		{
			perror("system");
			exit(0);
		}
			printf("%s\n",cmd[0]);

#ifdef	CMD
		printf("First time compilation complited successfully\n");
#endif

	}


}
































/*
void * read_cmd(char *ptr)
{
	char *p=ptr;
	char (*str)[100]=NULL;
	while(p=strstr(p,"cc"))
	{
		str=realloc(str,sizeof(*str)*(cnt+1));
		int i=0;
		do
		{
			str[cnt][i]=p[i];
		}
		while(str[cnt][i++]!='\n');

		str[cnt++][--i]='\0';
		p=p+strlen(str[cnt-1]);
	}
}
int check_exe(FILE *fp,DIR *dir)
{
	rewind(fp); // make offset at 0 or curse at begning
	char arr[20];
	int i=0;
	while((arr[i++]=getc(fp))!=':');
	arr[--i]='\0';

	return check_file(dir,arr) ? 1:0 ;


}

int check_file(DIR *dir,char *filename)
{
	struct dirent *ptr_dir=NULL;

	int flag=0;
	while(ptr_dir=readdir(dir))
	{
		char *fname=ptr_dir->d_name;

		if(fname==filename)
		{
			flag=1;
		}
	}

	return flag ? 1:0;
}



char * readfile(FILE *fp)
{
	char *ptr=NULL;

	fseek(fp,0,2);
	int size=ftell(fp);
	rewind(fp);

	ptr=calloc(1,size);
	fread(ptr,size,1,fp);
	return ptr;
}
*/

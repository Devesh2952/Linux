#include"myheader.h"
char exe_name[20];

void * read_cmd(char *ptr)
{
	char *p=ptr;
	char (*str)[100]=NULL;
	while(p=strstr(p,"cc"))
	{
		str=realloc(str,sizeof(*str)*(cmd_cnt+1));
		int i=0;
		do
		{
			str[cmd_cnt][i]=p[i];
		}
		while(str[cmd_cnt][i++]!='\n');

		str[cmd_cnt++][--i]='\0';
		p=p+strlen(str[cmd_cnt-1]);
	}
	return str;
}


void get_exe_fname(FILE *fp)
{
//	static char arr[20];
	int i=0;
	while((exe_name[i++]=getc(fp))!=':'); // reading the executable file name
	exe_name[--i]='\0';

	rewind(fp); // make offset at 0 or curse at begning


}
/*
int check_file(DIR *dir,char *filename)
{
	struct dirent *ptr_dir=NULL;

	printf("Filename for Comparission : %s",filename);
	int flag=0;
	while(ptr_dir=readdir(dir))
	{
		char *fname=ptr_dir->d_name;
#ifdef	CMD
		printf("%s\n",fname);
#endif
		if(strcmp(fname,filename)==0)
			//if(fname==filename)
		{
			flag=1;
		}
	}

	return flag ? 1:0;
}
*/


int check_file(char (*ptr)[50],char *filename)
{
//	char (*ptr)[50]=(char *[50])pptr;
	int flag=0;
	for(int i=0;i<dir_file_cnt;i++)
	{
		if(strcmp(ptr[i],filename)==0)
                {
                        flag=1;
                }
        }

        return flag ? 1:0;
}


void * read_dir(DIR *dir)
{
        struct dirent *ptr_dir=NULL;

	char (*ptr)[50]=NULL;
        while(ptr_dir=readdir(dir))
        {
                char *fname=ptr_dir->d_name;
		ptr=realloc(ptr,sizeof(*ptr)*(dir_file_cnt+1));
		if(ptr==NULL)
		{
		printf("Memory Not allocated to ptr in directory file reading\n");
		exit(0);
		}
		strcpy(ptr[dir_file_cnt],fname);
		dir_file_cnt++;
#ifdef  CMD
                printf("%s\n",fname);
#endif
	}
	return ptr;
}



char * read_file(FILE *fp)
{
	char *ptr=NULL;

	fseek(fp,0,2);
	int size=ftell(fp);
	rewind(fp);

	ptr=calloc(1,size);
	fread(ptr,size,1,fp);
	int i=size-1;
	while(!(isalpha(ptr[i])))
	{
	    ptr[i]='\0';
	    i--;
	}
	ptr[i+1]='\n';
	rewind(fp); // make offset at 0 or curse at begning
	return ptr;
}

long int file_Lastmodif_time(char *filename)
{
	struct stat file_stat;
                if(stat(filename, &file_stat)==-1)
                {
                        perror("stat : ");
                        exit(0);
                }

		//printf("%s\n", ctime(&file_stat.st_mtime));
		return file_stat.st_mtime;
		
}


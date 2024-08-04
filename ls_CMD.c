#include<stdio.h>
#include<string.h>
#include<time.h>
#include<dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<stdlib.h>
#include<pwd.h>
#include<grp.h>

void print_file_permissions(mode_t mode) {
	//	printf("Permissions: ");

	printf((mode & S_IRUSR) ? "r" : "-");  // User read permission
	printf((mode & S_IWUSR) ? "w" : "-");  // User write permission
	printf((mode & S_IXUSR) ? "x" : "-");  // User execute permission
	printf((mode & S_IRGRP) ? "r" : "-");  // Group read permission
	printf((mode & S_IWGRP) ? "w" : "-");  // Group write permission
	printf((mode & S_IXGRP) ? "x" : "-");  // Group execute permission
	printf((mode & S_IROTH) ? "r" : "-");  // Others read permission
	printf((mode & S_IWOTH) ? "w" : "-");  // Others write permission
	printf((mode & S_IXOTH) ? "x" : "-");  // Others execute permission

	printf("\t");
}

void update(char *arr)
{
	memmove(arr,arr+4,strlen(arr+4)+1);
	int len=strlen(arr);
	arr[len-5]='\0';
}

int main()
{
	//const char *path="/home/devesh8928/linux/make/";
	const char *path="./";
	DIR *dir = opendir(path);
	struct stat file_stat;

	if(dir==NULL)
	{
		perror("Directory : ");
		exit(0);
	}


	struct dirent *ptr_dir=NULL;

	while(ptr_dir=readdir(dir))
	{
		char arr[25];
		char *filename=ptr_dir->d_name;
		if(stat(filename, &file_stat)==-1)
		{
			perror("stat : ");
			exit(0);
		}

		struct passwd *pw = getpwuid(file_stat.st_uid);
		struct group *gr = getgrgid(file_stat.st_gid);

		print_file_permissions(file_stat.st_mode);
		//printf("GID: %ld\t", (long) file_stat.st_gid);
		printf("%s\t",gr->gr_name);
		//printf("UID: %ld\t", (long) file_stat.st_uid);
		printf("%s\t",pw->pw_name);
		// printf("Number of hard links: %ld\n", (long) file_stat.st_nlink);
		printf("%ld\t", (long) file_stat.st_nlink);
		//printf("Size: %ld bytes\t", (long) file_stat.st_size);
		printf("%ld\t", (long) file_stat.st_size);
		//printf("Last file modification:   %s\t", ctime(&file_stat.st_mtime));
		strcpy(arr,ctime(&file_stat.st_mtime));
		update(arr);
		printf("%s\t",arr);
		//printf("File: %s\n", filename);
		printf("%s\n", filename);
	}
	printf("\n");

	closedir(dir);
}

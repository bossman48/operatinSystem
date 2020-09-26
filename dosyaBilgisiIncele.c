#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
 
int main(int argc, char **argv)
{
	if(argc != 2)    
		return 1;

	struct stat fileStat;
	if(lstat(argv[1], &fileStat) < 0)    
		return 1;

	printf("\n");
	printf("Information for %s\n", argv[1]);
	printf("---------------------------\n");
	printf("File Size: \t\t%lu bytes\n", fileStat.st_size);
	printf("Number of Links: \t%d\n", fileStat.st_nlink);
	printf("File inode: \t\t%lu\n", fileStat.st_ino);

	printf("File Permissions: \t");
	printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
	printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
	printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
	printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
	printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
	printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
	printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
	printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
	printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
	printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
	printf("\n\n");

	if(S_ISDIR(fileStat.st_mode)) printf("%s is a directory.\n", argv[1]);
	if(S_ISREG(fileStat.st_mode)) printf("%s is a regular file.\n", argv[1]);
	if(S_ISLNK(fileStat.st_mode)) printf("%s is a symbolic link file.\n", argv[1]);
	if(S_ISCHR(fileStat.st_mode)) printf("%s is a character special file.\n", argv[1]);
	if(S_ISBLK(fileStat.st_mode)) printf("%s is a block special file.\n", argv[1]);
	if(S_ISFIFO(fileStat.st_mode)) printf("%s is a pipe file.\n", argv[1]);
	if(S_ISSOCK(fileStat.st_mode)) printf("%s is a socket file.\n", argv[1]);
	printf("\n");

	return 0;
}

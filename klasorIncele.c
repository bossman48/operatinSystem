#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

int main()
{
	DIR           * dirp;
	struct stat     buff;
	struct dirent * dptr;
	char            filepath[1024];
	char            filepath2[1024];
	char            dirname[100];
	int numberOfDirectroy=0;	
	int numberOfNormalFile=0;
	int numberOfSembolikLink=0;
	int total=0;
	char *maxFile="";
	int maxLen=0;	

	printf("Lutfen dizin yolunu giriniz:");
	scanf("%s", dirname);

	/* klavyeden girmis oldugunuz yoldaki dizine erismeye calisir */
	dirp = opendir(dirname);
	if (!(dirp))
	{
		perror("opendir()");
		return(1);
	};

	/* dizindeki dosyalari teker teker okur ve dptr degiskenine atar */
	while ((dptr = readdir(dirp)))
	{
		/* her bir dosyanın yolunu filepath degiskenine atar */ 
		strcpy(filepath, dirname);
		strcat(filepath, "/");
		strcat(filepath, dptr->d_name);
		//printf("pathname:%s\n",filepath);
		stat(filepath, &buff);
		total++;

		if(S_ISDIR(buff.st_mode)){
			numberOfDirectroy++;
		}
		else if(S_ISREG(buff.st_mode)){
			numberOfNormalFile++;
		}
		/*else if(S_ISLNK(buff.st_mode)){
			numberOfSembolikLink++;
		}*/
		//printf("size is %d\n",(int) buff.st_size);
		if((int) buff.st_size > maxLen){
			maxLen=(int) buff.st_size;
		
			//filepath2 = filepath;
 			strcpy(filepath2, filepath); 
		//printf("maxLen is %d + maxFile is %s\n",(int) maxLen,filepath2);
		}


		//printf("maxFile %s\n", maxFile);
	}
	printf("number of normal file: %d\n", numberOfNormalFile);
	printf("number of directory: %d\n", numberOfDirectroy);
	printf("number of sembolik link:%d \n",buff.st_nlink);

	printf("total files: %d\n", total);

	printf("biggest file (maxFile) : %s\n", filepath2);
	

	closedir(dirp);

	return 0;
}

#include<curl/curl.h>
#include<sys/stat.h>
#define MAX 50

int upload(char localpath[MAX], CURL *curl, FILE  *fd)
{
//	FILE *fd;
        struct stat file_info;
        fd = fopen(localpath, "rb");

        if(!fd){
		perror("fopen\n");
	//	exit(0);
               return 1;}

        //to get the file size 
        if(fstat(fileno(fd), &file_info) != 0)
                return 1;  //cannot continue 

        //uploading to url
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1);

        // set where to read from (on Windows you need to use READFUNCTION too) 
        curl_easy_setopt(curl, CURLOPT_READDATA, fd);

        // and give the size of the upload (optional) 
        curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t)file_info.st_size);
        printf("\nThe file size is: %lu\n", file_info.st_size);

	if(file_info.st_size == 0)
		return 1;
//        fclose(fd);     

        return 0;
}


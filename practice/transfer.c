// c code to download/upload files from server or upload to server
//both operations are in one code

#include<stdio.h>
#include<curl/curl.h>
#include<string.h>
#include<sys/stat.h>
//#include "updw.h"

FILE *fd;

int dwload(char localpath[50] , CURL *curl)
{
	/* open the file */
        fd = fopen(localpath , "wb");
        if(fd) {
	        printf("fd created to download file!!!\n");}
 
        /* write the page body to this file handle */
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fd);
}




int upload(char localpath[50], CURL *curl)
{
	struct stat file_info;
	fd = fopen(localpath, "rb");

	if(!fd){
		perror("fopen");
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
	
//	fclose(fd);	
	
	return 0;
}


int process(char localpath[50], char url[50], CURL *curl)
{
	int ch, rs;

	CURLcode res;
	//setting a url
        curl_easy_setopt(curl, CURLOPT_URL, url);
 
        //giving passwd and usernam efor authentication
        curl_easy_setopt(curl, CURLOPT_USERPWD, "dhvani:dhvc");
 
        //create missing directories
        curl_easy_setopt(curl, CURLOPT_FTP_CREATE_MISSING_DIRS,  CURLFTP_CREATE_DIR_RETRY);
 
 
        printf("\nEnter your choice\n1)Upload file\n2)Download file\n");
        scanf("%d", &ch);
 
        switch(ch)
        {
               case 1:
               rs = upload(localpath, curl);
               break;

              case 2:
              rs = dwload(localpath, curl);
              break;

              default:
              printf("Enter correct no\n");
 
        }
  
 
       //starting verbose mode to make connection more talkative
       curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);

       //perform all the operations that are given     
       res = curl_easy_perform(curl);
       printf("the res is:%d\n",res);
       if(res != CURLE_OK)
       {
               fprintf(stderr, "curl_easy_perform() failed: %s\n",
               curl_easy_strerror(res));
		return 0;
       }

       else{
               printf("file transfer successfully!!!\ncheck the given location\n");
		return 1;}
	
//	fclose(fd);

}


int main()
{
	int ch, rs;
	CURL *curl;
	//CURLcode res;
//	FILE *fd;
	//struct stat file_info;
	char localpath[50], url[50];

	//getting the local path
	printf("Enter the file path which you want to upload:\n\t");
        gets(localpath);

	//getting url from user
	printf("\nEnter URL:\n\t");
        gets(url);

	printf("\n");

	//initializing parameters
	curl_global_init(CURL_GLOBAL_ALL);
        curl = curl_easy_init();

	rs = process(localpath, url, curl);
	
 
 
        /* cleanup curl stuff */
        curl_easy_cleanup(curl);
 
        curl_global_cleanup();
	
	fclose(fd);
	
	return 0;

}

#include<curl/curl.h>
#include<unistd.h>
#define MAX 50


int dwload(char localpath[MAX] , CURL *curl, FILE *fd)
{
        //open the file 
        fd = fopen(localpath , "wb");
        if(!fd) {
                printf("fd created to download file!!!\n");}

        // write the page body to this file handle */
         curl_easy_setopt(curl, CURLOPT_WRITEDATA, fd);
	
	 return 0;
	
}


// c code to download/upload files from server or upload to server
//both operations are in one code


#include<unistd.h>
#include<stdio.h>
#include<curl/curl.h>
#include<string.h>
#include<sys/stat.h>
#include "updw.h"
#define MAX 50

FILE *fd;

int main()
{
	CURL *curl;
	char localpath[MAX], url[MAX];

	//getting the local path
	printf("Enter the file path from which you want to do transfer:\n\t");
	scanf("%s", localpath);

	printf("\nEnter URL:\n\t");
	scanf("%s", url);

	printf("\n");

	//initializing parameters
	curl_global_init(CURL_GLOBAL_ALL);
        curl = curl_easy_init();

	process(localpath, url, curl);
	
 
 
        /* cleanup curl stuff */
	printf("\n\n***********curl_easy_cleanup************\n\n");
        curl_easy_cleanup(curl);
 
	printf("\n**************curl_global_cleanup***************\n\n");
        curl_global_cleanup();
	

	return 0;

}

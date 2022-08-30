#include<curl/curl.h>
#include<stdlib.h>
#include "updw.h"
#define MAX 50


FILE *fd;

int process(char localpath[MAX], char url[MAX], CURL *curl)
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
            	{ 
             		rs = upload(localpath, curl, fd);
             		printf("\nreturn value of upload func: %d\n\n", rs);
             		if(rs != 0){ return 0; }
       	     	}
             	break;

             case 2:
             	rs = dwload(localpath, curl, fd);
             	break;

             default:
             	printf("Enter correct no\n");
	     	return 0;
        }
       

       //starting verbose mode to make connection more talkative
       curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
 
       //perform all the operations that are given     
       res = curl_easy_perform(curl);
       

       printf("\n\nthe res is:%d\n\n",res);
       if(res != CURLE_OK)
       {
               fprintf(stderr, "curl_easy_perform() failed: %s\n",
               curl_easy_strerror(res));
               return 0;
        }

       else{
               printf("file transfer successfully!!!\ncheck the given location\n");
	}


        fclose(fd);
	
	return 0;
}


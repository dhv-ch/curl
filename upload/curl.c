
//            curl program
//          C code to upload a file to a server



#include <stdio.h>
#include <curl/curl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<string.h>

/*
typedef enum {
  CURLFTP_CREATE_DIR_NONE,
  CURLFTP_CREATE_DIR,
  CURLFTP_CREATE_DIR_RETRY
} curl_ftpcreatedir;
*/

 
int main(void)
{
	CURL *curl;
 	CURLcode res;
  	struct stat file_info;
  	curl_off_t speed_upload, total_time;
  	FILE *fd;
	char path[50], url[80];

	printf("Enter the file path which you want to upload:\n\t");
	gets(path);

	printf("\nEnter URL:\n\t");
	gets(url);
	
 	printf("\n");

  	//fd = fopen("/home/dhvani/Desktop/base.cpp", "wb"); /* open file to upload */
	
	fd = fopen( path , "rb");


  	if(!fd)
	{
		printf("Can't open file..\n");
    		return 1; /* cannot continue */
 	}



 	 /* to get the file size */
  	if(fstat(fileno(fd), &file_info) != 0)
    		return 1; /* cannot continue */
 
  	curl = curl_easy_init();
  	if(curl) 
	{
		/* upload to this place */
    		//curl_easy_setopt(curl, CURLOPT_URL, "ftp://10.126.64.118//home/ftpuser/Desktop/base.cpp");


		curl_easy_setopt(curl, CURLOPT_URL, url);
		printf("\nGoing to entered url....................\n\n");

    		/*giving username and passwd*/
    		//curl_easy_setopt(curl, CURLOPT_USERPWD, "dhvani:dhv!!31");
		//printf("Giving username & psswsd for authentication\n\n");


   		/* option to create a new directory if this directory is not there*/
    		curl_easy_setopt(curl, CURLOPT_FTP_CREATE_MISSING_DIRS,  CURLFTP_CREATE_DIR_RETRY);
 
    		/* tell it to "upload" to the URL */
    		curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
		printf("Starting the upload\n\n");

		//    curl_easy_setopt(curl, CURLOPT_APPEND, 1L);
 
    		
		/* set where to read from (on Windows you need to use READFUNCTION too) */
    		curl_easy_setopt(curl, CURLOPT_READDATA, fd);
		printf("Writing data to buffer to send it on server\n\n");
 
    		/* and give the size of the upload (optional) */
    		curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t)file_info.st_size);
 		printf("\nThe file size is: %lu\n", file_info.st_size);

    		/* enable verbose for easier tracing */
   		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
 
   		res = curl_easy_perform(curl);
		printf("Performing the actions\n\n");


    		/* Check for errors */
    		if(res != CURLE_OK) 
		{
      			fprintf(stderr, "curl_easy_perform() failed: %s\n",
              		curl_easy_strerror(res));
    		}
    		
		
		else 
		{
      			/* now extract transfer info */
      			curl_easy_getinfo(curl, CURLINFO_SPEED_UPLOAD_T, &speed_upload);
      			curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &total_time);
 
      			fprintf(stderr, "Speed: %lu bytes/sec during %lu.%06lu seconds\n",
              		(unsigned long)speed_upload,
              		(unsigned long)(total_time / 1000000),
              		(unsigned long)(total_time % 1000000));
			printf("\nFile successfully traansferred!!!\n");
		}
    
   	     		 /* always cleanup */
    			curl_easy_cleanup(curl);
	}
  
	fclose(fd);
	


	return 0;
}

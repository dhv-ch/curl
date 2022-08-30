

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <curl/curl.h>

/*static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
	 size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
  	return written;
}*/



int main()
{
	CURL *curl_handle;
  	CURLcode res;
  	//static const char *pagefilename = "page.out";
  	FILE *pagefile;
	char path[50], url[80];

  
	printf("Enter the file path where you want to download the file:\n\t");
        gets(path);
  
        printf("\nEnter URL:\n\t");
        gets(url);
 
        printf("\n");


  	curl_global_init(CURL_GLOBAL_ALL);

  	/* init the curl session */
  	curl_handle = curl_easy_init();

  	/* set URL to get here */
  	curl_easy_setopt(curl_handle, CURLOPT_URL, url);

  //	curl_easy_setopt(curl_handle, CURLOPT_USERPWD, "dhvani:dhvc");

  	/* Switch on full protocol/debug output while testing */
  	curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);

  	/* send all data to this function  */
  	//curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);

  	/* open the file */
  	pagefile = fopen(path , "wb");
  	if(pagefile) {
		printf("fd created to download file!!!\n");}

    	/* write the page body to this file handle */
    	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, pagefile);

    	/* get it! */
    	res = curl_easy_perform(curl_handle);
	if(res != CURLE_OK)
        {
                fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
        }

	else
		printf("file downloaded successfully!!!\ncheck the given location\n");




    	/* close the header file */
    	fclose(pagefile);
  

  	/* cleanup curl stuff */
  	curl_easy_cleanup(curl_handle);

  	curl_global_cleanup();

  	return 0;
}

// program to download a file with writefunction option
// from scratch
// using buffer read/write

#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<curl/curl.h>
#include<fcntl.h>
#include<sys/stat.h>


struct MemoryStruct {
  char *memory;
  size_t size;
};




static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{

	printf("the contents of *userp is %p\n", userp);
	size_t realsize = size * nmemb;
  	struct MemoryStruct *mem = (struct MemoryStruct *)userp;

  	char *ptr = realloc(mem->memory, mem->size + realsize + 1);
  	if(!ptr) 
	{
    		/* out of memory! */
    		printf("not enough memory (realloc returned NULL)\n");
    		return 0;
	}

  	mem->memory = ptr;
  	memcpy(&(mem->memory[mem->size]), contents, realsize);
  	mem->size += realsize;
  	mem->memory[mem->size] = 0;

  	return realsize;
}




int main(void)
{
	CURL *curl_handle;
  	CURLcode res;

 	struct MemoryStruct chunk;

  	chunk.memory = malloc(1);  /* will be grown as needed by the realloc above */
  	chunk.size = 0;    /* no data at this point */

  	curl_global_init(CURL_GLOBAL_ALL);

  	/* init the curl session */
  	curl_handle = curl_easy_init();

  	/* specify URL to get */
  	curl_easy_setopt(curl_handle, CURLOPT_URL, "ftp://10.0.2.15//home/dhvani/Downloads/im1.jpeg");

  	curl_easy_setopt(curl_handle , CURLOPT_USERPWD, "dhvani:dhvc" );

  	/* send all data to this function  */
  	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

  	/* we pass our 'chunk' struct to the callback function */
  	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);

  	/* some servers do not like requests that are made without a user-agent
     	field, so we provide one */
  	//curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

  	/* get it! */
  	res = curl_easy_perform(curl_handle);

  	/* check for errors */
  	if(res != CURLE_OK) 
	{
    		fprintf(stderr, "curl_easy_perform() failed: %s\n",
        	curl_easy_strerror(res));
  	}
  	
	else 
	{

    		printf("%lu bytes retrieved\n", (unsigned long)chunk.size);

    		int fd;
    		fd = open ("/home/dhvani/Desktop/img1.jpeg", O_WRONLY | O_CREAT | O_TRUNC, 0664);
    		if (fd == -1 ){ perror("open"); }

    		ssize_t nr;
		/* write the string in 'buf' to 'fd' */
		nr = write (fd, chunk.memory, chunk.size);


  	}	

  	/* cleanup curl stuff */
  	curl_easy_cleanup(curl_handle);

  	free(chunk.memory);

  	/* we are done with libcurl, so clean it up */
  	curl_global_cleanup();

  	return 0;
}





#include <stdio.h>

#include <curl/curl.h>

/* define this to switch off the use of ssh-agent in this program */

#undef DISABLE_SSH_AGENT

/*
 * This is an example showing how to get a single file from an SFTP server.
 * It delays the actual destination file creation until the first write
 * callback so that it will not create an empty file in case the remote file
 * does not exist or something else fails.
 */

struct FtpFile {
	const char *filename;
  	FILE *stream;
};

static size_t my_fwrite(void *buffer, size_t size, size_t nmemb,
                        void *stream)
{
	struct FtpFile *out = (struct FtpFile *)stream;
  	if(!out->stream) 
	{
    		/* open file for writing */
    		out->stream = fopen(out->filename, "wb");
    		if(!out->stream){
      			return -1;} /* failure, cannot open file to write */
  	}
	
	return fwrite(buffer, size, nmemb, out->stream);
}




int main(void)
{
	CURL *curl;
  	CURLcode res;
  	struct FtpFile ftpfile = {"/home/dhvani/Desktop/test1.txt", /* name to store the file as if successful */
    				   NULL };

	curl_global_init(CURL_GLOBAL_DEFAULT);

	curl = curl_easy_init();
  	if(curl) {
    	/*
     	* You better replace the URL with one that works!
     	*/
    		curl_easy_setopt(curl, CURLOPT_URL, "sftp://dhvani@10.0.2.15//home/dhvani/c_code/f3.c");
    
		/* Define our callback to get called when there's data to be written */
    		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_fwrite);
    
		
		/* Set a pointer to our struct to pass to the callback */
    		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ftpfile);

#ifndef DISABLE_SSH_AGENT
    /* We activate ssh agent. For this to work you need
       to have ssh-agent running (type set | grep SSH_AGENT to check) or
       pageant on Windows (there is an icon in systray if so) */
	printf("hello welcome!!!\n");
    	curl_easy_setopt(curl, CURLOPT_SSH_AUTH_TYPES, CURLSSH_AUTH_PUBLICKEY);
    	printf("hello there!!!\n");
#endif

	/* Switch on full protocol/debug output */
   	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    	res = curl_easy_perform(curl);

    	/* always cleanup */
    	curl_easy_cleanup(curl);

    	if(CURLE_OK != res) 
	{
      		/* we failed */
      		fprintf(stderr, "curl told us %d\n", res);
    	}
  }

  	if(ftpfile.stream)
    		fclose(ftpfile.stream); /* close the local file */

  	curl_global_cleanup();

  	return 0;
}

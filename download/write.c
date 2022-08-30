

#include <stdio.h>
#include <curl/curl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<string.h>




int main(void)
{
        CURL *curl;
        CURLcode res;
        //struct stat file_info;
        curl_off_t speed_upload, total_time;
        FILE *fd;

        fd = fopen("/home/dhvani/Desktop/TOKEN.txt", "wb"); /* open file to upload */

        if(!fd)
        return 1; /* cannot continue */


        curl = curl_easy_init();
        if(curl)
        {
                /* upload to this place */
                curl_easy_setopt(curl, CURLOPT_URL, "ftp://10.126.64.118//home/dhvani/Desktop/token.txt");

		curl_easy_setopt(curl, CURLOPT_USERPWD, "dhvani:dhv!!31");

		 curl_easy_setopt(curl, CURLOPT_WRITEDATA, fd);


		 curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);


		 res = curl_easy_perform(curl);
                /* Check for errors */
                if(res != CURLE_OK)
                {
                        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                        curl_easy_strerror(res));
                }


		 curl_easy_cleanup(curl);
	}

	 fclose(fd);



        return 0;
}

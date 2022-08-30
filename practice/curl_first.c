//c code to start learning curl 

#include<stdio.h>
#include<curl/curl.h>

int main()
{
	CURL *curl_handle;

	curl_global_init(CURL_GLOBAL_ALL);

	curl_handle = curl_easy_init();

	curl_easy_cleanup(curl_handle);

	curl_global_cleanup();

	return 0;
}

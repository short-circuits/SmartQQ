/********************************************************************************
The MIT License

Copyright (c) 2016 田中くんはいつもけだるげ

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
********************************************************************************/


#include "network.h"

#include <curl/curl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "message.h"
#include "memstr.h"

size_t WriteFile(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

size_t WriteMemory(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    MemoryStruct *mem = (MemoryStruct *)userp;

    mem->ptr = realloc(mem->ptr, mem->len + realsize + 1);
    if(mem->ptr == NULL) {
        /* out of memory! */ 
        printf("\033[31m");
        print_time();
        printf("not enough memory (realloc returned NULL)\n");
        printf("\033[0m\n");
        return 0;
    }

    memcpy(&(mem->ptr[mem->len]), contents, realsize);
    mem->len += realsize;
    mem->ptr[mem->len] = 0;

    return realsize;
}

int curl_getfile(char* url, FILE * fp)
{
    CURL* curl;
    CURLcode res;

    long response_code=200;

    curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, url);

    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 1);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, _USERAGENT_);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteFile);

    /* we pass our 'chunk' struct to the callback function */ 
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)fp);

    res = curl_easy_perform(curl);

    curl_easy_cleanup(curl);
    if (res != CURLE_OK){
        printf("\033[31m");
        print_time();
        fprintf(stderr, "cURL error:%u", res);
        printf("\033[0m\n");
        return -1;
    }else{
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        if (response_code!=200)
        {
            printf("\033[31m");
            print_time();
            fprintf(stderr, "cURL get file return %ld", response_code);
            printf("\033[0m\n");
            return -1;
        }
    }
    return 0;
}

int curl_get(char* url, MemoryStruct * data)
{
    CURL* curl;
    CURLcode res;

    long response_code=200;

    curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, url);

    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 1);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, _USERAGENT_);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemory);

    /* we pass our 'chunk' struct to the callback function */ 
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)data);

    res = curl_easy_perform(curl);

    curl_easy_cleanup(curl);
    if (res != CURLE_OK){
        printf("\033[31m");
        print_time();
        fprintf(stderr, "cURL error:%u", res);
        printf("\033[0m\n");
        return -1;
    }else{
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        if (response_code!=200)
        {
            printf("\033[31m");
            print_time();
            fprintf(stderr, "cURL get page return %ld", response_code);
            printf("\033[0m\n");
            return -1;
        }
    }
    return 0;
}

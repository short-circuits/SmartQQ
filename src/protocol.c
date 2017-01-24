/********************************************************************************
The MIT License

Copyright (c) 2016 eaizy

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

#include "protocol.h"
#include <string.h>

int get_QR_login_status(QQClient * client)
{
    char *url=NULL;
    time_t time_now;
    MemoryStruct * data;
    char status_code[5];
    char * status_message;
    char * user_name;

    data=malloc(sizeof(MemoryStruct));
    data->ptr=NULL;
    data->len=0;

    time(&time_now);

    url = malloc((390)*sizeof(char));

    sprintf(url, QR_VALIDATION_URL, \
        client->appid, (time_now-client->start_time)*1000, client->mibao_css, client->js_ver, client->sign);

    curl_get_with_referer(url, data, INIT_URL);

    free(url);
    
    {
        int i,j,k,len;

        for (i = 0; data->ptr[i]!='\''; i++){
            ;
        }
        j=i+1;
        for (i++ ; data->ptr[i]!='\''; i++){
            ;
        }
        for (k=0; j<i; k++,j++){
            status_code[k]=data->ptr[j];
        }
        status_code[k]='\0';

        client->QR_status_code = atoi(status_code);

        for (i++ ; data->ptr[i]!='\''; i++){
            ;
        }
        for (i++ ; data->ptr[i]!='\''; i++){
            ;
        }


        for (i++ ; data->ptr[i]!='\''; i++){
            ;
        }
        j=i+1;
        for (i++ ; data->ptr[i]!='\''; i++){
            ;
        }
        len=i-j;
        client->redirect_url = malloc((len+1)*sizeof(char));
        for (k=0; j<i; k++,j++){
            client->redirect_url[k]=data->ptr[j];
        }
        client->redirect_url[k]='\0';

        for (i++ ; data->ptr[i]!='\''; i++){
            ;
        }
        for (i++ ; data->ptr[i]!='\''; i++){
            ;
        }


        for (i++ ; data->ptr[i]!='\''; i++){
            ;
        }
        j=i+1;
        for (i++ ; data->ptr[i]!='\''; i++){
            ;
        }
        len=i-j;
        client->status_message = malloc((len+1)*sizeof(char));
        for (k=0; j<i; k++,j++){
            client->status_message[k]=data->ptr[j];
        }
        client->status_message[k]='\0';

        for (i++ ; data->ptr[i]!='\''; i++){
            ;
        }
        j=i+1;
        for (i++ ; data->ptr[i]!='\''; i++){
            ;
        }
        len=i-j;
        client->user_name = malloc((len+1)*sizeof(char));
        for (k=0; j<i; k++,j++){
            client->user_name[k]=data->ptr[j];
        }
        client->user_name[k]='\0';
    }

    printf("\033[1A\033[K");
    print_time();
    printf("%s, status code %d\n", client->status_message,client->QR_status_code);
    fflush(stdout);

    mem_free(data);
    free(data);

    return 0;
}

int login_by_qrcode(QQClient * client)
{
    FILE * fp;
    MemoryStruct * data;
    char* cp;
    int i,j;
    char *url=NULL;

    data=malloc(sizeof(MemoryStruct));
    data->ptr=NULL;
    data->len=0;

    fp=fopen(QRCODE_FILE,"wb");

    if (fp==NULL){
        printf("\033[31m");
        print_time();
        fprintf(stderr, "login_by_qrcode() Cannot open file for QRcode. fopen returnd NULL");
        printf("\033[0m\n");
        return -1;
    }

    print_time();
    printf("Trying to login by qrcode.\n");

    curl_get(INIT_URL,data);

    cp=mem_match(data,"<input type=\"hidden\" name=\"aid\" value=\"");
    if (cp==NULL){
        printf("\033[31m");
        print_time();
        fprintf(stderr, "Cannot get appid. mem_match() returnd NULL");
        printf("\033[0m\n");
        return -1;
    }
    for(i=0;cp[i+39]!='\"';i++);
    client->appid = malloc((i+1)*sizeof(char));
    for(j=0;j<i;j++){
        client->appid[j]=cp[j+39];
    }
    client->appid[j]='\0';
    print_time();
    printf("Get appid: %s\n",client->appid);


    cp=mem_match(data,"g_pt_version=encodeURIComponent(\"");
    if (cp==NULL){
        printf("\033[31m");
        print_time();
        fprintf(stderr, "Cannot get js_ver. mem_match() returnd NULL");
        printf("\033[0m\n");
        return -1;
    }
    for(i=0;cp[i+33]!='\"';i++);
    client->js_ver = malloc((i+1)*sizeof(char));
    for(j=0;j<i;j++){
        client->js_ver[j]=cp[j+33];
    }
    client->js_ver[j]='\0';
    print_time();
    printf("Get js_ver: %s\n",client->js_ver);


    cp=mem_match(data,"g_mibao_css=encodeURIComponent(\"");
    if (cp==NULL){
        printf("\033[31m");
        print_time();
        fprintf(stderr, "Cannot get mibao_css. mem_match() returnd NULL");
        printf("\033[0m\n");
        return -1;
    }
    for(i=0;cp[i+32]!='\"';i++);
    client->mibao_css = malloc((i+1)*sizeof(char));
    for(j=0;j<i;j++){
        client->mibao_css[j]=cp[j+32];
    }
    client->mibao_css[j]='\0';
    print_time();
    printf("Get mibao_css: %s\n",client->mibao_css);


    cp=mem_match(data,"g_login_sig=encodeURIComponent(\"");
    if (cp==NULL){
        printf("\033[31m");
        print_time();
        fprintf(stderr, "Cannot get sign. mem_match() returnd NULL");
        printf("\033[0m\n");
        return -1;
    }
    for(i=0;cp[i+32]!='\"';i++);
    client->sign = malloc((i+1)*sizeof(char));
    for(j=0;j<i;j++){
        client->sign[j]=cp[j+32];
    }
    client->sign[j]='\0';
    print_time();
    printf("Get sign: %s\n",client->sign);


    mem_free(data);
    free(data);

    client->QR_status_code=65;
    
    for (;;){
        if (client->QR_status_code==65){
            url=malloc(73*sizeof(char));

            sprintf(url,QR_URL,client->appid);

            time(&client->start_time);

            print_time();
            printf("Downlanding QRcode\n");
            curl_getfile(url,fp);

            fclose(fp);
            free(url);

            print_time();
            printf("QRcode was save to %s, Please scan it on mobile phone\n\n",QRCODE_FILE);

        }
        sleep(1);
        if (client->QR_status_code==0){
            break;
        }
        get_QR_login_status(client);
    }

    print_time();
    printf("\033[1A\033[K%s, user_name [%s]\n", client->status_message,client->user_name);

    data=malloc(sizeof(MemoryStruct));
    data->ptr=NULL;
    data->len=0;

    curl_get(client->redirect_url,data);

    printf("%s\n", data->ptr);

    mem_free(data);
    free(data);

    return 0;
}

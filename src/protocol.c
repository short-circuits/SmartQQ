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

/*
*   又看代码
*   看你妹啊                      .. .vr
*                             qBMBBBMBMY
*                            8BBBBBOBMBMv
*                          iMBMM5vOY:BMBBv
*           .r,            OBM;   .: rBBBBBY
*           vUl            7BB   .;7. LBMMBBM.
*          .@Wwz           :uvir .i:.iLMOMOBM..
*          vv::r;             iY. ...rv,@arqiao.
*           Li. i:             v:.::::7vOBBMBL..
*           ,i7: vSUi,         :M7.:.,:uO8OP. .
*             .N2k5u1ju7,..     BMGiiL7   ,i,i.
*              :rLjFYjvjLY7r::.  ;v  vr...rE8q,.:,,
*             751jSLXPFu5uU@guohezou.,1vjY2E8@Yizero.
*             BB:FMu rkM8Eq0PFjF15FZOXu15F25uuLuu25Gi.
*           ivSvvXL    :v58ZOGZXF2UUkFSFkU1u125uUJUUZ.
*         :@kevensun       ,iY2OGOXSUXkSuS2F5XXkUX5SEv.
*     .:iOBMBMBBOOBMUi:,        ,:8PkFP5NkPXkFqPEqqkZu.
*   .rqMqBBMOMMBMBBBM .           @kexianli.S11kFSU5q5
* .7BBOi1L1MM8BBBOMBB..,          8kqS52XkkU1Uqkk1kUEJ
* .;MBZ:iiMBMBMMOBBBu ,           1OkS1F1X5kPP112F51kU
*   .rPY  OMBMBBBMBB2 ,.          rME5SSSFk1XPqFNkSUPZ,.
*          ;;JuBML::r:.:.,,        SZPXOSXSP5kXGNP15UBr.
*            L     :@sanshao.      :MNZqNXqSqXk2EOPSXPE.
*          vuLBX.,,v8Bj. i:r7:      2ZkqqOXXSNNONOXXSXOU
*        :r2. rMBGBMGi .7Y, 1i::i   vOOPMNNSXXEqP@Secbone.
*        .i1r. .jkY     vE. iY....  2OFqOq5X5F1S2F22uuv1M;
*/

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
/*
*        ?M                                                  
*        ?M .                 >H-N!       $NN                
*        OM                  $.  M;  . ?M   Q.               
*        HM .              O7   .7    Q!   ;M                
*        MN               H-    M   .M!    N;                
*        MN .            Q.    M.  ;N     7-                 
*        MH            ;QMH?!;.  .;-     CN                  
*        M$        ;HM!                    .?M;              
*        MC      $M                          .-HH            
*        MC     M-                              !M.          
*        MC    N      ?.      -                  :M.         
*        M7   :OMMMMMMM-      ;>CCOHNMMMMO        CQ         
*        M>   $>     $          O                 .M.        
*        M!   N-    ;Q          H                  M;        
*        M>  :$.                                  ;M         
*        M!  $!                                   N>         
*        M>  ?N        NNMMMM7                   N>          
*        M?   CM       ??                     -NM .          
*        MC     ?MM-   77                  ?MM-              
*        MM!M;     :QMMMC:  .       7NMMM$;                  
*        MN                 .  .;      N-                    
*        MM;              .C-  >!       QO                   
*        M$$QNMMMMMMMHQ$OC . M: .M?  Q-  ?M                  
*        M$            . M .ONM.   .NNH   N                  
*        MQ              M     $M .   .;  M                  
*        MH              M       >MH    -M!                  
*        MH              M          OMMN?                    
*        MN .          . M-            M.                    
*        MM              CH            NN                    
*        NM               M-           .M! 
*/

int get_self_info(QQClient *client)
{
    MemoryStruct * data;
    time_t time_now;
    char * url;

    data=malloc(sizeof(MemoryStruct));
    data->ptr=NULL;
    data->len=0;

    url = malloc(60*sizeof(char));

    time(&time_now);

    sprintf(url,"http://s.web2.qq.com/api/get_self_info2?t=%ld.55",time_now);

    curl_get(url,data);

    print_time();
    printf("%s.\n",data->ptr);

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
    printf("\033[1A\033[K%suser_name [%s]\n", client->status_message,client->user_name);

    data=malloc(sizeof(MemoryStruct));
    data->ptr=NULL;
    data->len=0;

    /* Get cookie */
    curl_get(client->redirect_url,data);

    mem_free(data);
    free(data);

    return 0;
}
/*                                                           
*.                                                           
*N!.Q; !::-                                                  
*?-Q?;!-::!                   ->?$QHO>-                      
*  N$>>-MM;-H-          CMMMMMMMMMMMMMMMMMM7                 
*    !>!M? -!;-;-?!  HMMMMMMMMMMMMMMMMMMMMMMMMM!             
*    -7C   -Q.   -.QMMMMMMMMMMMMMMMMMMMMMMMMMMMMMQ           
*               -CMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM.         
*                MMMMMMMMMQMMMMMMMMMMMMMMMMMMMMMMMMM         
*               >MMMMMMMMMMMMMMNMMMMMMMMMMMMMMMMMMMMH        
*               QMMMMMMNMMMMMMMCMMMMMMMMMMMMMMMMMMMMM        
*                MMM  !:HMMMMMCMMMMMMMMMMMMMMMMMMMMOOOO!.    
*                MMM - $N;7- - MMMMMMMMMMMMMMMMMMMMOOOOOOOOOO
*                MMM  MMMM;       M; -MMMMMMMMMMMMMMMM?C-OOOO
*                MMN   MM!        HMMMO MHMMMMMMMMMMMM       
*                MM$        :     >MMM7 .MMMMMMMMMMMMM.      
*                MMM                     MMMMMMMMMMMMM:      
*                MMM;                   7MMMMMMMMMMMMM?      
*               .MMMMN     >. .C        MMMMMMMMMMMMMMM      
*               .MMMMMMM.            >MMMMMMMMMMMMMMMMM      
*               .MMNHMMMMMMHO?$NMMMMMMMMMMMMMMMMMMMMMMM      
*               ?MMMMMMMMMM7!!7CHMMMMMMMMMMMMMMMMMMMMMM      
*               MMMMMMMMMMMQ        MMMMMMMMMMMMMMMMMMM.     
*               MMMMMMMMM$ !       :; .MMMMMMMMMMMMMMMM>     
*               M?MMMMMM   .     ?    MMMMMM   .. MMMMMC     
*             >   MMMMMM7-  C  C  !> -MMMMMN    .?!MMMMH     
*             !  .MMMMMM   .-  7     MMMMMM;  ;!> MMMMMM     
*              C .MMMMMM..77O.:-....?MMMMMM   :   >MMMMM
*/

int login_by_cookie(QQClient * client)
{
    FILE * fp;
    int ch;

    MemoryStruct * login_data;
    MemoryStruct * login_data2;
    MemoryStruct * cookie;
    cJSON *cjson_login = NULL;
    cJSON *cjson_login2 = NULL;
    cJSON *cjson_result = NULL;

    login_data=malloc(sizeof(MemoryStruct));
    login_data->ptr=NULL;
    login_data->len=0;

    login_data2=malloc(sizeof(MemoryStruct));
    login_data2->ptr=NULL;
    login_data2->len=0;

    cookie=malloc(sizeof(MemoryStruct));
    cookie->ptr=NULL;
    cookie->len=0;

    print_time();
    printf("Trying to load cookie file.\n");


    /* Read cookie file to memory */
    fp = fopen(COOKIE_FILE,"rb");

    if (fp==NULL){
        printf("\033[31m");
        print_time();
        fprintf(stderr, "Cannot open cookie file.");
        printf("\033[0m\n");
        return -1;
    }

    fseek(fp, 0, SEEK_END);
    cookie->len = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    cookie->ptr = malloc((cookie->len+1)*sizeof(char));

    for (int i = 0; (ch=fgetc(fp))!=EOF; i++){
        cookie->ptr[i]=ch;
    }
    cookie->ptr[cookie->len]='\0';

    fclose(fp);

    print_time();
    printf("Cookie file loaded.\n");

    {
        char * cp;
        int i,j;
        cp = mem_match(cookie,"ptwebqq");
        for(i=0;cp[i+8]!='\n';i++){
            ;
        }
        client->ptwebqq = malloc((i+2)*sizeof(char));
        if (client->ptwebqq==NULL){
            printf("\033[31m");
            print_time();
            fprintf(stderr, "Cannot set space for ptwebqq, malloc() return NULL.");
            printf("\033[0m\n");
            return -1;
        }
        for(j=0;j<i;j++){
            client->ptwebqq[j]=cp[j+8];
        }
        client->ptwebqq[j]='\0';
    }

    mem_free(cookie);
    free(cookie);

    print_time();
    printf("Trying to login by cookie.\n");

    {
        char * login_message;
        login_message = malloc((78+strlen(client->ptwebqq)+8)*sizeof(char));
        sprintf(login_message,"r={\"ptwebqq\":\"%s\",\"clientid\":%d,\"psessionid\":\"%s\",\"status\":\"online\"}",\
            client->ptwebqq, DEFAULT_CLIENT_ID, PSESSIONID);

        curl_post(LOGIN_URL,login_data,login_message,SMART_QQ_REFER);

        free(login_message);
    }

    cjson_login = cJSON_Parse(login_data->ptr);

    mem_free(login_data);
    free(login_data);

    if (cJSON_GetObjectItem(cjson_login, "retcode")->valueint != 0)
    {
        printf("\033[31m");
        print_time();
        fprintf(stderr, "Login by cookie failed.");
        printf("\033[0m\n");
        return -1;
    }

    print_time();
    printf("Login by cookie step 1 succeed.\n");

    cjson_result = cJSON_GetObjectItem(cjson_login, "result");

    client->uin = (long)cJSON_GetObjectItem(cjson_result, "uin")->valuedouble;

    client->psessionid = mem_dup(cJSON_GetObjectItem(cjson_result, "psessionid")->valuestring);
    client->vfwebqq = mem_dup(cJSON_GetObjectItem(cjson_result, "vfwebqq")->valuestring);

    print_time();
    printf("Login by cookie step 2.\n");

    {
        time_t time_now;
        char * url;
        url = malloc((strlen(client->ptwebqq)+\
            20+strlen(client->psessionid)\
            )*sizeof(char));
        time(&time_now);
        sprintf(url,LOGIN_URL2,client->ptwebqq,DEFAULT_CLIENT_ID,client->psessionid,time_now*1000);

        curl_get_with_referer(url,login_data2,SMART_QQ_REFER);    

        free(url);
    }

    cjson_login2 = cJSON_Parse(login_data2->ptr);

    mem_free(login_data2);
    free(login_data2);

    if (cJSON_GetObjectItem(cjson_login2, "retcode")->valueint != 0)
    {
        printf("\033[31m");
        print_time();
        fprintf(stderr, "Login by cookie failed.");
        printf("\033[0m\n");
        return -1;
    }

    print_time();
    printf("Login by cookie succeed. User ID: [\033[32m%ld\033[0m]\n",client->uin);

    sleep(4);

    get_self_info(client);

    return 0;
}
/*
*                                        777>777             
*                            >777777777777777777777777777::  
*                  -     >>7777777777777777777777777777777777
*                 ;77-- ;777777777777777777777777777777777777
*                 >> !!7>77>>777777777777777777777777777!  -7
*                 7!   >7>.     ;--:>>77777777777>;;;;-!7777!
*                 7: !!>;           -> ..;-:::::!!!!!>>>7??! 
*                 !>-          :>77!:7       ..7>       !>>  
*              --7>       .!!>>;   ;7-     :7!! >>       !!7.
*             ;>>>       !7>>:     :>     :7!   ;7-        7>
*            >>      >>7!.       ..7:  ..>>       >>>       >
*          :7;   !7!.            ::7  !77;      .  ;;>>.     
*        ..7! .>>7;      ->..    >>> -7::      ?C7:;;;>7:    
*       >77!7>C??    --CC?;      77->>           ;:77COC?>>7!
*      !777>-C7   ;?OCC-        ;77>>                   .::?:
*      >7>> 7O-   CC>..         -777-                        
*     >7:  7C-      .??CCC;      --;             -COOC7      
*    .!. ::O!       !CCCOCC                      CCOOOC;     
*        ??C.       -CCCCC>                      :CCCC>      
*       !CC:                                                 
*      .C??                                                  
*      :C!!                   .-          .C>                
*      CC                     C?    !C7    7C..             7
*     -C!                     >CC??OOCC77!CC:            ..77
*     !C-                      >CCC?;;?OOCC:             777>
*     ?C                                                .--  
*    .C7                                                     
*    ;C!                                                     
*    :O:                                                     
*    :O- 
*/

int check_message(QQClient * client)
{
    char * post_msg;
    MemoryStruct * msg_data;

    msg_data=malloc(sizeof(MemoryStruct));
    msg_data->ptr=NULL;
    msg_data->len=0;

    post_msg = malloc((70+strlen(client->ptwebqq)+strlen(client->psessionid))*sizeof(char));
    
    sprintf(post_msg,"r={\"psessionid\": \"%s\", \"key\": \"\", \"clientid\": %d, \"ptwebqq\": \"%s\"}",\
        client->psessionid, DEFAULT_CLIENT_ID,client->ptwebqq );
    
    curl_post(POLL_URL,msg_data,post_msg,SMART_QQ_REFER);
    
    print_time();
    printf("%s",msg_data->ptr);

    free(post_msg);
    mem_free(msg_data);
    free(msg_data);

    return 0;
}
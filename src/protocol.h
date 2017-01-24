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

#ifndef _PROTOCOL_
#define _PROTOCOL_

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "network.h"
#include "message.h"
#include "memstr.h"
#include "cJSON/cJSON.h"

#define QRCODE_FILE "./qrcode.bmp"

#define INIT_URL "https://ui.ptlogin2.qq.com/cgi-bin/login?daid=164&target=self&style=16&mibao_css=m_webqq&appid=501004106&enable_qlogin=0&no_verifyimg=1&s_url=http%3A%2F%2Fw.qq.com%2Fproxy.html&f_url=loginerroralert&strong_login=1&login_state=10&t=20131024001"
#define QR_URL "https://ssl.ptlogin2.qq.com/ptqrshow?appid=%s&e=0&l=L&s=8&d=72&v=4"
#define QR_VALIDATION_URL  "https://ssl.ptlogin2.qq.com/ptqrlogin?webqq_type=10&remember_uin=1&login2qq=1&aid=%s&u1=http%%3A%%2F%%2Fw.qq.com%%2Fproxy.html%%3Flogin2qq%%3D1%%26webqq_type%%3D10&ptredirect=0&ptlang=2052&daid=164&from_ui=1&pttype=1&dumy=&fp=loginerroralert&action=0-0-%ld&mibao_css=%s&t=undefined&g=1&js_type=0&js_ver=%s&login_sig=%s"
#define SMART_QQ_REFER "http://d1.web2.qq.com/proxy.html?v=20030916001&callback=1&id=2"
#define LOGIN_URL "http://d1.web2.qq.com/channel/login2"
#define LOGIN_URL2 "http://s.web2.qq.com/api/getvfwebqq?ptwebqq=%s&clientid=%d&psessionid=%s&t=%ld"

#define DEFAULT_CLIENT_ID 53999199
#define PSESSIONID ""


typedef struct
{
	char * appid;
	char * js_ver;
	char * mibao_css;
	char * sign;
	int QR_status_code;
	char * redirect_url;
	char * status_message;
	char * user_name;
	char * ptwebqq;
	char * psessionid;
	char * vfwebqq;
	long uin;
	time_t start_time;
} QQClient;

int login_by_qrcode(QQClient * client);
int login_by_cookie(QQClient * client);

#endif /* _PROTOCOL_ */

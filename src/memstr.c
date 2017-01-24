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

#include "memstr.h"

char * mem_dup(const char * string)
{	
	size_t len = strlen(string);
	char * ret;
	ret = malloc((len+1)*sizeof(char));
	memcpy(ret, string, len);
	ret[len] = '\0';
	return ret;
}

void mem_free(MemoryStruct * mem)
{
	free(mem->ptr);
	mem->ptr=NULL;
	mem->len=0;
}

char * mem_match(MemoryStruct * mem,char * mod)
{
	char *cp=mem->ptr;
	char *s1,*s2;
	if (!*mod){
		return mem->ptr;
	}
	while(*cp){
		s1=cp;
		s2=mod;
		while(*s1!='\0'&&*s2!='\0'&&(*s1-*s2)==0){
			s1++,s2++;
		}
		if (!*s2){
			return cp;
		}
		cp++;
	}
	return NULL;
}

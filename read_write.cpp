/*
	Name: read_write.cpp
	Copyright: GPLv3.0
	Author: xukl
	Date: 24/08/17 19:09
	Description: MY VERSION of FAST(?) I/O with integer
*/

#include <cstdio>

/**
 *	@breif	Fast read for signed integer.  
 *	@author	xukl
 *	@depend	buff[] with data to read.
 *	@note	To use this function, first use
 *			``fread(buff, 1, LEN, some_file_like_stdin);''
 *			to dump input data to buff[].  
 *			fread(void*, size_t, size_t, FILE*) is in <cstdio>.  
 *			When using stdin, don't forget to input EOF,
 *			or the program may look like dead.  
 *			If input is done in only one function,
 *			it is recommended to make ptr_buff a local variable
 *			to improve performance.  
*/
#define read_signed(a)\
{\
	while (*++ptr_buff >> 5 != 1);\
	bool flag = *ptr_buff == '-';\
	if (flag)\
		++ptr_buff;\
	(a) = 0;\
	do\
		(a) = (a) * 10 + *ptr_buff - '0';\
	while (*++ptr_buff >> 4 == 3);\
	if (flag)\
		(a) = -(a);\
}
#define read_unsigned(a)\
{\
	while (*++ptr_buff >> 4 != 3);\
	(a) = 0;\
	do\
		(a) = (a) * 10 + *ptr_buff - '0';\
	while (*++ptr_buff >> 4 == 3);\
}
#define LEN (1 << 25)
char buff[LEN];
const char *ptr_buff = buff - 1;

/**
 *	@breif	Fast(?) write for signed integer.  
 *	@author	xukl
 *	@depend	putchar(int) and puts(const char*) in <cstdio>
 *	@note	This function is distributed in the hope that it will be useful,
 *			but WITHOUT ANY WARRANTY.  IT MAY BE SLOW!!  
*/
inline void write_signed(int x)
{
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	static char buff[25];
	char * ptr = buff + 24;
	do
	{
		*--ptr = x % 10 + '0';
		x /= 10;
	}
	while (x != 0);
	puts(ptr);
}

//	Following shows a example.  
int main()
{
	fread(buff, 1, LEN, stdin);
	int n;
	read_signed(n);
	while (n--)
	{
		int a;
		read_signed(a);
		write_signed(a);
		unsigned b;
		read_unsigned(b);
		write_signed(b);
	}
	return 0;
}

#define _CRT_SECURE_NO_WARNINGS

#include "c_string.h"
#include <stdio.h>

int main(void)
{
	string str = createStringWithStr("test\nnew line");
	puts(getStringValue(str));

	puts("\n---\n");

	insertString("Hello!", &str, 3);
	puts(getStringValue(str));

	return 0;
};
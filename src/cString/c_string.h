#pragma once

#include <malloc.h>
#include <string.h>
#include <stdbool.h>

// string 类型
typedef struct s_string
{
	char* str;
}string;

string createString();
string createStringWithStr(char*);
void deleteString(string*);
bool appendString(char*, string*);
bool appendChar(char, string*);
bool insertString(char*, string*, size_t);
bool setStringBlock(char*, string*, size_t);
size_t getStringSize(string);
char* getStringValue(string);
bool haveNullChar(string);
bool addNullChar(string*, size_t);
bool resetStringSize(string*, size_t);
bool setStringSize(string*, size_t);
char* substring(string, size_t, size_t);
bool removeStringChar(string*, size_t);
bool removeStringBlock(string*, size_t, size_t);
bool removeStringEndChar(string*);
bool removeStringEndBlock(string*, size_t);

// 创建string
string createString()
{
	string result;
	setStringSize(&result, 1);
	return result;
}

// 使用char*初始化string
string createStringWithStr(char* str)
{
	string result;
	setStringSize(&result, 1);
	appendString(str, &result);
	return result;
}

// 删除string对象
void deleteString(string* str)
{
	if (str->str != NULL)
	{
		free(str->str);
		str->str = NULL;
	}
}

// 在string结尾添加data
bool appendString(char* data, string* str)
{
	if (!str || !data ||
		!resetStringSize(str, getStringSize(*str) + strlen(data) + 1) ||
		!strcat(str->str, data))
	{
		return false;
	}
	return true;
}

// 在string结尾添加ch
bool appendChar(char ch, string* str)
{
	char stri[2] = { ch, '\0' };
	if (!appendString(stri, str))
	{
		return false;
	}
	return true;
}

// 在string ix位置插入data
bool insertString(char* data, string* str, size_t ix)
{
	size_t stringLength = getStringSize(*str);
	size_t dataLength = strlen(data);
	if (ix > stringLength)
	{
		return false;
	}
	char* endString = substring(*str, ix, stringLength - ix);
	removeStringEndBlock(str, strlen(endString));
	if (!appendString(data, str) ||
		!appendString(endString, str))
	{
		return false;
	}

	return true;
}

// 删除位于str的ix上的数据
bool removeStringChar(string* str, size_t ix)
{
	if (!setStringBlock(substring(*str, ix + 1, getStringSize(*str) - ix - 1), str, ix))
	{
		return false;
	}

	return true;
}

// 删除位于str的ix开始的length个数据
bool removeStringBlock(string* str, size_t ix, size_t length)
{
	if (!setStringBlock(substring(*str, ix + length, getStringSize(*str) - ix - 1), str, ix))
	{
		return false;
	}

	return true;
}

// 删除str最后一个字符
bool removeStringEndChar(string* str)
{
	if (getStringSize(*str) < 1)
	{
		return false;
	}
	str->str[getStringSize(*str)] = '\0';
}

// 删除str最后length个字符
bool removeStringEndBlock(string* str, size_t length)
{
	if (!length ||
		getStringSize(*str) < 1)
	{
		return false;
	}
	str->str[getStringSize(*str) - length] = '\0';
	return true;
}

// 将ix到ix+strlen(data)之间的值更改为data，若大小不足则resetStringSize
bool setStringBlock(char* data, string* str, size_t ix)
{
	size_t dataLength = strlen(data);
	if (getStringSize(*str) < ix + dataLength &&
		!resetStringSize(str, ix + dataLength))
	{
		return false;
	}

	for (size_t i = ix; i < dataLength; ++i)
	{
		str->str[i] = data[i];
	}

	return true;
}

// 获取string的大小
size_t getStringSize(string str)
{
	return strlen(str.str);
}

// 获取string的值
char* getStringValue(string str)
{
	return str.str;
}

// 截取str从start的length个字符
char* substring(string str, size_t start, size_t length)
{
	if (start + length > getStringSize(str))
	{
		return NULL;
	}
	string result = createString();
	for (size_t i = 0; i < length; ++i)
	{
		if (!appendChar(str.str[start + i], &result))
		{
			return NULL;
		}
	}
	return result.str;
}

// string是否拥有\0符号
bool haveNullChar(string str)
{
	for (size_t i = 0; i < getStringSize(str); ++i)
	{
		if (str.str[i] == '\0')
		{
			return true;
		}
	}
	return false;
}

// 为string在ix位置添加\0
bool addNullChar(string* str, size_t ix)
{
	if (!resetStringSize(str, ix + 1))
	{
		return false;
	}
	str->str[ix] = '\0';
	return true;
}

// 重新设置string的大小
bool resetStringSize(string* str, size_t size)
{
	if (size <= 0 || !str)
	{
		return false;
	}
	size_t oldEnd = getStringSize(*str) + 1;
	char* newStr = realloc(str->str, sizeof(char) * size);
	if (!newStr)
	{
		return false;
	}
	str->str = newStr;
	str->str[oldEnd] = str->str[oldEnd + 1];
	str->str[size - 1] = '\0';
	return true;
}

//设置string的大小
bool setStringSize(string* str, size_t size)
{
	if (size <= 0 || !str)
	{
		return false;
	}
	char* newStr;
	newStr = (char*)malloc(sizeof(char) * size);
	if (!newStr)
	{
		return false;
	}
	str->str = newStr;
	str->str[size - 1] = '\0';
	return true;
}
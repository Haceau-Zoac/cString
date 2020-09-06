#pragma once

#include <malloc.h>
#include <string.h>
#include <stdbool.h>

// string ����
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

// ����string
string createString()
{
	string result;
	setStringSize(&result, 1);
	return result;
}

// ʹ��char*��ʼ��string
string createStringWithStr(char* str)
{
	string result;
	setStringSize(&result, 1);
	appendString(str, &result);
	return result;
}

// ɾ��string����
void deleteString(string* str)
{
	if (str->str != NULL)
	{
		free(str->str);
		str->str = NULL;
	}
}

// ��string��β���data
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

// ��string��β���ch
bool appendChar(char ch, string* str)
{
	char stri[2] = { ch, '\0' };
	if (!appendString(stri, str))
	{
		return false;
	}
	return true;
}

// ��string ixλ�ò���data
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

// ɾ��λ��str��ix�ϵ�����
bool removeStringChar(string* str, size_t ix)
{
	if (!setStringBlock(substring(*str, ix + 1, getStringSize(*str) - ix - 1), str, ix))
	{
		return false;
	}

	return true;
}

// ɾ��λ��str��ix��ʼ��length������
bool removeStringBlock(string* str, size_t ix, size_t length)
{
	if (!setStringBlock(substring(*str, ix + length, getStringSize(*str) - ix - 1), str, ix))
	{
		return false;
	}

	return true;
}

// ɾ��str���һ���ַ�
bool removeStringEndChar(string* str)
{
	if (getStringSize(*str) < 1)
	{
		return false;
	}
	str->str[getStringSize(*str)] = '\0';
}

// ɾ��str���length���ַ�
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

// ��ix��ix+strlen(data)֮���ֵ����Ϊdata������С������resetStringSize
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

// ��ȡstring�Ĵ�С
size_t getStringSize(string str)
{
	return strlen(str.str);
}

// ��ȡstring��ֵ
char* getStringValue(string str)
{
	return str.str;
}

// ��ȡstr��start��length���ַ�
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

// string�Ƿ�ӵ��\0����
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

// Ϊstring��ixλ�����\0
bool addNullChar(string* str, size_t ix)
{
	if (!resetStringSize(str, ix + 1))
	{
		return false;
	}
	str->str[ix] = '\0';
	return true;
}

// ��������string�Ĵ�С
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

//����string�Ĵ�С
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
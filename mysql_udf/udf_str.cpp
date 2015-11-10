#include <mysql.h>
#include <mysql_com.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

extern "C"
{
// str_reverse
my_bool str_reverse_init(UDF_INIT* initid, UDF_ARGS* args, char* message);
void str_reverse_deinit(UDF_INIT* initid);
char* str_reverse(UDF_INIT* initid, UDF_ARGS* args, char* result, unsigned long* length, char* is_null, char *error);

// LengthAll
my_bool mysum_init(UDF_INIT* initid, UDF_ARGS* args, char* message);
void mysum_deinit(UDF_INIT* initid);
void mysum_reset(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error);
void mysum_clear(UDF_INIT *initid, char *is_null, char *error);
void mysum_add(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error);
long long mysum(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);

}

char* StrData = 0;
int gSum = 0;

// str_reverse ==================================================
my_bool str_reverse_init(UDF_INIT* initid, UDF_ARGS* args, char* message)
{
	if (args->arg_count != 1)
	{    
		strcpy(message,"wrong number of arguments: str_reverse() requires one argument");    
		return 1;  
	}
    
	if (args->arg_type[0] != STRING_RESULT)  
	{    
		strcpy(message,"str_reverse() requires a string as parameter");    
		return 1;  
	}
    
	StrData = (char*)malloc(4096);
	memset(StrData, 0, 4096);
	
	initid->maybe_null = 1;  
	initid->max_length = 32; 
	initid->ptr = StrData;

	return 0;
}

void str_reverse_deinit(UDF_INIT* initid)
{  
	free(StrData);
}

char* str_reverse(UDF_INIT* initid, UDF_ARGS* args, char* result, unsigned long* length, char* is_null, char *error)
{
	if (args->arg_type[0] == STRING_RESULT)
	{   
		if (strlen(args->args[0]) > 256)
		{
			strncpy(StrData, args->args[0], 4096);
			StrData[4096-1] = 0;

			std::reverse(StrData, StrData + strlen(StrData));
			return StrData;
		}
		else
		{
			strncpy(result, args->args[0], 256);
			result[256-1] = 0;
			
			std::reverse(result, result + strlen(result));
			*length = (unsigned long)strlen(result);
			return result;
		}
	}

	return NULL;
}

// LengthAll ==================================================
my_bool mysum_init(UDF_INIT* initid, UDF_ARGS* args, char* message)
{
	if (args->arg_count != 1)  
	{    
		strcpy(message,"wrong number of arguments: mysum() requires one argument");    
		return 1;  
	}

	if (args->arg_type[0] != INT_RESULT)  
	{    
		strcpy(message,"wrong argument type of arguments: mysum() requires int");    
		return 1;  
	}

	gSum = 0;
	return 0;
}

void mysum_deinit(UDF_INIT* initid)
{	
}

void mysum_reset(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error)
{
	gSum = 0;
}

void mysum_clear(UDF_INIT *initid, char *is_null, char *error)
{
	gSum = 0;
}

void mysum_add(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error)
{
	gSum += *(int*)(args->args[0]);
}

long long mysum(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error)
{
	return gSum;
}

/* 
 * 用time()取得时间（秒数），利用localtime()
 * 转换成struct tm 再利用mktine（）将struct tm转换成原来的秒数
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char** argv)
{
	time_t timep;
	struct tm* p;
	time(&timep);
	printf("time() = %d\n", timep);
	p = localtime(&timep);
	timep = mktime(p);
	printf("time()->localtime()->mktime():%d\n", timep);
	return 0;
}

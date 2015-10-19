#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char** argv)
{
	time_t timep;
	time(&timep);
	printf("%s",ctime(&timep));
	return 0;
}

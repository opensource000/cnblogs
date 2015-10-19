#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char** argv)
{
	int seconds = time(NULL);
	printf("%d\n", seconds);
	return 0;
}

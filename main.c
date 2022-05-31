#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	int fd = open("/bin/main.c", O_RDONLY | O_CREAT);
	perror(NULL);
}
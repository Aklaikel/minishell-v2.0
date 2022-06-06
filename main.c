#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include "includes/minishell.h"

int main(int ac, char **av, char **env)
{
	int fd  = open("", O_RDONLY);
	perror(NULL);
}


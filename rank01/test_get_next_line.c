#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line/get_next_line.h"
#include <stdlib.h>

int main(void)
{
	int fd1;
	int	i;
	char	*line;

	i = 0;
	//fd1 = open("/home/bschwell/francinette/tests/get_next_line/fsoares/read_error.txt", O_RDONLY);
	//fptr2 = open("./test2.txt", O_RDONLY);
	//printf("fd1: %d\n", fd1);
	//printf("fptr2: %d\n", fptr2);
	
	//line = (char *) get_next_line(fd);
	//printf("line %d: %s\n", i++, get_next_line(fptr));
//	printf("[%d]: %s", i++, line);
//	free(line);
	//line = "init";
	
	fd1 = open("a.txt", O_RDONLY);	
	line = get_next_line(fd1);
	while(line != NULL)
	{
		printf("[%d:%d]%s", fd1, i++, line);
		free(line);
		line = NULL;
		line = get_next_line(fd1);
	}
	if (line != NULL)
		free(line);
	
	close(fd1);
	return (0);
}

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define BODY  "#include <stdio.h>\n\nint\t\tmain(int argc, char **argv)\n{\n\tint i = 0;\n\tprintf(\"Hello World\\n\");\n"

#define EBODY "\treturn(0);\n}\n"
#define BODY_SIZE 493

#define CONTENT1 "\ti++;\n\tprintf(\"content %d\\n\", "
#define CONTENT2 "\tif (i %% 2 == 0)\n\t\tprintf(\"osef\\n\");\n\telse\n\t\tprintf(\"osef aussi, mais different\\n\");\n"
#define CONTENT_SIZE 23

int			main(int argc, char **argv)
{
	int		iter = 1;
	FILE	*fd = fopen("creator.c", "w");
	fprintf(fd, BODY);

	if (argc == 2)
		iter = atoi(argv[1]);
	for (int i = 0; i < iter; i++)
	{
		fprintf(fd, "%s%d);", CONTENT1, i);
		fprintf(fd, CONTENT2);
	}
	fprintf(fd, EBODY);
	/*write(fd, BODY, sizeof(BODY) - 1);
	write(fd, CONTENT, 
	write(fd, EBODY, sizeof(EBODY) - 1);*/
	return (0);
}

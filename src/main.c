#include <stdio.h>
#include "netool.h"

CMD_OPT opt;

int main(int argc, char *argv[])
{
	parse_options(argc, argv, &opt);
	while(0)
		DoCmd(argc, argv);
	return 0;
}

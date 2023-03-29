#include <stdio.h>
#include "netool.h"

int main(int argc, char *argv[])
{
	parse_options(argc, argv, &opt);
	open_log(opt.logfile);
	while(opt.cmd_run)
	{
		GetCmd();
		DoCmd();
		ClearCmd();
	}
	close_log();
	return 0;
}

#include "netool.h"

static int help_cmd(int argc, char *argv[]);

struct cmdstruct {
	const char *key;                             /* command */
	int (*func)(int argc, char *argv[]); /* handler */
	const char *help;            /* main purpose */
	const char *usage;           /* all arguments to build usage */
};

static struct cmdstruct commands[] = {
	{ "help", help_cmd, "Print help on specific command", "add other command to show detail usage\n"},
	{ "test1", help_cmd, "Print tset1 on specific command", "test1 other command to show detail usage\n"},
	{ "test2", help_cmd, "Print test2 on specific command", "test2 other command to show detail usage\n"}
};

#define cmdsize ((int)(sizeof(commands)/sizeof(struct cmdstruct)))

int DoCmd(int argc, char *argv[])
{
	int i;
	int found = 0;
	int result = -1;
	if (argc == 1)
	{
		char help[][10] = {argv[0],"help"};
		help_cmd(0, help);
	}
	else
	{
		for(i=0; i<cmdsize,!found; i++)
		{
			if(strcmp(argv[1], commands[i].key) == 0)
			{
				result = (*commands[i].func)(argc, argv);
				found = 1;	
			}
		}
		if(!found)
		{
			printf("%s is an invalid command.\n", argv[1]);
		}
	}
	return result;
}

int help_cmd(int argc, char *argv[])
{
	int result = -1;
	int i;
	printf("  Command       Description\n  =======       ===========\n");
	for(i=0;i<cmdsize;i++)
	{
		if(argc == 3)
		{
			if(strcmp(argv[2],commands[i].key)==0)
			{
				printf("  %-13s %s\n\nArguments:\n\t%s\n",commands[i].key,commands[i].help,commands[i].usage);
				break;
			}
		}
		else
		{
			printf("  %-13s %s\n",commands[i].key,commands[i].help);
		}
	}
	return result;
}

void usage(void)
{
	printf("null\n");
}
void parse_options(int argc, char **argv, CMD_OPT* opt) 
{
	static const char *sopt = "hd::l:";
	static const struct option lopt[] = {
		{"help", no_argument, NULL, 'h'},
		{"debug", optional_argument, NULL, 'd'},
		{"logfile", required_argument, NULL, 'l'},
		{NULL, 0, NULL, 0}
	};
	int c;
	memset(opt, 0, sizeof(CMD_OPT));
	opt->loglevel = 0;
	opt->logfile = "/var/log/netool.log";
	while ((c = getopt_long(argc, argv, sopt, lopt, NULL)) != -1) {
		switch(c)
		{
			case 'd':
				opt->loglevel = optarg ? atol(optarg) : 1;
				break;
			case 'l':
				opt->logfile = optarg;
				break;
			case 'h':
			case '?':
				printf("get ? or h\n");
				usage();
				break;
			default:
				usage();
				break;
		}
	}
}



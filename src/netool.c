#include "netool.h"

FILE* msg = NULL;
static int help_cmd();

struct cmdstruct {
	const char *key;                             /* command */
	int (*func)(void); /* handler */
	const char *help;            /* main purpose */
	const char *usage;           /* all arguments to build usage */
};

static struct cmdstruct commands[] = {
	{ "help", help_cmd, "Print help on specific command", "add other command to show detail usage\n"},
	{ "test1", help_cmd, "Print tset1 on specific command", "test1 other command to show detail usage\n"},
	{ "test2", help_cmd, "Print test2 on specific command", "test2 other command to show detail usage\n"}
};

#define cmdsize ((int)(sizeof(commands)/sizeof(struct cmdstruct)))

void GetCmd(void)
{
	char buf[MAX_ARGLEN];
	const char s[2]=" ";
	char *tmp;
	opt.argc=0;
	log_mesg(LOG_ERROR,0,1,0,"\nEnter a command:\r\n*");	
	fgets(opt.cmd,sizeof(opt.cmd)-1,stdin);
	opt.cmd[strlen(opt.cmd)-1]='\0';
	log_mesg(LOG_DEBUG,0,1,0,"cmd:[%s]\n",opt.cmd);
	strcpy(buf,opt.cmd);
	tmp = strtok(buf, s);
	while(tmp != NULL)
	{
		strcpy(opt.argv[opt.argc],tmp);
		opt.argc++;
		tmp = strtok(NULL, s);
	}
	return;
}

int DoCmd()
{
	int i;
	int found = 0;
	int result = -1;
	if (opt.argc == 0)
	{
		return 0;
	}
	else
	{
		if(strcmp(opt.argv[0], "quit") == 0)
			opt.cmd_run=0;
		else
		{
			for(i=0; i<cmdsize && !found; i++)
			{
				if(strcmp(opt.argv[0], commands[i].key) == 0)
				{
					result = (*commands[i].func)();
					found = 1;
					break;
				}
			}
			if(!found)
			{
				log_mesg(LOG_ERROR,0,1,0,"%s is an invalid command.\n", opt.argv[0]);
			}
		}
	}
	return result;
}

int help_cmd()
{
	int i;
	int found=0;
	log_mesg(LOG_ERROR,0,1,0,"  Command       Description\n  =======       ===========\n");
	for(i=0;i<cmdsize;i++)
	{
		if(opt.argc == 2)
		{
			if(strcmp(opt.argv[1],commands[i].key)==0)
			{
				found=1;
				log_mesg(LOG_ERROR,0,1,0,"  %-13s %s\n\nArguments:\n\t%s\n",commands[i].key,commands[i].help,commands[i].usage);
				break;
			}
		}
		else
		{
			log_mesg(LOG_ERROR,0,1,0,"  %-13s %s\n",commands[i].key,commands[i].help);
		}
	}
	if(opt.argc == 2 && found == 0)
		log_mesg(LOG_ERROR,0,1,0,"\nCan't find %s command.\n",opt.argv[1]);
	return 0;
}

void usage(void)
{
	fprintf(stderr, "Usage: netool [OPTIONS]\n"
		"    test every thing I wanted in this code.\n"
		"    -h,  --help    Display this help\n"
		"    -dX, --debug=X    Set the debug level to X = [0|1|2|3]\n"
		"    -l, --logfile FILE    Log FILE\n");
	exit(0);
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
	opt->cmd_run = 1;
	opt->loglevel = 0;
	opt->logfile = "/var/log/netool.log";
	opt->argc = 0;
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
				usage();
				break;
			default:
				usage();
				break;
		}
	}
}

void open_log(char* source) {
	msg = fopen(source,"w");
	if (msg == NULL) {
		fprintf(stderr, "open logfile %s error\n", source);
		exit(0);
	}
}

void log_mesg(int log_level, int log_exit, int log_stderr, int log_debug, const char *fmt, ...) {

	va_list args;
	char tmp_str[1024];

	if (log_level > opt.loglevel && !log_exit)
		return;

	va_start(args, fmt);
	vsnprintf(tmp_str, sizeof(tmp_str), fmt, args);
	va_end(args);

	/// write log to stderr if log_stderr is true
	if ((log_stderr == 1) && (log_level <= opt.loglevel))
		fprintf(stderr, "%s", tmp_str);

	/// write log to logfile if debug is true
	if ((log_debug == 1) && log_level <= opt.loglevel)
		fprintf(msg, "%s", tmp_str);

	/// clear message
	fflush(msg);

	/// exit if log_exit true
	if (log_exit) {
		fprintf(stderr, "netool fail, please check %s !\n", opt.logfile);
		exit(1);
	}
}

void close_log(void) {
	fclose(msg);
}

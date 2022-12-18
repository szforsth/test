#ifndef NETOOL_H_
#define NETOOL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <stdarg.h>

#define MAX_ARGS 30
#define MAX_ARGLEN 1024
#define LOG_ERROR 0
#define LOG_WARN 1
#define LOG_INFO 2
#define LOG_DEBUG 3

typedef struct cmd_opt
{
	char* logfile;
	int loglevel;
	int cmd_run;
	char cmd[MAX_ARGLEN];
	int argc;
	char argv[MAX_ARGS][MAX_ARGLEN];
}CMD_OPT;
CMD_OPT opt;

void parse_options(int argc, char **argv, CMD_OPT* opt);

int DoCmd(void);
void GetCmd(void);

int parse_config();
void open_log(char* source);
void log_mesg(int log_level, int log_exit, int log_stderr, int log_debug, const char *fmt, ...);
void close_log();
#endif

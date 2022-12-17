#ifndef NETOOL_H_
#define NETOOL_H_

#include <stdio.h>
#include <string.h>
#include <getopt.h>

typedef enum log_level
{
	debug,info,warn,error
}LOG_LEVEL;

typedef struct cmd_opt
{
	char* logfile;
	LOG_LEVEL loglevel;
}CMD_OPT;


void parse_options(int argc, char **argv, CMD_OPT* opt);

int DoCmd(int argc, char *argv[]);

int parse_config();

#endif

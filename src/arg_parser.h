#ifndef ARG_PARSER_H
#define ARG_PARSER_H

/* INCLUDES */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>

/* DEFINES*/
#define REQUIRED_OPTION	true
#define OPTIONAL_OPTION	false

#define PARAM			0
#define FLAG			1
#define OPTION			2
#define INVALID			3

/* TYPEDEF */
typedef	char*		String;
typedef const char*	Cstring;

/* STRUCTS */
typedef struct
{
	Cstring	short_name;
	Cstring	long_name;
	Cstring	description;
	Cstring	value;
	bool	is_require;
	Cstring	(*check_value)(Cstring);
} ArgOption;

typedef struct
{
	Cstring	short_name;
	Cstring	long_name;
	Cstring	description;
	bool	is_set;
} ArgFlag;

typedef struct
{
	Cstring		program_name;
	ArgFlag**	flags;
	ArgOption**	options;
	String*		params;
	int			params_count;
	int			min_params_count;
	int			max_params_count;
} ArgParser;

/* FUNCTIONS */
ArgOption*	create_arg_option(Cstring short_name, Cstring long_name, Cstring description, Cstring default_value, bool is_require, Cstring (*check_value)(Cstring));
ArgOption*	create_arg_option_int(Cstring short_name, Cstring long_name, Cstring description, Cstring default_value,bool is_require);
ArgOption*	create_arg_option_double(Cstring short_name, Cstring long_name, Cstring description, Cstring default_value,bool is_require);
ArgOption*	create_arg_option_str(Cstring short_name, Cstring long_name, Cstring description, Cstring default_value,bool is_require);
ArgOption**	create_arg_options(int num, ...);

ArgFlag*	create_arg_flag(Cstring short_name, Cstring long_name, Cstring description);
ArgFlag**	create_arg_flags(int num, ...);

ArgParser*	create_arg_parser(Cstring program_name, ArgFlag** flags, ArgOption** options, int min_params_count, int max_params_count);

void		show_arg_help(ArgParser *arg_parser);
bool		parse_args(int argc, String* argv, ArgParser* arg_parser);

void*		free_arg_parser(ArgParser* arg_parser);

#endif

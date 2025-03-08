#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../src/arg_parser.h"

static Cstring	check_value(Cstring value)
{
	bool		result = false;

	if (strcmp(value, "KOLAY") == 0)
		result = true;
	if (strcmp(value, "ORTA") == 0)
		result = true;
	if (strcmp(value, "ZOR") == 0)
		result = true;
	//
	if (result)
		return ("");
	return ("['KOLAY', 'ORTA', 'ZOR']");
}

int main(int argc, char** argv)
{
	ArgParser*	arg_parser;
	bool		is_error;
	bool		is_help;
	// İstenen Parametreler
	int			genislik;
	int			yukseklik;
	double		hiz;
	const char*	test;
	const char*	zorluk;
	bool		mod;

	arg_parser = create_arg_parser(
		"test",
		create_arg_flags(
			2,
			create_arg_flag("?", "help", "yardim ekrani"),
			create_arg_flag("m", "mod", "modu degistirir")
		),
		create_arg_options(
			5,
			create_arg_option_int("g", "genislik", "oyun alaninin genisligini belirler", "10", OPTIONAL_OPTION),
			create_arg_option_int("y", "yukseklik", "oyun alaninin yuksekligini belirler", "12", OPTIONAL_OPTION),
			create_arg_option_double("h", "hiz", "oyunun hizini belirler", "5.5", OPTIONAL_OPTION),
			create_arg_option_str("t", "test", "test amaclidir", "test", OPTIONAL_OPTION),
			create_arg_option("z", "zorluk", "oyunun zorlugunu belirler (KOLAY, ORTA, ZOR)", "", REQUIRED_OPTION, check_value)
		),
		0,
		0
	);

	// Malloc Error
	if (arg_parser == NULL)
		return 0;

	// Hatalı Parametre Kontrolü
	is_error = !parse_args(argc, argv, arg_parser);
	is_help = arg_parser->flags[0]->is_set;

	// Parametre değerlerini değişkene atama
	genislik = (int)strtol(arg_parser->options[0]->value, NULL, 10);
	yukseklik = atoi(arg_parser->options[1]->value);
	hiz = atof(arg_parser->options[2]->value);
	test = arg_parser->options[3]->value;
	zorluk = arg_parser->options[4]->value;
	mod = arg_parser->flags[1]->is_set;

	// Parserı Freeleme	
	free_arg_parser(arg_parser);
	arg_parser = NULL;

	if (is_error)
		return (0);
	
	if (is_help)
		return (0);
	
	// Ekranda Gösterme
	printf("Genislik: %d\n", genislik);
	printf("Yukseklik: %d\n", yukseklik);
	printf("Hiz: %lf\n", hiz);
	printf("Test: %s\n", test);
	printf("Zorluk: %s\n", zorluk);
	printf("Mod: %d\n", mod);

	return (0);
}

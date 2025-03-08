#include "arg_parser.h"

// ALDIĞI PARAMETRELERDEN HERHANGİ BİRİSİ NULL İSE TRUE DÖNER.
// @param num: parametre sayısı 
// @param ...: void* türünde işaretçi 
// @return success: herhangi bir parametre NULL ise true.
// @return error: hiçbir parametre NULL değilse false.
static bool is_any_pointer_null(int num, ...)
{
	// Variables
	va_list args;
	bool result = false;
	// Argument Error
	if (num < 0)
		return (true);
	// Read (...) Args
	va_start(args, num);
	for (num = num; num > 0; num--)
		if (va_arg(args, void *) == NULL)
			result = true;
	va_end(args);
	// Return
	return (result);
}

// ARGOPTION TÜRÜNDE İŞARETÇİYİ FREELER
// @param arg_option: freelenecek ArgOption işaretçisi
// @return success: NULL
static void *free_arg_option(ArgOption *arg_option)
{
	// Argument Error
	if (arg_option == NULL)
		return (NULL);
	// Free
	free(arg_option);
	// Return
	return (NULL);
}

// ARGOPTIONS TÜRÜNDE İŞARETÇİYİ FREELER
// @param arg_options: freelenecek ArgOption* işaretçisi
// @return success: NULL
static void *free_arg_options(ArgOption **arg_options)
{
	int i;
	// Argument Error
	if (arg_options == NULL)
		return (NULL);
	// Free ArgOption
	for (i = 0; arg_options[i] != NULL; i++)
		free_arg_option(arg_options[i]);
	// Free
	free(arg_options);
	// Return
	return (NULL);
}

// ARGFLAG TÜRÜNDE İŞARETÇİYİ FREELER
// @param arg_flag: freelenecek ArgFlag işaretçisi
// @return success: NULL
static void *free_arg_flag(ArgFlag *arg_flag)
{
	// Argument Error
	if (arg_flag == NULL)
		return (NULL);
	// Free
	free(arg_flag);
	// Return
	return (NULL);
}

// ARGFLAGS TÜRÜNDE İŞARETÇİYİ FREELER
// @param arg_flags: freelenecek ArgFlag* işaretçisi
// @return success: NULL
static void *free_arg_flags(ArgFlag **arg_flags)
{
	int i;
	// Argument Error
	if (arg_flags == NULL)
		return (NULL);
	// Free ArgFlag
	for (i = 0; arg_flags[i] != NULL; i++)
		free_arg_flag(arg_flags[i]);
	// Free
	free(arg_flags);
	// Return
	return (NULL);
}

// STRING'IN SAYI OLUP OLMADIĞINI KONTROL EDER
// @param value: kontrol edilecek const metin
// @return success: eğer metin sayı ise "" döner.
// @return error: eğer metin sayı değil ise "integer" döner.
static Cstring check_int_value(Cstring value)
{
	// Variables
	char *endptr;
	// Argument Error
	if (value == NULL)
		return ("");
	// Casting Error
	strtol(value, &endptr, 10);
	if (*endptr != '\0')
		return ("integer");
	return ("");
}

// STRING'IN DOUBLE OLUP OLMADIĞINI KONTROL EDER
// @param value: kontrol edilecek const metin
// @return success: eğer metin double ise "" döner.
// @return error: eğer metin double değil ise "double" döner.
static Cstring check_double_value(Cstring value)
{
	// Variables
	char *endptr;
	// Argument Error
	if (value == NULL)
		return ("");
	// Casting Error
	strtod(value, &endptr);
	if (*endptr != '\0')
		return ("double");
	return ("");
}

// STRING'IN STRING OLUP OLMADIĞINI KONTROL EDER
// @param value: kontrol edilecek const metin
// @return success: her zaman "" döner.
static Cstring check_str_value(Cstring value)
{
	return ("");
}

// ARGOPTION TÜRÜNDE BİR DEĞİŞKEN OLUŞTURUR
// @param short_name: option'ın kısa ismi
// @param long_name: option'ın uzun ismi
// @param description: option'ın yardım menüsünde gösterilecek açıklama metni
// @param default_value: option'a değer verilmediğinde alacağı varsayılan değer 
// @param is_require: option'ın zorunlu olup olmadığı bilgisi
// @param check_value: option'ın alabileceği değerleri kontrol eden fonksiyon (doğru değer ise "" döner, yanlış değer ise hata metni döner)
// @return success: ArgOption* döner.
// @return error: hatalı parametre ve malloc error durumunda NULL döner.
ArgOption *create_arg_option(Cstring short_name, Cstring long_name, Cstring description, Cstring default_value, bool is_require, Cstring (*check_value)(Cstring))
{
	// Variables
	ArgOption *result;
	// Argument Error
	if (is_any_pointer_null(5, short_name, long_name, description, default_value, check_value))
		return (NULL);
	// Malloc Error
	result = (ArgOption *)malloc(sizeof(ArgOption));
	if (result == NULL)
		return (NULL);
	// Properties
	result->short_name = short_name;
	result->long_name = long_name;
	result->description = description;
	result->value = default_value;
	result->is_require = is_require;
	result->check_value = check_value;
	// Return
	return (result);
}

// YALNIZCA İNT DEĞERLER KABUL EDEN ARGOPTION TÜRÜNDE BİR DEĞİŞKEN OLUŞTURUR
// @param short_name: option'ın kısa ismi
// @param long_name: option'ın uzun ismi
// @param description: option'ın yardım menüsünde gösterilecek açıklama metni
// @param default_value: option'a değer verilmediğinde alacağı varsayılan değer 
// @param is_require: option'ın zorunlu olup olmadığı bilgisi
// @return success: ArgOption* döner.
// @return error: hatalı parametre ve malloc error durumunda NULL döner.
ArgOption *create_arg_option_int(Cstring short_name, Cstring long_name, Cstring description, Cstring default_value, bool is_require)
{
	return create_arg_option(short_name, long_name, description, default_value, is_require, check_int_value);
}

// YALNIZCA DOUBLE DEĞERLER KABUL EDEN ARGOPTION TÜRÜNDE BİR DEĞİŞKEN OLUŞTURUR
// @param short_name: option'ın kısa ismi
// @param long_name: option'ın uzun ismi
// @param description: option'ın yardım menüsünde gösterilecek açıklama metni
// @param default_value: option'a değer verilmediğinde alacağı varsayılan değer 
// @param is_require: option'ın zorunlu olup olmadığı bilgisi
// @return success: ArgOption* döner.
// @return error: hatalı parametre ve malloc error durumunda NULL döner.
ArgOption *create_arg_option_double(Cstring short_name, Cstring long_name, Cstring description, Cstring default_value, bool is_require)
{
	return create_arg_option(short_name, long_name, description, default_value, is_require, check_double_value);
}

// TÜM DEĞERLERİ KABUL EDEN ARGOPTION TÜRÜNDE BİR DEĞİŞKEN OLUŞTURUR
// @param short_name: option'ın kısa ismi
// @param long_name: option'ın uzun ismi
// @param description: option'ın yardım menüsünde gösterilecek açıklama metni
// @param default_value: option'a değer verilmediğinde alacağı varsayılan değer 
// @param is_require: option'ın zorunlu olup olmadığı bilgisi
// @return success: ArgOption* döner.
// @return error: hatalı parametre ve malloc error durumunda NULL döner.
ArgOption *create_arg_option_str(Cstring short_name, Cstring long_name, Cstring description, Cstring default_value, bool is_require)
{
	return create_arg_option(short_name, long_name, description, default_value, is_require, check_str_value);
}

// ARGOPTIONS DİZİSİ OLUŞTURUR
// @param num: parametre sayısı
// @param ...: ArgOption* türünde değişkenler
// @return success: ArgOption** döner.
// @return error: hatalı parametre ve malloc error durumunda NULL döner.
ArgOption **create_arg_options(int num, ...)
{
	// Variables
	ArgOption **result;
	va_list args;
	int i;
	// Argument Error
	if (num < 0)
		return (NULL);
	// Malloc Error
	result = (ArgOption **)malloc((num + 1) * sizeof(ArgOption *));
	if (result == NULL)
		return (NULL);
	// Read (...) Args
	result[num] = NULL;
	va_start(args, num);
	for (i = 0; i < num; i++)
	{
		result[i] = va_arg(args, ArgOption *);
		// (...) Args Error
		if (result[i] == NULL)
			return free_arg_options(result);
	}
	va_end(args);
	// Return
	return (result);
}

// ARGFLAG TÜRÜNDE BİR DEĞİŞKEN OLUŞTURUR
// @param short_name: flag'ın kısa ismi
// @param long_name: flag'ın uzun ismi
// @param description: flag'ın yardım menüsünde gösterilecek açıklama metni
// @return success: ArgFlag* döner.
// @return error: hatalı parametre ve malloc error durumunda NULL döner.
ArgFlag *create_arg_flag(Cstring short_name, Cstring long_name, Cstring description)
{
	// Variables
	ArgFlag *result;
	// Argument Error
	if (is_any_pointer_null(3, short_name, long_name, description))
		return (NULL);
	// Malloc Error
	result = (ArgFlag *)malloc(sizeof(ArgFlag));
	if (result == NULL)
		return (NULL);
	// Properties
	result->short_name = short_name;
	result->long_name = long_name;
	result->description = description;
	result->is_set = false;
	// Return
	return (result);
}

// ARGFLAG DİZİSİ OLUŞTURUR
// ** İLK FLAG HER ZAMAN YARDIM BAYRAĞIDIR **
// @param num: parametre sayısı
// @param ...: ArgFlag* türünde değişkenler
// @return success: ArgFlag** döner.
// @return error: hatalı parametre ve malloc error durumunda NULL döner.
ArgFlag **create_arg_flags(int num, ...)
{
	// Variables
	ArgFlag **result;
	va_list args;
	int i;
	// Argument Error
	if (num < 0)
		return (NULL);
	// Malloc Error
	result = (ArgFlag **)malloc((num + 1) * sizeof(ArgFlag *));
	if (result == NULL)
		return (NULL);
	// Read (...) Args
	result[num] = NULL;
	va_start(args, num);
	for (i = 0; i < num; i++)
	{
		result[i] = va_arg(args, ArgFlag *);
		// (...) Args Error
		if (result[i] == NULL)
			return free_arg_flags(result);
	}
	va_end(args);
	// Return
	return (result);
}

// ARG PARSER OLUŞTURUR
// @param program_name: help menüsünde gösterilecek program ismi
// @param flags: ArgFlag** türünde değişken
// @param options: ArgOptions** türünde değişken
// @param min_params_count: programın isteği en az parametre sayısı (option ve flag haricinde)
// @param max_params_count: programın isteği en fazla parametre sayısı (option ve flag haricinde)
// @return success: ArgParser* döner.
// @return error: hatalı parametre ve malloc error durumunda NULL döner.
ArgParser *create_arg_parser(Cstring program_name, ArgFlag **flags, ArgOption **options, int min_params_count, int max_params_count)
{
	// Variables
	ArgParser *result;
	// Argument Error
	if (is_any_pointer_null(3, program_name, flags, options) || min_params_count < 0 || max_params_count < min_params_count)
		return (NULL);
	// Malloc Error
	result = (ArgParser *)malloc(sizeof(ArgParser));
	if (result == NULL)
		return (NULL);
	// Properties
	result->program_name = program_name;
	result->flags = flags;
	result->options = options;
	result->params_count = 0;
	result->min_params_count = min_params_count;
	result->max_params_count = max_params_count;
	// Malloc Error
	result->params = (String *)malloc((max_params_count + 1) * sizeof(String));
	if (result->params == NULL)
		return free_arg_parser(result);
	// Return
	return (result);
}

// ARG PARSER'I FREELER
// @param arg_parser: freelenecek arg_parser
// @return success: her zaman NULL döner.
void *free_arg_parser(ArgParser *arg_parser)
{
	// Variables
	int i;
	// Argument Error
	if (arg_parser == NULL)
		return (NULL);
	// Free Flags
	free_arg_flags(arg_parser->flags);
	// Free Options
	free_arg_options(arg_parser->options);
	// Free Params
	if (arg_parser->params != NULL)
		free(arg_parser->params);
	// Free
	free(arg_parser);
	//
	arg_parser->flags = NULL;
	arg_parser->options = NULL;
	arg_parser->params = NULL;
	return (NULL);
}

// ARG PARSER'IN YARDIM MENÜSÜNÜ GÖSTERİR
// @param arg_parser: yardım menüsü gösterilecek arg_parser
// @return void
void show_arg_help(ArgParser *arg_parser)
{
	// Variables
	int i;
	// Argument Error
	if (arg_parser == NULL)
		return;
	// Show Program Name
	printf("Usage: %s [options...]", arg_parser->program_name);
	// Show Require Param Count
	for (i = 0; i < arg_parser->min_params_count; i++)
		printf(" <param%d>", i);
	// Show Optional Param Count
	for (i = 0; i < arg_parser->max_params_count - arg_parser->min_params_count; i++)
		printf(" <optional_param%d>", i);
	// Show Flags Names and Description
	for (i = 0; arg_parser->flags[i] != NULL; i++)
		printf("\n-%s, --%s\t\t\t\t\t%s", arg_parser->flags[i]->short_name, arg_parser->flags[i]->long_name, arg_parser->flags[i]->description);
	// Show Options Names and Description
	for (i = 0; arg_parser->options[i] != NULL; i++)
		printf("\n-%s, --%s <value>\t\t%c\t\t%s", arg_parser->options[i]->short_name, arg_parser->options[i]->long_name, arg_parser->options[i]->is_require * '*', arg_parser->options[i]->description);
	printf("\n");
}

// ARG PARSER'IN HATA KONTROLÜNÜ YAPAR
// 1. Parametre Sayısı Kontrolü
// 2. Zorunlu Parametre Eksikliği Kontrolü
// 3. Hatalı Tip / Tür Kontrolü
// @param arg_parser: hata kontrolü yapılacak olan arg_parser
// @return hata varsa false döner, hatasızsa true döner
static bool check_error(ArgParser *arg_parser)
{
	// Variables
	const char *error_message;
	bool result = false;
	int i;
	// Params Count Error
	if (arg_parser->min_params_count == arg_parser->max_params_count && arg_parser->params_count != arg_parser->min_params_count)
		printf("Param Error: You must provide %d arguments. You provided %d arguments.\n", arg_parser->min_params_count, arg_parser->params_count);
	else if (arg_parser->params_count < arg_parser->min_params_count)
		printf("Param Error: You must provide at least %d arguments. You provided %d arguments.\n", arg_parser->min_params_count, arg_parser->params_count);
	else if (arg_parser->params_count > arg_parser->max_params_count)
		printf("Param Error: You can provide no more than %d arguments. You provided %d arguments.\n", arg_parser->max_params_count, arg_parser->params_count);
	else
		result = true;

	for (i = 0; arg_parser->options[i] != NULL; i++)
	{
		// Require Option Error
		if (strcmp(arg_parser->options[i]->value, "") == 0 && arg_parser->options[i]->is_require)
		{
			result = false;
			printf("option --%s: is require.\n", arg_parser->options[i]->long_name);
		}
		// Option Type Error
		error_message = arg_parser->options[i]->check_value(arg_parser->options[i]->value);
		if (strcmp(arg_parser->options[i]->value, "") != 0 && strcmp(error_message, "") != 0)
		{
			result = false;
			printf("Type Error: option --%s expects an %s. You provided '%s'.\n", arg_parser->options[i]->long_name, error_message, arg_parser->options[i]->value);
		}
	}
	return (result);
}

// METNİN PARAMETRE OLUP OLMADIĞINI KONTROL EDER.
// @param arg: metin
// @return parametre ise true, değilse false döner.
static bool is_param(String arg)
{
	// Argument Error
	if (arg == NULL)
		return (false);
	// is long name
	if (arg[0] == '-' && arg[1] == '-')
		return (false);
	// is short name
	if (arg[0] == '-' && arg[1] != '\0' && arg[2] == '\0')
		return (false);
	return (true);
}

// METNİN FLAG OLUP OLMADIĞINI KONTROL EDER.
// @param index: argv[index] metninin kontrolü yapılır
// @param argv: argv[index] metninin kontrolü yapılır
// @param arg_parser: metnin buradaki bir flag olup olmadığı kontrol edilir.
// @return flag ise true, değilse false döner.
static bool is_flag(int index, String *argv, ArgParser *arg_parser)
{
	// Variables
	int i;
	int offset;
	// Argument Error
	if (argv == NULL || arg_parser == NULL)
		return (false);
	// Set Offset
	offset = 1;
	if (argv[index][0] == '-' && argv[index][1] == '-')
		offset = 2;
	// Check
	for (i = 0; arg_parser->flags[i] != NULL; i++)
	{
		if ((offset == 2 && strcmp(argv[index] + offset, arg_parser->flags[i]->long_name) == 0) ||
			(offset == 1 && strcmp(argv[index] + offset, arg_parser->flags[i]->short_name) == 0))
		{
			arg_parser->flags[i]->is_set = true;
			return (true);
		}
	}
	// Return
	return (false);
}

// METNİN OPTION OLUP OLMADIĞINI KONTROL EDER.
// @param index: argv[index] metninin kontrolü yapılır
// @param argv: argv[index] metninin kontrolü yapılır
// @param arg_parser: metnin buradaki bir option olup olmadığı kontrol edilir.
// @return option ise true, değilse false döner.
static bool is_option(int argc, int index, String *argv, ArgParser *arg_parser)
{
	// Variables
	int i;
	int offset;
	// Argument Error
	if (argv == NULL || arg_parser == NULL)
		return (false);
	// Set Offset
	offset = 1;
	if (argv[index][0] == '-' && argv[index][1] == '-')
		offset = 2;
	// Check
	for (i = 0; arg_parser->options[i] != NULL; i++)
	{
		if ((offset == 2 && strcmp(argv[index] + offset, arg_parser->options[i]->long_name) == 0) ||
			(offset == 1 && strcmp(argv[index] + offset, arg_parser->options[i]->short_name) == 0))
		{
			if (index + 1 < argc)
				arg_parser->options[i]->value = argv[index + 1];
			else
				printf("Warning: option --%s provided without a value. The command may not be complete.\n", arg_parser->options[i]->long_name);
			return (true);
		}
	}
	// Return
	return (false);
}

static int parse_arg(int argc, int index, String *argv, ArgParser *arg_parser)
{
	// Argument Error
	if (argv == NULL || arg_parser == NULL)
		return (INVALID);
	// Check Type
	if (is_param(argv[index]))
	{
		if (arg_parser->params_count < arg_parser->max_params_count)
			arg_parser->params[arg_parser->params_count] = argv[index];
		arg_parser->params_count++;
		return (PARAM);
	}
	else if (is_flag(index, argv, arg_parser))
		return (FLAG);
	else if (is_option(argc, index, argv, arg_parser))
		return (OPTION);
	// Return
	return (INVALID);
}

// PARSE İŞLEMİNİ YAPAR
// @param argc: argv'nin uzunluğu
// @param argv: parse işlemi yapılacak metin dizisi
// @param arg_parser: parse işlemi yapılırken kullanılacak kurallar, optionlar ve flag'ler
// @return success: parse başarılı ise true döner.
// @return error: parse başarısız ise false döner.
bool parse_args(int argc, String *argv, ArgParser *arg_parser)
{
	// Variables
	bool result = true;
	int i;
	// Argument Error
	if (argv == NULL || arg_parser == NULL || argc < 0)
		return (false);
	// Parse Arg
	for (i = 1; i < argc; i++)
	{
		switch (parse_arg(argc, i, argv, arg_parser))
		{
		case INVALID:
			result = false;
			printf("option %s: is unknown\n", argv[i]);
		case OPTION:
			i++;
			break;
		}
	}
	// 
	if (arg_parser->flags[0] != NULL && arg_parser->flags[0]->is_set)
		show_arg_help(arg_parser);
	else
		result = result && check_error(arg_parser);

	return (result);
}

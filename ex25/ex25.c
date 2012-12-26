#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "../ex20/dbg.h"

#define MAX_DATA 100

int read_string(char **out_string, int max_buffer)
{
	*out_string = calloc(1, max_buffer + 1);
	check_mem(*out_string);

	char *result = fgets(*out_string, max_buffer, stdin);
	check(result != NULL, "Input error.");

	return 0;
error:
	if (*out_string)
		free(*out_string);
	*out_string = NULL;
	return -1;
}

int read_int(int *out_int)
{
	char *input = NULL;
	int rc = read_string(&input, MAX_DATA);
	check(rc == 0, "Failed to read number");

	*out_int = atoi(input);

	free(input);
	return 0;
error:
	if (input)
		free(input);
	return -1;
}

int read_scan(const char *fmt, ...)
{
	int i = 0;
	int rc = 0;
	int *out_int = NULL;
	char *out_char = NULL;
	char **out_string = NULL;
	int max_buffer = 0;

	va_list argp;
	va_start(argp, fmt);

	for (i = 0; fmt[i] != '\0'; i++) {
		if (fmt[i] == '%') {
			i++;
			switch(fmt[i]) {
				case '\0':
					sentinel("Invalid format");
					break;
				case 'd':
					out_int = va_arg(argp, int *);
					rc = read_int(out_int);
					check(rc == 0, "Failed to read int.");
					break;
				case 'c':
					out_char = va_arg(argp, char *);
					*out_char = fgetc(stdin);
					break;
				case 's':
					max_buffer = va_arg(argp, int);
					out_string = va_arg(argp, char **);
					rc = read_string(
						out_string, max_buffer
					);
					check(rc == 0, 
						"Failed to read string."
					);
					break;
				default:
					sentinel("Invalid format.");
			}
		} else {
			fgetc(stdin);
		}
		
		check(!feof(stdin) && !ferror(stdin), "Input error.");
	}

	va_end(argp);
	return 0;
error:
	va_end(argp);
	return -1;
}

int write_string(char *out_string, int length)
{
	int i;

	for (i = 0; i < length; i++)
		putchar(out_string[i]);

	return 0;
}


/* reverse(char *) - reverse order of string */
int reverse(char s[])
{
	int i, j;

	for (i = 0, j = strlen(s)-1; i < j; i++, j--)
		s[i] ^= s[j], s[j] ^= s[i], s[i] ^= s[j];

	return 0;
}

/* itoa - integer to string */
char *itoa(int n)
{
	int i, sign;
	char *s = calloc(1, 33); // TODO: make log work
	check_mem(s); 

	if ((sign = n) < 0)
		n = -n;
	
	i = 0;
	do {
		s[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);

	if (sign < 0)
		s[i++] = '-';
	
	s[i] = '\0';

	reverse(s);

	return s;
error:
	if (s)
		free(s);
	return NULL;
}

int write_int(int i)
{
	char *s = itoa(i);
	check(s != NULL, "Could not read integer.");

	write_string(s, strlen(s));

	free(s);
	return 0;
error:
	if (s)
		free(s);
	return -1;
}

int write_print(const char *fmt, ...)
{
	int i = 0;
	int rc = 0;
	int out_int;
	char out_char;
	char *out_string;
	
	va_list argp;
	va_start(argp, fmt);

	for (i = 0; fmt[i] != '\0'; i++) {
		if (fmt[i] == '%') {
			i++;
			switch (fmt[i]) {
				case '\0':
					sentinel("Invalid format.");
					break;
				case 'd':
					out_int = va_arg(argp, int);
					rc = write_int(out_int);
					check(rc == 0, 
						"Failed to write integer"
					);
					break;
				case 'c':
					out_char = (char)va_arg(argp, int);
					rc = putchar(out_char);
					check(rc != EOF,
						"Failed to write char"
					);
					break;
				case 's':
					out_string = va_arg(argp, char *);
					rc = write_string(
						out_string, 
						strlen(out_string)
					);
					check(rc == 0,
						"Failed to write string"
					);
					break;
				default:
					sentinel("Invalid format.");
			}
		} else {
			putchar(fmt[i]);
		}

		check(!feof(stdin) && !ferror(stdin), "Input error.");
	}

	va_end(argp);
	return 0;
error:
	va_end(argp);
	return -1;
}

int main(int argc, char *argv[])
{
	char *first_name = NULL;
	char initial = ' ';
	char *last_name = NULL;
	int age = 0;

	write_print("What's your first name? ");
	int rc = read_scan("%s", MAX_DATA, &first_name);
	check(rc == 0, "Failed to read first name.");

	write_print("What's your initial? ");
	rc = read_scan("%c\n", &initial);
	check(rc == 0, "Failed to read initial.");

	write_print("What's your last name? ");
	rc = read_scan("%s", MAX_DATA, &last_name);
	check(rc == 0, "Failed last name.");

	write_print("How old are you? ");
	rc = read_scan("%d", &age);

	write_print("---- RESULTS ----\n");
	write_print("First Name: %s", first_name);
	write_print("Initial: %c\n", initial);
	write_print("Last Name: %s", last_name);
	write_print("Age: %d\n", age);

	free(first_name);
	free(last_name);
	return 0;
error:
	return -1;
}

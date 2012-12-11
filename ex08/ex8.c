#include <stdio.h>

int main (int argc, char * argv[]) 
{
	int areas[] = { 10, 12, 13, 14, 20 };
	char name[] = "Noud";
	char full_name[] = {
		'N', 'o', 'u', 'd', ' ',
		'A', 'l', 'd', 'e', 'n', 'h', 'o', 'v', 'e', 'n', '\0'
	};

	printf("The size of an int: %u", sizeof(int));
	printf("The size of areas (int[]): %u\n", sizeof(areas));
	printf("The numer of intes in areas: %u\n",
		sizeof(areas) / sizeof(int));
	printf("The fires area is %d, the second area %d\n",
		areas[0], areas[1]);
	
	printf("The size of a char: %u\n", sizeof(char));
	printf("The size of name (char[]): %u\n", sizeof(name));
	printf("The numer of chars: %u\n", sizeof(name) / sizeof(char));
	
	printf("The size of full_name (char[]): %u\n", sizeof(full_name));
	printf("The number of chars: %u\n", sizeof(full_name) / sizeof(char));
	
	printf("name=\"%s\" and full_name=\"%s\"\n", name, full_name);

	return 0;
}

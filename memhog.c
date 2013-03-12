#include <sys/mman.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, const char* argv[]) {
	char* lastchar;
	long kb_to_hog;
	void* mem;
	if (argc != 2) {
		printf("Failed: Missing argument, make sure to pass a base 10 or 16 integer (ex: 255 or 0xFF)\n");
		return 1;
	}
	if (strstr(argv[1], "0x") == argv[1]) {
		/* base 16 */
		kb_to_hog = strtol(argv[1], &lastchar, 16);
	} else {
		/* must be base 10 */
		kb_to_hog = strtol(argv[1], &lastchar, 10);
	}
	if (*lastchar != '\0') {
		printf("Failed: Invalid argument %s, make sure to pass a base 10 or 16 integer (ex: 255 or 0xFF)\n", argv[1]);
		return 1;
	}
	printf("Attempting to hog %li kbytes of RAM.\n", kb_to_hog);
 	mem = malloc(kb_to_hog*1024);
	if (!mem) {
		printf("Failied! Couldn't malloc.\n");
		return 1;
	}
	if (mlock(mem, kb_to_hog)) {
		printf("Failed! Couldn't mlock.\n");
		return 1;
	}
	printf("Success! Press any key to kill me and get back the RAM.\n");
	getchar();
	return 0;
}

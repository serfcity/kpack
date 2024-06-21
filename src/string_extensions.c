#include "string_extensions.h"

#include <string.h>
#include <memory.h>
#include <stdlib.h>

char *
kpack_clonestr(const char *s)
{
	char *new_s;
	new_s = malloc(strlen(s) + 1);
	if (!new_s)
		return NULL;
	else
		return strcpy(new_s, s);
}

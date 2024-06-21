#ifndef KPACK_STRING_EXTENSIONS
#define KPACK_STRING_EXTENSIONS

/* This function clone string using malloc() */
/* so free() needed. It returns NULL if malloc() error */
char *kpack_clonestr(const char *);

#endif /* KPACK_STRING_EXTENSIONS */

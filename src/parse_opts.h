#ifndef KPACK_PARSE_OPTS_H
#define KPACK_PARSE_OPTS_H

#include "bool.h"

/* Mode of kpack */
enum kpack_mode {
	kpack_encoding,
	kpack_decoding
};

/* Command-line parameters */
struct kpack_program_opts {
	/* Input and output filenames, if exists */
	const char *input_file;
	const char *output_file;
	
	kpack_mode mode;

	/* true = file mode, false = POSIX streaming mode */
	bool is_input_file_mode;
	bool is_output_file_mode;
};

/* Do: */
/*   Mantain command-line data to struct kpack_program_opts */
/* Arguments: */
/*   1. Pointer to a struct */
/*   2. Number of command-line arguments (int argc) */
/*   3. Pointer to array of command-line words (char argv**) */
/* Errors: */
/*   0 = No error */
/*   1 = Invalid arguments */
int kpack_parse_command_line_opts(struct kpack_program_opts *, int, char **);

/* Do: */
/*   Destroy struct kpack_program_opts created by */
/*   kpack_parse_command_line_opts */
void kpack_program_opts_destroy(struct kpack_program_opts *);

#endif /* KPACK_PARSE_OPTS_H */

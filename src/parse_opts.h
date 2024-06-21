#ifndef KPACK_PARSE_OPTS_H
#define KPACK_PARSE_OPTS_H

/* Mode of kpack */
enum kpack_mode {
	kpack_encoding,
	kpack_decoding
};

/* Work with stdin/stdout or with custom files? */
enum kpack_io_mode {
	kpack_io_file,
	kpack_io_stream
};

/* Command-line parameters */
struct kpack_program_opts {
	/* Input and output filenames, if exists */
	char *input_file;
	char *output_file;
	
	enum kpack_mode mode;
	
        enum kpack_io_mode input_file_mode;
	enum kpack_io_mode output_file_mode;
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
/*   2 = Malloc error */
/*   3 = User want to see `help' */
int kpack_parse_command_line_opts(struct kpack_program_opts *, int, char **);

/* Do: */
/*   Destroy struct kpack_program_opts created by */
/*   kpack_parse_command_line_opts */
void kpack_program_opts_destroy(struct kpack_program_opts *);

#endif /* KPACK_PARSE_OPTS_H */

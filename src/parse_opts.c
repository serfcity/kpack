#include "parse_opts.h"

#include <string.h>
#include <stdlib.h>

#include "bool.h"
#include "string_extensions.h"

int
kpack_parse_command_line_opts(struct kpack_program_opts *opt, int argc,
			      char **argv)
{
	int i;
	/* Flags for checking exists command-line options */
	bool is_compress = false;
	bool is_decompress = false;
	bool is_input_file = false;
	bool is_output_file = false;

	for (i = 0; i < argc; ++i) {
		/* Parse basic options */
		if (0 == strcmp(argv[i], "--help"))
			return 3;
		else if (0 == strcmp(argv[i], "-c"))
			is_compress = true;
		else if (0 == strcmp(argv[i], "--compress"))
			is_compress = true;
		else if (0 == strcmp(argv[i], "-d"))
			is_decompress = true;
		else if (0 == strcmp(argv[i], "--decompress"))
			is_decompress = true;
		/* End parsing basic options */
		/* Parse options, which require next option. */
		else if (i + 1 < argc) {
			if (0 == strcmp(argv[i], "-i")) {	
				char *s;
				s = kpack_clonestr(argv[i + 1]);
				if (!s)
					return 2;
				opt->input_file = s;
				is_input_file = true;
			}
			else if (0 == strcmp(argv[i], "--input")) {
				char *s;
				s = kpack_clonestr(argv[i + 1]);
				if (!s)
					return 2;
				opt->input_file = s;
				is_input_file = true;
			}
			else if (0 == strcmp(argv[i], "-o")) {
				char *s;
				s = kpack_clonestr(argv[i + 1]);
				if (!s)
					return 2;
				opt->output_file = s;
				is_output_file = true;
			}
			else if (0 == strcmp(argv[i], "--output")) {
				char *s;
				s = kpack_clonestr(argv[i + 1]);
				if (!s)
					return 2;
				opt->output_file = s;
				is_output_file = true;
			}
		}
		/* If next options not exists, fail */
		else {
			if (0 == strcmp(argv[i], "-i"))
				return 1;
			else if (0 == strcmp(argv[i], "--input"))
				return 1;
			else if (0 == strcmp(argv[i], "-o"))
				return 1;
			else if (0 == strcmp(argv[i], "--output"))
			        return 1;
		}	
	}

	/* Compressing and decompressing options are not compatible */
	if (is_compress && is_decompress)
		return 1;

	/* Kpack mode must be specify */
	if (is_compress == false && is_decompress == false)
		return 1;

	if (is_compress)
		opt->mode = kpack_encoding;

	if (is_decompress)
		opt->mode = kpack_decoding;
	
	if (is_input_file)
		opt->input_file_mode = kpack_io_file;
	else
		opt->input_file_mode = kpack_io_stream;

	if (is_output_file)
		opt->output_file_mode = kpack_io_file;
	else
		opt->output_file_mode = kpack_io_stream;

	return 0;
}

void
kpack_program_opts_destroy(struct kpack_program_opts *opt)
{
	free(opt->input_file);
	free(opt->output_file);
}

/*
  kpack is a KolibriOS-NG archiver, which uses liblzma
  Copyright (C) 2024  Leonid Gribanov
  
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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
				opt->input_file = argv[i + 1];
				is_input_file = true;
			}
			else if (0 == strcmp(argv[i], "--input")) {
				opt->input_file = argv[i + 1];
				is_input_file = true;
			}
			else if (0 == strcmp(argv[i], "-o")) {
				opt->output_file = argv[i + 1];
				is_output_file = true;
			}
			else if (0 == strcmp(argv[i], "--output")) {
				opt->output_file = argv[i + 1];
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

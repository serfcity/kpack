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

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

#ifndef KPACK_KPACK_HEADER_H
#define KPACK_KPACK_HEADER_H

#include <stdio.h>

/* The binary header of kpak is 12 bytes: */
/*   0-3 bytes for `KPCK' characters */
/*   4-7 bytes for unpacked size (little-endian) */
/*   8-11 bytes for flags (little-endian) see also `enum kpack_flags' */
struct kpack_header_bin {
	char kpck[4];
	unsigned char unpacked_size[4];
	unsigned char flags[4];
};


/* Header of kpack have `flags'. */
/* There are have a binary representation. */
/* There are for set encoding optimization. */
enum kpack_flags {
	kpack_bcj_none = 0x01,
	kpack_bcj1 = 0x41,
	kpack_bcj2 = 0x81
};

/* Kpack header in `ready for use' representation */
struct kpack_header {
	unsigned long int unpacked_size;
	enum kpack_flags flags;
};

/* Do: */
/*   Read binary header from file */
/* Errors: */
/*   0 = No error */
/*   1 = Reading failed */
int kpack_read_header_bin(struct kpack_header_bin *, FILE *);

/* Do: */
/*   Read binary header from file */
/* Errors: */
/*   0 = No error */
/*   1 = Writing failed */
int kpack_write_header_bin(struct kpack_header_bin *, FILE *);

/* Do: */
/*   Verfy binary header */
/* Errors: */
/*   0 = OK */
/*   1 = Invalid header */
int kpack_verfy_header_bin(struct kpack_header_bin *);

/* Do: */
/*   Pack kpack_header to kpack_header_bin */
void kpack_header_pack(struct kpack_header *, struct kpack_header_bin *);

/* Do: */
/*   Unpack kpack_header_bin to kpack_header */
/*   IF BINARY HEADER NOT VALID -> UNDEFINED BEHAVOUR */
/*   USE kpack_verfy_header_bin FIRST */
void kpack_header_unpack(struct kpack_header *, struct kpack_header_bin *);


#endif /* KPACK_HEADER_H */

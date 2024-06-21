#include "kpack_header.h"

#include <string.h>
#include <memory.h>

/* There are headers for print about non-implemented features */
#include <stdio.h>
#include <stdlib.h>

/* Big-endian and little-endian machines require different */
/* algorithms. This enum for swithcing machine type. */
enum kpack_machine_type {
	kpack_machine_big_endian = 0,
	kpack_machine_little_endian = 1
};

static enum kpack_machine_type
kpack_get_this_machine_endian(void)
{
	size_t a = 1;
	return *(char*)&a;
}

/* Implementation kpack_header_pack for little-endian machines */
static void
kpack_header_pack_LE(struct kpack_header *h, struct kpack_header_bin *bh)
{
	strncpy(bh->kpck, "KPCK", 4);
	memcpy(bh->unpacked_size, &h->unpacked_size, 4);
	bh->flags[0] = h->flags;
}

/* Implementation kpack_header_unpack for little-endian machines */
static void
kpack_header_unpack_LE(struct kpack_header *h, struct kpack_header_bin *bh)
{
	memcpy(bh->unpacked_size, &h->unpacked_size, 4);
	h->flags = bh->flags[0];
}

/* Implementation kpack_header_pack for big-endian machines */
static void
kpack_header_pack_BE(struct kpack_header *h, struct kpack_header_bin *bh)
{
        fprintf(stderr, "Big endian not implemented yet.\n");
	exit(1);
}

/* Implementation kpack_header_unpack for big-endian machines */
static void
kpack_header_unpack_BE(struct kpack_header *h, struct kpack_header_bin *bh)
{
	fprintf(stderr, "Big endian not implemented yet.\n");
	exit(1);
}

int
kpack_read_header_bin(struct kpack_header_bin *h, FILE *f)
{
	int read_bytes;

        read_bytes = fread(&h->kpck, 1, 4, f);
	if (read_bytes != 4)
		goto fail;
	
	read_bytes = fread(&h->unpacked_size, 1, 4, f);
	if (read_bytes != 4)
		goto fail;
	
	read_bytes = fread(&h->flags, 1, 4, f);
	if (read_bytes != 4)
		goto fail;

	return 0;
fail:
	return 1;
}

int
kpack_write_header_bin(struct kpack_header_bin *h, FILE *f)
{
	int written_bytes;

        written_bytes = fwrite(&h->kpck, 1, 4, f);
	if (written_bytes != 4)
		goto fail;
	
	written_bytes = fwrite(&h->unpacked_size, 1, 4, f);
	if (written_bytes != 4)
		goto fail;
	
	written_bytes = fwrite(&h->flags, 1, 4, f);
	if (written_bytes != 4)
		goto fail;

	return 0;
fail:
	return 1;
}

int
kpack_verfy_header_bin(struct kpack_header_bin *h)
{
	/* kpack_header_bin.kpck must be `KPCK' */
	/* kpack_header_bin.flags must be 0x01 or 0x41 or 0x81 */
	if (strncmp(h->kpck, "KPCK", 4))
		goto fail;
	if (h->flags[0] != 0x01 && h->flags[0] != 0x41 && h->flags[0] != 0x81)
		goto fail;
	
	return 0;
fail:
	return 1;
}

void
kpack_header_pack(struct kpack_header *h, struct kpack_header_bin *bh)
{
	enum kpack_machine_type endian;
	
	endian = kpack_get_this_machine_endian();
	switch(endian) {
	case kpack_machine_big_endian:
		kpack_header_pack_BE(h, bh);
	case kpack_machine_little_endian:
		kpack_header_pack_LE(h, bh);
	}
}

void
kpack_header_unpack(struct kpack_header *h, struct kpack_header_bin *bh)
{
	enum kpack_machine_type endian;
	
	endian = kpack_get_this_machine_endian();
	switch(endian) {
	case kpack_machine_big_endian:
		kpack_header_unpack_BE(h, bh);
	case kpack_machine_little_endian:
		kpack_header_unpack_LE(h, bh);
	}
}

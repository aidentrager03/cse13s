#include "bitreader.h"

#include <stdio.h>
#include <stdlib.h>

struct BitReader {
    FILE *underlying_stream;
    uint8_t byte;
    uint8_t bit_position;
};

BitReader *bit_read_open(const char *filename) {
    BitReader *bit_reader = (BitReader *) malloc(sizeof(BitReader));
    if (bit_reader == NULL) {
        return NULL; // Memory allocation error
    }

    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        free(bit_reader);
        return NULL; // File opening error
    }

    bit_reader->underlying_stream = file;
    bit_reader->byte = 8;
    bit_reader->bit_position = 8;

    return bit_reader;
}

void bit_read_close(BitReader **pbuf) {
    if (*pbuf != NULL) {
        fclose((*pbuf)->underlying_stream);
        free(*pbuf);
        *pbuf = NULL;
    }
}

uint8_t bit_read_bit(BitReader *buf) {
    if (buf->bit_position > 7) {
        int read_byte = fgetc(buf->underlying_stream);
        if (read_byte == EOF) {
            return NULL;
            //exit(EXIT_FAILURE);
        }
        buf->byte = (uint8_t) read_byte;
        buf->bit_position = 0;
    }

    uint8_t bit = (buf->byte >> buf->bit_position) & 1;
    buf->bit_position += 1;

    return bit;
}

uint8_t bit_read_uint8(BitReader *buf) {
    uint8_t byte = 0x00;
    for (int i = 0; i < 8; ++i) {
        byte |= (bit_read_bit(buf) << i);
    }
    return byte;
}

uint16_t bit_read_uint16(BitReader *buf) {
    uint16_t word = 0x0000;
    for (int i = 0; i < 16; ++i) {
        word |= (bit_read_bit(buf) << i);
    }
    return word;
}

uint32_t bit_read_uint32(BitReader *buf) {
    uint32_t word = 0x00000000;
    for (int i = 0; i < 32; ++i) {
        word |= (bit_read_bit(buf) << i);
    }
    return word;
}

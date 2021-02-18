#include "io.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static uint8_t char_buffer[BLOCK_SIZE];
static uint8_t code_buffer[BLOCK_SIZE];
uint32_t char_counter;
uint32_t code_counter;

// used for set the bit in buffer
// find the block and index
// set_bit : use shift to set the bit
void buffer_set_bit(uint32_t i) {
  uint32_t set_block = i / 8;
  uint32_t set_index = i % 8;
  code_buffer[set_block] |= (0x01 << set_index);
}

// used for get bit from buffer
uint8_t buffer_get_bit(uint32_t i) {
  uint32_t get_block = i / 8;
  uint32_t get_index = i % 8;
  uint8_t temp = code_buffer[get_block];
  for (uint32_t i = 1; i <= get_index; i++) {
    temp = (temp) / 2;
  }
  return temp % 2;
}

// used to get the no.i bit from a code
uint16_t code_get_bit(uint16_t code, uint32_t i) {
  uint16_t temp = code;
  uint16_t bit_i = (temp >> i);
  bit_i &= 0x01;
  return bit_i;
}

// read the header from infile and check
// the magic number
void read_header(int infile, FileHeader *header) {
  read(infile, header, sizeof(FileHeader));
  if (header->magic != MAGIC) {
    exit(1);
  }
  return;
}

// write the header to outfile
void write_header(int outfile, FileHeader *header) {
  write(outfile, header, sizeof(FileHeader));
  return;
}

// return next char each time
// if the buffer full, reset it
uint8_t next_char(int infile) {
  if (char_counter == 0) {
    memset(char_buffer, 0, BLOCK_SIZE);
    read(infile, char_buffer, BLOCK_SIZE);
  }
  uint8_t singel_char = char_buffer[char_counter];
  char_counter++;
  if (char_counter == BLOCK_SIZE) {
    char_counter = 0;
  }
  return singel_char;
}

// read the code if buffer is empty
// use code_get_bit to get the bit
// use buffer_set_bit to set the bit in buffer
void buffer_code(int outfile, uint16_t code, uint8_t bit_len) {
  for (uint8_t i = 0; i < bit_len; i++) {
    if (code_counter == BLOCK_SIZE * 8) {
      write(outfile, code_buffer, BLOCK_SIZE);
      memset(code_buffer, 0, BLOCK_SIZE);
      code_counter = 0;
    }
    uint16_t check_bit = code_get_bit(code, i);
    if (check_bit) {
      buffer_set_bit(code_counter);
    }
    code_counter++;
  }
  return;
}

// flush all remaining code to outfile
void flush_code(int outfile) {
  write(outfile, code_buffer, (code_counter / 8) + 1);
  return;
}

// read if buffer is empty
// use buffer_get_bit to get the bit from buffer
uint16_t next_code(int infile, uint8_t bit_len) {
  uint16_t n_code = 0;
  for (uint8_t i = 0; i < bit_len; i++) {
    if (code_counter == 0) {
      memset(code_buffer, 0, BLOCK_SIZE);
      read(infile, code_buffer, BLOCK_SIZE);
    }
    uint8_t bit_i = buffer_get_bit(code_counter);
    n_code |= (bit_i << i);
    code_counter++;
    if (code_counter == BLOCK_SIZE * 8) {
      code_counter = 0;
    }
  }
  return n_code;
}

// write the word to buffer in each time
// write the word to outfile if the buffer full
void buffer_word(int outfile, Word *w) {
  for (uint64_t i = 0; i < w->word_len; i++) {
    char_buffer[char_counter] = w->word[i];
    char_counter++;
    if (char_counter == BLOCK_SIZE) {
      write(outfile, char_buffer, BLOCK_SIZE);
      memset(char_buffer, 0, BLOCK_SIZE);
      char_counter = 0;
    }
  }
  return;
}

// flush the remaining word in buffer
void flush_word(int outfile) {
  write(outfile, char_buffer, char_counter);
  return;
}

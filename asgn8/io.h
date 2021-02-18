#ifndef __IO_H__
#define __IO_H__

#include "word.h"
#include <inttypes.h>

#define MAGIC 0xdeadcafe
#define BLOCK_SIZE 4096

// Variables to keep track of statistics for verbose flag.
extern uint64_t char_total;
extern uint64_t bit_total;
//
// Struct definition for a compressed file's header.
//
// magic:       Magic number that verifies this compression program.
// file_size:   File size of original, uncompressed file.
// protection:  The protection bit mask.
// padding:     Padding to align struct to 32-bits.
//
typedef struct FileHeader {
  uint32_t magic;
  uint64_t file_size;
  uint16_t protection;
  uint16_t padding;
} FileHeader;

//
// Reads a file header from the input file.
// This should read sizeof (FileHeader) bytes into the header.
// Should verify the magic number in the header that is read in.
// Programs with an incorrect magic number should not be decompressed.
//
// infile:     Input file descriptor.
// header:     The file header struct to read into.
//
void read_header(int infile, FileHeader *header);

//
// Writes a file header to the output file and returns original file size.
// This should write sizeof (FileHeader) bytes from the header.
//
// outfile:    Output file descriptor.
// header:     FileHeader to set values in and write.
//
void write_header(int outfile, FileHeader *header);

//
// Returns next character, or byte, from the input file.
// Should utilize a static 4KB uint8_t array to store bytes.
// 4KB ( BLOCK_SIZE ) are read into the buffer whenever the buffer is empty.
// A byte index is used to indicate the next character to return .
// This is called once for each byte in the input file.
// This is only called once for each byte in the input file.
//
// infile:     Input file descriptor
//
uint8_t next_char(int infile);

//
// Buffers a code into the code buffer for writing.
// The binary of the code is placed into the buffer in reverse.
//
// Adds the binary representation of a code to a buffer .
// Should utilize a static 4KB uint8_t array to store bits .
// The buffer is written to the output file whenever it is full .
// The binary code to add should be padded out to bit_len bits .
// Ex. buffer_code ( outfile , 5, 6) means adding "101000".
// A bit index is used to indicate which bit to set in the
// buffer when adding a code .
//
// outfile:   Output file descriptor.
// code:      The code to buffer.
// bit_len:   The length in bits of the code.
//
void buffer_code(int outfile, uint16_t code, uint8_t bit_len);

//
// Flushes any remaining codes in the buffer to the output file.
// Warning : this may not necessarily mean 4KB of codes.
//
// outfile:    Output file descriptor.
//
void flush_code(int outfile);

//
// Returns the next code in the input file .
// Should utilize a static 4KB uint8_t array to store bits .
// 4KB ( BLOCK_SIZE ) are read into the buffer whenever it is empty .
// The binary of the next code is bit_len number of bits long .
// Converts the binary of the next code into a uint16_t and returns it.
// Called until main decompression loop decodes all characters .
//
// infile:     Input file descriptor.
// bit_len:    The length in bits of the code to read.
//
uint16_t next_code(int infile, uint8_t bit_len);

//
// Adds a word into the character buffer to write to the output file.
// Buffer is written when it's filled with 4KB of characters.
//
// Should utilize a static 4KB uint8_t array to store bytes.
// The buffer is written when it ’s full of characters.
// Should utilize a byte index to keep track of where each byte
// of the Word to add should be set in the static 4KB buffer.
// This will involve looping through the byte array in a Word.
// Why? Each byte in the array of a Word must be buffered.
//
// outfile:    Output file descriptor.
// word:       Word to output.
// word_len:   Length of word to output.
//
void buffer_word(int outfile, Word *w);

//
// Flushes the character buffer to the output file if not empty.
//
// Flushes the buffer used to store words to the output file.
// Warning : this many not necessarily mean 4KB of characters.
//
// outfile:    Output file descriptor.
//
void flush_word(int outfile);

#endif

#include "endian.h"
#include "io.h"
#include "trie.h"
#include "word.h"
#include <fcntl.h>
#include <getopt.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define OPTIONS "vcdi:o:"

int main(int argc, char *argv[]) {
  bool verb_perform = false;
  bool comp_perform = false;
  bool deco_perform = false;
  bool default_in = true;
  bool default_out = true;
  bool mode_ch = false;
  char *input_name;
  char *output_name;

  int ch;
  // Show error if there are no arguments
  if (argc == 1) {
    printf("You have to provide command -v -c -d -i: -o:\n");
    return 0;
  }

  while ((ch = getopt(argc, argv, OPTIONS)) != -1) {

    switch (ch) {
    case 'v':
      verb_perform = true;
      break;

    // Show error if user choose -c -d at the same time
    case 'c':
      if (mode_ch == true) {
        printf("You can only choose one compress or decompress mode!\n)");
        exit(1);
      }
      comp_perform = true;
      mode_ch = true;
      break;

    case 'd':
      if (mode_ch == true) {
        printf("You can only choose one compress or decompress mode!\n)");
        exit(1);
      }
      deco_perform = true;
      mode_ch = true;
      break;

    case 'i':
      default_in = false;
      input_name = optarg;
      break;

    case 'o':
      default_out = false;
      output_name = optarg;
      break;

    default:
      printf("You can provide -v -c -d -i: -o:\n");
      return 0;
    }
  }
  // User have to provide -c or -d command
  if (!comp_perform && !deco_perform) {
    printf("You have to provide -c or -d for mode\n");
  }

  // read the infile and outfile by using open
  int infile = 0;
  int outfile = 0;

  if (!default_in) {
    infile = open(input_name, O_CREAT | O_RDWR, 0600);
  }
  if (!default_out) {
    outfile = open(output_name, O_CREAT | O_RDWR, 0600);
  }

  FileHeader *fh = calloc(1, sizeof(FileHeader));
  if (fh == NULL) {
    exit(1);
  }

  // if choose comperssion, run the function
  // This part is write by using Pseudocode from Eugene Chou
  if (comp_perform) {
    struct stat buff;
    uint8_t stat = fstat(infile, &buff);
    if (stat >= 0) {
      fh->magic = MAGIC;
      fh->file_size = buff.st_size;
      fh->protection = buff.st_mode;
    }
    write_header(outfile, fh);
    TrieNode *root = trie_create();
    TrieNode *curr_node = root;
    TrieNode *next_node;
    uint8_t curr_char;
    uint8_t bit_len;
    uint16_t next_avail_code = 256;
    uint64_t encoded_chars = 0;

    while (encoded_chars != fh->file_size) {
      curr_char = next_char(infile);
      next_node = trie_step(curr_node, curr_char);
      if (encoded_chars == 0 || next_node) {
        curr_node = next_node;
      } else {
        bit_len = log2(next_avail_code) + 1;
        buffer_code(outfile, curr_node->code, bit_len);
        curr_node->children[curr_char] = trie_node_create(next_avail_code);
        curr_node = root->children[curr_char];
        next_avail_code++;
      }
      encoded_chars++;

      if (next_avail_code == UINT16_MAX) {
        trie_reset(root);
        curr_node = root->children[curr_char];
        next_avail_code = 256;
      }
    }
    bit_len = log2(next_avail_code) + 1;
    buffer_code(outfile, curr_node->code, bit_len);
    flush_code(outfile);
    trie_delete(root);
    root = NULL;
    // if choose verb mode, print some data
    if (verb_perform) {
      printf("Original file size: %lu\n", fh->file_size);
      stat = fstat(outfile, &buff);
      if (stat >= 0) {
        printf("Compressed file size: %lu\n", (uint64_t)buff.st_size);
        double ori_size = fh->file_size;
        double com_size = buff.st_size;
        double com_ratio = 100 * (1 - (com_size / ori_size));
        printf("Compression ratio: %.4f%%", com_ratio);
        printf("\n");
      }
    }
  }

  // if choose deco mode, run this program
  // This part is written by using Pseudocode from Eugene Chou
  if (deco_perform) {
    read_header(infile, fh);
    WordTable *wt = wt_create();
    Word *curr_entry = NULL;
    Word *prev_entry = NULL;
    Word *miss_entry = NULL;
    uint8_t bit_len = 0;
    uint8_t *new_word = NULL;
    uint8_t *curr_word = NULL;
    uint8_t *prev_word = NULL;
    uint16_t curr_code = 0;
    uint16_t prev_code = 0;
    uint16_t next_avail_code = 256;
    bool reset = false;
    uint64_t decoded_chars = 0;

    while (decoded_chars != fh->file_size) {
      bit_len = log2(next_avail_code + 1) + 1;
      curr_code = next_code(infile, bit_len);
      curr_entry = wt->entries[curr_code];
      if (decoded_chars == 0 || reset) {
        buffer_word(outfile, curr_entry);
        //prev_word = curr_entry->word;
        reset = false;
        decoded_chars += curr_entry->word_len;
      } else if (curr_entry != NULL) {
        curr_word = curr_entry->word;
        prev_entry = wt->entries[prev_code];
        prev_word = prev_entry->word;
        new_word = calloc(prev_entry->word_len + 1, sizeof(uint8_t));
        for (uint64_t i = 0; i < prev_entry->word_len; i++) {
          new_word[i] = prev_word[i];
        }
        new_word[prev_entry->word_len] = curr_word[0];
        wt->entries[next_avail_code]
            = word_create(new_word, prev_entry->word_len + 1);
        next_avail_code++;
        buffer_word(outfile, curr_entry);
        decoded_chars += curr_entry->word_len;
        free(new_word);
        new_word = NULL;
      } else {
        prev_entry = wt->entries[prev_code];
        prev_word = prev_entry->word;
        curr_word = calloc(prev_entry->word_len + 1, sizeof(uint8_t));
        for (uint64_t i = 0; i < prev_entry->word_len; i++) {
          curr_word[i] = prev_entry->word[i];
        }
        curr_word[prev_entry->word_len] = prev_word[0];
        miss_entry = word_create(curr_word, prev_entry->word_len + 1);
        wt->entries[next_avail_code] = miss_entry;
        next_avail_code++;
        buffer_word(outfile, miss_entry);
        decoded_chars += miss_entry->word_len;
        free(curr_word);
        curr_word = NULL;
      }
      prev_code = curr_code;
      if (next_avail_code == UINT16_MAX - 1) {
        wt_reset(wt);
        next_avail_code = 256;
        reset = true;
      }
    }
    flush_word(outfile);
    wt_delete(wt);
    // if choose verbe mode print some data
    if (verb_perform) {
      struct stat buff;
      uint8_t stat = fstat(infile, &buff);
      if (stat >= 0) {
        printf("Original file size: %lu\n", fh->file_size);
        printf("Compressed file size: %lu\n", (uint64_t)buff.st_size);
        double ori_size = fh->file_size;
        double com_size = buff.st_size;
        double com_ratio = 100 * (1 - (com_size / ori_size));
        printf("Compression ratio: %.4f%%", com_ratio);
        printf("\n");
      }
    }
  }
  // close file and free the memory for header
  close(infile);
  close(outfile);
  free(fh);
  fh = NULL;
  return 0;
}

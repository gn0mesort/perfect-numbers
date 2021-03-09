#include <stdio.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdlib.h>
#include <limits.h>

#include <getopt.h>

#include "perfect.h"

#define HELP \
  "Usage: %s [options]\n" \
  "Options:\n" \
  "  --help, -h\n" \
  "    Print this help message.\n" \
  "  --bits=<8,16,32,64>, -b=<8,16,32,64>\n" \
  "    Generate perfect numbers within the range of the given bit width."

static const struct option longopts[] = {
  { "bits", required_argument, NULL, 'b' },
  { "help", no_argument, NULL, 'h' },
  { NULL, 0, NULL, 0 }
};

int main(int argc, char** argv) {
  int exit = EXIT_SUCCESS;
  size_t bits = sizeof(void*) * CHAR_BIT; // This is probably the processor word length.
  {
    int opt = 0;
    while ((opt = getopt_long(argc, argv, "hb:", longopts, NULL)) != -1)
    {
      switch (opt)
      {
      case 'b':
        if (!sscanf(optarg, "%zu\n", &bits))
        {
          fprintf(stderr, "%s: \"%s\" is not a valid number.\n", argv[0], optarg);
          goto err;
        }
        break;
      case 'h':
        printf(HELP "\n", argv[0]);
        goto done;
      default:
        goto err;
      }
    }
  }

  enum perfect_result res = PERFECT_RESULT_SUCCESS;
  struct perfect_generator* generator = NULL;
  res = perfect_create_generator(&generator);
  if (res != PERFECT_RESULT_SUCCESS)
  {
    fprintf(stderr, "%s: failed to create perfect_generator.\n", argv[0]);
    goto err;
  }
  union {
    uint8_t u8;
    uint16_t u16;
    uint32_t u32;
    uint64_t u64;
  } value;
  value.u64 = 0;
  do {
    switch (bits)
    {
    case 8:
      res = perfect_next8(generator, &value.u8);
      break;
    case 16:
      res = perfect_next16(generator, &value.u16);
      break;
    case 32:
      res = perfect_next32(generator, &value.u32);
      break;
    case 64:
      res = perfect_next64(generator, &value.u64);
      break;
    default:
      fprintf(stderr, "%s: bad bit width %zu.\n", argv[0], bits);
      goto err;
    }
    if (res < 0)
    {
      fprintf(stderr, "%s: failed to generate perfect numbers.\n", argv[0]);
      goto err;
    }
    if (res == PERFECT_RESULT_SUCCESS)
    {
      printf("%" PRIu64 "\n", value.u64);
    }
  } while (res != PERFECT_RESULT_NOMORE);
  goto done;
err:
  exit = EXIT_FAILURE;
done:
  perfect_destroy_generator(&generator);
  return exit;
}

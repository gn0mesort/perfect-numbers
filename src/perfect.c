#include "perfect.h"

#include <stdlib.h>

/**
 * A Mersenne prime is an integer n such that (1 << n) - 1 is prime.
 * This is a list of Mersenne primes such that n + (n - 1) < 64.
 *
 * Assuming a perfect number is (1 << (n - 1)) * ((1 << n) - 1) these are
 * the only numbers worth checking for the possible ranges of 8,16,32, or 64
 * bit computers.
 */
static const uintmax_t mersenne_primes[] = {
  2, 3, 5, 7, 13, 17, 19, 31
};

/**
 * Maximum constants for each width of possible perfect numbers.
 */
enum {
  MPRIME_8BIT_MAX = 2,
  MPRIME_16BIT_MAX = 4,
  MPRIME_32BIT_MAX = 5,
  MPRIME_64BIT_MAX = 8
};

/**
 * Generator retains an index into mersenne_primes.
 */
struct perfect_generator {
  size_t position;
};

enum perfect_result perfect_create_generator(struct perfect_generator* *const generator) {
  enum perfect_result result = PERFECT_RESULT_SUCCESS;
  if (!generator)
  {
    result = PERFECT_ERROR_NULLPTR;
    goto done;
  }
  *generator = malloc(sizeof(struct perfect_generator));
  if (!*generator)
  {
    result = PERFECT_ERROR_BADALLOC;
    goto done;
  }
  (*generator)->position = 0;
done:
  return result;
}

// Just parameterize the body of the next functions
#define CALC_PERFECT(size, one) \
  do { \
    enum perfect_result result= PERFECT_RESULT_SUCCESS; \
    if (!generator || !value) \
    { \
      result = PERFECT_ERROR_NULLPTR; \
      goto done; \
    } \
    if (generator->position >= (size)) \
    { \
      result = PERFECT_RESULT_NOMORE; \
      goto done; \
    } \
    *value = \
      ((one) << (mersenne_primes[generator->position] - (one))) * \
      (((one) << mersenne_primes[generator->position]) - (one)); \
    ++generator->position; \
done: \
    return result; \
  } while (0)

enum perfect_result perfect_next8(struct perfect_generator *const generator, uint8_t *const value) {
  CALC_PERFECT(MPRIME_8BIT_MAX, 1);
}


enum perfect_result perfect_next16(struct perfect_generator *const generator, uint16_t *const value) {
  CALC_PERFECT(MPRIME_16BIT_MAX, 1);
}

enum perfect_result perfect_next32(struct perfect_generator *const generator, uint32_t *const value) {
  CALC_PERFECT(MPRIME_32BIT_MAX, 1);
}


enum perfect_result perfect_next64(struct perfect_generator *const generator, uint64_t *const value) {
  CALC_PERFECT(MPRIME_64BIT_MAX, 1ULL);
}

enum perfect_result perfect_reset(struct perfect_generator *const generator) {
  enum perfect_result result = PERFECT_RESULT_SUCCESS;
  if (!generator)
  {
    result = PERFECT_ERROR_NULLPTR;
    goto done;
  }
  generator->position = 0;
done:
  return result;
}

enum perfect_result perfect_destroy_generator(struct perfect_generator* *const generator) {
  if (generator)
  {
    free(*generator);
    *generator = NULL;
  }
  return PERFECT_RESULT_SUCCESS;
}

#ifndef PERFECT_H
#define PERFECT_H

#include <inttypes.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

enum perfect_result {
  PERFECT_RESULT_NOMORE = 1,
  PERFECT_RESULT_SUCCESS = 0,
  PERFECT_ERROR_NULLPTR = -1,
  PERFECT_ERROR_BADALLOC = -2
};

enum {
  PERFECT_SIZE_8BITS = 8,
  PERFECT_SIZE_16BITS = 16,
  PERFECT_SIZE_32BITS = 32,
  PERFECT_SIZE_64BITS = 64
};

struct perfect_generator;

enum perfect_result perfect_create_generator(struct perfect_generator* *const generator);
enum perfect_result perfect_next8(struct perfect_generator *const generator, uint8_t *const value);
enum perfect_result perfect_next16(struct perfect_generator *const generator, uint16_t *const value);
enum perfect_result perfect_next32(struct perfect_generator *const generator, uint32_t *const value);
enum perfect_result perfect_next64(struct perfect_generator *const generator, uint64_t *const value);
enum perfect_result perfect_reset(struct perfect_generator *const generator);
enum perfect_result perfect_destroy_generator(struct perfect_generator* *const generator);

#ifdef __cplusplus
}
#endif

#endif

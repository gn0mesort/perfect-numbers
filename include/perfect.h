#ifndef PERFECT_H
#define PERFECT_H

#include <inttypes.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Possible results for perfect.h functions.
 */
enum perfect_result {
  /**
   * No more perfect numbers of the given size can be generated.
   */
  PERFECT_RESULT_NOMORE = 1,
  /**
   * Function completed successfully.
   */
  PERFECT_RESULT_SUCCESS = 0,
  /**
   * A pointer passed to a function was null.
   */
  PERFECT_ERROR_NULLPTR = -1,
  /**
   * An allocation failed.
   */
  PERFECT_ERROR_BADALLOC = -2
};

/**
 * An opaque structure to hold perfect number generator data.
 */
struct perfect_generator;

/**
 * Create a new perfect_generator.
 *
 * The pointer pointed to by generator will be filled with a new perfect_generator on success.
 *
 * @param generator A pointer to a struct perfect_generator* to fill.
 * @return PERFECT_RESULT_SUCCESS on success. PERFECT_ERROR_NULLPTR if generator is null.
 * PERFECT_ERROR_BADALLOC if malloc() fails.
 */
enum perfect_result perfect_create_generator(struct perfect_generator* *const generator);

/**
 * Generate the next perfect 8-bit number.
 *
 * Value will be filled with the resulting perfect number on success.
 *
 * @param generator A pointer to the generator to use.
 * @param value A pointer to store the resulting perfect number in.
 * @return PERFECT_RESULT_SUCCESS on successfully generating a new perfect number. PERFECT_ERROR_NULLPTR if generator
 * or value is null. PERFECT_RESULT_NOMORE if no perfect number can be generated.
 */
enum perfect_result perfect_next8(struct perfect_generator *const generator, uint8_t *const value);


/**
 * Generate the next perfect 16-bit number.
 *
 * Value will be filled with the resulting perfect number on success.
 *
 * @param generator A pointer to the generator to use.
 * @param value A pointer to store the resulting perfect number in.
 * @return PERFECT_RESULT_SUCCESS on successfully generating a new perfect number. PERFECT_ERROR_NULLPTR if generator
 * or value is null. PERFECT_RESULT_NOMORE if no perfect number can be generated.
 */
enum perfect_result perfect_next16(struct perfect_generator *const generator, uint16_t *const value);


/**
 * Generate the next perfect 32-bit number.
 *
 * Value will be filled with the resulting perfect number on success.
 *
 * @param generator A pointer to the generator to use.
 * @param value A pointer to store the resulting perfect number in.
 * @return PERFECT_RESULT_SUCCESS on successfully generating a new perfect number. PERFECT_ERROR_NULLPTR if generator
 * or value is null. PERFECT_RESULT_NOMORE if no perfect number can be generated.
 */
enum perfect_result perfect_next32(struct perfect_generator *const generator, uint32_t *const value);


/**
 * Generate the next perfect 64-bit number.
 *
 * Value will be filled with the resulting perfect number on success.
 *
 * @param generator A pointer to the generator to use.
 * @param value A pointer to store the resulting perfect number in.
 * @return PERFECT_RESULT_SUCCESS on successfully generating a new perfect number. PERFECT_ERROR_NULLPTR if generator
 * or value is null. PERFECT_RESULT_NOMORE if no perfect number can be generated.
 */
enum perfect_result perfect_next64(struct perfect_generator *const generator, uint64_t *const value);

/**
 * Reset a struct perfect_generator to its initial state.
 *
 * This will cause the input generator to begin at the lowest possible perfect number again.
 *
 * @param generator The struct perfect_generator to reset.
 * @return PERFECT_RESULT_SUCCESS on successfully resetting the generator. PERFECT_ERROR_NULLPTR if generator is null.
 */
enum perfect_result perfect_reset(struct perfect_generator *const generator);

/**
 * Destroy a struct perfect_generator.
 *
 * The value pointed to by generator will be set to NULL upon success.
 * If generator is null this is a no-op.
 *
 * @param generator A pointer to a struct perfect_generator* to destroy.
 * @return PERFECT_RESULT_SUCCESS in all cases.
 */
enum perfect_result perfect_destroy_generator(struct perfect_generator* *const generator);

#ifdef __cplusplus
}
#endif

#endif

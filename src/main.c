#include <stdio.h>
#include <inttypes.h>
#include <limits.h>

#include "perfect.h"

int main() {
  enum perfect_result res = PERFECT_RESULT_SUCCESS;
  struct perfect_generator* generator = NULL;
  res = perfect_create_generator(&generator);
  if (res != PERFECT_RESULT_SUCCESS)
  {
    goto err;
  }
  uint32_t perfect = 0;
  while ((res = perfect_next32(generator, &perfect)) != PERFECT_RESULT_NOMORE)
  {
    if (res < 0)
    {
      goto err;
    }
    printf("%" PRIu32 "\n", perfect);
  }
  perfect_destroy_generator(&generator);
  goto done;
err:
  fprintf(stderr, "Failed to generate perfect numbers.");
  return 1;
done:
  return 0;
}

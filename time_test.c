#include <stdio.h>
#include "clz.h"

int main(int argc, char const *argv[])
{
    __attribute__((unused)) uint32_t N = 0xFF;
    int zero = 0;

#if defined(RECUR)
    zero = clz_recur(N, SIZE);
#endif

#if defined(ITERA)
    zero = clz_itera(N);
#endif

#if defined(HARLEY)
    zero = clz_Harley(N);
#endif

   printf("N = %d , zero = %d\n", N, zero);

    return 0;
}

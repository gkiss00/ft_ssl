#include "./../include/ft_ssl.h"

static uint64_t random_64(uint64_t n) {
    uint64_t res;
    uint8_t tab[8];
    int     tmp;

    tmp = rand();
    memcpy(tab, &tmp, 4);
    tmp = rand();
    memcpy(&tab[4], &tmp, 4);
    memcpy(&res, tab, 8);
    res =  res % n;
    return res < 2 ? res + 2 : res;
}

static float    solovay_strassen(uint64_t n) {
    int prime = 0;

    printf("n : %lld\n", n);
    for (int k = 0; k < 100; ++k) {
        uint64_t a = random_64(n);
        printf("a : %lld\n", a);
        double x = a / n;
        printf("x : %f\n", x);
        uint64_t tmp = (uint64_t)pow(a, (n - 1) / 2) % n;
        printf("t : %f\n", pow(a, (n - 1) / 2));
        //if (x == 0 || x =/ tmp) => composit
        if (x == 0 || x != tmp) {

        } else {
            ++prime;
        }
        // else => prime
    }
    printf("%d\n", prime);
    return 0;
}

void ft_genrsa(int argc, char **argv, t_data *data) {
    parsing_genrsa(argc, argv, data);
    solovay_strassen(random_64(ULLONG_MAX));
}
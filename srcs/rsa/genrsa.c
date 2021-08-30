#include "./../include/ft_ssl.h"

// n an odd intger ≥ 3, an integer > 1
// bool miller_witness(uint64_t n, uint64_t a){

// }


void ft_genrsa(int argc, char **argv, t_data *data) {
    parsing_genrsa(argc, argv, data);
    srandom(time(NULL));
    uint64_t rand = (random() << 32) | random();
    printf("%lld\n", rand);
    PRINT_UINT64(&rand);
}
#include <iostream>
#include <fstream>
#include <gmpxx.h>
#include <cmath>
#include <chrono>
#include <vector>
#include <iomanip>

void mpf_pow(mpf_t &result, mpz_t base, mpz_t pow){
    mpz_t res;
    mpz_init(res);
    if(mpz_cmp_ui(pow, 0)==0){
        mpz_set_ui(res, 1);
        mpf_set_z(result, res);
        mpz_clear(res);
        return;
    }

    mpz_set_ui(res, 1);

    while (mpz_cmp_ui(pow, 0)> 0) {
        mpz_t temp;
        mpz_init(temp);
        if(mpz_mod_ui(temp, pow, 2)==1){
            mpz_mul(res, res, base);
        }
        mpz_clear(temp);
        mpz_mul(base, base, base);
        mpz_div_ui(pow, pow, 2);
    }
    mpf_set_z(result, res);
    mpz_clear(res);
}

void expm(mpf_t result, mpf_t p, mpf_t ak) {

    if (mpf_cmp_d(ak, 1.0)==0) {
        mpf_set_d(result, 0.0);
    }

    int i, j;

    mpf_t pt;
    mpf_init_set_d(pt, 1.0);
    mpf_t r;
    mpf_init_set_d(r, 1.0);

    const int ntp = 25;
    static mpf_t tp[ntp];

    for (int s=0; s<ntp; s++){
        mpf_init_set_d(tp[s], 0.0);
    }

    mpz_t tp1;
    mpz_init_set_ui(tp1, 0);

    // Fill the power of two table if not already filled
    if (mpz_cmp_ui(tp1, 0) == 0) {
        mpz_set_ui(tp1, 1);
        mpf_init_set_d(tp[0], 1.0);
        for (i = 1; i < ntp; i++) {
            // tp[i] = 2.0 * tp[i - 1];
            mpf_mul_ui(tp[i], tp[i-1], 2);
        }
    }

    // Find the greatest power of two less than or equal to p
    for (i = 0; i < ntp; i++) {
        if (mpf_cmp(tp[i], p) > 0) {
            break;
        }
    }
    // pt = tp[i - 1];
    mpf_init_set(pt, tp[i - 1]);

    // Binary exponentiation algorithm modulo ak
    for (j = 1; j <= i; j++) {
        if (mpf_cmp(p, pt)>= 0) {
            // r = 16.0 * r;
            mpf_mul_ui(r, r, 16);
            // r -= (int)(r / ak) * ak;
            // div
            mpf_t test;
            mpf_init(test);
            mpf_div(test, r, ak);

            // trunc
            mpf_trunc(test, test);
            // mul
            mpf_mul(test, test, ak);
            // sub
            mpf_sub(r, r, test);
            // p -= pt;
            mpf_sub(p, p, pt);
            mpf_clear(test);
        }
        // pt *= 0.5;
        mpf_t z;
        mpf_init_set_d(z, 0.5);
        mpf_mul(pt, pt, z);
        mpf_clear(z);
        if (mpf_cmp_d(pt, 1.0)>=0) { 
            mpf_mul(r, r, r);
            // r -= (int)(r / ak) * ak;
            // div
            mpf_t test;
            mpf_init(test);
            mpf_div(test, r, ak);

            // trunc
            mpf_trunc(test, test);
            // mul
            mpf_mul(test, test, ak);
            // sub
            mpf_sub(r, r, test);
            mpf_clear(test);
        }
    }
    mpf_set(result, r);
    mpf_clear(pt);
    mpf_clear(r);
    for (int s=0; s<ntp; s++){
        mpf_clear(tp[s]);
    }
    mpz_clear(tp1);
}


mpf_class S_j(int j, char *d, const std::chrono::time_point<std::chrono::system_clock>& startTime, std::string name, const std::string file_path) {
    // mpf_set_default_prec(128);
    mpf_t sum1, sum2, num;
    mpf_init(sum1);
    mpf_init(sum2);
    mpf_init(num);

    mpf_t result;
    mpf_init(result);
    mpf_t frac_term;
    mpf_init(frac_term);

    mpf_t d_mpf;

    mpf_init_set_str(d_mpf, d, 10);

    mpf_t k;
    mpf_init(k);

    for (mpf_set_ui(k, 0); mpf_cmp(k, d_mpf)<0; mpf_add_ui(k, k, 1)) {

        mpf_t p;
        mpf_init(p);
        mpf_sub(p, d_mpf, k);

        mpf_t ak;
        mpf_init(ak);
        mpf_mul_ui(ak, k, 8);
        mpf_add_ui(ak, ak, j);

        expm(result, p, ak);

        mpf_div(frac_term, result, ak);

        mpf_add(sum1, sum1, frac_term);

        mpf_t teste;
        mpf_init(teste);
        mpf_trunc(teste, sum1);
        mpf_sub (sum1, sum1, teste);
        mpf_clear(teste);

        mpf_clear(p);
        mpf_clear(ak);
        // system("pause");

        // if (i == 10000000) {
            // auto now = std::chrono::system_clock::now();
            // std::chrono::duration<double> elapsed_seconds = now - startTime;
            // std::cout << "SUM1: time: [" << elapsed_seconds.count() << "] | k: " << k << " | sum1: " << sum1 << std::endl;
        //     i=-1;
        // }
    }
    mpf_clear(result);
    mpf_clear(frac_term);
    

    mpf_t test;
    mpf_init(test);
    mpf_trunc(test, sum1);
    mpf_sub (sum1, sum1, test);
    mpf_clear(test);

    std::cout << "SUM1 Done: " << sum1 << std::endl;
    mpf_t d_mpf_100;
    mpf_init(d_mpf_100);
    mpf_add_ui(d_mpf_100, d_mpf, 100);
    for (mpf_set(k, d_mpf); mpf_cmp(k, d_mpf_100)<=0; mpf_add_ui(k, k, 1)) {
        mpf_t term;
        mpf_init(term);
        mpf_sub(term, d_mpf, k);

        mpf_abs(term, term);

        mpz_t pow;
        mpz_init(pow);
        mpz_set_f(pow, term);

        mpf_t temp;
        mpf_init(temp);
        mpz_t base;
        mpz_init_set_ui(base, 16);
        mpf_pow(temp, base, pow);

        mpz_clear(base);
        mpz_clear(pow);
        

        mpf_t result;
        mpf_init(result);
        mpf_ui_div(result, 1, temp);
        mpf_clear(temp);

        mpf_t ak;
        mpf_init(ak);
        mpf_mul_ui(ak, k, 8);
        mpf_add_ui(ak, ak, j);

        mpf_t frac_term;
        mpf_init(frac_term);
        mpf_div(frac_term, result, ak);

        mpf_add(sum2, sum2, frac_term);

        mpf_t test2;
        mpf_init(test2);
        mpf_trunc(test2, sum2);
        mpf_sub (sum2, sum2, test2);
        mpf_clear(test2);

        mpf_clear(term);
        mpf_clear(result);
        mpf_clear(frac_term);
        mpf_clear(ak);
    }

    auto now = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = now - startTime;
    std::cout << "SUM2: time: [" << elapsed_seconds.count() << "] | k: " << d + (24 * 16) << " | sum2: " << sum2 << std::endl;


    mpf_add(num, sum1, sum2);
    mpf_clear(sum1);
    mpf_clear(sum2);
    mpf_clear(k);
    mpf_clear(d_mpf);

    return mpf_class(num);
}

void main_function() {
    auto startTime = std::chrono::system_clock::now();
    mpf_set_default_prec(128);
    std::cout << std::setprecision(50);
    // std::cout << "precision: " << mpf_get_default_prec() << std::endl;

    std::string path = "C:\\path\\";

    std::vector<std::string> arr = 
    {
        // "50",
        // "1000000",
        // "9999950",
        // "10000000",
        "11999950",
        "14999950",
        "19999950",
        "24999950",
        "39999950"
        // "999999950",
        // "1000000000",
        // "9999999950",
        // "10000000000"
    };

    char* n;

    mpf_t S1, S2, S3, S4;

    for (std::string a : arr) {
        n = a.data();
        std::cout << "--- Computing n: " << n << std::endl;
        mpf_init_set(S1, S_j(1, n, startTime, "S1", path).get_mpf_t());

        mpf_init_set(S2, S_j(4, n, startTime, "S2", path).get_mpf_t());

        mpf_init_set(S3, S_j(5, n, startTime, "S3", path).get_mpf_t());

        mpf_init_set(S4, S_j(6, n, startTime, "S4", path).get_mpf_t());

        mpf_t result;
        mpf_init(result);

        mpf_mul_ui(S1, S1, 4);
        mpf_mul_ui(S2, S2, 2);

        mpf_sub(result, S1, S2);
        mpf_sub(result, result, S3);
        mpf_sub(result, result, S4);

        mpf_clear(S1);
        mpf_clear(S2);
        mpf_clear(S3);
        mpf_clear(S4);

        std::cout << "Result: " << result << " " << mpf_get_prec(result) << std::endl;

        mpf_t turnc;
        mpf_init(turnc);
        mpf_trunc(turnc, result);
        mpf_sub(result, result, turnc);
        if(mpf_cmp_ui(result, 0)<0) mpf_add_ui(result, result, 1);

        mp_exp_t expptr = 0;
        char hexy[50];
        mpf_get_str (hexy, &expptr, 16, 0, result);

        std::cout << "Result: " << hexy << " " << std::endl;
        
        auto now = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = now - startTime;
        std::cout << "Result: [" << elapsed_seconds.count() << "]"<< std::endl;

        std::ofstream file(path + "1-test-n" + a + "-result.txt");
        file << std::setprecision(129) << result << std::endl;
        file << hexy << std::endl;
        mpf_clear(result);
    }
}

int main() {
    main_function();
    system("pause");
    return 0;
}

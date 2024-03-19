#include <iostream>
#include <fstream>
#include <gmpxx.h>
#include <cmath>
#include <chrono>
#include <vector>
#include <iomanip>

void S_j(int j, int d, const std::chrono::time_point<std::chrono::system_clock>& startTime, std::string name, const std::string file_path) {
    mpf_set_default_prec(128);
    mpf_t sum1, sum2, num;
    mpf_init(sum1);
    mpf_init(sum2);
    mpf_init(num);

    mpz_t term;
    mpz_init(term);
    mpz_t result;
    mpz_init(result);
    mpf_t frac_term;
    mpf_init(frac_term);
    

    for (int k = 0; k <= d; ++k) {
        
        mpz_pow_ui(term, mpz_class(16).get_mpz_t(), (d - k));
        std::cout << std::setprecision(129);
        // std::cout << "term: " << term << std::endl;
        
        mpz_mod_ui(result, term, (8 * k + j));
        // std::cout << "(8 * k + j): " << (8 * k + j) << std::endl;
        // std::cout << "res: " << result << std::endl;
        mpf_t res;
        char *str;
        mpz_get_str(str, 10, result);
        mpf_init_set_str(res, str, 10);
        // std::cout << "res: " << res << std::endl;
        mpf_div_ui(frac_term, res, (8 * k + j));
        // std::cout << "frac: " << frac_term << std::endl;
        // system("pause");
        mpf_add(sum1, sum1, frac_term);
        // sum1 += frac_term;
        mpf_clear(res);
        if (k % 10000 == 0) {
            auto now = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = now - startTime;
            std::cout << "SUM1: time: [" << elapsed_seconds.count() << "] | k: " << k << " | sum1: " << sum1 << std::endl;
        }
    }
    mpz_clear(term);
    mpz_clear(result);
    mpf_clear(frac_term);
    

    // sum1 = mpf_fract(sum1);
    mpf_t test;
    mpf_init(test);
    mpf_trunc(test, sum1);
    mpf_sub (sum1, sum1, test);
    mpf_clear(test);

    std::cout << "SUM1 Done: " << sum1 << std::endl;

    for (int k = d + 1; k < d + (24 * 16); ++k) {
        mpf_t term;
        mpf_init(term);
        mpf_pow_ui(term, mpf_class(16).get_mpf_t(), abs(d - k));
        // std::cout << "term: " << term << std::endl;
        // system("pause");

        mpf_t result;
        mpf_init(result);
        mpf_ui_div(result, 1, term);
        // std::cout << "result: " << result << std::endl;
        // system("pause");

        mpf_t frac_term;
        mpf_init(frac_term);
        mpf_div_ui(frac_term, result, (8 * k + j));
        // std::cout << "frac_term: " << frac_term << std::endl;
        // system("pause");
        mpf_add(sum2, sum2, frac_term);
        // std::cout << "sum2: " << sum2 << std::endl;
        // system("pause");
        mpf_clear(term);
        mpf_clear(result);
        mpf_clear(frac_term);
    }

    mpf_t test2;
    mpf_init(test2);
    mpf_trunc(test2, sum2);
    mpf_sub (sum2, sum2, test2);
    mpf_clear(test2);

    auto now = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = now - startTime;
    std::cout << "SUM2: time: [" << elapsed_seconds.count() << "] | k: " << d + (24 * 16) << " | sum2: " << sum2 << std::endl;

    // system("pause");

    // num = mpf_fract(sum1 + sum2);
    mpf_add(num, sum1, sum2);
    mpf_clear(sum1);
    mpf_clear(sum2);
    std::cout << "NUM: " << num << " " << mpf_get_prec(num) << std::endl;
    system("pause");
    std::ofstream file(file_path + "n" + std::to_string(d) + "-"+name+"-.txt");
    file << num << std::endl;
    mpf_clear(num);
    // return 0;
}

void main_function() {
    auto startTime = std::chrono::system_clock::now();
    mpf_set_default_prec(128);
    std::cout << "precision: " << mpf_get_default_prec() << std::endl;
    mpf_class pi = 0;
    std::string path = "";

    std::vector<int> arr = {100000000}; // Add more values if needed

    for (int n : arr) {
        std::cout << "--- Computing n: " << n << std::endl;
        // S_j(1, n, startTime, "S1", path);
        // save_mpfr_object(path+"n" + std::to_string(n) + "-S1-.txt", S1);

        // S_j(4, n, startTime, "S2", path);
        // // save_mpfr_object(path+"n" + std::to_string(n) + "-S2-.txt", S2);

        // S_j(5, n, startTime, "S3", path);
        // // save_mpfr_object(path+"n" + std::to_string(n) + "-S3-.txt", S3);

        // S_j(6, n, startTime, "S4", path);
        // // save_mpfr_object(path+"n" + std::to_string(n) + "-S4-.txt", S4);
    }
}

int main() {
    main_function();
    system("pause");
    return 0;
}

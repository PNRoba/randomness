// Programme: Convert to hexadecimal
/* Description:
*    Convert pi digit string to hexadecimal
*/

#include <iostream>
#include <fstream>
#include <gmpxx.h>
#include <cmath>
#include <chrono>

int main() {
    std::ifstream file("C:\\path\\chunk_1.txt");
    auto startTime = std::chrono::system_clock::now();
    std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    
    std::ofstream file2("pi-result-hex2.txt", std::ios::app);

    int d = 20000100; // set precision
    str = str.substr(0, d); // shorter substring of pi constant

    str = "0." + str;

    file.close();
    std::cout << str.length() << std::endl;
    
    int precis = d*4;
    mpf_set_default_prec(precis);
    char hx[] = "0123456789abcdef";
    mpf_t pi;
    mpf_init(pi);
    mpf_set_str(pi, str.c_str(), 10); // convert string to mpf number
    
    str = "";

    // iterate through each digit multiplying by 16 and storing integer value after each iteration
    for(int i=0; i<d; i++){
        mpf_t result;
        mpf_init(result);
        mpf_mul_ui(pi, pi, 16);
        mpf_trunc(result, pi);
        mpf_sub(pi, pi, result);
        file2 << hx[mpf_get_si(result)];
        // auto now = std::chrono::system_clock::now();
        // std::chrono::duration<double> elapsed_seconds = now - startTime;
        // std::cout << "Time: [" << elapsed_seconds.count() << "] | digit: " << mpf_get_si(result) << "] | pi: " << pi << std::endl;
        if(i%1000==0){
            std::cout << "Precision: " << mpf_get_prec(pi) << std::endl;
            auto now = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = now - startTime;
            std::cout << "Time: [" << elapsed_seconds.count() << "] | i: " << i << "] | digit: " << mpf_get_si(result) << "] | pi: " << pi << std::endl;
        }
        mpf_clear(result);
        // n-=1;
        // precis-=4;
        // mpf_set_default_prec(precis);
        // if(n<=1) break;
    }
    mpf_clear(pi);
    file2.close();
    system("pause");
    return 0;
}

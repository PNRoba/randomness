// Programme: Sqrt(2) generation
/* Description:
*    Sqrt(2) generation using Newton-Raphson method
*/

#include <iostream>
#include <cmath>
#include <limits>
#include <gmpxx.h>
#include <iomanip>
#include <fstream>
#include <chrono>

// Function to find the square root of 2 up to a certain precision
void sqrtWithPrecision(mpf_t x, int precision, const std::chrono::time_point<std::chrono::system_clock>& startTime) {
    // double guess = x / 2.0; // Initial guess
    mpf_t guess;
    mpf_init(guess);
    mpf_div_ui(guess, x, 2);

    // double prevGuess = 0.0;
    mpf_t prevGuess;
    mpf_init_set_ui(prevGuess, 0);

    // Calculate the epsilon value based on the desired precision
    mpf_t epsilon;
    mpf_init(epsilon);
    
    const int arraySize = precision+2;
    char *charArray = new char[arraySize];

    memset(charArray, '0', arraySize);
    charArray[arraySize - 1] = '1'; // Set the last element to '1'
    charArray[0] = '0';
    charArray[1] = '.';

    mpf_set_str(epsilon, charArray, 10);

    // Iterate until the difference between consecutive guesses is less than epsilon
    mpf_t cmpr;
    mpf_init(cmpr);
    mpf_sub(cmpr, guess, prevGuess);
    mpf_abs(cmpr, cmpr);

    mpf_t prevCmpr;
    mpf_init_set(prevCmpr, epsilon);
    int k=0;
    while (mpf_cmp(cmpr, prevCmpr)!=0) { //mpf_cmp(cmpr, epsilon)>0 && 
        k++;
        // prevGuess = guess;
        mpf_set(prevGuess, guess);
        mpf_set(prevCmpr, cmpr);
        // guess = (guess + x / guess) / 2.0;
        mpf_t(temp);
        mpf_init(temp);
        mpf_div(temp, x, guess);
        mpf_add(guess, guess, temp);
        mpf_div_ui(guess, guess, 2);

        mpf_sub(cmpr, guess, prevGuess);
        mpf_abs(cmpr, cmpr);

        // if(k%10000==0){
        //     auto now = std::chrono::system_clock::now();
        //     std::chrono::duration<double> elapsed_seconds = now - startTime;
        //     std::cout << "SUM2: time: [" << elapsed_seconds.count() << "] | k: 1000" << std::endl;
        //     k=0;
        // }
        mpf_clear(temp);
    }
    std::cout << "guess: " << guess << std::endl;
    system("pause");

    mpf_clear(epsilon);
    mpf_clear(cmpr);
    mpf_clear(prevGuess);

    std::cout.precision(precision);
    std::cout << "Square root of " << x << " up to precision " << precision << " is: " << guess << std::endl;
    std::ofstream file("sqrt2-" +  std::to_string(precision) + "-result.txt");
    file << std::setprecision(precision+1) << guess << std::endl;
    file.close();

    mpf_clear(guess);
    system("pause");
}

int main() {
    auto startTime = std::chrono::system_clock::now();
    mpf_t number;
    mpf_init_set_ui(number, 2);

    int precision = 1000; // Set the desired precision here
    mpf_set_default_prec(precision*4); // set bit precision
    std::cout << std::setprecision(precision+1);
    sqrtWithPrecision(number, precision, startTime);

    return 0;
}

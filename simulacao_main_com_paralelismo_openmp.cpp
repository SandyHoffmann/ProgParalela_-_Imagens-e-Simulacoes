#include <iostream>
#include <math.h>

using namespace std;

void sum_pi_test_com_paralelismo(long int max_repeticoes=1000000000){
    long int max_n = max_repeticoes;
    long double sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (int n = 0; n < max_n; n += 1)
    {
        double temp = 1.0 / (2.0 * static_cast<double>(n) + 1.0);
        if (n % 2 == 0) // n is even
        {
            sum += temp;
        }
        else
        {
            // n is odd
            sum -= temp;
        }
    }
    #pragma omp master
    {
        std::cout << "Pi is about " << 4.0 * sum
            << " with error " << 4.0 * sum - M_PI
            << "\n";
    }
}

int main(int argc, char *argv[])
{

    long int valor = stol(argv[1]);
    sum_pi_test_com_paralelismo(valor);

    return 0;
}


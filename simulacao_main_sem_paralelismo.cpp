#include <iostream>
#include <math.h>

using namespace std;


void sum_pi_test_sem_paralelismo(long int max_repeticoes=1000000000){
 
    long int max_n = max_repeticoes;
    long double sum = 0;
    int num_procs = 1;
    printf("Numero de processos: %d\n", num_procs);
    int rank = 0;
    for (int n = rank; n < max_n; n += num_procs)
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
    double global_sum = sum;
    // * Só a redução conta com o paralelismo nesse caso
    // * Reduce = Função de soma (dados concentrados em apenas um processo)
    // * Se fosse de vários processos poderiamos usar a função de Broadcast (Bcast)
    printf("Soma: %d\n",sum);
    if (rank == 0)
    {
        std::cout << "Pi is about " << 4.0 * global_sum << " with error " << 4.0 * global_sum - M_PI << "\n";
    }

}


int main(int argc, char *argv[]){
    long int valor = stol(argv[1]);
    sum_pi_test_sem_paralelismo(valor);
    return 0;    
}
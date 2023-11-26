#include <iostream>
#include <mpi.h>
#include <math.h>

using namespace std;

void sum_pi_test_com_paralelismo(long int max_repeticoes=1000000000){
    long int max_n = max_repeticoes;
    long double sum = 0;
    // * COMM_WORLD.Get_size() - retorna quantas processos estão na rede MPI 
    int num_procs = MPI::COMM_WORLD.Get_size();
    printf("Numero de processos: %d\n", num_procs);
    // * COMM_WORLD.Get_rank() - obter o identificador do processo
    int rank = MPI::COMM_WORLD.Get_rank();
    printf("Rank: %d\n", rank);
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
    long double global_sum;
    // * Só a redução conta com o paralelismo nesse caso
    // * Reduce = Função de soma (dados concentrados em apenas um processo)
    // * Se fosse de vários processos poderiamos usar a função de Broadcast (Bcast)
    printf("Soma: %d\n",sum);
    MPI::COMM_WORLD.Reduce(&sum, &global_sum, 1, MPI::LONG_DOUBLE, MPI::SUM, 0);
    if (rank == 0)
    {
        std::cout << "Pi is about " << 4.0 * global_sum
                << " with error " << 4.0 * global_sum - M_PI
                << "\n";
    }
}

int main(int argc, char *argv[])
{
   MPI_Init(NULL, NULL);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    long int valor = stol(argv[1]);
    sum_pi_test_com_paralelismo(valor);
    MPI_Finalize();

    return 0;
}


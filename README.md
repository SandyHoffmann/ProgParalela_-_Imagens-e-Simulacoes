# ProgParalela_-_Imagens-e-Simulacoes

# Instalações e configurações (Linux)

## openCV

Instalei a biblioteca libopencv-dev:
```
>> sudo apt install libopencv-dev
```
Segui esse tutorial para setar os pacotes: 
>http://www.codebind.com/cpp-tutorial/install-opencv-ubuntu-cpp/

Se der o erro que a flag de desenvolvimento não estiver configurada basta:
```
>> pkg-config --list-all

Vai dar o nome do pacote (o meu por exemplo estava como opencv4)
```
E então compilar o código da seguinte maneira:
```
>> g++ main.cpp -o a.out `pkg-config --cflags --libs opencv4`
```


## MPI

```
>> sudo apt-get install openmpi-bin openmpi-doc libopenmpi-dev
>> module load openmpi/gcc
```
Para compilar com o g++ uma opção é especificando o caminho absoluto da biblioteca, o que pode ser feito desse jeito:
```
>> g++ main.cpp -o a.out ` -I/usr/lib/x86_64-linux-gnu/openmpi/$(mpic++ -showme:compile) $(mpic++ -showme:link)
```

## openMP

Só adicionar a diretiva `-fopenmp` no final da linha de compilação

# Compilando exemplos

## simulacao_main_sem_paralelismo.cpp
```
>> g++ simulacao_main_sem_paralelismo.cpp
```
## simulacao_main_com_paralelismo_openmp.cpp
```
>> g++ simulacao_main_sem_paralelismo.cpp -fopenmp
```
## simulacao_main_com_paralelismo_MPI.cpp
```
>> g++ simulacao_main_com_paralelismo_MPI.cpp -o a.out  -I/usr/lib/x86_64-linux-gnu/openmpi/$(mpic++ -showme:compile) $(mpic++ -showme:link)
>> mpirun -np 2 ./a.out 
```
## imagens_main.cpp
Sem openmp
```
>> g++ imagens_main.cpp -o a.out `pkg-config --cflags --libs opencv4`
```
Com openmp
```
>> g++ imagens_main.cpp -o a.out `pkg-config --cflags --libs opencv4` -fopenmp
```
/**
 * \author Sandy Hoffmann
 * \date November 11, 2023
 * \version November 11, 2023
 **/

#ifndef IFMOVE_MATRIX_H
#define IFMOVE_MATRIX_H
#include <vector>
#include <math.h>       /* pow */
#include <string.h>

using namespace std;
/**
* Matrix basic class
* \param i = linha
* \param j = coluna
* \param array = matrix ixj
*/

class Matrix {
    public:
        int i;
        int j;
        vector<vector<double>> matrix;
        Matrix(vector<vector<double>> matrix_atr){
            cout << "Inicializating matrix...";
            // definine i and j
            i = matrix_atr.size();
            j = (i > 0) ? matrix_atr[0].size() : 0;
            cout << "i: " << i << ", j: " << j << "\n";
            // matrix is matriz_atr (params)
            matrix = matrix_atr;
        }


        void printar_matriz(){
            cout << "[ ";
            for (int linha = 0; linha < i; ++linha){
                cout << "[";
                for (int coluna = 0; coluna < j; ++coluna){
                    cout << matrix[linha][coluna]; 
                    if (coluna != j-1){
                        cout<< ", ";
                    }

                }
                cout << "] ";
            }
            cout << "] ";
        }

        void mudar_valor(int linha, int coluna, double valor){
            matrix[linha][coluna] = valor;
        }

        void box_bluring(int kernelSize=3){
            // * EDGES ESTÃO SENDO DESCONSIDERADOS
            // * MULTIPLICAR A MATRIZ
            int metade_kernel = kernelSize/2;
            #pragma omp parallel for collapse(2)
            for (int linha = 0; linha < i; ++linha){
                for (int coluna = 0; coluna < j; ++coluna){
                    long int total = 0;
                    for (int linha_r = -metade_kernel; linha_r <= metade_kernel; linha_r++){
                        if (!(linha + linha_r < 0 || linha + linha_r > i-1)){
                            for (int coluna_r = -metade_kernel; coluna_r <= metade_kernel; coluna_r++){
                                if (!(coluna + coluna_r < 0 || coluna + coluna_r > j-1)){
                                // linha = linha - 1; linha - 0; linha + 1
                                // coluna = coluna - 1; coluna - 0; coluna + 1

                                    total += matrix[linha + linha_r][coluna + coluna_r];
                                }
                            }
                        }
                    }
                    int finalCor = total/(pow(kernelSize,2));
                    mudar_valor(linha, coluna, finalCor);
                }
            }
        }

        void flip_image(){
            for (int linha = 0; linha < i; ++linha){
                for (int coluna = 0; coluna < j/2; ++coluna){

                    int valor_coluna_selecionada_fim = matrix[i-linha-1][j-coluna-1];
                    mudar_valor( i-linha-1, j-coluna-1, matrix[linha][coluna]);
                    mudar_valor(linha, coluna, valor_coluna_selecionada_fim);
                }
            }
        }


        void gauss_blur(){
            printf("GAUSS\n");

            double sigma = 5;
            float m = 2.0;
            double n = 2 * (4 * 5 + 0.5) + 1;

            printf("\nm: %d",m);
            printf("\nn: %d",n);
            // vector<vector<double>> kernel (m, vector<double>(n, 0));

            // // for (int y=-m; y<=m; y++){
            // //     for (int x=-n; x<=n; x++){
            // //         double normal = 1 / (2*3.14*pow(sigma,2));
            // //         double expoente_e = -((pow(x,2)+pow(y,2))/(2*(pow(sigma,2))));
            // //         double exp = pow(2.71,expoente_e);
            // //         kernel[y+m][x+n]= normal*exp;
            // //     }
            // // }


            // // * SE PREOCUPAR COM EDGES
            // // * MULTIPLICAR A MATRIZ

            // // * A cada iteração crio uma nova matrix 3x3 ?

            
            // for (int linha = 0; linha < i; ++linha){

            //     for (int coluna = 0; coluna < j; ++coluna){
            //         int total = 0;
            //         // ! ADAPTAR PARA KERNEL VARIAVEL DPS
            //         for (int linha_r = -1; linha_r <= 1; linha_r++){
            //             if (!(linha + linha_r < 0 || linha + linha_r > i-1)){
            //                 for (int coluna_r = -1; coluna_r <= 1; coluna_r++){
            //                     if (!(coluna + coluna_r < 0 || coluna + coluna_r > j-1)){
            //                     // linha = linha - 1; linha - 0; linha + 1
            //                     // coluna = coluna - 1; coluna - 0; coluna + 1
            //                         printf("COLUNAJ: %d", j);

            //                         printf("LINHA: %d", linha + linha_r);
            //                         printf("COLUNA: %d", coluna + coluna_r);

            //                         total += matrix[linha + linha_r][coluna + coluna_r]*kernel[linha_r][coluna_r];

            //                     }
            //                 }
            //             }
            //         }
            //         mudar_valor(linha, coluna, total);
            //         printf("Total: %d", total);

            //     }
            // }
        }

        vector<double> to_single_vector(){
            vector<double> my_vector;
            for (int linha = 0; linha < i; ++linha){
                for (int coluna = 0; coluna < j; ++coluna){
                    my_vector.push_back(matrix[linha][coluna]); 
                }
            }
            return my_vector;
        }
        
};


#endif

#include <iostream>
#include <string>
#include "matrix.h"

#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


void test_box_blurring(vector<vector<double>> matrixImg, int rows, int columns){
    Matrix matrix_img_points(matrixImg);
    matrix_img_points.box_bluring(35);
    Mat minha_img(rows,columns,CV_8UC1);
    for (int r=0; r< rows; r++) {
        for (int c=0; c < columns; c++) {
            minha_img.at<uchar>(r,c) = static_cast<uchar>(matrix_img_points.matrix[r][c]);
        }
    }
    namedWindow("BOX BLURRING", WINDOW_NORMAL);
    resizeWindow("BOX BLURRING",400,400);
    imshow("BOX BLURRING", minha_img);

}

void test_box_blurring_opencv(Mat matrixImg){
    Mat outputMatrixImg;
    // Parametros:
    // Input Image
    // Output Image
    // Depth - Profundidade da imagem de output em relação a de input
    // Tamanho do kernel
    // Ancora (de onde começar - nesse caso é centro)
    // Se o kernel é normalizado ou não
    // Tipo da borda;
    boxFilter(matrixImg, outputMatrixImg, 0, Size(35, 35), Point(-1, -1), true, BORDER_DEFAULT);
    namedWindow("BOX BLURRING OPENCV", WINDOW_NORMAL);
    resizeWindow("BOX BLURRING OPENCV",400,400);

    imshow("BOX BLURRING OPENCV", outputMatrixImg);
}

void test_flip(vector<vector<double>> matrixImg, int rows, int columns){
    Matrix matrix_img_points(matrixImg);
    matrix_img_points.flip_image();
    Mat minha_img(rows,columns,CV_8UC1);
    for (int r=0; r< rows; r++) {
        for (int c=0; c < columns; c++) {
            minha_img.at<uchar>(r,c) = static_cast<uchar>(matrix_img_points.matrix[r][c]);
        }
    }
    namedWindow("FLIP", WINDOW_NORMAL);
    resizeWindow("FLIP",400,400);
    imshow("FLIP", minha_img);

}

void test_img(){
    Mat image;

    // IMREAD_GRAYSCALE
    // IMREAD_COLOR
    
    image = imread("images/gatobig.jpg", IMREAD_GRAYSCALE);   // Read the file

    cout << "Width : " << image.cols << endl;
    cout << "Height: " << image.rows << endl;

    namedWindow("O GATO", WINDOW_NORMAL);
    resizeWindow("O GATO",400,400);
    imshow("O GATO", image);

    vector<vector<double>> matrixImg (
    image.rows,
    vector<double>(image.cols, 0));

    for (int r=0; r< image.rows; r++){
        for (int c=0; c < image.cols; c++){
            matrixImg[r][c] = static_cast<double>(image.at<uchar>(r,c));    
        }
    }
    test_box_blurring(matrixImg, image.rows, image.cols);
    test_box_blurring_opencv(image);
    test_flip(matrixImg, image.rows, image.cols);

    waitKey(0);
}

int main()
{
    cout << "Teste Simuação de Imagens\n";
    test_img();

    return 0;
}


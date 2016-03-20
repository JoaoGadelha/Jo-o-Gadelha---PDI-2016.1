#include "opencv2/highgui.hpp"

#include "opencv2/highgui/highgui_c.h"

#include <stdio.h>

#include <iostream>

#include <string.h>

#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock


using namespace std;
using namespace cv;

int main(int, char**){
  Mat image[5],aux;
  Vec3b val;
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  int breakx,breaky; // coordenadas x e y do ponto central da imagem
  int randArray[4] = {1,2,3,4}; // a imagem sera cortada em quatro partes e 
 				// e redistribuida de acordo com a ordem do numeros presentes
				// no array randArray, o qual tera seus elementos embaralhados 
				// pela funcao shuffle, logo abaixo. 
  
  shuffle(&randArray[0],&randArray[4],default_random_engine(seed));
  
  image[0]= imread("lena.jpg",CV_LOAD_IMAGE_GRAYSCALE); // le a imagem de entrada
  aux = imread("lena.jpg",CV_LOAD_IMAGE_GRAYSCALE);
  breakx = image[0].rows/2;
  breaky = image[0].cols/2;

// a imagem é então quebrada em 4 quadrantes
image[1] = image[0](Rect(0,0,breakx,breaky)); // quadrante noroeste 
image[2] = image[0](Rect(breakx,0,breakx,breaky)); // quadrante nordeste 
image[3] = image[0](Rect(0,breakx,breakx,breaky)); // quadrante sudoeste 
image[4] = image[0](Rect(breakx,breaky,breakx,breaky)); // quadrante  sudeste

// reescrita da imagem gravada na variavel aux, de acordo com os valores de grayscale presentes em cada quadrante
 
for  ( int i = 0; i < breakx ; i ++ ){
	for ( int j = 0 ; j < breaky; j++) {
		aux.at<uchar>(i,j) = image[randArray[0]].at<uchar>(i,j);	
	}
}

for  ( int i = 0; i < breakx ; i ++ ){
	for ( int j = 0 ; j < breaky; j++) {
		aux.at<uchar>(i,j+breaky) = image[randArray[1]].at<uchar>(i,j);	
	}
}
for  ( int i = 0; i < breakx ; i ++ ){
	for ( int j = 0 ; j < breaky; j++) {
		aux.at<uchar>(i+breakx,j) = image[randArray[2]].at<uchar>(i,j);	
	}
}
for  ( int i = 0; i < breakx ; i ++ ){
	for ( int j = 0 ; j < breaky; j++) {
		aux.at<uchar>(i+breakx,j+breaky) = image[randArray[3]].at<uchar>(i,j);	
	}
}

  imshow("janela", aux);  // mostra o resultado do embaralhamento da imagem original
  waitKey();
  return 0;
}

#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <iostream>
#include <cv.h>
#include <highgui.h>
#include <math.h>

using namespace std;
using namespace cv;


int main(int argc, char *argv[]){
	Mat img = imread(argv[2],CV_LOAD_IMAGE_GRAYSCALE);
	
	imshow("Before",img);
	waitKey(0);
	int max = img.at<uchar>(0,0);
	int min=max;
	for(int j=0;j<img.rows;j++) 
	{
	  for (int i=0;i<img.cols;i++)
	  {
		int temp = img.at<uchar>(j,i);
		if(temp>max) max = temp;
		if(temp<min) min = temp;
//	       img.at<uchar>(j,i) = img.at<uchar>(j,i); //white
	  }
	}
//	cout<<"Max is "<<max<<endl<<"Min is "<<min<<endl;
	for(int j=0;j<img.rows;j++)
	{
	  for (int i=0;i<img.cols;i++)
	  {
		int temp = img.at<uchar>(j,i);
//		cout<<"1. "<<temp<<endl;
		float value = (((temp - min)*1.0)/(max - min))*(.99);
		value = pow(value,atoi(argv[1]));
//		cout<<"2. "<<value<<endl;
		img.at<uchar>(j,i) = value*255;
//		cout<<"3. "<<img.at<uchar>(j,i)<<endl<<endl;
//		if(temp>max) max = temp;
//		if(temp<min) min = temp;
//	       img.at<uchar>(j,i) = img.at<uchar>(j,i); //white
	  }
	}
	imshow("After",img);
	imwrite("inn.jpg",img);
	waitKey(0);
	Mat dst1,dst2,dst3;
	//# global thresholding
	threshold(img,dst1,127,255,CV_THRESH_BINARY);
	imshow("Binary",dst1);
	waitKey(0);
	
	//# Otsu's thresholding
	threshold(img,dst2,0,255,CV_THRESH_BINARY|CV_THRESH_OTSU);
	imshow("Binary otsu",dst2);
	waitKey(0);
	
	//# Otsu's thresholding after Gaussian filtering
	Mat blur;
	GaussianBlur(img,blur,Size(5,5),0,0);
	threshold(blur,dst3,0,255,THRESH_BINARY|CV_THRESH_OTSU);
	imshow("Binary otsu with blur",blur);
	imwrite("end.jpg",dst3);
	waitKey(0);
 
	Mat dst4;	
	bilateralFilter (img,blur, 2, 4, 1);
	threshold(blur,dst4,0,255,THRESH_ZERO|CV_THRESH_OTSU);
	imshow("Binary otsu with bilateral blur",blur);
	imwrite("end2.jpg",dst4);
	waitKey(0);
 	
	return 0;
}

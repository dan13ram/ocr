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
	Mat img = imread("a.jpg",CV_LOAD_IMAGE_GRAYSCALE);
	int VAL;
//	VAL = atoi(argv[1]);
//	VAL = 1.8;
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
	Mat img2 = imread("a.jpg",CV_LOAD_IMAGE_GRAYSCALE);
//	cout<<"Max is "<<max<<endl<<"Min is "<<min<<endl;
	for(int j=0;j<img.rows;j++)
	{
	  for (int i=0;i<img.cols;i++)
	  {
		int temp = img.at<uchar>(j,i);
		float value = (((temp - min)*1.0)/(max - min))*(.99);
		value = pow(value,1.7);
		img.at<uchar>(j,i) = value*255;
	  }
	}

	for(int j=0;j<img2.rows;j++)
	{
	  for (int i=0;i<img2.cols;i++)
	  {
		int temp = img2.at<uchar>(j,i);
		float value = (((temp - min)*1.0)/(max - min))*(.99);
		value = pow(value,4);
		img2.at<uchar>(j,i) = value*255;
	  }
	}
	
	imshow("1.7",img);
	imwrite("after1_7.jpg",img);
	waitKey(0);
	Mat dst;
	adaptiveThreshold(img,dst,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY,11,0);
	imshow("Binary otsu with bilateral blur",dst);
	waitKey(0);
 
	Mat dst1;	
	threshold(img,dst1,0,255,CV_THRESH_BINARY|CV_THRESH_OTSU);
	imshow("Binary",dst1);
	imwrite("mid.jpg",dst1);
	waitKey(0);
	for(int i=0;i<dst.rows;i++){
		for(int j=0;j<dst.cols;j++){
			if(dst1.at<uchar>(i,j) == 255)	dst.at<uchar>(i,j)=255;
			if(img2.at<uchar>(i,j) < 5)	dst.at<uchar>(i,j)=0;
		}
	}
	imshow("Binary",dst);
	imwrite("end.jpg",dst);
	waitKey(0);
	return 0;
}

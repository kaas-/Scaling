#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int roundNum(float num) {

	if (num - floor(num) >= 0.5)
		num = ceil(num);
	else
		num = floor(num);

	return num;
}

//Simple scaling algorithm using forward mapping
Mat simpleScaling(Mat src, float Sx, float Sy)
{

	if (Sx <= 0 || Sy <= 0)
	{
		cout << "Negative scaling is not possible";
		return src;
	}
		
	//Create a Mat object with scaled dimensions, greyscale, completely black.
	Mat output(src.rows*Sy,src.cols*Sx, CV_8U, Scalar(0, 0, 0));

	for (int y = 0; y < src.rows; ++y)
	{
		for (int x = 0; x < src.cols; ++x)
		{
			output.at<uchar>(y*Sy, x*Sx) = src.at<uchar>(y, x);
		}
	}

	return output;
}

Mat backScaling(Mat src, float Sx, float Sy)
{
	if (Sx <= 0 || Sy <= 0)
	{
		cout << "Negative scaling is not possible";
		return src;
	}

	Mat output(src.rows*Sy, src.cols*Sx, CV_8U, Scalar(0, 0, 0));
	int tmpy, tmpx;

	for (int y = 0; y < output.rows; ++y)
	{
		for (int x = 0; x < output.cols; ++x)
		{
			tmpy = roundNum(1 / Sy*y);
			tmpx = roundNum(1 / Sx*x);

			if (tmpy >= src.rows)
				tmpy = src.rows - 1;

			if (tmpx >= src.cols)
				tmpx = src.cols - 1;

			output.at<uchar>(y, x) = src.at<uchar>(tmpy, tmpx);
		}
	}
	return output;
}

int main(int, char)
{
	Mat image = imread("input.jpg");
	cvtColor(image, image, CV_BGR2GRAY);
	
	float Sx, Sy;
	cout << "Enter horizontal scalar: "; cin >> Sx; cout << endl;
	cout << "Enter vertical scalar: "; cin >> Sy; cout << endl;

	Mat image2 = simpleScaling(image, Sx, Sy);
	Mat image3 = backScaling(image, Sx, Sy);
	imshow("IMAGE", image);
	imshow("IMAGE2", image2);
	imshow("IMAGE3", image3);
	waitKey(0);
		
	return 0;
}
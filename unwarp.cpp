#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include <iostream>

#define IMG "1.jpeg"
const int maxShift = 5;

using namespace std;
using namespace cv;

Mat shiftRow(Mat img, int y, int shift)
{
	if(shift > 0)
	{
		for(int i = 0; i < shift; ++i)
		{
			for(int x = 0; x < img.cols; ++x)
			{
				if(x + 1 < img.cols)
					img.at<uchar>(y,x) = img.at<uchar>(y,x+1);
				else
					img.at<uchar>(y,x) = 0;
			}
		}
	}
	else if(shift < 0)
	{
		for(int i = 0; i < -shift; ++i)
		{
			for(int x = img.cols-1; x >= 0; --x)
			{
				if(x - 1 >= 0)
					img.at<uchar>(y,x) = img.at<uchar>(y,x-1);
				else
					img.at<uchar>(y,x) = 0;
			}
		}
	}
	return img;
}

Mat shiftCol(Mat img, int x, int shift)
{
	if(shift > 0)
	{
		for(int i = 0; i < shift; ++i)
		{
			for(int y = 0; y < img.rows; ++y)
			{
				if(y + 1 < img.rows)
					img.at<uchar>(y,x) = img.at<uchar>(y+1,x);
				else
					img.at<uchar>(y,x) = 0;
			}
		}
	}
	else if(shift < 0)
	{
		for(int i = 0; i < -shift; ++i)
		{
			for(int y = img.rows-1; y >= 0; --y)
			{
				if(y - 1 >= 0)
					img.at<uchar>(y,x) = img.at<uchar>(y-1,x);
				else
					img.at<uchar>(y,x) = 0;
			}
		}
	}
	return img;
}


Mat warpX(Mat img, Mat imgUW)
{
	int topX; 
	for(int x = img.cols-1; x >= 0; --x)
	{
		if(img.at<uchar>(0,x) <= 128)
		{
			topX = x;
			break;
		}
		else if(x == 0)
			return img;
	}
	int currentX = topX;
	for(int y = 0; y < img.rows; ++y)
	{
		for(int i = 0; i < maxShift; ++i)
		{
			if(currentX - i >= 0)
				if(img.at<uchar>(y,currentX - i) <= 128)
				{
					currentX = currentX - i;
					break;
				}
			if(currentX + i < img.cols)
				if(img.at<uchar>(y,currentX + i) <= 128)
				{
					currentX = currentX + i;
					break;
				}
		}
		img = shiftRow(imgUW, y, currentX - topX);
	}
	return imgUW;
}

Mat warpY(Mat img, Mat imgUW)
{
	int topY; 
	for(int y = 0; y < img.rows; ++y)
	{
		if(img.at<uchar>(y,img.cols - 1) <= 128)
		{
			topY = y;
			break;
		}
		else if(y == img.rows-1)
			return img;
	}
	int currentY = topY;
	for(int x = img.cols - 1; x >= 0; --x)
	{
		for(int i = 0; i < maxShift; ++i)
		{
			if(currentY - i >= 0)
				if(img.at<uchar>(currentY - i,x) <= 128)
				{
					currentY = currentY - i;
					break;
				}
			if(currentY + i < img.rows)
				if(img.at<uchar>(currentY + i,x) <= 128)
				{
					currentY = currentY + i;
					break;
				}
		}
		img = shiftCol(imgUW, x, currentY - topY);
	}
	return imgUW;
}

int main(int argc, char *argv[])
{
	Mat img = imread(IMG, 0);
	Mat imgUW = imread(IMG,0);
	if(argc == 2)
	{
		img = imread(argv[1], 0);
		imgUW = imread(argv[1], 0);
	}
	imshow("Original",img);
	threshold(img, img, 128, 255, THRESH_BINARY);
	imgUW = warpX(img, imgUW);
	imgUW = warpY(img, imgUW);
	//GaussianBlur(imgUW, imgUW, Size(5,5), 0.1);
	//medianBlur(imgUW, imgUW, 3);
	imshow("Unwarped",imgUW);
	waitKey(0);
}
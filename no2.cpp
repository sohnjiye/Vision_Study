#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void on_threshold(int pos, void* userdata);

void erode_dilate(InputArray src, OutputArray dst, InputArray kernel, Point anchor = Point(-1, -1), int iterations = 10, int borderType = BORDER_CONSTANT, const Scalar&
	borderValue = morphologyDefaultBorderValue());

void erode_dilate()
{
	Mat src = imread("computervision_img.png", IMREAD_GRAYSCALE);

	if (src.empty())
	{
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat bin;
	threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);
	Mat dst1, dst2;
	erode(bin, dst1, Mat());
	dilate(bin, dst2, Mat());
	int iterations = 10;

	imshow("src", src);
	imshow("erode", dst1);
	/*imshow("dilate", dst2);*/

	waitKey();
	destroyAllWindows();
}

void open_close()
{
	Mat src = imread("computervision_img.png", IMREAD_GRAYSCALE);

	if (src.empty())
	{
		cerr << "Image load failed!" << endl;
		return;

	}

	Mat bin;
	threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);
	Mat dst1, dst2;
	morphologyEx(src, dst1, MORPH_OPEN, Mat());
	morphologyEx(src, dst2, MORPH_CLOSE, Mat());

	imshow("src", src);
	imshow("bin", bin);
	imshow("erode", dst1);
	imshow("dilate", dst2);

	waitKey();
	destroyAllWindows();
}


int main(int argc, char* argv[])
{
	Mat src;

	/*if (argc < 2)
		src = imread("computervision_img.png", IMREAD_GRAYSCALE);
	else
		src = imread(argv[1], IMREAD_GRAYSCALE);

	if (src.empty())
	{
		cerr << "Image load failed!" << endl;
		return -1;
	}

	imshow("src", src);

	namedWindow("dst");
	createTrackbar("Treshold", "dst", 0, 255, on_threshold, (void*)&src);
	setTrackbarPos("Treshold", "dst", 128);

	waitKey(0);*/
	erode_dilate();
	return 0;
}

void on_threshold(int pos, void * userdata)
{
	Mat src = *(Mat*)userdata;

	Mat dst;
	threshold(src, dst, pos, 255, THRESH_BINARY);

	imshow("dst", dst);
}

void erode_dilate(InputArray src, OutputArray dst, InputArray kernel, Point anchor, int iterations, int borderType, const Scalar & borderValue)
{
}




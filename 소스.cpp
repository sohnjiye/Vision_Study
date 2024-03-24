#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void detect_face()
{
	Mat src = imread("cats.jpg");

	if (src.empty())
	{
		cerr<<"Image load failed!"<<endl;
			return;
	}

	// ����� �� ���� xml haarcascade_frontalcatface ���
	CascadeClassifier classifier("haarcascade_frontalcatface.xml");

	if (classifier.empty())
	{
		cerr << "XML load failed!" << endl;
		return;
	}

	vector<Rect> faces;
	classifier.detectMultiScale(src, faces);

	for (Rect rc : faces)
	{
		rectangle(src, rc, Scalar(255, 0, 255), 2);
	}

	imshow("src", src);

	waitKey(0);
	destroyAllWindows();
}

int main()
{
	detect_face();

}
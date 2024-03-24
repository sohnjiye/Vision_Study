#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

bool mouse_pressing = false;	// ���콺 �ަU��ư ����
bool drawing_mode = true;	// ���� �׸����� ���� (��/�簢��)

// ���ʷ� ���콺 ���� ��ư�� ���� ��ġ ������ ���� ����
int start_x = -1;
int start_y = -1;
int a, b, c;

// ���� ���θ� ä�� ���� ����
Scalar color(255, 255, 255);

Mat img;
RNG rng(9);	// ������ �������� �����ϱ� ����

void mouse_callback(int event, int x, int y, int flags, void *userdata)
{
	if (event == EVENT_MOUSEMOVE)	// ���콺�� �̵��ϴ� �̺�Ʈ�� �߻� �ϸ�
	{
		if (mouse_pressing == true)	// ���콺 ���� ��ư�� ����ä �̵��ϸ�
		{
			if (drawing_mode == true)	// �̵��� ���콺 Ŀ�� ��ġ�� �ݿ��Ͽ� �簢�� or ���׸���
			{

				//�簢��
				rectangle(img, Point(start_x, start_y), Point(x, y), color, -1);
			}
			else
			{
				//��
				circle(img, Point(start_x, start_y), max(abs(start_x - x), abs(start_y - y)), color, -1);
			}
		}
	}
	else if (event == EVENT_LBUTTONDOWN)	// �������� (blue, green, red) �� ���� �� ����
	{
		color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		mouse_pressing = true;	// ���콺 ���� ��ư ���� �� üũ

		// ���콺 ���� ��ư ���� ��ġ ����
		start_x = x;
		start_y = y;
	}
	else if (event == EVENT_LBUTTONUP)	// ���콺 ���� ��ư�� ������ �̺�Ʈ�� �߻��ϸ�
	{
		// ���콺 ���� ��ư���� �ն� ���� üũ
		mouse_pressing = false;
		if (drawing_mode == true)	// ���� ��ư�� ���� ��ġ�� �� �� ��ġ�� ����Ͽ� �簢�� or �� �׸���
		{
			//�簢��
			rectangle(img, Point(start_x, start_y), Point(x, y), color, -1);
		}
		else
		{
			//��
			circle(img, Point(start_x, start_y), max(abs(start_x - x), abs(start_y - y)), color, -1);
		}
	}
	else if (event == EVENT_RBUTTONDOWN)	// ���콺 ������ ��ư�� ������ �̺�Ʈ�� �߻��ϸ�
	{
		drawing_mode = !drawing_mode;
	}
}

int main()
{
	int width = 500;
	int height = 500;

	img = Mat(height, width, CV_8UC3, Scalar(0, 0, 0));

	namedWindow("image");
	setMouseCallback("image", mouse_callback, 0);


	while (1)
	{
		imshow("image", img);

		int key = waitKey(1);
		if (key == 27)
			break;
	}

	destroyAllWindows();

}

#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

bool mouse_pressing = false;	// 마우스 왼쪾버튼 상태
bool drawing_mode = true;	// 현재 그리기모드 상태 (원/사각형)

// 최초로 마우스 왼쪽 버튼을 누른 위치 저장을 위한 변수
int start_x = -1;
int start_y = -1;
int a, b, c;

// 도형 내부를 채울 색상 지정
Scalar color(255, 255, 255);

Mat img;
RNG rng(9);	// 색상을 랜덤으로 설정하기 위함

void mouse_callback(int event, int x, int y, int flags, void *userdata)
{
	if (event == EVENT_MOUSEMOVE)	// 마우스를 이동하는 이벤트가 발생 하면
	{
		if (mouse_pressing == true)	// 마우스 왼쪽 버튼을 누른채 이동하면
		{
			if (drawing_mode == true)	// 이동된 마우스 커서 위치를 반영하여 사각형 or 원그리기
			{

				//사각형
				rectangle(img, Point(start_x, start_y), Point(x, y), color, -1);
			}
			else
			{
				//원
				circle(img, Point(start_x, start_y), max(abs(start_x - x), abs(start_y - y)), color, -1);
			}
		}
	}
	else if (event == EVENT_LBUTTONDOWN)	// 랜덤으로 (blue, green, red) 로 사용될 색 생성
	{
		color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		mouse_pressing = true;	// 마우스 왼쪽 버튼 누른 것 체크

		// 마우스 왼쪽 버튼 누른 위치 저장
		start_x = x;
		start_y = y;
	}
	else if (event == EVENT_LBUTTONUP)	// 마우스 왼쪽 버튼을 누르는 이벤트가 발생하면
	{
		// 마우스 왼쪽 버튼에서 손뗀 것을 체크
		mouse_pressing = false;
		if (drawing_mode == true)	// 왼쪽 버튼을 누른 위치와 손 뗀 위치를 사용하여 사각형 or 원 그리기
		{
			//사각형
			rectangle(img, Point(start_x, start_y), Point(x, y), color, -1);
		}
		else
		{
			//원
			circle(img, Point(start_x, start_y), max(abs(start_x - x), abs(start_y - y)), color, -1);
		}
	}
	else if (event == EVENT_RBUTTONDOWN)	// 마우스 오른쪽 버튼을 누르는 이벤트가 발생하면
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

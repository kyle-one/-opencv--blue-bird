#pragma once
#include <iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
class Grade {

private: 
	int grade;

public:
	int getgrade() { return grade; }
	int count() {
		static int m = 0;
		static int grade = 0;
		m++;
		if (m >=10) {    //ÿʮ��ѭ��������1
			grade++;
			m = m - 10;
		}
		return grade;
	}
	void showcount(Mat frame) {
		String Text1;
		static int gradelock = 1; //����Ϸ����ʱ����֤�������ٸı�
		static int finalcount = 0;
		if (gradelock > 0) {
		 finalcount = count();
		 gradelock--;
		}
		
		Text1 = "Your score is " + to_string(finalcount);
		putText(frame, Text1, Point(185, 100), CV_FONT_HERSHEY_COMPLEX, 1.2, Scalar(0, 0, 255), 1, CV_AA);
	}

};

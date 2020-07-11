#pragma once
#include<opencv2/opencv.hpp>
#include <iostream>
#include <Windows.h>
#include "hinder.h"
#include "source.h"
#include "ui.h"
#include "user.h"
#include "grade.h"
#include "isHit.h"
using namespace cv;

int play() {
	VideoCapture capture;
	capture.open(0);
	if (!capture.isOpened())
	{
		printf("can not open video file   \n");
		return -1;
	}
	Mat frame, dst;
	Mat kernel;
	//����������
	kernel = getStructuringElement(MORPH_RECT, Size(5, 5));


	namedWindow("input", CV_WINDOW_AUTOSIZE);
	namedWindow("output", CV_WINDOW_AUTOSIZE);
	std::vector<std::vector<Point>> contours;
	std::vector<Vec4i> hireachy;
	Rect rect;//������
	Point2f center;
	float radius = 20;
	Point2f a = Point2f(0, 0);
	int i = 1;
	Ui ui1;
	Source src;
	Hinder h1 = Hinder(50, 100, src.uptube, 8, 1, 0, 0);       //�����ϰ������
	Hinder h2 = Hinder(50, 280, src.downtube, 8, 1, 0, 200);
	Hinder h3 = Hinder(50, 150, src.uptube, 8, 1, 0, 0);
	Hinder h4 = Hinder(50, 230, src.downtube, 8, 1, 0, 250);
	Grade G1;
	int T = 0;//ʱ�������

	int flag = 0;//���Ƴ����˳��ı�־
	int flag_2 = 0;
	while (capture.read(frame))//ѭ��������Ƶ֡
	{
		flip(frame, frame, 1);//��Ƶ����ת

		//blur(frame, dst, Size(5,5));
		inRange(frame, Scalar(0, 0, 213), Scalar(255, 128, 255), dst);
		//��ɫͼ��ָ����ͼ�����ޣ����ޣ����ͼ��

		//������
		morphologyEx(dst, dst, MORPH_OPEN, kernel);
		//��ȡ�߽�
		findContours(dst, contours, hireachy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
		//��ѡ������ı߽�
		if (contours.size() > 0)
		{
			double maxArea = 0;
			for (int i = 0; i < contours.size(); i++)
			{
				double area = contourArea(contours[static_cast<int>(i)]);
				if (area > maxArea)
				{
					maxArea = area;
					rect = boundingRect(contours[static_cast<int>(i)]);
					minEnclosingCircle(contours[static_cast<int>(i)], center, radius);

				}
				//center�������ƶ�

					//if (center.x > 10 && center.y > 10)
						//center = center - Point2f(10.0, 10.0);
			}
		}

		/**/
		int flag_play=ui1.choice(center.x, center.y);  //ѡ��ؿ�
		User u1 = User(50, 50, src.userImage);


		//cout << flag_2;
		if (flag_2 == 0) {
			//cout << flag_play;
			ui1.picture(frame, center);
			//User u1 = User(50, 50, src.userImage);
			//u1.show(frame, center);
			u1.show(frame, center);
			if (flag_play == 1) {
				cv::imshow("input", frame);
				cv::imshow("output", dst);

				waitKey(1);
				continue;
			}
			if (flag_play == 2) {
				h1.setSpeed(8);
				h2.setSpeed(8);
				h3.setSpeed(8);
				h4.setSpeed(8);
				flag_2 = 1;
				
			}
			else if (flag_play == 3) {
				h1.setSpeed(10);
				h2.setSpeed(10);
				h3.setSpeed(10);
				h4.setSpeed(10);
				flag_2 = 1;

			}
			else if (flag_play == 4) {
				h1.setSpeed(13);
				h2.setSpeed(13);
				h3.setSpeed(13);
				h4.setSpeed(13);
				flag_2 = 1;

			}
		}

		else {
			ui1.gameui(frame);             //��Ϸ����
			u1.show(frame, center);
			ui1.countdown(frame); //��ʽ��ʼǰ����ʱ
			G1.count();

			h1.hindershow(frame, center, u1, &h2, &h3, &h4);
			ui1.gamecount(frame);
			h1.setT(h1.getT() + 1);
			isHit ishit;

			if (ishit.hited(frame, center, u1, &h1, &h2, &h3, &h4) == 1)
				return -1;


			//���ο�
			//rectangle(frame,rect, Scalar(0,255,0),2);
			//Բ�ο�
			//circle(frame, Point(center.x, center.y), (int)radius, Scalar(0, 255, 0), 2);
			//circle(frame, Point(center.x, center.y), 20, Scalar(0, 255, 0), 2);
			//Դͼ��ָ�룬Բ�����꣬�뾶����ɫ�����
			cv::imshow("input", frame);
			cv::imshow("output", dst);
			waitKey(1);
		}

		
	}

	capture.release();
	return 0;
}
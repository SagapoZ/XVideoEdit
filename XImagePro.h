/**
   ͼ�������
**/
#pragma once
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>


class XImagePro
{
public:
	XImagePro();
	~XImagePro();

	//����ԭͼ��������֮ǰ�Ĵ�����
	void Set(cv::Mat mat1, cv::Mat mat2);
	//��ȡ�����Ľ��
	cv::Mat Get() { return des; }
	//�������ȺͶԱȶ�
	///@para bright double ���� 0~100
	///@para constrast int �Աȶ� 1.0~3.0
	void Gain(double bright, double contrast);
private:
	cv::Mat src1, src2;
	
	//Ŀ��ͼ
	cv::Mat des;
};


/**
   图像处理的类
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

	//设置原图，会清理之前的处理结果
	void Set(cv::Mat mat1, cv::Mat mat2);
	//获取处理后的结果
	cv::Mat Get() { return des; }
	//设置亮度和对比度
	///@para bright double 亮度 0~100
	///@para constrast int 对比度 1.0~3.0
	void Gain(double bright, double contrast);
private:
	cv::Mat src1, src2;
	
	//目标图
	cv::Mat des;
};


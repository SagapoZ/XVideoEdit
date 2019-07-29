#include "XImagePro.h"

void XImagePro::Set(cv::Mat mat1, cv::Mat mat2)
{
	if (mat1.empty()) return;
	this->src1 = mat1;
	this->src2 = mat2;

	//将src1拷贝到des中
	this->src1.copyTo(des);
}

//设置亮度和对比度
	///@para bright double 亮度 0~100
	///@para constrast int 对比度 1.0~3.0
void XImagePro::Gain(double bright, double contrast)
{
	if (des.empty()) return;
	des.convertTo(des, -1, contrast, bright);
}

XImagePro::XImagePro()
{

}


XImagePro::~XImagePro()
{
}

#pragma once
#include <opencv2/core.hpp>
#include <iostream>
#include <vector>

//�����б�
enum XTaskType
{
	XTASK_NONE,
	XTASK_GAIN,  //���ȶԱȶȵ�������
};
//��������
struct XTask
{
	XTaskType type;
	std::vector<double>para; //�洢����
};
//�ӿ���
class XFilter
{
public:
	virtual cv::Mat Filter(cv::Mat mat1, cv::Mat mat2) = 0;
	virtual void Add(XTask task) = 0;
	virtual void Clear() = 0;
	static XFilter *Get();
	virtual ~XFilter();
protected:
	XFilter();
};


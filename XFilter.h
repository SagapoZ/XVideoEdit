#pragma once
#include <opencv2/core.hpp>
#include <iostream>
#include <vector>

//任务列表
enum XTaskType
{
	XTASK_NONE,
	XTASK_GAIN,  //亮度对比度调整任务
};
//处理任务
struct XTask
{
	XTaskType type;
	std::vector<double>para; //存储参数
};
//接口类
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


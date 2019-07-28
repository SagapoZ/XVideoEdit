#include "XVideoThread.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

//定义一个静态变量存储一号视频源
static VideoCapture cap1;
static bool isexit = false;
//打开一号视频源
bool XVideoThread::Open(const std::string file)
{
	cout << "open: "<<file << endl;
	this->mutex.lock();
	int ret = cap1.open(file);
	this->mutex.unlock();
	cout << ret << endl;
	return ret;
}

void XVideoThread::run()
{
	//读取视频
	Mat mat1;
	for (;;)
	{
		this->mutex.lock();
		if (isexit)
		{
			mutex.unlock();
			break;
		}
		//判断视频是否打开
		if (!cap1.isOpened())
		{
			this->mutex.unlock();
			msleep(5);
			continue;
		}
		//读取一帧视频，解码并颜色转换，判断是否成功
		if (!cap1.read(mat1) || mat1.empty())
		{
			this->mutex.unlock();
			msleep(5);
			continue;
		}
		//显示图像
		this->ViewImage1(mat1);
		msleep(40);

		this->mutex.unlock();
	}
}

XVideoThread::XVideoThread()
{
	//启动线程
	start();
}


XVideoThread::~XVideoThread()
{
	mutex.lock();
	isexit = true;
	mutex.unlock();
}

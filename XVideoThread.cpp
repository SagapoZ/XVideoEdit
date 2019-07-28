#include "XVideoThread.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

//����һ����̬�����洢һ����ƵԴ
static VideoCapture cap1;
static bool isexit = false;
//��һ����ƵԴ
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
	//��ȡ��Ƶ
	Mat mat1;
	for (;;)
	{
		this->mutex.lock();
		if (isexit)
		{
			mutex.unlock();
			break;
		}
		//�ж���Ƶ�Ƿ��
		if (!cap1.isOpened())
		{
			this->mutex.unlock();
			msleep(5);
			continue;
		}
		//��ȡһ֡��Ƶ�����벢��ɫת�����ж��Ƿ�ɹ�
		if (!cap1.read(mat1) || mat1.empty())
		{
			this->mutex.unlock();
			msleep(5);
			continue;
		}
		//��ʾͼ��
		this->ViewImage1(mat1);
		msleep(40);

		this->mutex.unlock();
	}
}

XVideoThread::XVideoThread()
{
	//�����߳�
	start();
}


XVideoThread::~XVideoThread()
{
	mutex.lock();
	isexit = true;
	mutex.unlock();
}

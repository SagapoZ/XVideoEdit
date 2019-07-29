#include "XVideoThread.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include "XFilter.h"
using namespace cv;
using namespace std;

//定义一个静态变量存储一号视频源
static VideoCapture cap1;
static bool isexit = false;
//保存视频
static VideoWriter vw;

//开始保存视频
bool XVideoThread::StartSave(const std::string filename, int width, int height)
{
	cout << "开始导出" << endl;
	Seek(0);
	mutex.lock();
	if (!cap1.isOpened())
	{
		mutex.unlock();
		return false;
	}
	if (width <= 0)
	{
		width = cap1.get(CAP_PROP_FRAME_WIDTH);

	}
	if (height <= 0)
	{
		height = cap1.get(CAP_PROP_FRAME_HEIGHT);
	}
	vw.open(filename,
		VideoWriter::fourcc('X', '2', '6', '4'),
		fps,
		Size(width,height)
		);
	if (!vw.isOpened())
	{
		cout << "start save failed!" << endl;
		mutex.unlock();
		return false;
	}

	this->isWrite = true;

	mutex.unlock();
	return true;
}

//停止保存视频，写入视频帧的索引
void XVideoThread::StopSave()
{
	cout << "停止导出" << endl;
	mutex.lock();
	vw.release();
	isWrite = false;
	mutex.unlock();
}

//设置播放进度
bool XVideoThread::Seek(int frame)
{
	mutex.lock();
	if (!cap1.isOpened())
	{
		mutex.unlock();
		return false;
	}
	//跳到设置的帧
	int re = cap1.set(CAP_PROP_POS_FRAMES, frame);
	mutex.unlock();
	return re;
}
//重写Seek
bool XVideoThread::Seek(double pos)
{
	double count = cap1.get(CAP_PROP_FRAME_COUNT);
	int frame = pos*count;
	return Seek(frame);
}

//返回当前播放的位置
double XVideoThread::GetPos()
{
	double pos = 0;
	mutex.lock();
	if (!cap1.isOpened())
	{
		mutex.unlock();
		return pos;
	}
	//总帧数和当前位置，算出时间
	double count = cap1.get(CAP_PROP_FRAME_COUNT);
	double cur = cap1.get(CAP_PROP_POS_FRAMES);
	if (count > 0.001)
	{
		pos = cur / count;
	}

	mutex.unlock();

	return pos;
}
//打开一号视频源
bool XVideoThread::Open(const std::string file)
{
	cout << "open: "<<file << endl;
	this->mutex.lock();
	int ret = cap1.open(file);
	this->mutex.unlock();
	cout << ret << endl;
	if (!ret)
		return ret;
	fps = cap1.get(CAP_PROP_FPS);
	if (fps <= 0) fps = 25;

	return true;
}

void XVideoThread::run()
{
	//读取视频
	Mat mat1;
	for (;;)
	{
		this->mutex.lock();
		//判断是否执行了析构函数
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
		if (!cap1.read(mat1) || mat1.empty()) //不成功时
		{
			this->mutex.unlock();
			//导出到结尾时停止导出
			if (isWrite)  //导出完毕
			{
				StopSave();
				SaveEnd();
			}
			msleep(5);
			continue;
		}
		//显示图像1的信号
		if(!isWrite)   //没有导出时，播放视频
			ViewImage1(mat1);

		//视频传入过滤器进行设置
		Mat des = XFilter::Get()->Filter(mat1, Mat());
		//显示处理后的图像,发送显示目标图的信号
		if (!isWrite)
			ViewDes(des);

		int s = 0;
		s = 1000 / fps;

		if (isWrite)  //如果在导出
		{
			//开始写入
			s = 1;
			vw.write(des);
		}
		//通过fps设置播放速度
		msleep(s);

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
	wait();
}



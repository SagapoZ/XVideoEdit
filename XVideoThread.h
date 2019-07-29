#pragma once
#include <QThread>
#include <QMutex>
#include <string>
#include <opencv2/core.hpp>

class XVideoThread:public QThread
{
	Q_OBJECT

public:
	int fps;

	~XVideoThread();

	static XVideoThread*Get()
	{
		static XVideoThread vt;
		return &vt;
	}
	//打开视频源
	bool Open(const std::string file);
	
	//返回当前播放的位置
	double GetPos();

	//跳转视频的播放进度
	///@para frame int 帧位置
	bool Seek(int frame);
	bool Seek(double pos);
	//线程入口函数
	void run();

	//开始保存视频
	bool StartSave(const std::string filename, int width=0, int height=0);

	//停止保存视频，写入视频帧的索引
	void StopSave();

	//添加信号函数
signals:
	//显示原视频1的信号
	void ViewImage1(cv::Mat mat);
	//显示目标视频的信号
	void ViewDes(cv::Mat mat);
	void SaveEnd();

protected:
	//单例模式
	XVideoThread();
	QMutex mutex;
	//是否需要写
	bool isWrite = false;

};


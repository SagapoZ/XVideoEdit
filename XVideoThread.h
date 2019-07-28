#pragma once
#include <QThread>
#include <QMutex>
#include <string>
#include <opencv2/core.hpp>

class XVideoThread:public QThread
{
	Q_OBJECT

public:
	~XVideoThread();

	static XVideoThread*Get()
	{
		static XVideoThread vt;
		return &vt;
	}
	//打开视频源
	bool Open(const std::string file);
	//线程入口函数
	void run();

	//添加信号函数
signals:
	void ViewImage1(cv::Mat mat);

protected:
	//单例模式
	XVideoThread();
	QMutex mutex;
};


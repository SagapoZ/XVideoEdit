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
	//����ƵԴ
	bool Open(const std::string file);
	//�߳���ں���
	void run();

	//����źź���
signals:
	void ViewImage1(cv::Mat mat);

protected:
	//����ģʽ
	XVideoThread();
	QMutex mutex;
};


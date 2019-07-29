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
	//����ƵԴ
	bool Open(const std::string file);
	
	//���ص�ǰ���ŵ�λ��
	double GetPos();

	//��ת��Ƶ�Ĳ��Ž���
	///@para frame int ֡λ��
	bool Seek(int frame);
	bool Seek(double pos);
	//�߳���ں���
	void run();

	//��ʼ������Ƶ
	bool StartSave(const std::string filename, int width=0, int height=0);

	//ֹͣ������Ƶ��д����Ƶ֡������
	void StopSave();

	//����źź���
signals:
	//��ʾԭ��Ƶ1���ź�
	void ViewImage1(cv::Mat mat);
	//��ʾĿ����Ƶ���ź�
	void ViewDes(cv::Mat mat);
	void SaveEnd();

protected:
	//����ģʽ
	XVideoThread();
	QMutex mutex;
	//�Ƿ���Ҫд
	bool isWrite = false;

};


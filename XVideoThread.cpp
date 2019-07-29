#include "XVideoThread.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include "XFilter.h"
using namespace cv;
using namespace std;

//����һ����̬�����洢һ����ƵԴ
static VideoCapture cap1;
static bool isexit = false;
//������Ƶ
static VideoWriter vw;

//��ʼ������Ƶ
bool XVideoThread::StartSave(const std::string filename, int width, int height)
{
	cout << "��ʼ����" << endl;
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

//ֹͣ������Ƶ��д����Ƶ֡������
void XVideoThread::StopSave()
{
	cout << "ֹͣ����" << endl;
	mutex.lock();
	vw.release();
	isWrite = false;
	mutex.unlock();
}

//���ò��Ž���
bool XVideoThread::Seek(int frame)
{
	mutex.lock();
	if (!cap1.isOpened())
	{
		mutex.unlock();
		return false;
	}
	//�������õ�֡
	int re = cap1.set(CAP_PROP_POS_FRAMES, frame);
	mutex.unlock();
	return re;
}
//��дSeek
bool XVideoThread::Seek(double pos)
{
	double count = cap1.get(CAP_PROP_FRAME_COUNT);
	int frame = pos*count;
	return Seek(frame);
}

//���ص�ǰ���ŵ�λ��
double XVideoThread::GetPos()
{
	double pos = 0;
	mutex.lock();
	if (!cap1.isOpened())
	{
		mutex.unlock();
		return pos;
	}
	//��֡���͵�ǰλ�ã����ʱ��
	double count = cap1.get(CAP_PROP_FRAME_COUNT);
	double cur = cap1.get(CAP_PROP_POS_FRAMES);
	if (count > 0.001)
	{
		pos = cur / count;
	}

	mutex.unlock();

	return pos;
}
//��һ����ƵԴ
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
	//��ȡ��Ƶ
	Mat mat1;
	for (;;)
	{
		this->mutex.lock();
		//�ж��Ƿ�ִ������������
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
		if (!cap1.read(mat1) || mat1.empty()) //���ɹ�ʱ
		{
			this->mutex.unlock();
			//��������βʱֹͣ����
			if (isWrite)  //�������
			{
				StopSave();
				SaveEnd();
			}
			msleep(5);
			continue;
		}
		//��ʾͼ��1���ź�
		if(!isWrite)   //û�е���ʱ��������Ƶ
			ViewImage1(mat1);

		//��Ƶ�����������������
		Mat des = XFilter::Get()->Filter(mat1, Mat());
		//��ʾ������ͼ��,������ʾĿ��ͼ���ź�
		if (!isWrite)
			ViewDes(des);

		int s = 0;
		s = 1000 / fps;

		if (isWrite)  //����ڵ���
		{
			//��ʼд��
			s = 1;
			vw.write(des);
		}
		//ͨ��fps���ò����ٶ�
		msleep(s);

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
	wait();
}



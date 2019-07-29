#include "XVideoUI.h"
#include <QFileDialog>
#include <string>
#include <QMessageBox>
#include "XVideoThread.h"
#include "XVideoWidget.h"
#include "XFilter.h"
#include <iostream>
using namespace std;

static bool pressSlider = false;
static bool isExport = false;

XVideoUI::XVideoUI(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//���ر�����
	setWindowFlags(Qt::FramelessWindowHint);

	//����1�ۺ���
	qRegisterMetaType<cv::Mat>("cv::Mat");

	QObject::connect(XVideoThread::Get(),
		SIGNAL(ViewImage1(cv::Mat)),
		ui.src1video,
		SLOT(SetImage(cv::Mat))
		);
	//����2�ۺ���
	QObject::connect(XVideoThread::Get(),
		SIGNAL(ViewDes(cv::Mat)),
		ui.des,
		SLOT(SetImage(cv::Mat))
	);
	//����3�ۺ���
	QObject::connect(XVideoThread::Get(),
		SIGNAL(SaveEnd()),
		this,
		SLOT(ExportEnd())
	);
	startTimer(40);
}

//��д��ʱ��ʱ�亯��������ʾ��ǰ���ŵ��Ľ���
void XVideoUI::timerEvent(QTimerEvent *e)
{
	if (pressSlider == true) return;

	double pos = XVideoThread::Get()->GetPos();
	ui.playSlider->setValue(pos * 1000);
}


void XVideoUI::Open()
{
	QString name = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("ѡ����Ƶ�ļ�"));
	if (name.isEmpty()) return;

	string file = name.toLocal8Bit().data();
	if (!XVideoThread::Get()->Open(file))
	{
		QMessageBox::information(this, "error", name + "open failed!");
		return;
	}
	//QMessageBox::information(this, "success", name);

}



//����������
void XVideoUI::SliderPress()
{
	pressSlider = true;
}
void XVideoUI::SliderRelease()
{
	pressSlider = false;
}
//�϶����϶�
void XVideoUI::SetPos(int pos)
{
	XVideoThread::Get()->Seek((double)pos/1000);
}
//���ù�����
void XVideoUI::Set()
{
	XFilter::Get()->Clear();
	//���öԱȶȺ�����
	if (ui.bright->value() > 0 ||
		ui.contrast->value() > 1)
	{
		//�������
		XFilter::Get()->Add(XTask{ XTASK_GAIN,
			{(double)ui.bright->value(),ui.contrast->value()} 
			});
	}

}
//��������
void XVideoUI::ExportEnd()
{
	isExport = false;
	cout << "��������" << endl;
	ui.exportBt->setText("Start Export");
}
//������Ƶ
void XVideoUI::Export()
{
	
	if (isExport)
	{
		//ֹͣ����
		XVideoThread::Get()->StopSave();
		isExport = false;
		ui.exportBt->setText("Start Export");
		return;
	}
	QString name = QFileDialog::getSaveFileName(this, "save", "out1.avi");
	if (name.isEmpty()) return;
	std::string filename = name.toLocal8Bit().data();
	
	//�����ɹ�
	if (XVideoThread::Get()->StartSave(filename))
	{
		isExport = true;
		ui.exportBt->setText("Stop Export");
	}

}



void XVideoUI::mouseMoveEvent(QMouseEvent *event)
{
	QWidget::mouseMoveEvent(event);

	QPoint y = event->globalPos();

	QPoint x = y - this->z;

	this->move(x);
}
void XVideoUI::mousePressEvent(QMouseEvent *event)
{
	QWidget::mousePressEvent(event);

	QPoint y = event->globalPos(); //���������������Ͻǵ�λ��
	QPoint x = this->geometry().topLeft(); //����������������Ͻǵ�λ��
	this->z = y - x;   //�������ڴ������Ͻǵ�λ�ã���ֵ
}
void XVideoUI::mouseReleaseEvent(QMouseEvent *event)
{
	QWidget::mouseReleaseEvent(event);
	this->z = QPoint();
}
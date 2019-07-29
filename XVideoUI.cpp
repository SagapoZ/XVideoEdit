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
	//隐藏标题栏
	setWindowFlags(Qt::FramelessWindowHint);

	//关联1槽函数
	qRegisterMetaType<cv::Mat>("cv::Mat");

	QObject::connect(XVideoThread::Get(),
		SIGNAL(ViewImage1(cv::Mat)),
		ui.src1video,
		SLOT(SetImage(cv::Mat))
		);
	//关联2槽函数
	QObject::connect(XVideoThread::Get(),
		SIGNAL(ViewDes(cv::Mat)),
		ui.des,
		SLOT(SetImage(cv::Mat))
	);
	//关联3槽函数
	QObject::connect(XVideoThread::Get(),
		SIGNAL(SaveEnd()),
		this,
		SLOT(ExportEnd())
	);
	startTimer(40);
}

//重写定时器时间函数，来显示当前播放到的进度
void XVideoUI::timerEvent(QTimerEvent *e)
{
	if (pressSlider == true) return;

	double pos = XVideoThread::Get()->GetPos();
	ui.playSlider->setValue(pos * 1000);
}


void XVideoUI::Open()
{
	QString name = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("选择视频文件"));
	if (name.isEmpty()) return;

	string file = name.toLocal8Bit().data();
	if (!XVideoThread::Get()->Open(file))
	{
		QMessageBox::information(this, "error", name + "open failed!");
		return;
	}
	//QMessageBox::information(this, "success", name);

}



//滑动条设置
void XVideoUI::SliderPress()
{
	pressSlider = true;
}
void XVideoUI::SliderRelease()
{
	pressSlider = false;
}
//拖动条拖动
void XVideoUI::SetPos(int pos)
{
	XVideoThread::Get()->Seek((double)pos/1000);
}
//设置过滤器
void XVideoUI::Set()
{
	XFilter::Get()->Clear();
	//设置对比度和亮度
	if (ui.bright->value() > 0 ||
		ui.contrast->value() > 1)
	{
		//添加任务
		XFilter::Get()->Add(XTask{ XTASK_GAIN,
			{(double)ui.bright->value(),ui.contrast->value()} 
			});
	}

}
//导出结束
void XVideoUI::ExportEnd()
{
	isExport = false;
	cout << "导出结束" << endl;
	ui.exportBt->setText("Start Export");
}
//导出视频
void XVideoUI::Export()
{
	
	if (isExport)
	{
		//停止导出
		XVideoThread::Get()->StopSave();
		isExport = false;
		ui.exportBt->setText("Start Export");
		return;
	}
	QString name = QFileDialog::getSaveFileName(this, "save", "out1.avi");
	if (name.isEmpty()) return;
	std::string filename = name.toLocal8Bit().data();
	
	//导出成功
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

	QPoint y = event->globalPos(); //鼠标相对于桌面左上角的位置
	QPoint x = this->geometry().topLeft(); //窗口相对于桌面左上角的位置
	this->z = y - x;   //鼠标相对于窗口左上角的位置，定值
}
void XVideoUI::mouseReleaseEvent(QMouseEvent *event)
{
	QWidget::mouseReleaseEvent(event);
	this->z = QPoint();
}
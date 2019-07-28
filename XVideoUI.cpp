#include "XVideoUI.h"
#include <QFileDialog>
#include <string>
#include <QMessageBox>
#include "XVideoThread.h"
#include "XVideoWidget.h"

using namespace std;

XVideoUI::XVideoUI(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//隐藏标题栏
	setWindowFlags(Qt::FramelessWindowHint);

	//关联槽函数
	qRegisterMetaType<cv::Mat>("cv::Mat");
	QObject::connect(XVideoThread::Get(),
		SIGNAL(ViewImage1(cv::Mat)),
		ui.src1video,
		SLOT(SetImage(cv::Mat))
		);
	
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



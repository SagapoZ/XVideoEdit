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
	//���ر�����
	setWindowFlags(Qt::FramelessWindowHint);

	//�����ۺ���
	qRegisterMetaType<cv::Mat>("cv::Mat");
	QObject::connect(XVideoThread::Get(),
		SIGNAL(ViewImage1(cv::Mat)),
		ui.src1video,
		SLOT(SetImage(cv::Mat))
		);
	
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



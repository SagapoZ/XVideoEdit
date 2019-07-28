#pragma once
#include<QOpenGLWidget.h>
#include <opencv2/core.hpp>

class XVideoWidget:public QOpenGLWidget
{
	Q_OBJECT

public:
	XVideoWidget(QWidget *p);
	virtual ~XVideoWidget();
	void paintEvent(QPaintEvent*e);

public slots:
	void SetImage(cv::Mat mat);

protected:
	QImage img;
};


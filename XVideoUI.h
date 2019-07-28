#pragma once

#include <QtWidgets/QWidget>
#include "ui_XVideoUI.h"
#include <QPoint>
#include <QMouseEvent>


class XVideoUI : public QWidget
{
	Q_OBJECT

public:
	XVideoUI(QWidget *parent = Q_NULLPTR);

	//鼠标时间函数，控制窗口拖动
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

public slots:
	//打开视频的槽函数
	void Open();

private:
	Ui::XVideoUIClass ui;
	QPoint z;
};

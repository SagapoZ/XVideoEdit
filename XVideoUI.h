#pragma once

#include <QtWidgets/QWidget>
#include "ui_XVideoUI.h"
#include <QPoint>
#include <QMouseEvent>
#include <QTimer>

class XVideoUI : public QWidget
{
	Q_OBJECT

public:
	XVideoUI(QWidget *parent = Q_NULLPTR);

	//鼠标时间函数，控制窗口拖动
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

	//重载定时器函数
	void timerEvent(QTimerEvent *e);
public slots:
	//打开视频的槽函数
	void Open();
	void SliderPress();
	void SliderRelease();
	//互动条拖动
	void SetPos(int);
	//设置过滤器
	void Set();
	//导出视频
	void Export();
	//结束导出
	void ExportEnd();

private:
	Ui::XVideoUIClass ui;
	QPoint z;
};

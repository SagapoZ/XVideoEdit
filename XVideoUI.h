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

	//���ʱ�亯�������ƴ����϶�
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

public slots:
	//����Ƶ�Ĳۺ���
	void Open();

private:
	Ui::XVideoUIClass ui;
	QPoint z;
};

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

	//���ʱ�亯�������ƴ����϶�
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

	//���ض�ʱ������
	void timerEvent(QTimerEvent *e);
public slots:
	//����Ƶ�Ĳۺ���
	void Open();
	void SliderPress();
	void SliderRelease();
	//�������϶�
	void SetPos(int);
	//���ù�����
	void Set();
	//������Ƶ
	void Export();
	//��������
	void ExportEnd();

private:
	Ui::XVideoUIClass ui;
	QPoint z;
};

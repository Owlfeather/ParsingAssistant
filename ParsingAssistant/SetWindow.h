#pragma once

#include <QWidget>
#include "ui_SetWindow.h"
#include "TestWindow.h"

class SetWindow : public QWidget
{
	Q_OBJECT

public:
	SetWindow(QWidget* parent = Q_NULLPTR);
	~SetWindow();

private:
	Ui::SetWindow ui;
	TestWindow* t_win;

signals:
	void sWindowClosed();

private slots:
	void onBackClicked();
	void onStartClicked();
	//void onClosedClicked();

protected:
	void closeEvent(QCloseEvent* event);
	void setTestWinParams();

};

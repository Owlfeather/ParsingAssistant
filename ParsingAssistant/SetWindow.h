#pragma once

#include <QWidget>
#include "ui_SetWindow.h"

class SetWindow : public QWidget
{
	Q_OBJECT

public:
	SetWindow(QWidget* parent = Q_NULLPTR);
	~SetWindow();

private:
	Ui::SetWindow ui;

signals:
	void sWindowClosed();

private slots:
	void onBackClicked();
	//void onClosedClicked();

protected:
	void closeEvent(QCloseEvent* event);

};

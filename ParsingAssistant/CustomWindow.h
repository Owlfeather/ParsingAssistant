#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CustomWindow.h"


class CustomWindow : public QMainWindow
{
	Q_OBJECT

public:
	CustomWindow(QWidget *parent = Q_NULLPTR);

private:
	Ui::MainWindow ui;

//private slots:
	//void onExitClicked();
};

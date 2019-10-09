#pragma once

#include <QtWidgets/QMainWindow>
//#include "ui_ParsingAssistant.h"
#include "ui_MainMenu.h"
#include"CWindow.h"
#include <iostream>
//#include <RulesManager.h>


class MainMenu : public QMainWindow
{
	Q_OBJECT

public:
	MainMenu(QWidget *parent = Q_NULLPTR);

private:
	Ui::MainWindow ui;
	CWindow * c_win;

private slots:
	void onExitClicked();
	void onLtoRClicked();
	void onTtoDClicked();
};

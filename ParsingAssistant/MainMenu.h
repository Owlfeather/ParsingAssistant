#pragma once

#include <QtWidgets/QMainWindow>
//#include "ui_ParsingAssistant.h"
#include "ui_MainMenu.h"
#include"CWindow.h"
//#include"IWindow.h"

#include <iostream>
//#include <RulesManager.h>


class MainMenu : public QMainWindow
{
	Q_OBJECT

public:
	MainMenu(QWidget *parent = Q_NULLPTR);
	~MainMenu();

private:
	Ui::MainWindow ui;
	CWindow * c_win;
	//IWindow * i_win;

private slots:
	void onExitClicked();
	void onLtoRClicked();
	void onTtoDClicked();
	void onLLkTtoDClicked();
	void onHelpClicked();

protected:
	void closeEvent(QCloseEvent* event);

};

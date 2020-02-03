#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainMenu.h"
#include"CWindow.h"
#include <iostream>


class MainMenu : public QMainWindow
{
	Q_OBJECT

public:
	MainMenu(QWidget *parent = Q_NULLPTR);
	~MainMenu();

private:
	Ui::MainWindow ui;
	CWindow * c_win;

private slots:
	void onExitClicked();
	void onLtoRClicked();
	void onTtoDClicked();
	void onLLkTtoDClicked();
	void onLRkStackClicked();
	void onHelpClicked();

protected:
	void closeEvent(QCloseEvent* event);

};

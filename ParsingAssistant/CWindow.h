#pragma once

#include <QWidget>
#include "ui_CWindow.h"


class CWindow : public QWidget
{
	Q_OBJECT

public:
	CWindow(QWidget *parent = Q_NULLPTR);
	~CWindow();
	void RenderCWin(unsigned type);
	void SetType(unsigned inp_alg_type);

private:
	Ui::Form ui;
	unsigned alg_type;

signals:
	void mainMenu();

private slots:
	void onBackClicked();
};

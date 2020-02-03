#pragma once

#include <QWidget>
#include <qfile.h>
#include "ui_IWindow.h"
#include "Basic_Elements.h"


class IWindow : public QWidget
{
	Q_OBJECT

public:
	IWindow(QWidget* parent = Q_NULLPTR);
	~IWindow();

	void SetHelpInfo();
	void SetAlgorithmInfo(TypeOfAlg alg_type);
	

private:
	Ui::Form1 ui;

signals:

private slots:
	void onClosedClicked();
};
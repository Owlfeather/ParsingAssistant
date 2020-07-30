#pragma once

#include <QWidget>
#include <qfile.h>
#include "ui_InfWindow.h"
#include "Basic_Elements.h"


class InfWindow : public QWidget
{
	Q_OBJECT

public:
	InfWindow(QWidget* parent = Q_NULLPTR);
	~InfWindow();

	void SetHelpInfo();
	void SetAlgorithmInfo(TypeOfAlg alg_type);


private:
	Ui::Form2 ui;

signals:

private slots:
	void onClosedClicked();
};

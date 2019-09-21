#pragma once

#include <QWidget>
#include "ui_CWindow.h"
#include "Algorithm_LtoR.h"
#include "Algorithm_TtoD.h"
#include "LogTable.h"


class CWindow : public QWidget
{
	Q_OBJECT

public:
	CWindow(QWidget *parent = Q_NULLPTR);
	~CWindow();
	void RenderCWin(unsigned type);
	void SetAlgorithm(unsigned inp_alg_type);
	void DrawRules();
	void ChangeColor(unsigned i, unsigned j);

private:
	Ui::Form ui;
	unsigned alg_type;
	std::vector<std::vector<QLabel *>> drawed_rules;
	ParseAlgorithm* algorithm;
	//LogTable* log_table;


signals:
	void cWindowClosed();

private slots:
	void onBackClicked();
	void onParseModeClicked();
	void onStartClicked();
};

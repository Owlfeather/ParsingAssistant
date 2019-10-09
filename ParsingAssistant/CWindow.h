#pragma once

#include <QWidget>
#include "ui_CWindow.h"
#include "Algorithm_LtoR.h"
#include "Algorithm_TtoD.h"
//#include "LogTable.h"
#include <iostream>
#include "RulesManager.h"



class CWindow : public QWidget
{
	Q_OBJECT

public:
	CWindow(QWidget *parent = Q_NULLPTR);
	~CWindow();
	void RenderCWin(ModeOfCWin type);
	void SetAlgorithm(TypeOfAlg inp_alg_type);
	void DrawRules();
	void ChangeColor(unsigned i, unsigned j, Color inp_color);

private:
	Ui::Form ui;
	QScrollBar* scrollbar_table;
	QScrollBar* scrollbar_comments;
	RulesManager* rules_manager;
	//-----------------------------
	TypeOfAlg alg_type;
	std::vector<std::vector<QLabel *>> drawed_rules;
	ParseAlgorithm* algorithm;

	RuleNum cur_rule;
	RuleNum prev_rule;
	int cur_table_row;
	int cur_comment_row;
	//int 
	//bool rollback;
	//LogTable* log_table;

	void HideRows();


signals:
	void cWindowClosed();

private slots:
	void onBackClicked();
	void onParseModeClicked();
	void onStartClicked();
	void onStepClicked();
	void onShowAllClicked();
};

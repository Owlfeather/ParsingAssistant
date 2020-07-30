#pragma once

#include <QWidget>
#include "ui_CWindow.h"
#include "Algorithm_LtoR.h"
#include "Algorithm_TtoD.h"
#include "Algorithm_LLk_TtoD.h"
#include "Algorithm_LRk_Stack.h"
#include "IWindow.h"
#include "InfWindow.h"
#include <iostream>
#include "RulesManager.h"
#include "StringGenerator.h"
#include <QRandomGenerator>




class CWindow : public QWidget
{
	Q_OBJECT

public:
	CWindow(QWidget *parent = Q_NULLPTR);
	~CWindow();
	void RenderCWin(ModeOfCWin type);
	void SetAlgorithm(TypeOfAlg inp_alg_type);
	void DrawRules();
	InfWindow* GetIWin() { return i_win;  };


private:
	Ui::Form ui;
	InfWindow* i_win;

	QScrollBar* scrollbar_table;
	QScrollBar* scrollbar_comments;
	RulesManager* rules_manager;
	TestStringGenerator* string_generator;
	//-----------------------------
	TypeOfAlg alg_type;
	ParseAlgorithm* algorithm;


	void HideRows();


signals:
	void cWindowClosed();

private slots:
	void onBackClicked();
	void onParseModeClicked();
	void onStartClicked();
	void onStepClicked();
	void onShowAllClicked();
	void onRepeatClicked();
	void onNewParseClicked();
	void onInformClicked();
	void onGenCorClicked();
	void onGenIncorClicked();
	void onGenRandClicked();

protected:
	void closeEvent(QCloseEvent* event);
	
};

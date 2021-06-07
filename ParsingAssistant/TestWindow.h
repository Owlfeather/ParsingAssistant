#pragma once

#include <QWidget>
#include "ui_TestWindow.h"
#include "Algorithm_LtoR_u.h"
#include "AnsTable.h"

class TestWindow : public QWidget
{
	Q_OBJECT

public:
	TestWindow(QWidget* parent = Q_NULLPTR);
	~TestWindow();
	void setTestParams(unsigned t_num, TypeOfAlg a_type);

	QLayout* DrawRules(const std::vector<ItemRule>& rules);

private:
	Ui::TestWindow ui;
	unsigned task_num;
	TypeOfAlg alg_type;

	unsigned ans_step;
	AnsTable* ans_table;
	vector<vector<QLabel*>> my_rules;

signals:
	void tWindowClosed();

private slots:
	void onBackClicked();
	void onEndClicked();

	void setTest();
	
	//void onClosedClicked();

protected:
	void closeEvent(QCloseEvent* event);

};
#pragma once
#pragma once

#include <QWidget>
#include "ui_EdWindow.h"
#include "RulesEditorManager.h"
#include "ConfWindow.h"

class EdWindow : public QWidget
{
	Q_OBJECT

public:
	EdWindow(QWidget* parent = Q_NULLPTR);
	~EdWindow();

	vector<ItemRule> rules;
	QVBoxLayout* main_layout;

private:
	Ui::EdWindow ui;
	RulesEditorManager* rules_editor_manager;
	ConfWindow* confirmation_window;

	void SaveRulesAsXML(QString fileName);
	void LoadRulesFromXML(QString fileName);
	void ShowInfoMessage(EditorInfoMessageType info_type);


signals:
	void edWindowClosed();

private slots:
	void onBackClicked();
	void onAddRuleClicked();
	void onSaveClicked();
	void onLoadClicked();
	void checkFocusChange(QWidget* old, QWidget* now);
	void axiomChosen();
	void timeIsUp();

protected:
	void closeEvent(QCloseEvent* event);
};


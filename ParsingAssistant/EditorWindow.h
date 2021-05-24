#pragma once
#pragma once

#include <QWidget>
#include "ui_EditorWindow.h"
#include "Alg_Elements_u.h"

//#include "RulesEditorManager.h"
//#include "ConfirmationWindow.h"

class EditorWindow : public QWidget
{
    Q_OBJECT

public:
    vector<ItemRule> rules;
    QVBoxLayout* main_layout;
    EditorWindow(QWidget* parent = Q_NULLPTR);

private:
    Ui::EditorWindow ui;
    //RulesEditorManager* rules_editor_manager;
    //ConfirmationWindow* confirmation_window;

    //void SaveRulesAsXML(QString fileName);
    //void LoadRulesFromXML(QString fileName);
    //void ShowInfoMessage(EditorInfoMessageType info_type);

private slots:
    //void onAddRuleClicked();
    //void onSaveClicked();
   // void onLoadClicked();
    //void checkFocusChange(QWidget* old, QWidget* now);
    //void axiomChosen();
    //void timeIsUp();

};

#pragma once

#include <QWidget>
#include "ui_ConfWindow.h"

class ConfWindow : public QWidget
{
    Q_OBJECT

public:
    std::vector<QString> rules;

    ConfWindow(QWidget* parent = Q_NULLPTR);
    //void SetParentWindow(QWidget* parent) { parent_window = parent; }
    void ShowRules(const QString& rules_text);
    void ShowRecType(const QString& rec_type);
    void AddNonterminalsToComboBox(std::vector<QString>& nonterminals);
    void SetAxiom(){ axiom = ui.axiomChooseComboBox->currentText(); }
    const QString& GetAxiom() { return axiom; }
    void ClearComboBox() { ui.axiomChooseComboBox->clear(); }

private:
    Ui::ConfWindow ui;
    //QWidget* parent_window;
    QString axiom;

signals:
    void acception();

private slots:
    void onAcceptionClicked();
    void onRejectionClicked();

};

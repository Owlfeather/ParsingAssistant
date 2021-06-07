#include "ConfWindow.h"
#include <QTextCodec>
#include <QMessageBox>
#include <QTimer>

#define RUS( str ) codec->toUnicode(str)

ConfWindow::ConfWindow(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    connect(ui.okButton, SIGNAL(clicked()), this, SLOT(onAcceptionClicked()));
    connect(ui.cancelButton, SIGNAL(clicked()), this, SLOT(onRejectionClicked()));
}

void ConfWindow::ShowRules(const QString& rules_text)
{
    ui.textBrowser->setText(rules_text);
}

void ConfWindow::ShowRecType(const QString& rec_type)
{
    ui.recursionTypeLabel->setText(rec_type);
}

void ConfWindow::AddNonterminalsToComboBox(std::vector<QString>& nonterminals)
{
    ClearComboBox();
    for (int i = 0; i < nonterminals.size(); i++) {
        ui.axiomChooseComboBox->addItem(nonterminals[i]);
    }
}

void ConfWindow::onRejectionClicked()
{
    hide();
}

void ConfWindow::onAcceptionClicked()
{
    SetAxiom();
    emit acception();
}
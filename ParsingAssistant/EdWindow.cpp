#include "EdWindow.h"
#include <QTextCodec>
#include <QString>
#include <QFileDialog>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QMessageBox>
#include <QTimer>
#include <QMessageBox>
#include <QColorDialog>
#include <QAbstractItemView>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QMouseEvent>

#define RUS( str ) codec->toUnicode(str)


EdWindow::EdWindow(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	rules_editor_manager = new RulesEditorManager;
	ui.scrollArea->setWidgetResizable(true);
	main_layout = rules_editor_manager->DrawBasicForms(); ///////////////////
	ui.groupBox_rules->setLayout(main_layout);

	//connect(ui.btnClose, SIGNAL(clicked()), this, SLOT(onClosedClicked()));
	connect(ui.btnBack, SIGNAL(clicked()), this, SLOT(onBackClicked()));
	connect(ui.addRuleButton, SIGNAL(clicked()), this, SLOT(onAddRuleClicked()));
	connect(ui.saveButton, SIGNAL(clicked()), this, SLOT(onSaveClicked()));
	connect(ui.loadButton, SIGNAL(clicked()), this, SLOT(onLoadClicked()));

	QApplication* app = static_cast<QApplication*>(QApplication::instance());
	connect(app, SIGNAL(focusChanged(QWidget*, QWidget*)), this, SLOT(checkFocusChange(QWidget*, QWidget*)));

	confirmation_window = new ConfWindow;
	// confirmation_window->SetParentWindow(this);
	confirmation_window->hide();

	connect(confirmation_window, SIGNAL(acception()), this, SLOT(axiomChosen()));
	ui.infoLabel->setText("");
}

EdWindow::~EdWindow()
{
}

void EdWindow::SaveRulesAsXML(QString fileName)
{
    QTextCodec* codec = QTextCodec::codecForName("Windows-1251");

    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    QXmlStreamWriter xmlWriter(&file);

    xmlWriter.setAutoFormatting(true);  // ������������� ������������������ ������
    xmlWriter.writeStartDocument();     // ��������� ������ � ��������

    xmlWriter.writeStartElement("rules");   // ���������� ������ ������� � ��� ������

    QString type_of_recursion;
    switch (rules_editor_manager->GetRecDirection())
    {
    case DirectionOfRecursion::LTOR_REC:
        type_of_recursion = "LTOR_REC";
        break;
    case DirectionOfRecursion::RTOL_REC:
        type_of_recursion = "RTOL_REC";
        break;
    case DirectionOfRecursion::NESTED_REC:
        type_of_recursion = "NESTED_REC";
        break;
    case DirectionOfRecursion::NOT_DEFINED_REC:
        type_of_recursion = "NOT_DEFINED_REC";
        break;
    case DirectionOfRecursion::MIXED_ERROR:
        type_of_recursion = "MIXED_ERROR";
        break;
    default:
        break;
    }
    xmlWriter.writeAttribute("recursion", type_of_recursion);

    unsigned num_of_rules = rules.size();
    for (unsigned i = 0; i < num_of_rules; i++) {

        xmlWriter.writeStartElement("rule");

        xmlWriter.writeStartElement("left");
        xmlWriter.writeAttribute("axiom",
            (rules[i].GetLeft().IsAxiom() ? "true" : "false"));
        xmlWriter.writeCharacters((rules[i].GetLeft()).to_QString());
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("right");
        unsigned right_size = rules[i].RightSize();
        for (unsigned j = 0; j < right_size; j++) {
            xmlWriter.writeStartElement("option");
            unsigned option_size = rules[i].GetRightOption(j).Length();
            for (unsigned k = 0; k < option_size; k++) {
                xmlWriter.writeStartElement("el");
                xmlWriter.writeAttribute("terminal",
                    (rules[i].GetRightOption(j)[k].IsTerm() ? "true" : "false"));
                xmlWriter.writeCharacters((rules[i].GetRightOption(j)[k]).to_QString());
                xmlWriter.writeEndElement();
            }
            xmlWriter.writeEndElement();
        }
        xmlWriter.writeEndElement();

        xmlWriter.writeEndElement();

    }
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();
    QMessageBox::information(0, RUS("������ ������"), RUS("������ ������� ���������!"));
}

void EdWindow::LoadRulesFromXML(QString fileName)
{
    QFile file(fileName);
    QTextCodec* codec = QTextCodec::codecForName("Windows-1251");

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this,
            RUS("������ �����"),
            RUS("�� ������� ������� ����"),
            QMessageBox::Ok);
    }
    else {

        rules.clear();

        ItemRule rule;
        ItemString option;

        QXmlStreamReader xmlReader;
        xmlReader.setDevice(&file);
        xmlReader.readNext();   // ��������� � ������� �������� � �����

        // �������� � ����� �� ��� ���, ���� �� ��������� ����� ���������
        while (!xmlReader.atEnd()) {

            if (xmlReader.isStartElement()) {
                if (xmlReader.name() == "rules") {
                    // ������
                }
                else if (xmlReader.name() == "rule") {
                    rule.Clear();
                }
                else if (xmlReader.name() == "left") {
                    foreach(const QXmlStreamAttribute & attr, xmlReader.attributes()) {
                        if (attr.name().toString() == "axiom") {
                            QString attribute_value = attr.value().toString();
                            bool axiom = (QString::compare(attribute_value, "true") == 0) ? true : false;
                            ItemSymb symb(xmlReader.readElementText(), false, axiom);
                            rule.SetLeft(symb);
                        }
                    }
                }
                else if (xmlReader.name() == "right") {
                    ///
                }
                else if (xmlReader.name() == "option") {
                    option.DeleteSymb(0, option.Length());
                }
                else if (xmlReader.name() == "el") {
                    foreach(const QXmlStreamAttribute & attr, xmlReader.attributes()) {
                        if (attr.name().toString() == "terminal") {
                            QString attribute_value = attr.value().toString();
                            bool terminal = (QString::compare(attribute_value, "true") == 0) ? true : false;
                            ItemSymb symb(xmlReader.readElementText(), terminal, false);
                            option.AddSymb(symb);
                        }
                    }
                }
            }
            else if (xmlReader.isEndElement()) {
                if (xmlReader.name() == "rules") {

                }
                else if (xmlReader.name() == "rule") {
                    rules.push_back(rule);
                }
                else if (xmlReader.name() == "left") {

                }
                else if (xmlReader.name() == "right") {

                }
                else if (xmlReader.name() == "option") {
                    rule.AddOption(option);
                }
                else if (xmlReader.name() == "el") {

                }
            }
            xmlReader.readNext();
        }
        file.close(); // ��������� ����
        //rules_editor_manager->MarkAxiomInLoadedRules(rules);
    }
}

void EdWindow::ShowInfoMessage(EditorInfoMessageType info_type)
{
    QString message = "";

    switch (info_type)
    {
    case CH_R_TO_DEL:
        ui.infoLabel->setStyleSheet("QLabel { color : red; }");
        message = QString::fromLocal8Bit("�������� ������� ��� ��������");
        break;
    case MIN_SIZE:
        ui.infoLabel->setStyleSheet("QLabel { color : red; }");
        message = QString::fromLocal8Bit("��������� ����������� ������ �������");
        break;
    case CH_R_TO_ADD_SYMB:
        ui.infoLabel->setStyleSheet("QLabel { color : red; }");
        message = QString::fromLocal8Bit("�������� ������� ��� ���������� ��������");
        break;
    case SEP_ADDED:
        ui.infoLabel->setStyleSheet("QLabel { color : red; }");
        message = QString::fromLocal8Bit("����������� ��� ��������");
        break;
    case CH_LEDIT_TO_RED:
        ui.infoLabel->setStyleSheet("QLabel { color : red; }");
        message = QString::fromLocal8Bit("�������� ���� ��� ����� ��� ��������������");
        break;
    default:
        break;
    }
    ui.infoLabel->setText(message);
    ui.infoLabel->setVisible(true);
    QTimer::singleShot(5000, this, &EdWindow::timeIsUp);
}

void EdWindow::onAddRuleClicked()
{
    main_layout->addWidget(rules_editor_manager->AddRule());
    ui.groupBox_rules->repaint();
}

void EdWindow::onSaveClicked()
{
    if (rules_editor_manager->FoundEmptyEditLines()) { // ���� ������������� ����
        QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
        QMessageBox::warning(this,
            RUS("������"),
            RUS("�� ��� ����� ��� ����� �������� ���������"),
            QMessageBox::Ok);
    }
    else if (rules_editor_manager->NoRules()) {
        QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
        QMessageBox::warning(this,
            RUS("������"),
            RUS("�� ���������� �� ������ �������"),
            QMessageBox::Ok);
    }
    else { // ��� ���� ���������
        // �������� ��������� �������
        rules_editor_manager->WriteInRules(rules);
        // ��������� ������������
        rules_editor_manager->MarkNonterminalsInRules(rules);

        if (rules_editor_manager->RepetitionsInTheLeftPartsOfRules(rules)) {
            QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
            QMessageBox::warning(this,
                RUS("������"),
                RUS("� ����� ������ ������������ ������ ������� ����������"),
                QMessageBox::Ok);
            return;
        }
        if (rules_editor_manager->RepetitionsInTheRightPartsOfRules(rules)) {
            QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
            QMessageBox::warning(this,
                RUS("������"),
                RUS("� ������ ������ ������������ ������ ������� ����������"),
                QMessageBox::Ok);
            return;
        }

        // �������� ��������
        rules_editor_manager->DefineDirectionOfRecursion(rules);

        if (rules_editor_manager->GetRecDirection() == DirectionOfRecursion::MIXED_ERROR) {
            QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
            QMessageBox::warning(this,
                RUS("������"),
                RUS("� �������� ���������� ��� �������������� ���� ��������"),
                QMessageBox::Ok);
            return;
        }

        // ������ ������� + ���������
        confirmation_window->ShowRules(rules_editor_manager->GetRulesText(rules));
        confirmation_window->ShowRecType(rules_editor_manager->GetRecTypeInString());
        confirmation_window->AddNonterminalsToComboBox(rules_editor_manager->GetNonterminals(rules));
        confirmation_window->show();
    }
}

void EdWindow::onLoadClicked()
{
    QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
    QString fileName = QFileDialog::getOpenFileName(0, RUS("�������� ���� ������"), "./Files", "XML(*.xml)");

    if (!fileName.isEmpty()) // ���� ������� ���
    {
        LoadRulesFromXML(fileName);

        if (main_layout != nullptr) {
            for (int i = 0; i < main_layout->count(); ++i)
            {
                delete main_layout->takeAt(i);
            }
        }

        rules_editor_manager->ShowLoadedRules(rules, main_layout);
    }
}

void EdWindow::checkFocusChange(QWidget* old, QWidget* now)
{
    if ((old == nullptr) || (now == nullptr))
        return;

    QString old_w_name = old->metaObject()->className();
    QString now_w_name = now->metaObject()->className();
    if ((old_w_name == "RuleBox") && (now_w_name == "QPushButton")) {
        old->setFocus();
        QPushButton* button = qobject_cast<QPushButton*>(now);
        QString text = button->text();

        if (text == QString::fromLocal8Bit("������� �������")) {
            // �������
            RuleBox* deleted_rulebox = qobject_cast<RuleBox*>(old);
            // ������������ ��������� �������� old:
            rules_editor_manager->DeleteRuleBox(deleted_rulebox);
            main_layout->removeWidget(deleted_rulebox);
            // ��������������� ������:
            rules_editor_manager->CorrectNumOfRuleBoxes();
            ui.groupBox_rules->repaint();
        }

        if (text == QString::fromLocal8Bit("�������� ������")) {
            RuleBox* editable_rulebox = qobject_cast<RuleBox*>(old);
            rules_editor_manager->AddSymbToRuleBox(editable_rulebox);
            ui.groupBox_rules->repaint();
        }

        if (text == QString::fromLocal8Bit("������� ������")) {
            RuleBox* editable_rulebox = qobject_cast<RuleBox*>(old);
            if (editable_rulebox->HasMinSize()) {
                ShowInfoMessage(EditorInfoMessageType::MIN_SIZE);
            }
            rules_editor_manager->DeleteSymbFromRuleBox(editable_rulebox);
            ui.groupBox_rules->repaint();
        }

        if (text == QString::fromLocal8Bit("|")) {
            RuleBox* editable_rulebox = qobject_cast<RuleBox*>(old);
            if (editable_rulebox->LastWidgetIsSeparator()) {
                ShowInfoMessage(EditorInfoMessageType::SEP_ADDED);
            }
            rules_editor_manager->AddSeparatorToRuleBox(editable_rulebox);
            ui.groupBox_rules->repaint();

        }

        if (text == QString::fromLocal8Bit("<...>")) {
            ShowInfoMessage(EditorInfoMessageType::CH_LEDIT_TO_RED);
        }

    }
    else if ((old_w_name == "QLineEdit") && (now_w_name == "QPushButton")) {
        QPushButton* button = qobject_cast<QPushButton*>(now);
        QString text = button->text();
        if (text == QString::fromLocal8Bit("<...>")) {
            QLineEdit* editable_line_edit = qobject_cast<QLineEdit*>(old);

            QString line_edit_text = editable_line_edit->text();
            QString new_line_edit_text = "";
            if ((line_edit_text[0] == '<') && (line_edit_text[line_edit_text.size() - 1] == '>')) {
                for (int i = 1; i < line_edit_text.size() - 1; i++) {
                    new_line_edit_text = new_line_edit_text + line_edit_text[i];
                }
            }
            else {
                new_line_edit_text = "<" + line_edit_text + ">";
            }
            editable_line_edit->setText(new_line_edit_text);
            editable_line_edit->repaint();
            editable_line_edit->setFocus();
        }
        if (text == QString::fromLocal8Bit("������� �������")) {
            ShowInfoMessage(EditorInfoMessageType::CH_R_TO_DEL);
        }
        if (text == QString::fromLocal8Bit("������� ������")) {
            ShowInfoMessage(EditorInfoMessageType::CH_R_TO_DEL);
        }
        if ((text == QString::fromLocal8Bit("�������� ������")) || (text == QString::fromLocal8Bit("|"))) {
            ShowInfoMessage(EditorInfoMessageType::CH_R_TO_ADD_SYMB);
        }
    }
    else if ((now_w_name == "QPushButton")) {
        QPushButton* button = qobject_cast<QPushButton*>(now);
        QString text = button->text();
        if (text == QString::fromLocal8Bit("������� �������")) {
            ShowInfoMessage(EditorInfoMessageType::CH_R_TO_DEL);
        }
        if (text == QString::fromLocal8Bit("������� ������")) {
            ShowInfoMessage(EditorInfoMessageType::CH_R_TO_DEL);
        }
        if ((text == QString::fromLocal8Bit("�������� ������")) || (text == QString::fromLocal8Bit("|"))) {
            ShowInfoMessage(EditorInfoMessageType::CH_R_TO_ADD_SYMB);
        }
        if (text == QString::fromLocal8Bit("<...>")) {
            ShowInfoMessage(EditorInfoMessageType::CH_LEDIT_TO_RED);
        }
    }
}

void EdWindow::axiomChosen()
{
    QString axiom = confirmation_window->GetAxiom();
    rules_editor_manager->SetAxiomInRules(rules, axiom);
    confirmation_window->hide();

    /// ���������� � ����
    QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
    QString fileName = QFileDialog::getSaveFileName(0, RUS("��������� ���� ������ ���"), "./Files", "XML(*.xml)");

    if (!fileName.isEmpty()) // ���� ������� ���
    {
        SaveRulesAsXML(fileName);
    }
}

void EdWindow::timeIsUp()
{
    ui.infoLabel->setText("");
}

void EdWindow::closeEvent(QCloseEvent* event)
{
	QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
	QMessageBox msgBox;
	msgBox.setWindowTitle(RUS("�����"));
	msgBox.setText(RUS("��������� ����������?"));
	QAbstractButton* pButtonYes = msgBox.addButton(RUS("��"), QMessageBox::YesRole);
	msgBox.addButton(RUS("���"), QMessageBox::NoRole);

	msgBox.exec();

	if (msgBox.clickedButton() == pButtonYes)
	{
		hide();
	}
	else
	{
		event->ignore();

	}
}

void EdWindow::onBackClicked()
{
	hide();
	emit edWindowClosed();
}
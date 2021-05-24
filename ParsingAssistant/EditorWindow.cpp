#include "EditorWindow.h"
#include <QTextCodec>
#include <QFileDialog>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QMessageBox>
#include <QTimer>

#define RUS( str ) codec->toUnicode(str)

EditorWindow::EditorWindow(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);
   // rules_editor_manager = new RulesEditorManager;
    ui.scrollArea->setWidgetResizable(true);
    //main_layout = rules_editor_manager->DrawBasicForms(); ///////////////////
    ui.groupBox_rules->setLayout(main_layout);

    connect(ui.addRuleButton, SIGNAL(clicked()), this, SLOT(onAddRuleClicked()));
    connect(ui.saveButton, SIGNAL(clicked()), this, SLOT(onSaveClicked()));
    connect(ui.loadButton, SIGNAL(clicked()), this, SLOT(onLoadClicked()));

    QApplication* app = static_cast<QApplication*>(QApplication::instance());
    connect(app, SIGNAL(focusChanged(QWidget*, QWidget*)), this, SLOT(checkFocusChange(QWidget*, QWidget*)));

    //confirmation_window = new ConfirmationWindow;
    //confirmation_window->hide();

    //connect(confirmation_window, SIGNAL(acception()), this, SLOT(axiomChosen()));
    ui.infoLabel->setText("");
}

/*
void EditorWindow::LoadRulesFromXML(QString fileName)
{
    QFile file(fileName);
    QTextCodec* codec = QTextCodec::codecForName("Windows-1251");

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this,
            RUS("Ошибка файла"),
            RUS("Не удалось открыть файл"),
            QMessageBox::Ok);
    }
    else {

        rules.clear();

        ItemRule rule;
        ItemString option;

        QXmlStreamReader xmlReader;
        xmlReader.setDevice(&file);
        xmlReader.readNext();   // Переходит к первому элементу в файле

        // Крутимся в цикле до тех пор, пока не достигнем конца документа
        while (!xmlReader.atEnd()) {

            if (xmlReader.isStartElement()) {
                if (xmlReader.name() == "rules") {
                    // ничего
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
        file.close(); // Закрываем файл
        //rules_editor_manager->MarkAxiomInLoadedRules(rules);
    }
}

void EditorWindow::SaveRulesAsXML(QString fileName)
{
    QTextCodec* codec = QTextCodec::codecForName("Windows-1251");

    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    QXmlStreamWriter xmlWriter(&file);

    xmlWriter.setAutoFormatting(true);  // Устанавливаем автоформатирование текста
    xmlWriter.writeStartDocument();     // Запускаем запись в документ

    xmlWriter.writeStartElement("rules");   // Записываем первый элемент с его именем

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
    QMessageBox::information(0, RUS("Запись правил"), RUS("Запись успешно выполнена!"));
}


void EditorWindow::ShowInfoMessage(EditorInfoMessageType info_type)
{
    QString message = "";

    switch (info_type)
    {
    case CH_R_TO_DEL:
        ui.infoLabel->setStyleSheet("QLabel { color : red; }");
        message = QString::fromLocal8Bit("Выберите правило для удаления");
        break;
    case MIN_SIZE:
        ui.infoLabel->setStyleSheet("QLabel { color : red; }");
        message = QString::fromLocal8Bit("Достигнут минимальный размер правила");
        break;
    case CH_R_TO_ADD_SYMB:
        ui.infoLabel->setStyleSheet("QLabel { color : red; }");
        message = QString::fromLocal8Bit("Выберите правило для добавления элемента");
        break;
    case SEP_ADDED:
        ui.infoLabel->setStyleSheet("QLabel { color : red; }");
        message = QString::fromLocal8Bit("Разделитель уже добавлен");
        break;
    case CH_LEDIT_TO_RED:
        ui.infoLabel->setStyleSheet("QLabel { color : red; }");
        message = QString::fromLocal8Bit("Выберите поле для ввода для редактирования");
        break;
    default:
        break;
    }
    ui.infoLabel->setText(message);
    ui.infoLabel->setVisible(true);
    QTimer::singleShot(5000, this, &EditorWindow::timeIsUp);
}

void EditorWindow::onSaveClicked()
{
    if (rules_editor_manager->FoundEmptyEditLines()) { // есть незаполненные поля
        QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
        QMessageBox::warning(this,
            RUS("Ошибка"),
            RUS("Не все формы для ввода символов заполнены"),
            QMessageBox::Ok);
    }
    else if (rules_editor_manager->NoRules()) {
        QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
        QMessageBox::warning(this,
            RUS("Ошибка"),
            RUS("Не определено ни одного правила"),
            QMessageBox::Ok);
    }
    else { // все поля заполнены
        // менеджер формирует правила
        rules_editor_manager->WriteInRules(rules);
        // уточнение нетерминалов
        rules_editor_manager->MarkNonterminalsInRules(rules);

        if (rules_editor_manager->RepetitionsInTheLeftPartsOfRules(rules)) {
            QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
            QMessageBox::warning(this,
                RUS("Ошибка"),
                RUS("В левых частях определенных правил найдены совпадения"),
                QMessageBox::Ok);
            return;
        }
        if (rules_editor_manager->RepetitionsInTheRightPartsOfRules(rules)) {
            QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
            QMessageBox::warning(this,
                RUS("Ошибка"),
                RUS("В правых частях определенных правил найдены совпадения"),
                QMessageBox::Ok);
            return;
        }

        // проверка рекурсии
        rules_editor_manager->DefineDirectionOfRecursion(rules);

        if (rules_editor_manager->GetRecDirection() == DirectionOfRecursion::MIXED_ERROR) {
            QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
            QMessageBox::warning(this,
                RUS("Ошибка"),
                RUS("В правилах содержатся два противоречащих вида рекурсии"),
                QMessageBox::Ok);
            return;
        }

        // запрос аксиомы + установка
        confirmation_window->ShowRules(rules_editor_manager->GetRulesText(rules));
        confirmation_window->ShowRecType(rules_editor_manager->GetRecTypeInString());
        confirmation_window->AddNonterminalsToComboBox(rules_editor_manager->GetNonterminals(rules));
        confirmation_window->show();
    }
}

void EditorWindow::onLoadClicked()
{
    QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
    QString fileName = QFileDialog::getOpenFileName(0, RUS("Выберите файл правил"), "./Files", "XML(*.xml)");

    if (!fileName.isEmpty()) // если введено имя
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

void EditorWindow::checkFocusChange(QWidget* old, QWidget* now)
{
    if ((old == nullptr) || (now == nullptr))
        return;

    QString old_w_name = old->metaObject()->className();
    QString now_w_name = now->metaObject()->className();
    if ((old_w_name == "RuleBox") && (now_w_name == "QPushButton")) {
        old->setFocus();
        QPushButton* button = qobject_cast<QPushButton*>(now);
        QString text = button->text();

        if (text == QString::fromLocal8Bit("Удалить правило")) {
            //удаляем
            RuleBox* deleted_rulebox = qobject_cast<RuleBox*>(old);
            // делегировать менеджеру удаление old:
            rules_editor_manager->DeleteRuleBox(deleted_rulebox);
            main_layout->removeWidget(deleted_rulebox);
            // скорректировать номера:
            rules_editor_manager->CorrectNumOfRuleBoxes();
            ui.groupBox_rules->repaint();
        }

        if (text == QString::fromLocal8Bit("Добавить символ")) {
            RuleBox* editable_rulebox = qobject_cast<RuleBox*>(old);
            rules_editor_manager->AddSymbToRuleBox(editable_rulebox);
            ui.groupBox_rules->repaint();
        }

        if (text == QString::fromLocal8Bit("Удалить символ")) {
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
        if (text == QString::fromLocal8Bit("Удалить правило")) {
            ShowInfoMessage(EditorInfoMessageType::CH_R_TO_DEL);
        }
        if (text == QString::fromLocal8Bit("Удалить символ")) {
            ShowInfoMessage(EditorInfoMessageType::CH_R_TO_DEL);
        }
        if ((text == QString::fromLocal8Bit("Добавить символ")) || (text == QString::fromLocal8Bit("|"))) {
            ShowInfoMessage(EditorInfoMessageType::CH_R_TO_ADD_SYMB);
        }
    }
    else if ((now_w_name == "QPushButton")) {
        QPushButton* button = qobject_cast<QPushButton*>(now);
        QString text = button->text();
        if (text == QString::fromLocal8Bit("Удалить правило")) {
            ShowInfoMessage(EditorInfoMessageType::CH_R_TO_DEL);
        }
        if (text == QString::fromLocal8Bit("Удалить символ")) {
            ShowInfoMessage(EditorInfoMessageType::CH_R_TO_DEL);
        }
        if ((text == QString::fromLocal8Bit("Добавить символ")) || (text == QString::fromLocal8Bit("|"))) {
            ShowInfoMessage(EditorInfoMessageType::CH_R_TO_ADD_SYMB);
        }
        if (text == QString::fromLocal8Bit("<...>")) {
            ShowInfoMessage(EditorInfoMessageType::CH_LEDIT_TO_RED);
        }
    }
}

void EditorWindow::axiomChosen()
{
    QString axiom = confirmation_window->GetAxiom();
    rules_editor_manager->SetAxiomInRules(rules, axiom);
    confirmation_window->hide();

    /// сохранение в файл
    QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
    QString fileName = QFileDialog::getSaveFileName(0, RUS("Сохранить файл правил как"), "./Files", "XML(*.xml)");

    if (!fileName.isEmpty()) // если введено имя
    {
        SaveRulesAsXML(fileName);
    }
}

void EditorWindow::timeIsUp()
{
    ui.infoLabel->setText("");
}

void EditorWindow::onAddRuleClicked() {

    main_layout->addWidget(rules_editor_manager->AddRule());
    ui.groupBox_rules->repaint();
}
*/
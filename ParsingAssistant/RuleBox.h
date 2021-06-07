#pragma once
#include <QLineEdit>
#include <QHBoxLayout>
#include <QLabel>

#include <QGroupBox>

class RuleBox : public QGroupBox
{
    Q_OBJECT
public:
    RuleBox(QGroupBox* parent = 0);
    void ClearRuleBox() {
        line_of_widgets.clear();
        managed_edit_lines.clear();
    }
    void AddWidget(QWidget* widget) {
        line_of_widgets.push_back(widget);
    }
    void AddLineEdit(QLineEdit* line_edit) {
        managed_edit_lines.push_back(line_edit);
    }
    void SetRuleBox() {
        
        QHBoxLayout* hbox = new QHBoxLayout;
        for (int i = 0; i < line_of_widgets.size(); i++) {
            hbox->addWidget(line_of_widgets[i]);
        }
        setLayout(hbox);
        setMaximumHeight(50);
    }
    void ResetRuleBox() {
        QLayout* current_layout = layout();
        if (current_layout != nullptr){
            for (int i = 0; i < current_layout->count(); ++i)
            {
                delete current_layout->takeAt(i);
            }
        }
        else {
            QHBoxLayout* hbox = new QHBoxLayout;
            current_layout = hbox;
            setLayout(current_layout);
        }
        for (int i = 0; i < line_of_widgets.size(); i++) 
        {
            current_layout->addWidget(line_of_widgets[i]);
        }
        setMaximumHeight(50);
    }
    int GetLineEditsNumber() {
        return managed_edit_lines.size();
    }

    int GetManagedWidgetsNumber() {
        return line_of_widgets.size();
    }

    std::vector<QWidget*> GetLineOfWidgets() {
        return line_of_widgets;
    }

    void DeleteLastLineEdit() {
        managed_edit_lines[managed_edit_lines.size() - 1]->setVisible(false);
        managed_edit_lines.erase(managed_edit_lines.begin() + (managed_edit_lines.size() - 1));
        line_of_widgets.erase(line_of_widgets.begin() + (line_of_widgets.size() - 1));
        ResetRuleBox();
    }

    void DeleteLastWidget() {
        line_of_widgets[line_of_widgets.size() - 1]->setVisible(false);
        line_of_widgets.erase(line_of_widgets.begin() + (line_of_widgets.size() - 1));
        ResetRuleBox();
    }

    bool HasMinSize() {
        return (line_of_widgets.size() == 4);
    }

    bool LastWidgetIsSeparator() {
        QString class_name = line_of_widgets[line_of_widgets.size() - 1]->metaObject()->className();
        if (class_name == "QLabel") {
            return true;
        }
        else {
            return false;
        }
    }

    bool LastWidgetIsLineEdit() {
        QString w_name = line_of_widgets[line_of_widgets.size() - 1]->metaObject()->className();
        if (w_name == "QLineEdit")
            return true;
        else
            return false;
    }

    bool HasEmptyLineEdit() {
        for (QLineEdit* line_edit : managed_edit_lines) {
            if (line_edit->text() == "")
                return true;
        }
        return false;
    }

    void SetNumLabel(int i);

protected:

    void focusInEvent(QFocusEvent* event);
    void focusOutEvent(QFocusEvent* event);

private:
    std::vector<QWidget*> line_of_widgets;
    std::vector<QLineEdit*> managed_edit_lines;
};
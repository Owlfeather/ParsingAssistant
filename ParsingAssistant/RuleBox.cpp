#include "RuleBox.h"

RuleBox::RuleBox(QGroupBox* parent) :
	QGroupBox(parent)
{
	//setFocusPolicy(Qt::ClickFocus);
	setFocusPolicy(Qt::StrongFocus);
}

void RuleBox::SetNumLabel(int i)
{
	QLabel* label = qobject_cast<QLabel*>(line_of_widgets[0]);
	label->setText(QString::number(i));
}

void RuleBox::focusInEvent(QFocusEvent* event)
{
	setStyleSheet(QString::fromUtf8("\
					QGroupBox {\
						background-color: #F0F8FF;\
						border: 2px solid gray;\
						border-radius: 5px;\
					}"));
}

void RuleBox::focusOutEvent(QFocusEvent* event)
{
	setStyleSheet("");
}

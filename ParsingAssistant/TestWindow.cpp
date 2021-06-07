#include "TestWindow.h"
#include <QTextCodec>
#include <QString>
#include <QMessageBox>
#include <QColorDialog>
#include <QAbstractItemView>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <fstream>

#define RUS( str ) codec->toUnicode(str)


TestWindow::TestWindow(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ans_table = new AnsTable;

	//connect(ui.btnClose, SIGNAL(clicked()), this, SLOT(onClosedClicked()));
	connect(ui.btnBack, SIGNAL(clicked()), this, SLOT(onBackClicked()));
	connect(ui.btnFinTest, SIGNAL(clicked()), this, SLOT(onEndClicked()));

}

TestWindow::~TestWindow()
{
}


void TestWindow::setTestParams(unsigned t_num, TypeOfAlg a_type)
{
	task_num = t_num;
	alg_type = a_type;
	ui.groupBox_results->setVisible(false);

	ui.label_cur_task->setText("1");
	ui.label_all_tasks->setText(QString::number(t_num));
	ui.btnPrevTask->setDisabled(true);

	ui.label_method->setText(QString::fromLocal8Bit("Левосторонний восходящий метод разбора"));

	setTest();
}

QLayout* TestWindow::DrawRules(const std::vector<ItemRule>& rules)
{
	QVBoxLayout* returned_l = new QVBoxLayout;
	QVBoxLayout* vbox = new QVBoxLayout;
	//QWidget* gbox = new QWidget;
	//QTextCodec* codec = QTextCodec::codecForName("Windows-1251");

	std::vector<QLabel*> buf;
	std::vector<QHBoxLayout*> array_h_layouts;
	std::vector<QLabel*> separators;
	separators.resize(1);
	ItemRule cur_rule;
	QString text;
	unsigned rules_size = rules.size(); // размер строк правил

	array_h_layouts.resize(rules_size); //число правил
	my_rules.resize(rules_size); ///число правил

	cur_rule = rules[0];
	int size = cur_rule.RightSize() + 1; // число вариантов раскрытия первого правила

	//for (int i = 0; i < size; i++) {
	for (int i = 0; i < rules_size; i++) {

		cur_rule = rules[i];
		size = cur_rule.RightSize() + 1;

		array_h_layouts[i] = new QHBoxLayout;
		buf.clear();
		buf.resize(size);

		//drawed_rules[i].resize(size);

		for (int j = 0; j < size; j++) {
			buf[j] = new QLabel;

			if (j == 0) {
				text = QString::fromLocal8Bit((string(cur_rule.GetLeft())).c_str());
				buf[j]->setText(text);
				my_rules[i].push_back(buf[j]);
				array_h_layouts[i]->addWidget(buf[j]);

				text = "::=";
				separators.resize(separators.size() + 1);
				unsigned last_sep_num = separators.size() - 1;
				separators[last_sep_num] = new QLabel;
				separators[last_sep_num]->setText(text);
				array_h_layouts[i]->addWidget(separators[separators.size() - 1]);
			}
			else {
				text = QString::fromLocal8Bit((string(cur_rule.GetRightOption(j - 1))).c_str());
				buf[j]->setText(text);
				my_rules[i].push_back(buf[j]);
				array_h_layouts[i]->addWidget(buf[j]);

				if (j != size - 1) {
					text = "|";
					separators.resize(separators.size() + 1);
					unsigned last_sep_num = separators.size() - 1;
					separators[last_sep_num] = new QLabel;
					separators[last_sep_num]->setText(text);
					array_h_layouts[i]->addWidget(separators[separators.size() - 1]);
				}
			}
		}

		array_h_layouts[i]->insertStretch(array_h_layouts[i]->count(), 1);
		vbox->addLayout(array_h_layouts[i]);
		returned_l->addLayout(vbox);
		++size;
	}
	return returned_l;
}

void TestWindow::onEndClicked()
{
	ui.groupBox_testing->setVisible(false);
	ui.groupBox_results->setVisible(true);

	ofstream myfile;
	myfile.open("result.htm");
	myfile << "<html lang=\"ru\"><head><meta charset=\"utf - 8\"></head><body>"; //starting html

	//add some html content
	//as an example: if you have array of objects featuring the properties name & value, you can print out a new line for each property pairs like this:
	
	myfile << "<center><p><span style='font-weight: bold'>" << "Результаты тестирования" << "</span></p></center>";
	myfile << "<p><span style='font-weight: bold'>" << "Метод разбора:" << "</span><span>" << "   Левосторонний восходящий метод разбора" << "</span></p>";
	myfile << "<p><span style='font-weight: bold'>" << "Количество заданий:" << "</span><span>" << "   3 "<< "</span></p>";
	myfile << "<p><span style='font-weight: bold'>" << "Решено:" << "</span><span>" << "   2/3 " << "</span></p>";
	myfile << "<p><span style='font-weight: bold'>" << "Процент выполнения:" << "</span><span>" << "   66% " << "</span></p>";
	myfile << "<br>";
	myfile << "<center><p><span style='font-weight: bold'>" << "Ошибки:" << "</span></p></center>";
	myfile << "<p><span style='font-weight: bold'>" << "1:" << "</span></p>";
	myfile << "<p><span>" << "       Разбираемая строка: " << "</span><span>" << "   +18" << "</span></p>";
	myfile << "<p><span>" << "       Шаг разбора: " << "</span><span>" << "   10" << "</span></p>";
	myfile << "<p><span>" << "       Ваш ответ: " << "</span><span>" << "   &#60;Знак>&#60;ЦБЗ>&#60;ЦБЗ>" << "</span></p>";
	myfile << "<p><span>" << "       Правильный ответ: " << "</span><span>" << "   &#60;Целое>&#60;Цифра>" << "</span></p>";

	//ending html
	myfile << "</body></html>";
	myfile.close();
	/*
	QFile* file;
	file = new QFile(":/ParsingAssistant/result.htm");

	if ((file->exists()) && (file->open(QIODevice::ReadWrite)))
	{
		QString html(file->readAll());
		ui.textBrowser->setHtml(html);
		ui.textBrowser->show();
		file->close();
	}
	delete file;
	*/

	QFile file("result.htm");
	file.open(QIODevice::ReadOnly);
	QByteArray a = file.readAll();
	QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
	QString text = codec->toUnicode(a);
	ui.textBrowser->setHtml(text);
	file.close();

	//ui.textBrowser->setSource(QString("result.htm"));

	//QString res_str = QString::fromLocal8Bit("\bРезультаты тестирования\b\n\nМетод разбора:\n   Левосторонний восходящий метод разбора\n\nЧисло заданий:\n   3\n\nРешено верно:\n\   2\n\nПроцент выполнения:\n   66%\n\n\nОшибки:");
	
}

void TestWindow::setTest()
{
	LtoR_MethodAlg_u* algorithm = new LtoR_MethodAlg_u;
	algorithm->SetLogTableType(TypeOfAlg::LTOR);
	algorithm->SetRulesOfAlg();
	algorithm->SetParsingStr(ItemString("+18"));
	algorithm->DoParse();


	ans_step = 5;
	ui.tableView_Task->setModel(algorithm->GetTable());
	for (int i = 6; i < algorithm->GetTable()->Size(); i++) {
		ui.tableView_Task->setRowHidden(i, true);
	}
	

	ui.tableView_Task->resizeColumnsToContents();
	ui.tableView_Task->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
	ui.tableView_Task->horizontalHeader()->setStyleSheet("font-weight: bold;");

	ui.tableView_Answer->setModel(ans_table);
	ui.tableView_Answer->resizeColumnsToContents();
	ui.tableView_Answer->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
	ui.tableView_Answer->horizontalHeader()->setStyleSheet("font-weight: bold;");

	ui.scrollArea_rules->setLayout(DrawRules(algorithm->GetRules()));

	//QTableWidgetItem* headerItem = new QTableWidgetItem(records);
	//ans_table->setVerticalHeaderItem(row, headerItem);
}

void TestWindow::closeEvent(QCloseEvent* event)
{
	QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
	QMessageBox msgBox;
	msgBox.setWindowTitle(RUS("Выход"));
	msgBox.setText(RUS("Завершить приложение?"));
	QAbstractButton* pButtonYes = msgBox.addButton(RUS("Да"), QMessageBox::YesRole);
	msgBox.addButton(RUS("Нет"), QMessageBox::NoRole);

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

void TestWindow::onBackClicked()
{
	hide();
	emit tWindowClosed();
}
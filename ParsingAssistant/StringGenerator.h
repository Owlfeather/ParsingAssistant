#pragma once
#include <QCoreApplication>
#include <QRandomGenerator>
#include <QDebug>

class TestStringGenerator {
private:

	const vector<QString> valid_signs = { QString(), QString("-"), QString("+") };;
	const QString expr_signs = QString("+-*/");
	const QString not_valid_signs = QString("*.?)(^:|}{~");
	const QString alphabet = QString("abcdefghijklmnopqrstuvwxyz");

public:

	TestStringGenerator() {}

	QString correctNumber()
	{
		QString res = valid_signs[QRandomGenerator::global()->bounded(valid_signs.size())]
			+ QString::number(QRandomGenerator::global()->bounded(9999));

		return res;
	}

	QString incorrectNumber()
	{
		int number_i = QRandomGenerator::global()->bounded(5);
		int alphabet_i = QRandomGenerator::global()->bounded(1) + 1;
		int valid_signs_i = QRandomGenerator::global()->bounded(1);
		int not_valid_signs_i = QRandomGenerator::global()->bounded(1) + 1;

		QString res = QString::number(QRandomGenerator::global()->bounded(10));
		for (int i = 0; i < number_i; i++) {
			res.insert(QRandomGenerator::global()->bounded(res.size())
				, QString::number(QRandomGenerator::global()->bounded(10)));
		}

		for (int i = 0; i < alphabet_i; i++) {
			res.insert(QRandomGenerator::global()->bounded(res.size())
				, alphabet[QRandomGenerator::global()->bounded(alphabet.size())]);
		}

		for (int i = 0; i < valid_signs_i; i++) {
			res.insert(QRandomGenerator::global()->bounded(res.size())
				, valid_signs[QRandomGenerator::global()->bounded(3)]);
		}

		for (int i = 0; i < not_valid_signs_i; i++) {
			res.insert(QRandomGenerator::global()->bounded(res.size())
				, not_valid_signs[QRandomGenerator::global()->bounded(not_valid_signs.size())]);
		}
		//if (!QRandomGenerator::global()->bounded(10)) res = "ALOHA";
		return res;
	}

	QString expression(QString expr = "")
	{
		if (!QRandomGenerator::global()->bounded(5) && expr.size() != 0) {
			return expr;
		}
		if (expr.size() != 0) {
			expr = "(" + expr + ")";
		}
		int num = QRandomGenerator::global()->bounded(5);
		for (int i = 0; i < num; i++) {
			int id_len = QRandomGenerator::global()->bounded(3) + 1;
			QString id;
			for (int j = 0; j < id_len; j++) {
				id += alphabet[QRandomGenerator::global()->bounded(alphabet.size())];
			}
			if (expr.size() == 0) {
				expr = id;
				continue;
			}
			if (QRandomGenerator::global()->bounded(2))
			{
				expr += expr_signs[QRandomGenerator::global()->bounded(expr_signs.size())] + id;

			}
			else {
				expr = id + expr_signs[QRandomGenerator::global()->bounded(expr_signs.size())] + expr;
			}

		}
		return expression(expr);
	}
	
	QString incorrectExpression()
	{
		QString wrong_expr;
		QString mistake = expr_signs[QRandomGenerator::global()->bounded(expr_signs.size())];
		mistake += expr_signs[QRandomGenerator::global()->bounded(expr_signs.size())];

		wrong_expr = expression();
		wrong_expr.insert(QRandomGenerator::global()->bounded(wrong_expr.size()), mistake);

		return wrong_expr;
	}

};
//const QString TestStringGenerator::valid_signs[] = { QString(), QString("-"), QString("+") };
//const QString TestStringGenerator::not_valid_signs = QString("*.?)(^:|}{~");
//const QString TestStringGenerator::alphabet = QString("abcdefghijklmnopqrstuvwxyz");
//const QString TestStringGenerator::expr_signs = QString("+-*/");

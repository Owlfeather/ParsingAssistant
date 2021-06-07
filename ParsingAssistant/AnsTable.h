#pragma once
#include <QAbstractTableModel>
#include <iostream>
#include "Alg_Elements_u.h"
#include <QTableWidgetItem>

using namespace std;

class AnsTable :
	public QAbstractTableModel
{
	Q_OBJECT
public:
	AnsTable() { 
		alg_type = TypeOfAlg::LTOR; 
		Create();

		
	}
	~AnsTable() {}
	void SetType(TypeOfAlg type) { alg_type = type; };

	TypeOfAlg alg_type;

	///
	vector<vector<QString>> records;
	int Size() { return records.size(); }
	void Create();
	///
public:
	int rowCount(const QModelIndex& parent) const;
	int columnCount(const QModelIndex& parent) const;
	QVariant data(const QModelIndex& index, int role) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;

signals:
	void editCompleted(const QString&);
};
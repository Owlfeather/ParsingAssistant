#include "Basic_Algorithm.h"
//#define LTOR 0
//#define TTOD 1


void ParseAlgorithm::SetLogTable(TypeOfAlg type_alg)
{
	table_model->SetRowCount(parsing_log.Size());
	switch (type_alg)
	{
	case TypeOfAlg::LTOR: {
		table_model->SetColomnCount(2);
		break;
		//table_view->headerData(1, "dfrg");
	}
	case TypeOfAlg::TTOD: {
		table_model->SetColomnCount(4);
		break;
	}
	}
}
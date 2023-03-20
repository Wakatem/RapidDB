#pragma once
#include "..\headers\Report.h"

class Query_Report : public Report
{
	private:
		std::string query;
	public:
		Query_Report(std::string an_ty, std::string d, std::string query);
		std::string getQuery() const;
};


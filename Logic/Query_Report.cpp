#include "Query_Report.h"

Query_Report::Query_Report(std::string an_ty, std::string d, std::string query)
	:Report(an_ty, d)
{
	this->query = query;
}

std::string Query_Report::getQuery() const
{
	return this->query;
};

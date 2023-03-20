#include "Report.h"

Report::Report(std::string an_ty, std::string d)
{
	this->analysis_type = an_ty;
	this->desc = d;
}

void Report::addSuggestions(std::string suggestion)
{
	this->report_suggestions.push_back(suggestion);
}

std::string Report::getAnalysisType() const
{
	return this->analysis_type;
};

std::string Report::getDesc() const
{
	return this->desc;
};

std::vector<std::string> Report::getSuggestions() const
{
	return this->report_suggestions;
}










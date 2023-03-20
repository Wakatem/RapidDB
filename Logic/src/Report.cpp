#include "Report.h"

Report::Report(std::string an_ty, std::string d)
{
	this->analysis_type = an_ty;
	this->desc = d;
}

void Report::addSuggestions(std::vector<std::string> suggestion)
{
	for (int i = 0; i < suggestion.size(); i++)
	{
		this->report_suggestions.push_back(suggestion[i]);
	}
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

std::vector<std::string> Report::retrieveSuggestions() const
{
	return report_suggestions;
}









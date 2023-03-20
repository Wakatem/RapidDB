#pragma once
#include <string>
#include <vector>

class Report
{
	private:
		std::string analysis_type;
		std::string desc;
		std::vector<std::string> report_suggestions;
	public:
		Report(std::string an_ty, std::string d);
		void addSuggestions(std::string);

		// retrieve report information
		std::vector<std::string> getSuggestions() const;
		std::string getDesc() const;
		std::string getAnalysisType() const;


};


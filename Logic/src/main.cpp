#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include "Database.h"

using namespace std;

std::vector<std::string> analyzeQueryTime(Database db, std::string query)
{
	std::vector <std::string> suggestions;
	try
	{

		clock_t start_time = clock();
		ResultSet* rs = db.executeQuery(query);
		while (rs->next()) {};
		clock_t end_time = clock();

		float duration = (float)end_time / (float)start_time;
		//std::cout << "Query took: " << duration << " seconds" << std::endl;

		if (query.find("SELECT *") >= 0)
		{
			suggestions.push_back("Avoid using SELECT * because it may result in unnecessary columns being fetched as output");
		}
		if (query.find("WHERE") == -1)
		{
			suggestions.push_back("Consider adding a WHERE clause to filter the data being returned");
		}
		if (query.find("ORDER BY") > 0 && query.find("ORDER BY") < 10000000)
		{
			suggestions.push_back("Avoid using ORDER BY clauses on large tables to fasten query.");
		}

		return suggestions;
	}
	catch (const std::exception& e)
	{
		std::cout << "ERROR: " << e.what();
	}
}
void getRecentQuery(Database db)
{
	ResultSet* rs = db.executeQuery("SELECT sql_fulltext FROM V$SQL WHERE rownum = 1 ORDER BY last_active_time DESC");
	rs->next();
	std::string line = rs->getString(1);
	std::cout << line;
} 
ResultSet* getExplainPlan(std::string query, Database db)
{
	db.executeQuery("EXPLAIN PLAN FOR " + query);
	ResultSet* rs = db.executeQuery("SELECT * FROM TABLE(DBMS_XPLAN.DISPLAY)");

	return rs;
}
std::vector<std::string> checkDatabaseStatus (Database db)
{
	std::vector<std::string> suggestions;

	// Check buffer cache size
	ResultSet* rs = db.executeQuery("SELECT value FROM V$PARAMETER WHERE name = 'db_block_buffers'");

	rs->next();
	unsigned long buffer_cache_size = (unsigned long)rs->getNumber(1);
	if (buffer_cache_size < 100000)
	{
		suggestions.push_back("Buffer cache size is set to a low value. You should try increasing it to improve I/O performance.");
	}
	rs->~ResultSet();

	// Check max open cursors
	rs = db.executeQuery("SELECT value FROM V$PARAMETER WHERE name = 'open_cursors'");
	
	rs->next();
	int open_cursors = rs->getInt(1);
	if (open_cursors < 100)
	{
		suggestions.push_back("Maximum number of open cursors is set to a low value. You should try increasing it to avoid cursor cache thrashing.");
	}

	//rs->~ResultSet();

	// Check datafile size
	rs = db.executeQuery("SELECT SUM(bytes) FROM dba_data_files");
	
	rs->next();
	unsigned long datafile_size = (unsigned long)rs->getNumber(1);
	if (datafile_size < (unsigned long)1073741824)
	{
		suggestions.push_back("Total size of datafiles is less than 1GB. You should try adding more datafiles to increase storage capacity.");
	}
	rs->~ResultSet();

	// If no suggestions needed
	if (suggestions.size() == 0)
	{
		suggestions.push_back("Database configuration is optimal");
	}

	return suggestions;
}
std::vector<std::string> analyzeLockTime(Database db, int max_wait_time)
{
	std::vector < std::string> suggestions;

	// Find session id and serial
	ResultSet* rs = db.executeQuery("SELECT sid, serial# FROM V$SESSION WHERE status = 'ACTIVE' ORDER BY DBMS_RANDOM.VALUE FETCH FIRST 1 ROWS ONLY");
	rs->next();

	int sid = rs->getNumber(1);
	unsigned int serial = rs->getUInt(2);
	
	// Find wait time
	rs = db.executeQuery(std::string("SELECT NVL(SUM(time_waited), 0) FROM V$SESSION_EVENT WHERE sid = ") + std::to_string(sid) + " AND event = 'enq: TX - row lock contention'");
	rs->next();
	unsigned int wait_time = rs->getUInt(1);
	
	std::cout << "The lock wait time for the session: " << sid << " is " << wait_time << " centiseconds" << std::endl;

	// Suggestions to reduce wait time for locks
	if (wait_time > max_wait_time)
	{
		suggestions.push_back("Replace table-level locking with row-level locking");
		suggestions.push_back("Consider expanding your hardware CPU, RAM, and storage space");
		suggestions.push_back("Try partioning large tables into sections that are more manageable");
		suggestions.push_back("Optimize your queries to reduce the number of required locks");
		suggestions.push_back("Avoid lengthy transactions that require locks on many rows or tables");
	}
	else
	{
		suggestions.push_back("Wait times are within acceptable ranges");
	}

	return suggestions;
}

std::vector<std::string> analyzeDBfile(Database db, std::string tablespace_name)
{
	std::vector<std::string> suggestions;
	ResultSet* rs = db.executeQuery("SELECT file_name, bytes, maxbytes, autoextensible FROM dba_data_files WHERE tablespace_name = '" + tablespace_name + "'");
	
	while (rs->next())
	{
		std::string file_name = rs->getString(1);
		double dfSize = rs->getDouble(2) / 1024 / 1024;
		double maxDFSize = rs->getDouble(3) / 1024 / 1024;
		std::string autoextensible = rs->getString(4);

		if (autoextensible == "NO")
		{
			if (dfSize / maxDFSize >= 0.9)
			{
				suggestions.push_back("Data file " + file_name + " is running out of space. Extend.");
			}
		}
	}

	if (suggestions.size() == 0)
	{
		suggestions.push_back("Data files for " + tablespace_name + " is configured properly.");
	}

	return suggestions;
}
std::vector<std::string> analyzePCTFree(Database db, std::string table_name)
{
	// get pct free of a table
	ResultSet* rs = db.executeQuery("SELECT pctfree FROM user_tables WHERE table_name = '" + table_name + "'");
	rs->next();
	int pctfree = rs->getInt(1);

	// get num of rows for a table
	rs = db.executeQuery("SELECT COUNT(*) FROM " + table_name);
	int NumOfRows = rs->getInt(1);

	// get ratio of updates to the toal number of rows
	rs = db.executeQuery("SELECT (SUM(decode(bitand(flag, 2), 0, 1, null)) / NumOfRows) FROM " + table_name);
	rs->next();
	int updateRatio = rs->getInt(1);
}

struct Database_Report 
{
	std::string analysis_type;
	std::string desc;
	std::vector<std::string> report_suggestions;
};
struct Query_Report
{ 
	std::string query;
	std::string analysis_type;
	std::string desc;
	std::vector<std::string> report_suggestions;
};

// ooo eee ooo ooo ah ting tang wala wala bing bang
// ooo eee ooo ah ting tang wala wala bing bang

void addToQueryReport(Query_Report& rep, const std::vector<std::string>& suggestions)
{
	for (int i = 0; i < suggestions.size(); i++)
	{
		rep.report_suggestions.push_back(suggestions[i]);
	};
}

void addToDatabaseReport(Database_Report& rep, const std::vector<std::string>& suggestions)
{
	for (int i = 0; i < suggestions.size(); i++)
	{
		rep.report_suggestions.push_back(suggestions[i]);
	};
}

void displayQueryReport(Query_Report& rep)
{
	std::cout << "QUERY: " << rep.query << std::endl;
	std::cout << "ANALYSIS TYPE: " << rep.analysis_type<< std::endl;
	std::cout << "DESCRIPTION: " << rep.desc<< std::endl;

	std::cout << "Suggestions: " << std::endl;
	for (int i = 0; i < rep.report_suggestions.size(); i++)
	{
		std::cout << rep.report_suggestions[i] << std::endl;
	}
}
void displayDatabaseReport(Database_Report& rep)
{
	std::cout << "ANALYSIS TYPE: " << rep.analysis_type << std::endl;
	std::cout << "DESCRIPTION: " << rep.desc << std::endl;

	std::cout << "Suggestions: " << std::endl;
	for (int i = 0; i < rep.report_suggestions.size(); i++)
	{
		std::cout << rep.report_suggestions[i] << std::endl;
	}
}

//int main() {
//	std::vector<std::string> titles = { "Query Performance", "Database Design" };
//	std::vector<std::string> contents = { "Analyzing Query performance", "Analyzing Database Design" };
//	Report report = createReport(titles, contents);
//
//
//	for (const auto& addition : report.additions) {
//		std::cout << "\u001b[1m" << addition.title << "\u001b[0m" << std::endl;
//		std::cout << addition.content << std::endl;
//	}
//	return 0;
//}

int main()
{
	try
	{
		// Creating database connection
		Database oracleDB("localhost", 1521, "xepdb1");
		oracleDB.connect("CSCI317", "oracle");

		// Database Analysis
		//auto dbStatus = checkDatabaseStatus(oracleDB);
		//auto lockTime = analyzeLockTime(oracleDB, 50); // session
		//auto DBFiles = analyzeDBfile(oracleDB, "TPCHR");

		// Query Analysis
		std::string query = "SELECT * FROM CUSTOMER";
		auto queryTime = analyzeQueryTime(oracleDB, query);

		Query_Report q_rep;
		q_rep.query = query;
		q_rep.analysis_type = "Query Time Analysis";
		q_rep.desc = "Analysing the type of the query";
		addToQueryReport(q_rep, queryTime);
		
		displayQueryReport(q_rep);

		oracleDB.freeResources();
		oracleDB.disconnect();
		oracleDB.closeEnvironment();
	}
	catch (const exception& x)
	{
		cout << x.what();
	}
}


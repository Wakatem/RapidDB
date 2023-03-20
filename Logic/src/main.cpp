#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include "Database.h"
#include "Query_Report.h"
#include "Database_Report.h"

using namespace std;

/*------------QUERY ANALYSIS------------*/
std::vector<std::string> analyzeQueryTime(Database& db, std::string query)
{
	std::vector <std::string> suggestions;
	try
	{

		clock_t start_time = clock();
		ResultSet* rec = db.executeQuery(query);
		while (rec->next()) {};
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

/* not compelted */
std::vector<std::string> analyzeMultiBlockReadCount(Database& db, std::string query)
{
	std::vector<std::string> suggestions;
	ResultSet* rec = db.executeQuery("SELECT mbrc, ((executions * buffer_gets) / disk_reads) AS the_iops FROM v$sql WHERE sql_text = query;");
	return suggestions;
}
/* not compelted */

std::vector<std::string> denormalizationSuggestion(Database& db, std::string query)
{
	std::vector<std::string> suggestions;
	int statement_id = rand();
	std::string explain_query = "EXPLAIN PLAN SET STATEMENT_ID = '" + std::to_string(statement_id) + "' INTO PLAN_TABLE FOR " + query;
	db.executeDML(explain_query);

	// get avg cost and cardinality for query
	ResultSet* rs = db.executeQuery("SELECT AVG(cost), AVG(cardinality) FROM PLAN_TABLE WHERE statement_id = '" + std::to_string(statement_id) + "' AND operation LIKE '%JOIN%'");
	long avg_cost = (long)rs->getNumber(1);
	long avg_card = (long)rs->getNumber(2);

	// loop through all the different join operations from the plan table
	ResultSet* rec = db.executeQuery("SELECT statement_id, operation, options, object_name, id, parent_id, cost, cardinality FROM plan_table WHERE statement_id = '" + std::to_string(statement_id) +"' AND operation LIKE '%JOIN%' OR operation LIKE '%SORT%' OR operation LIKE '%NESTED LOOPS%'");
	while (rec->next())
	{
		ResultSet* tab_ = db.executeQuery("SELECT object_name, id, options FROM plan_table WHERE statement_id ='" + std::to_string(statement_id) + "' AND parent_id = '" + rec->getString(5) + "' AND operation LIKE '%TABLE ACCESS%'");
		while (tab_->next())
		{
			// Get tables taht have more than 10% DML activity in the past 30 days
			ResultSet* get_volatile = db.executeQuery("SELECT COUNT(*) FROM dba_tab_modifications WHERE table_name = '" + tab_->getString(1) + "' AND (inserts + updates + deletes) / 3.0 > (SELECT SUM(inserts + updates + deletes) / 3.0 * 0.1 FROM dba_tab_modifications WHERE timestamp > SYSDATE - 30) AND timestamp > SYSDATE - 30");
			get_volatile->next();
			int is_volatile = get_volatile->getInt(1);
		
			// Suggestion if table is volatile
			if (is_volatile > 0)
			{
				suggestions.push_back("Table " + tab_->getString(1) + " is highly volatile. I.e- goes through frequent changes. Denormalization is not recommended");
			}
			else
			{
				// suggestion if table has ful join, high cardinality and cost in the query
				if (tab_->getString(3) == "FULL")
				{
					if (rec->getDouble(8) > avg_card)
					{
						if (rec->getDouble(7) > avg_cost)
						{
							std::string str = "The query provided has a full table scan on " + tab_->getString(1) + ".";
							str += "  The join performed on this table has a high cardinality of " + std::to_string((long)rec->getNumber(8)) + ",";
							str += " which is above the average cardinality of " + std::to_string(avg_card) + " and a cost of " + std::to_string((long)rec->getNumber(7));
							str += " which is above the average cost of " + std::to_string(avg_cost) + " of all joins performed in the query.";
							str += " Also note that the table does not usually undergo a lot of changes, hence " + tab_->getString(1) + " could be a potential denormalization opportunity";

							suggestions.push_back(str);
						}
						// suggestion if table has full join, high cardinality but low cost in query
						else
						{
							std::string str = "The " + tab_->getString(1) + " in the provided query has a high cardinality, a full table scan performed and is stable in terms of data volatility,";
							str += " but the cost seems to be below the average cost of all the joins in the query. Attempt to";
							str += " analyze further or try other performance tuning measures to avoid these expensive joins and";
							str += " keep the denormalization of this table as a last resort.";

							suggestions.push_back(str);
						}
					}
					// Suggestion if table has full join, low cardinality and cost in the query
					else
					{
						std::string str = "In the provided query, a full table scan has been performed on";
						str += tab_->getString(1) + " and it is stable in terms of data volatility but  does not meet the";
						str += " cost and cardinality estimates. Denormalizing this table might not be the best option";

						suggestions.push_back(str);
					}
				}
			}
		}
	}

	return suggestions;
}

/*------------QUERY ANALYSIS------------*/

/*------------DATABASE ANALYSIS------------*/
std::vector<std::string> analyzeLockTime(Database& db, int max_wait_time)
{
	std::vector < std::string> suggestions;

	// Find session id and serial
	ResultSet* rec = db.executeQuery("SELECT sid, serial# FROM V$SESSION WHERE status = 'ACTIVE' ORDER BY DBMS_RANDOM.VALUE FETCH FIrecT 1 ROWS ONLY");
	rec->next();

	int sid = rec->getNumber(1);
	unsigned int serial = rec->getUInt(2);
	
	// Find wait time
	rec = db.executeQuery(std::string("SELECT NVL(SUM(time_waited), 0) FROM V$SESSION_EVENT WHERE sid = ") + std::to_string(sid) + " AND event = 'enq: TX - row lock contention'");
	rec->next();
	unsigned int wait_time = rec->getUInt(1);
	
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
std::vector<std::string> analyzeDBfile(Database& db, std::string tablespace_name)
{
	std::vector<std::string> suggestions;
	ResultSet* rec = db.executeQuery("SELECT file_name, bytes, maxbytes, autoextensible FROM dba_data_files WHERE tablespace_name = '" + tablespace_name + "'");
	
	while (rec->next())
	{
		std::string file_name = rec->getString(1);
		double dfSize = rec->getDouble(2) / 1024 / 1024;
		double maxDFSize = rec->getDouble(3) / 1024 / 1024;
		std::string autoextensible = rec->getString(4);

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

/* not needed, repeat info */
std::vector<std::string> checkDatabaseStatus (Database& db)
{
	std::vector<std::string> suggestions;

	// Check buffer cache size
	ResultSet* rec = db.executeQuery("SELECT value FROM V$PARAMETER WHERE name = 'db_block_bufferec'");

	rec->next();
	unsigned long buffer_cache_size = (unsigned long)rec->getNumber(1);
	if (buffer_cache_size < 100000)
	{
		suggestions.push_back("Buffer cache size is set to a low value. You should try increasing it to improve I/O performance.");
	}
	rec->~ResultSet();

	// Check max open curecorec
	rec = db.executeQuery("SELECT value FROM V$PARAMETER WHERE name = 'open_curecorec'");
	
	rec->next();
	int open_curecorec = rec->getInt(1);
	if (open_curecorec < 100)
	{
		suggestions.push_back("Maximum number of open curecorec is set to a low value. You should try increasing it to avoid curecor cache thrashing.");
	}

	//rec->~ResultSet();

	// Check datafile size
	rec = db.executeQuery("SELECT SUM(bytes) FROM dba_data_files");
	
	rec->next();
	unsigned long datafile_size = (unsigned long)rec->getNumber(1);
	if (datafile_size < (unsigned long)1073741824)
	{
		suggestions.push_back("Total size of datafiles is less than 1GB. You should try adding more datafiles to increase storage capacity.");
	}
	rec->~ResultSet();

	// If no suggestions needed
	if (suggestions.size() == 0)
	{
		suggestions.push_back("Database configuration is optimal");
	}

	return suggestions;
}
/* not needed, repeat info */
/* Not completed */
std::vector<std::string> analyzePCTFree(Database& db, std::string tablespace_name)
{
	std::vector<std::string> suggestions;
	
	// Get all table names in a tablespace
	ResultSet* table_names = db.executeQuery("SELECT table_name FROM user_tables WHERE tablespace_name = '" + tablespace_name + "'");
	while (table_names->next())
	{
		ResultSet* rec = db.executeQuery("SELECT pct_free, num_rows FROM user_tables WHERE tablespace_name = '" + tablespace_name + "' AND table_name = " + table_names->getString(1));
		rec->next();

		int pct_free = rec->getInt(1);
		double num_rows = rec->getDouble(2);

		rec = db.executeQuery("SELECT value FROM V$SYSSTAT WHERE name = 'table fetch by rowid'");
		rec->next();

		double num_updates = rec->getDouble(1);

		int updatePct = (num_updates / num_rows) * 100;

		if (updatePct > 30)
		{
			suggestions.push_back(table_names->getString(1) + " table is prone to constant updates. Increase PCTFREE to improve updates performance");
		}
	}

	if (suggestions.size() == 0)
	{
		suggestions.push_back("All tables have appropriate PCTFREE values set");
	}

	return suggestions;
}
/* Not completed */

std::vector<std::string> suggestLeastUsedIndexes(Database& db)
{
	std::vector<std::string> suggestions;
	ResultSet* rec = db.executeQuery("SELECT index_name, last_analyzed, (to_date(SYSDATE) - to_date(last_analyzed)) AS duration FROM user_indexes WHERE (to_date(SYSDATE) - to_date(last_analyzed)) > 365");
	suggestions.push_back("Consider removing these indexes.");
	while (rec->next())
	{
		std::string str = "Index " + rec->getString(1) + std::string(" has not been used for ") + std::to_string(rec->getInt(3));
		suggestions.push_back(str);
	}

	if (suggestions.size() == 1)
	{
		suggestions.clear();
		suggestions.push_back("All indexes are being used");
	}
	return suggestions;
}
std::vector<std::string> suggestIndexFragmentation(Database& db)
{
	std::vector<std::string> suggestions;
	ResultSet* rec = db.executeQuery("SELECT index_name, blevel, leaf_blocks FROM user_indexes WHERE blevel>leaf_blocks");
	while (rec->next())
	{
		suggestions.push_back("Index " + rec->getString(1) + " has higer value of blevel in comparison to leaf blocks and hence suggested to be rebuilt in case of an fragmentation of indexes. ");
	}

	if (suggestions.size() == 0)
	{
		suggestions.push_back("All indexes are stored properly");
	}
	return suggestions;
}
std::vector<std::string> suggestPartitioningIndex(Database& db)
{
	std::vector<std::string> suggestions;
	ResultSet* rec = db.executeQuery("SELECT index_name, leaf_blocks, num_rows FROM user_indexes WHERE  leaf_blocks>= num_rows");
	while (rec->next())
	{
		suggestions.push_back("Index: " + rec->getString(1) + " is suggested for clustering or partitioning because of the higher number of leaf blocks in comparison to the size of the data. ");
	}

	if (suggestions.size() == 0)
	{
		suggestions.push_back("No index requires partitioning.");
	}

	return suggestions;
}
std::vector<std::string> suggestRemovalLowSelectivity(Database& db, int selectivityPercentage = 0.15)
{
	std::vector<std::string> suggestions;
	ResultSet* rec = db.executeQuery("SELECT index_name FROM user_indexes WHERE num_rows > 0 and distinct_keys/ num_rows < " + selectivityPercentage);
	suggestions.push_back("Suggest removing these indexes due to low selectivity: ");
	while (rec->next())
	{
		suggestions.push_back(rec->getString(1));
	}

	if (suggestions.size() == 1)
	{
		suggestions.clear();
		suggestions.push_back("All indexes' selectivity are higher than the defined limit");
	}

	return suggestions;
}

std::vector<std::string> analyzeBufferCacheSize(Database& db)
{
	std::vector<std::string> suggestions;
	ResultSet* rec = db.executeQuery("SELECT value FROM V$PARAMETER WHERE name = 'db_cache_size'");
	rec->next();
	double buffer_cache_size = rec->getDouble(1);

	rec = db.executeQuery("SELECT SUM(value) FROM v$sysstat WHERE name = 'physical reads'");
	rec->next();
	double phys_reads = rec->getDouble(1);

	rec = db.executeQuery("  SELECT SUM(value) INTO l_hits FROM v$sysstat WHERE name = 'db block gets'");
	rec->next();
	double the_hits = rec->getDouble(1);

	int hit_ratio = the_hits / (the_hits + phys_reads);

	if (hit_ratio < 0.9)
	{
		suggestions.push_back("The buffer hit cache ratio is " + std::to_string(hit_ratio) + ". Try increasing the cache size to improve perfroamnce");
	}
	
	if (suggestions.size() == 0)
	{
		suggestions.push_back("Buffer hit ratio is at an acceptable percentage. No need for changes");
	}
	return suggestions;
}
std::vector<std::string> analyzePGAAggeregate(Database& db, long long low_thresh = 100000000, long long high_thresh = 2147483648)
{
	std::vector <std::string> suggestions;
	
	ResultSet* rec = db.executeQuery("SELECT value FROM V$PGASTAT WHERE name = 'aggregate PGA target parameter'");
	rec->next();
	long long pga_aggregate_target = (long)rec->getNumber(1);

	if (pga_aggregate_target < low_thresh)
	{
		suggestions.push_back("The PGA aggregate target is too low, which may be causing excessive disk I/O due to server processes that do not have enough memory to perform memory-intensive operations efficiently. Try increasing it to improve performance.");
	}
	else if (pga_aggregate_target > high_thresh)
	{
		suggestions.push_back("PGA aggregate target is too high, which may cause unnecessary memory allocation and compete with the memory allocation for other components such as the shared pool. Try decreasing it to improve performance.");
	}
	else
	{
		suggestions.push_back("The PGA aggregate target is within the recommended range.");
	}

	return suggestions;
}



/* not completed */
std::vector<std::string> analyzeHitRatioSharedPool(Database& db)
{
	std::vector<std::string> suggestions;
	ResultSet* rec = db.executeQuery("SELECT SUM(PINS + RELOADS) AS buffer_Gets, SUM(pareceCalls) AS parece_Calls FROM V$LIBRARYCACHE");
	rec->next();
	int bufferGets = rec->getInt(1);
	int pareceCalls = rec->getInt(2);

	int hitRatio = (bufferGets - pareceCalls) / bufferGets;

	if (hitRatio < 0.9)
	{
		suggestions.push_back("Try increasing the shared pool size to improve performance");
	}
	else
	{
		suggestions.push_back("Shared pool hit ratio is acceptable");
	}

	return suggestions;
}
/* not completed */

/*------------DATABASE ANALYSIS------------*/

/*------------SUPPORTING FUNCTION------------*/
void printSuggestions(const std::vector<std::string>& arr)
{
	for (int i = 0; i < arr.size(); i++)
	{
		std::cout << arr[i] << std::endl;
	}
}

/*------------SUPPORTING FUNCTION------------*/



void getRecentQuery(Database db)
{
	ResultSet* rec = db.executeQuery("SELECT sql_fulltext FROM V$SQL WHERE rownum = 1 ORDER BY last_active_time DESC");
	rec->next();
	std::string line = rec->getString(1);
	std::cout << line;
} 
// not complete
ResultSet* getExplainPlan(std::string query, Database db)
{
	db.executeQuery("EXPLAIN PLAN FOR " + query);
	ResultSet* rec = db.executeQuery("SELECT * FROM TABLE(DBMS_XPLAN.DISPLAY)");

	return rec;
}

void displayReports(std::vector<Report> reports, std::string title)
{
	std::cout << "--------------------------------------------------------------------------";
	std::cout << "                               " << title << "                            ";
	std::cout << "--------------------------------------------------------------------------";
	for (int i = 0; i < reports.size(); i++)
	{
		std::cout << "   Category: ";
		std::cout << reports[i].getAnalysisType();

		std::cout << "     Suggestions:";
		for (int j = 0; j < reports[i].retrieveSuggestions().size(); j++)
		{
			std::cout << "      " << reports[i].retrieveSuggestions()[j] << " ";
		}
	}
}


int main()
{
	try
	{
		// Creating database connection
		Database oracleDB("localhost", 1521, "xepdb1");
		oracleDB.connect("CSCI317", "oracle");

		// Database analysis
		auto lockTimeSuggestions = analyzeLockTime(oracleDB, 50);
		auto DBFileSuggestions = analyzeDBfile(oracleDB, "TPCHR");
		auto leastUsedIndexes = suggestLeastUsedIndexes(oracleDB);
		auto IndexFragmentation = suggestIndexFragmentation(oracleDB);
		auto PartitioningIndex = suggestPartitioningIndex(oracleDB);
		auto lowSelectivitySuggestions = suggestRemovalLowSelectivity(oracleDB);
		auto bufferCache = analyzeBufferCacheSize(oracleDB);
		auto PGASuggestions = analyzePGAAggeregate(oracleDB);

		Database_Report lockTime("Lock Time", "This analyzes the lock time of a random session and provides suggestions based on it");
		lockTime.addSuggestions(lockTimeSuggestions);
		
		Database_Report DBFile("Database File", "This analyzes the sizes of database files.");
		DBFile.addSuggestions(DBFileSuggestions);

		Database_Report leastUsed("Least Used Index", "Analyzes all indexes present in the atabase and suggests removal of the least used indexes");
		leastUsed.addSuggestions(leastUsedIndexes);

		Database_Report IndexFragment("Index Fragmentation", "Analyzes if fragmentation is present in indexes and suggests rebuilt of the ones that do");
		IndexFragment.addSuggestions(IndexFragmentation);

		Database_Report PartitionIndex("Index Partition", "Analyzes Index leaf blocks present in proportion to the number of rows present");
		PartitionIndex.addSuggestions(PartitioningIndex);

		Database_Report lowSelectivity("Index Selectivity", "Analyzes indexes of a database that has low selectivity and suggests removal");
		lowSelectivity.addSuggestions(lowSelectivitySuggestions);

		Database_Report bufferC("Buffer Cache", "Analyzes the buffer cache hit ratio and determines if the buffer is large enough to contain all frequently requested objects");
		bufferC.addSuggestions(bufferCache);

		Database_Report PGA("PGA", "Analyzes the PGA available to the program and determines if the program has enough space to operate");
		PGA.addSuggestions(PGASuggestions);

		// Query Analysis
		std::string query = "SELECT * FROM CUSTOMER";
		auto QueryTimeSuggestions = analyzeQueryTime(oracleDB, "SELECT * FROM CUSTOMER");
		
		Query_Report queryTimeAnalysis(std::string("Query Time Analysis"), std::string("This report shows the analysis of a given query"), query);
		queryTimeAnalysis.addSuggestions(QueryTimeSuggestions);

		std::vector<Report> database_reports;
		database_reports.push_back(lockTime);
		database_reports.push_back(DBFile);
		database_reports.push_back(leastUsed);
		database_reports.push_back(IndexFragment);
		database_reports.push_back(PartitionIndex);
		database_reports.push_back(lowSelectivity);
		database_reports.push_back(bufferC);
		database_reports.push_back(PGA);

		std::vector<Report> query_reports;
		query_reports.push_back(queryTimeAnalysis);

		displayReports(database_reports, " Database Reports ");
		displayReports(query_reports, " Query Reports");



		oracleDB.freeResources();
		oracleDB.disconnect();
		oracleDB.closeEnvironment();
	}
	catch (const exception& x)
	{
		cout << x.what();
	}
}


/*
		// Rida
		
		printSuggestions(leastUsedIndexes(oracleDB));
		printSuggestions(IndexFragmentation(oracleDB));
		printSuggestions(suggestPartitioningIndex(oracleDB));
		printSuggestions(suggestRemovalLowSelectivity(oracleDB, 0.15));
		

		// Maryam
		
		printSuggestions(checkDatabaseStatus(oracleDB));
		printSuggestions(analyzeLockTime(oracleDB, 50));
		


		// Hiba
		//printSuggestions(analyzeDBfile(oracleDB, "TPCHR"));
		//printSuggestions(analyzePCTFree(oracleDB, "TPCHR"));
		//printSuggestions(analyzePGAAggeregate(oracleDB));
		//printSuggestions(analyzeHitRatioSharedPool(oracleDB));

		// Omar
		std::string query = "SELECT R.r_name AS region, SUM(L.l_extendedprice * (1 - L.l_discount) - PS.ps_supplycost * L.l_quantity) AS revenue FROM csci317.lineitem L";
		query += " JOIN csci317.partsupp PS ON L.l_partkey = PS.ps_partkey AND L.l_suppkey = PS.ps_suppkey";
		query += " JOIN csci317.part P ON L.l_partkey = P.p_partkey";
		query += " JOIN csci317.supplier S ON L.l_suppkey = S.s_suppkey";
		query += " JOIN csci317.nation N ON S.s_nationkey = N.n_nationkey";
		query += " JOIN csci317.region R ON N.n_regionkey = R.r_regionkey";
		query += " GROUP BY R.r_name";
		//printSuggestions(denormalizationSuggestion(oracleDB, query));

		oracleDB.executeDML("EXPLAIN PLAN FOR " + std::string("SELECT * FROM LINEITEM"));

		//oracleDB.executeQuery("EXPLAIN PLAN FOR " + std::string("SELECT * FROM LINEITEM"));
*/	
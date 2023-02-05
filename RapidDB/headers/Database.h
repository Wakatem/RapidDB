#pragma once
#include <occi.h>
#include <string>

using namespace oracle::occi;
using namespace std;

/**
The main communication channel with a database.
@param ServiceName -> the name of a pluggable database (optional)
*/
class Database 
{
private:
	string URL;
	string username;
	string password;
	Environment* env;
	Connection* con;
	Statement* statement = NULL;
	ResultSet* result = NULL;
	bool autoCommit;

public:
	Database(string databaseIP, unsigned short databasePort, string ServiceName = "");
	ResultSet* query(string SQLCommand);

	/**
	Executes a non-query statement such as a SQL INSERT, UPDATE, DELETE statement, a DDL statement such as CREATE/ALTER and so on, or a stored procedure call. Returns either the row count for INSERT, UPDATE or DELETE or 0 for SQL statements that return nothing
	*/
	unsigned int execute(string SQLCommand);
	/**
	A function to terminate all allocated resources related to SQL
	*/
	void freeResources();
	void commit();
	void rollback();
	void connect(string username, string password);
	void disconnect();
	void closeEnvironment();
};

#pragma once
#include <occi.h>
#include <string>
#include <boost/serialization/string.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>

using namespace oracle::occi;
using namespace std;

/**
The main communication channel with a database.
@param ServiceName -> the name of a pluggable database (optional)
*/

enum DatabaseLocation
{
	LOCAL,
	EXTERNAL
};
class Database 
{
	friend class boost::serialization::access;
private:
	string name;
	string type = "Oracle";
	DatabaseLocation location;
	string databaseIP;
	unsigned databasePort;
	string serviceName="";
	string URL;
	Environment* env;
	Connection* con;
	Statement* statement = NULL;
	ResultSet* result = NULL;
	bool autoCommit;

	//serialization of non-POD data
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& name;
		ar& type;
		ar& location;
		ar& databaseIP;
		ar& serviceName;
		ar& URL;
		ar& env;
		ar& con;
		ar& statement;
		ar& result;
	}

public:
	Database(string name, string type, DatabaseLocation location, string databaseIP, unsigned short databasePort, string ServiceName = "");
	Database(string databaseIP, unsigned short databasePort, string ServiceName = "");
	ResultSet* executeQuery(string SQLCommand);

	/**
	Executes a non-query statement such as a SQL INSERT, UPDATE, DELETE statement, a DDL statement such as CREATE/ALTER and so on, or a stored procedure call. Returns either the row count for INSERT, UPDATE or DELETE or 0 for SQL statements that return nothing
	*/
	unsigned int executeDML(string SQLCommand);
	/**
	A function to terminate all allocated resources related to SQL
	*/
	void freeResources();
	void commit();
	void rollback();
	void connect(string username, string password);
	void disconnect();
	void closeEnvironment();

	string getName();
	string getType();
	DatabaseLocation getLocation();
	string getLocationText();
	string getIP();
	unsigned short getPort();
	string getServiceName();
	string getURL();
};

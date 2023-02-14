
#include <iostream>
#include "Database.h"

Database::Database(string databaseIP, unsigned short databasePort, string ServiceName)
{
	//setup OCCI environment
	env = Environment::createEnvironment(Environment::DEFAULT);

	//setup connection url
	URL = databaseIP + ":" + to_string(databasePort) + (ServiceName.empty() ? "" : "/" + ServiceName);
}


ResultSet* Database::query(string SQLCommand)
{
	result = statement->executeQuery(SQLCommand);
	result->next(); //move cursor to first row

	return result;
}

unsigned int Database::execute(string SQLCommand)
{
	return statement->executeUpdate(SQLCommand);
}


void Database::commit()
{
	if (statement == NULL)
		cout << "Nothing to commit";
	else
		statement->executeUpdate("Commit");
}

void Database::rollback()
{
	if (statement == NULL)
		cout << "Nothing to rollback to";
	else
		statement->executeUpdate("Rollback");
}

void Database::connect(string username, string password)
{
	//create connection
	con = env->createConnection(username, password, URL);
	cout << "Connected!" << endl;

	//create blank statement
	statement = con->createStatement();
}

void Database::disconnect()
{
	env->terminateConnection(con);
}



void Database::closeEnvironment()
{
	Environment::terminateEnvironment(env);
}

void Database::freeResources()
{
	//only when a query took place, release results
	if (result != NULL) 
		statement->closeResultSet(result);

	con->terminateStatement(statement);
}



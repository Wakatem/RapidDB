#include <iostream>
#include <occi.h>
#include "Database.h"

using namespace oracle::occi;
using namespace std;

int main()
{

	string command = "Create table HALL (\
		said NUMBER NOT NULL PRIMARY KEY,\
		fname VARCHAR(10),\
		lname VARCHAR(10),\
		salary SMALLINT,\
		hours SMALLINT,\
		rate NUMBER) ";
	try
	{
		Database oracleDB("labwork", "lab", "localhost", 1521, "xepdb1");
		oracleDB.execute(command);
		oracleDB.commit();

		oracleDB.freeResources();
		oracleDB.closeConnection();
		oracleDB.closeEnvironment();
	}
	catch (const exception& x)
	{
		cout << x.what();
	}

}

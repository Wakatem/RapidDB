
#include <iostream>
#include "Database.h"

using namespace std;

int main()
{

	string command = "Create table HALL (said NUMBER NOT NULL PRIMARY KEY fname VARCHAR(10)) ";

	try
	{
		Database oracleDB("localhost", 1521, "xepdb1");
		oracleDB.connect("labwork", "lab");


		//oracleDB.execute(command);
		//oracleDB.commit();

		oracleDB.freeResources();
		oracleDB.disconnect();
		oracleDB.closeEnvironment();
	}
	catch (const exception& x)
	{
		cout << x.what();
	}

}

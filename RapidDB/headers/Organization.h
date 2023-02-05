#pragma once

#include <string>
#include <vector>
#include "Database.h"
#include "User.h"

using namespace::std;

class Organization
{
protected:
	vector <User> users;
	vector <Database> databases;

private:
	string name;
	string country;
	string timezone;
	string passcode;
	string privatekey;
	string email;
	int reports[4]; //still unknown

public:
	Organization();
	vector <Database> getDatabases();
	vector <User> getModerators();
};

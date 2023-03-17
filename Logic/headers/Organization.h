#pragma once

#include <string>
#include <vector>
#include "Database.h"
#include "User.h"

using namespace::std;

class Organization
{
private:
	string name;
	string country;
	string timezone;
	string passcode;
	string privatekey;
	string email;
	vector <User> users;
	vector <Database> databases;
	//vector <Report> reports;

public:
	Organization(string orgName, string orgCountry, string timezone, string passcode, string email);
	Organization();
	string gerOrgName();
	string getCountry();
	string getTimezone();
	string getPasscode();
	string getPrivatekey();
	string getEmail();
	vector <User> getUsers();
	vector <Database> getDatabases();
	void setPrivatekey(string newPrivatekey);
	//vector <Report> getReports();
};

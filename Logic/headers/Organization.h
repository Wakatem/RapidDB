#pragma once

#include <string>
#include <vector>
#include "Database.h"
#include "User.h"
#include <boost/serialization/string.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>

using namespace::std;

class Organization
{
	friend class boost::serialization::access;
private:

	string name;
	string country;
	string timezone;
	string passcode;
	string privatekey="a";
	string email;
	vector <User> users;
	vector <Database> databases;
	//vector <Report> reports;

	//serialization of non-POD data
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& name;
		ar& country;
		ar& timezone;
		ar& passcode;
		ar& privatekey;
		ar& email;
		ar& users;
		ar& databases;
	}

public:
	Organization(string orgName, string orgCountry, string timezone, string passcode, string email);
	Organization();
	~Organization();

	void setDetails(string orgName, string orgCountry, string timezone, string passcode, string email);
	string gerOrgName();
	string getCountry();
	string getTimezone();
	string getPasscode();
	string getPrivatekey();
	string getEmail();
	void setPrivatekey(string newPrivatekey);

	vector <User>& getUsers();
	vector <Database>& getDatabases();
	//vector <Report> getReports();
};

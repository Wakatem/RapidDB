#pragma once

#include <string>
#include "Organization.h"
#include <tuple>
#include <vector>


class User : protected Organization
{
protected:
	string firstName;
	string lastName;
	char gender;
	string email;
	string phoneNumber;
	string username;
	string password;
	int activityHistory [4]; //still unknown
	int reports[4]; //still unknown
	vector <tuple <string, string>> associatedDBs;

public:
	User();
	void setDetails();
	void changeFirstname();
	void changeLastname();
	void changeEmail();
	void changePhoneNumber();
	void changeUsername();
	void changePassword();
	vector<tuple <string, string>>& getAssociatedDBs();
};


class Admin : public User
{
public:
	void createUser();
	void deleteUser();
	void addDatabase();
	void removeDatabase();
	void updateDatabaseIP();
	void updateDatabasePort();
	void updateDatabaseServiceName();
};

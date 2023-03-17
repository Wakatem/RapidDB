#pragma once

#include <string>
#include "Organization.h"
#include <tuple>
#include <vector>


enum UserType
{
	ADMIN,
	MOD
};

class User
{
protected:
	string firstName;
	string lastName;
	char gender;
	string email;
	string phoneNumber;
	string username;
	string password;
	//int activityHistory [4]; //still unknown
	//vector <Report> reports;
	//vector <tuple <string, string>> associatedDBs;

public:
	User(string firstName, string lastName, char gender, string email, string phoneNumber, string username, string password);
	string getFirstname();
	string getLastname();
	char getGender();
	string getEmail();
	string getPhoneNumber();
	string getUsername();
	string getPassword();
	//vector<tuple <string, string>> getAssociatedDBs();
};

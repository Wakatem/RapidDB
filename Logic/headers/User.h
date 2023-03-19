#pragma once

#include <string>
#include <tuple>
#include <vector>
#include <boost/serialization/serialization.hpp>

using namespace std;

enum UserType
{
	ADMIN,
	MOD
};

class User
{
	friend class boost::serialization::access;
protected:
	string firstName;
	string lastName;
	char gender;
	string email;
	string phoneNumber;
	string username;
	string password;
	UserType userType;
	//int activityHistory [4]; //still unknown
	//vector <Report> reports;
	//vector <tuple <string, string>> associatedDBs;

	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& firstName;
		ar& lastName;
		ar& email;
		ar& phoneNumber;
		ar& username;
		ar& password;
		ar& userType;
	}

public:
	User(string firstName, string lastName, char gender, string email, string phoneNumber, string username, string password, UserType userType);
	User();
	string getFirstname();
	string getLastname();
	char getGender();
	string getEmail();
	string getPhoneNumber();
	string getUsername();
	string getPassword();
	UserType getUserType();

	void setFirstname(string newFirstname);
	void setLastname(string newLastname);
	void setEmail(string newEmail);
	void setPhoneNumber(string newPhoneNumber);
	void setPassword(string newPassword);
	//vector<tuple <string, string>> getAssociatedDBs();
};

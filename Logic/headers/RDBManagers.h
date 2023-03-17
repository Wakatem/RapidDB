#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include "Organization.h"

namespace fs = std::filesystem;
using std::fstream;
using std::string;

namespace RDBFileManager
{

	void createRDBfile(Organization* org, string path);
	void readRDBfile(Organization* org, string path);
	void saveToRDBfile(string path);
	bool findRDBfile(string path);
	bool findLoginFile();
}


namespace RDBUserManager
{
	//void setDetails(Organization org, User user, string firstName, string lastName, char gender, string email, string phoneNumber, string username, string password);
	//void changeFirstname(User user, string newFirstname);
	//void changeLastname(User user, string newLastname);
	//void changeEmail(User user, string newEmail);
	//void changePhoneNumber(User user, string newPhoneNumber);
	//void changePassword(User user, string oldPassword, string newPassword);
	User createUser(Organization org, User user);
	void deleteUser();
	//void changeUsername(User user, string newUsername);
};

namespace RDBDatabaseManager
{
	void addDatabase();
	void removeDatabase();
	void updateDatabaseIP();
	void updateDatabasePort();
	void updateDatabaseServiceName();
}

namespace RDBSecurityManager
{
	void orgSignin();
	void userLogin();
	void encrypt();
	void decrypt();
}
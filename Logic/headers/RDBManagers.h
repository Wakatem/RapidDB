#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include "Organization.h"
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/binary_object.hpp>
#include <boost/serialization/serialization.hpp>

namespace fs = std::filesystem;
using std::fstream;
using std::string;
using boost::serialization::make_binary_object;

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
	void addUser(Organization org, User user);
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
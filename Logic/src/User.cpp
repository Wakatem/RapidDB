#include "User.h"

User::User(string firstName, string lastName, char gender, string email, string phoneNumber, string username, string password, UserType userType)
{
	this->firstName = firstName;
	this->lastName = lastName;
	this->gender = gender;
	this->email = email;
	this->phoneNumber = phoneNumber;
	this->username = username;
	this->password = password;
	this->userType = userType;
}

User::User()
{

}

string User::getFirstname()
{
	return this->firstName;
}

string User::getLastname()
{
	return this->lastName;
}

char User::getGender()
{
	return this->gender;
}

string User::getEmail()
{
	return this->email;
}

string User::getPhoneNumber()
{
	return this->phoneNumber;
}

string User::getUsername()
{
	return this->username;
}

string User::getPassword()
{
	return this->password;
}

UserType User::getUserType()
{
	return this->userType;
}


void User::setFirstname(string newFirstname)
{
	this->firstName = newFirstname;
}


void User::setLastname(string newLastname)
{
	this->lastName= newLastname;
}

void User::setEmail(string newEmail)
{
	this->email= newEmail;
}


void User::setPhoneNumber(string newPhoneNumber)
{
	this->phoneNumber= newPhoneNumber;
}


void User::setPassword(string newPassword)
{
	this->password= newPassword;
}
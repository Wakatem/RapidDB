#include "Organization.h"

Organization::Organization(string orgName, string orgCountry, string timezone, string passcode, string email)
{
	this->name = orgName;
	this->country = orgCountry;
	this->timezone = timezone;
	this->passcode = passcode;
	this->email = email;
}

Organization::Organization()
{
}

Organization::~Organization()
{
	databases.clear();
	users.clear();
}

void Organization::setDetails(string orgName, string orgCountry, string timezone, string passcode, string email)
{
	this->name = orgName;
	this->country = orgCountry;
	this->timezone = timezone;
	this->passcode = passcode;
	this->email = email;
}

string Organization::gerOrgName()
{
	return this->name;
}

string Organization::getCountry()
{
	return this->country;
}

string Organization::getTimezone()
{
	return this->timezone;
}

string Organization::getPasscode()
{
	return this->passcode;
}

string Organization::getPrivatekey()
{
	return this->privatekey;
}

string Organization::getEmail()
{
	return this->email;
}

vector<User>& Organization::getUsers()
{
	return this->users;
}

vector<Database>& Organization::getDatabases()
{
	return this->databases;
}


void Organization::setPrivatekey(string newPrivatekey)
{
	this->privatekey = newPrivatekey;
}


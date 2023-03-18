#include "RDBManagers.h"

namespace RDBSecurityManager
{

	string loadOrgName(string path)
	{
		Organization temp;
		RDBFileManager::readRDBfile(temp, path);
		return temp.gerOrgName();
	}

	bool orgSignin(Organization& org, string orgPasscode, string path)
	{
		Organization temp;
		RDBFileManager::readRDBfile(temp, path);

		//Return true if passcode matches
		if (temp.getPasscode() == orgPasscode)
		{
			org = temp;
			return true;
		}
		
		return false;
	}

	bool userLogin(Organization& org, User& user, string username, string password, string path)
	{
		Organization temp;
		RDBFileManager::readRDBfile(temp, path);

		//find user by username
		for (User& savedUser : org.getUsers())
		{
			if (savedUser.getUsername() == username)
			{
				if (savedUser.getPassword() == password)
				{
					user = savedUser;
					return true;
				}
			}
		}

		return false;
	}
}
#include "RDBManagers.h"

namespace RDBSecurityManager
{

	string loadOrgName()
	{
		Organization temp;
		RDBFileManager::readRDBfile(temp);
		return temp.gerOrgName();
	}

	bool orgSignin(Organization& org, string orgPasscode)
	{
		Organization temp;
		RDBFileManager::readRDBfile(temp);

		//Return true if passcode matches
		if (temp.getPasscode() == orgPasscode)
		{
			org = temp;
			return true;
		}
		
		return false;
	}

	bool userLogin(Organization& org, User& user, string username, string password, UserType userType)
	{
		Organization temp;
		RDBFileManager::readRDBfile(temp);

		//find user by username
		for (User& savedUser : org.getUsers())
		{
			if (savedUser.getUserType() == userType)
			{
				if (savedUser.getUsername() == username)
				{
					if (savedUser.getPassword() == password)
					{
						user = savedUser;

						//create RDBU file if it doesn't exist
						if (!RDBFileManager::findRDBUfile())
						{
							RDBFileManager::createRDBUfile(user);
						}
						return true;
					}
				}
			}
		}

		return false;
	}
}
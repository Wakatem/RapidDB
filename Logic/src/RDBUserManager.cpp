#include "RDBManagers.h"

namespace RDBUserManager
{
	bool addUser(Organization& org, User user)
	{
		bool existingUsername = false;
		for (User& savedUser : org.getUsers())
		{
			if (savedUser.getUsername() == user.getUsername())
				existingUsername = true;
		}
		
		if (existingUsername)
		{
			return false;
		}
		else
		{
			org.getUsers().push_back(user);
			return true;
		}
	}

	void deleteUser(Organization& org, User user)
	{
		for (int i = 0; i < org.getUsers().size(); i++)
		{
			if (org.getUsers()[i].getUsername() == user.getUsername())
			{
				org.getUsers().erase(org.getUsers().begin()+i);
				break;
			}
		}
	}


	int findUser(Organization& org, User user)
	{
		int i = 0;
		for (User& savedUser : org.getUsers())
		{
			if (savedUser.getUsername() == user.getUsername())
				return i;
			i++;
		}

	}

	void changeFirstname(Organization& org, User user, string newFirstname)
	{
		int userPos = findUser(org, user);
		org.getUsers()[userPos].setFirstname(newFirstname);
	}

	void changeLastname(Organization& org, User user, string newLastname)
	{
		int userPos = findUser(org, user);
		org.getUsers()[userPos].setLastname(newLastname);
	}

	void changeEmail(Organization& org, User user, string newEmail)
	{
		int userPos = findUser(org, user);
		org.getUsers()[userPos].setEmail(newEmail);
	}

	void changePhoneNumber(Organization& org, User user, string newPhoneNumber)
	{
		int userPos = findUser(org, user);
		org.getUsers()[userPos].setPhoneNumber(newPhoneNumber);
	}

	bool changePassword(Organization& org, User user, string oldPassword, string newPassword)
	{
		int userPos = findUser(org, user);
		if (user.getPassword() == oldPassword)
		{
			org.getUsers()[userPos].setPassword(newPassword);
			return true;
		}

		return false;
	}
}
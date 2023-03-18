#include "RDBManagers.h"

namespace RDBUserManager
{
	void addUser(Organization& org, User user)
	{
		org.getUsers().push_back(user);
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


	//void changeFirstname(Organization& org, User user, string newFirstname)
	//{
	//	for (User& savedUser: org.getUsers())
	//	{
	//		if (savedUser.getUsername() == user.getUsername())
	//		{
	//			savedUser.setFirstname(newFirstname);
	//		}
	//	}
	//}
}
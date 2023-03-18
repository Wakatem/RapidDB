#include "RDBManagers.h"

namespace RDBFileManager
{
	void encrypt()
	{

	}


	void decrypt()
	{

	}

	void createRDBfile(Organization& org, string path)
	{
		string filename = path + "\\" + org.gerOrgName() + ".rdb";
		fstream f(filename, std::ios::out | std::ios::binary);
		boost::archive::binary_oarchive outputAR(f, boost::archive::no_header);

		outputAR << org;

	}



	void readRDBfile(Organization& org, string path)
	{
		bool RDBfound = findRDBfile(path);

		if (RDBfound)
		{
			for (const auto& entry : fs::directory_iterator(path))
			{
				if (entry.path().extension() == ".rdb")
				{
					//process reading
					string filename = path + "\\" + entry.path().filename().string();
					fstream f(filename, std::ios::in | std::ios::binary);
					boost::archive::binary_iarchive inputAR(f, boost::archive::no_header);

					inputAR >> org;
					break;
				}

			}
		}

	}


	bool findRDBfile(string path)
	{
		bool RDBfound = false;
		for (const auto& entry : fs::directory_iterator(path))
		{
			if (entry.path().extension() == ".rdb")
			{
				RDBfound = true;
				break;
			}
		}

		if (!RDBfound)
		{
			//send message indicating no RDB file was found
			cout << "Cannot find a RDB file";
		}

		return RDBfound;
	}


	bool findRDBUfile(string path)
	{
		bool LoginFilefound = false;
		for (const auto& entry : fs::directory_iterator(path))
		{
			if (entry.path().extension() == ".rdbu")
			{
				LoginFilefound = true;
				break;
			}
		}

		if (!LoginFilefound)
		{
			//send message indicating no LoginFile was found
			cout << "Cannot find a LoginFile";
		}

		return LoginFilefound;
	}





	void createRDBUfile(User& user, string path)
	{
		string filename = path + "\\" + (user.getFirstname() + user.getLastname()) + ".rdbu";
		fstream f(filename, std::ios::out | std::ios::binary);
		boost::archive::binary_oarchive outputAR(f, boost::archive::no_header);

		outputAR << user;
	}

	void readRDBUfile(User& user, string path)
	{
		bool RDBUfound = findRDBUfile(path);

		if (RDBUfound)
		{
			for (const auto& entry : fs::directory_iterator(path))
			{
				if (entry.path().extension() == ".rdbu")
				{
					//process reading
					string filename = path + "\\" + entry.path().filename().string();
					fstream f(filename, std::ios::in | std::ios::binary);
					boost::archive::binary_iarchive inputAR(f, boost::archive::no_header);

					inputAR >> user;
					break;
				}

			}
		}
	}
}
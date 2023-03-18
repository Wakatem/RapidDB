#include "RDBManagers.h"
string programFolderPath = "", assetsFolderPath="", dataFolderPath = "", reportsFolderPath = "";

namespace RDBFileManager
{

	void addPaths(string programPath, string dataPath, string reportsPath)
	{
		programFolderPath = programPath;
		dataFolderPath = dataPath;
		reportsFolderPath = reportsPath;
	}

	void createFolders()
	{
		fs::create_directory(assetsFolderPath);
		fs::create_directory(dataFolderPath);
		fs::create_directory(reportsFolderPath);
	}

	void saveRDBfile(Organization& org)
	{
		string filename = dataFolderPath + "\\" + org.gerOrgName() + ".rdb";
		fstream f(filename, std::ios::out | std::ios::binary);
		boost::archive::binary_oarchive outputAR(f, boost::archive::no_header);

		outputAR << org;

	}

	void readRDBfile(Organization& org)
	{
		bool RDBfound = findRDBfile();

		if (RDBfound)
		{
			for (const auto& entry : fs::directory_iterator(dataFolderPath))
			{
				if (entry.path().extension() == ".rdb")
				{
					//process reading
					string filename = dataFolderPath + "\\" + entry.path().filename().string();
					fstream f(filename, std::ios::in | std::ios::binary);
					boost::archive::binary_iarchive inputAR(f, boost::archive::no_header);

					inputAR >> org;
					break;
				}

			}
		}

	}


	bool findRDBfile()
	{
		bool RDBfound = false;
		for (const auto& entry : fs::directory_iterator(dataFolderPath))
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


	bool findRDBUfile()
	{
		bool LoginFilefound = false;
		for (const auto& entry : fs::directory_iterator(dataFolderPath))
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





	void createRDBUfile(User& user)
	{
		string filename = dataFolderPath + "\\" + (user.getFirstname() + user.getLastname()) + ".rdbu";
		fstream f(filename, std::ios::out | std::ios::binary);
		boost::archive::binary_oarchive outputAR(f, boost::archive::no_header);

		outputAR << user;
	}

	void readRDBUfile(User& user)
	{
		bool RDBUfound = findRDBUfile();

		if (RDBUfound)
		{
			for (const auto& entry : fs::directory_iterator(dataFolderPath))
			{
				if (entry.path().extension() == ".rdbu")
				{
					//process reading
					string filename = dataFolderPath + "\\" + entry.path().filename().string();
					fstream f(filename, std::ios::in | std::ios::binary);
					boost::archive::binary_iarchive inputAR(f, boost::archive::no_header);

					inputAR >> user;
					break;
				}

			}
		}
	}
}
#include "RDBManagers.h"

namespace RDBFileManager
{
	void encrypt()
	{

		std::cout << "w";
	}


	void decrypt()
	{

	}

	void createRDBfile(Organization* org, string path)
	{
		fstream f;
		string filename = path + "\\" + org->gerOrgName() + ".rdb";
		f.open(filename, std::ios::out | std::ios::binary);

		if (f.is_open())
		{

			f.write(reinterpret_cast<char*>(org), sizeof(Organization));
			f.close();
		}
		else
		{
			cout << "ERROOROR";
		}

	}



	void readRDBfile(Organization* org, string path)
	{
		bool RDBfound = findRDBfile(path);

		if (RDBfound)
		{
			for (const auto& entry : fs::directory_iterator(path))
			{
				//process reading
				string filename = path + "\\" + entry.path().filename().string();
				fstream f;
				f.open(filename, std::ios::in | std::ios::binary);

				if (f.is_open())
				{
					f.read(reinterpret_cast<char*>(org), sizeof(Organization));
					f.close();
				}
				else
				{
					cout << "ERROOROR";
				}

				break;

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
	}


	bool findLoginFile(string path)
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
	}
}
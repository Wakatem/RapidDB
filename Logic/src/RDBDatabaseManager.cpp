#include "RDBManagers.h"

namespace RDBDatabaseManager
{
	void addDatabase(Organization& org, Database db)
	{
		org.getDatabases().push_back(db);
	}

}
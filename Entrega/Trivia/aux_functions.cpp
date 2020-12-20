#ifndef Aux_Class
#define Aux_Class

#include <vector>
#include <iostream>
#include <dirent.h>
#include <windows.h>
//para los hilos en windows y la funcion Sleep();

//

#include <string>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <thread>


//para los hilos y la funcion Sleep() en linux;

//----------------------------------


using namespace std;

class Aux
{
  public:
	static void readDirectory(const string path, vector<string> &v, bool sorting = false, string pattern = "")
	{
		DIR *dir;
		v.clear();

		if ((dir = opendir(path.c_str())) != NULL)
		{
			dirent *data;
			while ((data = readdir(dir)) != NULL)
			{
				string path(data->d_name);

				double pos = path.find_last_of(pattern);
				if (path != "." and path != ".." and path != ".DS_Store" and pos > -1)
				{
					v.push_back(path);
				}
			}
			closedir(dir);

			if (sorting)
			{
				sort(v.begin(), v.end());
			}
		}
	};
};
#endif

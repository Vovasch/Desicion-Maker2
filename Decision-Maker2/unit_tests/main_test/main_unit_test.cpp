#include "main_unit_test.h"


void mainTest()
{
	assert(!DoesThisFileExist("some_rundom_file.txt")&&"Found file that is not supposted to exist"); //1

	char dir[1000]{ "unit_tests/tests_for_file_processing" };
	std::string testingFile{ "file_for_tests.txt" };

	assert(DoesThisFileExist(testingFile, dir) && "Couldn't find file");//2

	char dirAndName[1000];
	ConcatinateDirAndNameOfFile(dirAndName, testingFile, dir);

	assert(Get_Amount_Of_Strings_from_File(dirAndName)==3 && "Wrong amount of strings in file");//3

	char testDir[]{ "unit_tests/tests_for_file_processing/testing_dir" };
	assert(CountAmountOfFilsInDir(testDir)==2);//4
}
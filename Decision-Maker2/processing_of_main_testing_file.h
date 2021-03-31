#pragma once

#include<fstream>

// Copy into folder data and name as a main.txt 
// Chek if last string isn't character of new stiring, 
// if so this string will be deleted
void Copy_and_Parse_Main_Testing_File(const char* name_of_main_testing_file); //TODO make cheking of cases when file isn't opened

// 
int Get_Amount_Of_Strings_from_File(const char* name_of_file); //TODO make cheking of cases when file isn't opened
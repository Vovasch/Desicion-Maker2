#pragma once

#include<fstream>

// Main tesging file will be named just main.txt
void Init_Main_Tesgin_File(char * name_of_file);


// 
void Get_Name_of_Main_Tesgin_File_From_User(char *name_of_file);


// Copy into folder data and name as a main.txt 
// Chek if last string isn't character of new stiring, 
// if so this string will be deleted
void Copy_and_Parse_Main_Testing_File(char* name_of_main_testing_file); //TODO make cheking of cases when file isn't opened

// 
int Get_Amount_Of_Strings_from_File(char* name_of_file); //TODO make cheking of cases when file isn't opened
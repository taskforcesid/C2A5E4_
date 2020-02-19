// Aladin Sidahmed U08614258 
// aladin.sidahmed@gmail.com
// C/C++ Programming II 
// Section 145010 Ray Mitchell 
// 17 FEB 2020
// C2A5E4_OpenFile.cpp
// Operating System: Windows 7 
// Visual Studio Community 2019 Version 16.3.2 
//
// This file contains one function:
//      OpenFile: Implements a function that opens a text file 
//      in read only mode and terminates the program if it fails
//      to open the file
//

#include <iostream>
#include <fstream>
using namespace std;

void OpenFile(const char *fileName, ifstream &inFile)
{
    //open the file, and print a message in case of an error
    inFile.open(fileName);
    if (!inFile.is_open()) {
        cerr << "Failed to open file: " << fileName << "\n";
        exit(EXIT_FAILURE);
    }
}

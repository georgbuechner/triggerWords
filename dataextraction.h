#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <list>
#include "CFunctions.h"
#include "CVigenere.h"

class CDataExtraction
{
public:
    void addData();
    void extractData();
    void help() {
        std::cout << "No information.\n";
    }

};

void CDataExtraction::addData()
{
    CFunctions function;
    CVigenere vigenere;
    std::string sInput="";
    std::string sWritter="";

    std::cout << "Filename: ";
    function.m_getline(sInput);

    string sPath = "data/";
    sPath.append(sInput);
    ofstream write(sPath.c_str(),std::ios::out|std::ios::binary);
    sInput = "";
    
    std::cout << "Enter words: \n";
    for(int i=0; i<10; i++)
    {
        std::cout << i << ": ";
        function.m_getline(sInput);
        const char* chInput = sInput.c_str();
        sWritter.append(vigenere.encryption(const_cast<char*>(chInput), const_cast<char*>("GAWASI")));
	sWritter.append("\n");
	std::cout<<chInput<<std::endl;
    }

    std::cout<<"Swritter: "<<sWritter<<std::endl;
    //sWritter.append("\n1.");

    sInput="";
    std::cout << "Enter data: \n";
    for(int i=1; i<5; i++)
    {
        std::cout << i << ": ";
        function.m_getline(sInput);
        const char* chInput = sInput.c_str();
        sWritter.append(vigenere.encryption(const_cast<char*>(chInput), const_cast<char*>("GAWASI")));
        sWritter.append("\n\n");
    }

    write << sWritter;
    write.close();
}


void CDataExtraction::extractData()
{
    CFunctions function;
    CVigenere vigenere;
    std::string sFromPerson;

    std::cout << "Get data from: ";
    function.m_getline(sFromPerson);

    string sPath = "data/";
    sPath.append(sFromPerson);
    ifstream read(sPath.c_str(),std::ios::in|std::ios::binary);

    if(!read)
    {
        std::cout << "Selected person not found in data.\n";
        return;
    }

    std::list<std::string>* l_triggerWords = new std::list<std::string>;
    std::string sBuffer;
    for(int i=0;i<10;i++)
    {
        getline(read, sBuffer);
        const char* chBuffer = sBuffer.c_str();
        l_triggerWords->push_back(vigenere.decryption(const_cast<char*>(chBuffer), const_cast<char*>("gawasi")));
    }

    std::cout << "Enter information to extract data of person: \n";

    std::list<std::string>* l_inputWords = new std::list<std::string>;
    std::string sInput;
    for(int i=0; i<10; i++)
    {
        std::cout << i << ": ";
        function.m_getline(sInput);
        l_inputWords->push_back(sInput);
    }

    unsigned int counter=0;
    for(auto it=l_inputWords->begin(); it!=l_inputWords->end(); it++)
    {
        std::cout << (*it) << "\n";
        for(auto yt=l_triggerWords->begin(); yt!=l_triggerWords->end(); yt++)
        {
            std::cout << "-- " << (*yt);
            if(function.compare((*it).c_str(), (*yt).c_str()) == true)
            {
                std::cout << " *";
                counter++;
            }

            std::cout << "\n";
        }
    }
        
    std::cout << "Matches: " << counter << "\n";

    delete l_triggerWords;
}
        
        
        

        
         
    
    

    
    

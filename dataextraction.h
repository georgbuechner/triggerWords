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

    std::cout << "Path: ";
    function.m_getline(sInput);

    ifstream read;
    std::string sPath = "clear/";
    sPath.append(sInput);
    read.open(sPath);

    std::cout << "Charactername: ";
    function.m_getline(sInput);
    sPath = "data/";
    sPath.append(sInput);
    ofstream write(sPath.c_str(),std::ios::out|std::ios::binary);
    sInput = "";
    

    std::string sBuffer;
    while(!read.eof())
    {
        getline(read, sBuffer);
        
        if(sBuffer.compare("#") == true)
            continue;
    
        const char* chBuffer = sBuffer.c_str();
        char* chEncrypt = new char[20000];
        vigenere.encryption(const_cast<char*>(chBuffer), const_cast<char*>("GAWASI"), chEncrypt);
        
        write << chEncrypt << "\n";
    }

    std::cout << "writing finished...\n";

    write.close();
}


void CDataExtraction::extractData()
{
    CFunctions function;
    CVigenere vigenere;
    std::string sFromPerson;

    std::cout << "Verdächtige Person (Name der verschlüsselten Datei): ";
    function.m_getline(sFromPerson);

    string sPath = "data/";
    sPath.append(sFromPerson);
    ifstream read(sPath.c_str(),std::ios::in|std::ios::binary);

    if(!read)
    {
        std::cout << "Ausgewählte Person in unserem Datensatz nicht vorhanden.\n";
        return;
    }

    std::list<std::string>* l_triggerWords = new std::list<std::string>;
    std::string sBuffer;
    for(int i=0;i<10;i++)
    {
        getline(read, sBuffer);
        const char* chBuffer = sBuffer.c_str();
        char* chDecrypt = new char[20000];
        vigenere.decryption(const_cast<char*>(chBuffer), const_cast<char*>("GAWASI"), chDecrypt);
        std::string sDecrypt = chDecrypt;
        l_triggerWords->push_back(sDecrypt);
        delete []chDecrypt;
    }

    std::list<std::string>* l_inputs = new std::list<std::string>;
    while(!read.eof())
    {
        if(sBuffer.find("j") != std::string::npos)
        {
            std::string sNewInput;
            while(!read.eof())
            {
                getline(read, sBuffer); 

                if(sBuffer[0] == 'j')
                    break;

                const char* chBuffer = sBuffer.c_str();
                char* chDecrypt = new char[20000];
                vigenere.decryption(const_cast<char*>(chBuffer), const_cast<char*>("GAWASI"), chDecrypt);
                sNewInput.append(chDecrypt);
                sNewInput.append("\n");

            }
            l_inputs->push_back(sNewInput);
        }
                
        else
            getline(read, sBuffer);
    }
                
    std::cout << "Informationen zu der verdächtigten person eingeben \n";
    std::cout << "(Dies können einzelne Wörter oder kurze Phrasen sein. \n";
    std::cout << "10 Eingaben möglich): \n";

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
        for(auto yt=l_triggerWords->begin(); yt!=l_triggerWords->end(); yt++)
        {
            if(function.compare((*it).c_str(), (*yt).c_str()) == true)
                counter++;
        }
    }

    std::cout << counter << " Übereinstimmungen.\n\n\n";
        
    unsigned int sndCounter = 0;
    for(auto it=l_inputs->begin(); it!=l_inputs->end(); it++)
    {
        if(sndCounter == 0 && counter >= 2)
            std::cout << (*it) << "\n\n";
        else if(sndCounter == 1 && counter >= 4)
            std::cout << (*it) << "\n\n";
        else if(sndCounter == 2 && counter >= 6)
            std::cout << (*it) << "\n\n";
        sndCounter++;   
    }
   
    delete l_triggerWords;
}
        
        
        

        
         
    
    

    
    

#include "dataextraction.h"
#include "CFunctions.h"
#include <iostream>

int main()
{
    CDataExtraction extractor;  //Extractor
    CFunctions function;        //Various functions, here: compare

    extractor.addData();

    bool end = false;
    do
    {
        std::cout << "**** Ministerium fuer Justiz ****\n";
        std::cout << "[E]xtract data from a selected subject of crime.\n";
        std::cout << "[H]elp and information.\n";
        std::cout << "[C]lose programm.\n";
        std::cout << ">";
        std::string sInput;
        function.m_getline(sInput); 
    
        //"E": extract data
        if(function.compare(sInput.c_str(), "E") == true)
            extractor.extractData();
        //"H": call help
        else if(function.compare(sInput.c_str(), "H") == true)
            extractor.help();
        //"C": close programm
        else if(function.compare(sInput.c_str(), "C") == true)
            end=true;
        //Wrong input
        else
            std::cout << "Wrong input!\n";

        std::cout << "\n\n";
    }while(end==false);

    //Leave programm
    std::cout << "Closing programm...\n";
}

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
        std::cout << "**** Ministerium für Justiz ****\n";
        std::cout << "[D]aten einer verdächtigen Person extrahieren.\n";
        std::cout << "[H]ilfe und Informationen.\n";
        std::cout << "[P]rogramm beenden.\n";
        std::cout << ">";
        std::string sInput;
        function.m_getline(sInput); 
    
        //"E": extract data
        if(function.compare(sInput.c_str(), "D") == true)
            extractor.extractData();
        //"H": call help
        else if(function.compare(sInput.c_str(), "H") == true)
            extractor.help();
        //"C": close programm
        else if(function.compare(sInput.c_str(), "P") == true)
            end=true;
        //Wrong input
        else
            std::cout << "Falsche Eingabe!\n";

        std::cout << "\n\n";
    }while(end==false);

    //Leave programm
    std::cout << "Programm wird beendet...\n";
}

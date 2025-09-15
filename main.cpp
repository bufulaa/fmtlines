#include <iostream>
#include <conio.h>
#include <fstream>
#include <filesystem>
#include <windows.h>

using std::cout;
using std::cin;
using std::endl;

int main();

std::string
inputfile = "input.txt",
outputfile = "output.txt";

void backToMain(std::string msg) {
    cout << msg << "\n\n( press any key to continue )";
    _getch();
    main();
}

void asciiFlowToPrints() {
    system("cls");
    
    std::string
    placeholder = "\%LINE\%\n",
    format_const = "<< \"" + placeholder + "\"",
    format = format_const,
    format_input,
    line,
    output = "";
    
    cout << "Enter format, default is:\n " << format_const << "\n\ntype \"default\" to leave it as is:\n";
    
    std::getline(std::cin, format_input);

    std::ifstream inputtext(inputfile);
    std::ofstream outputtext(outputfile);

    if (format_input != "default") { format_const = format_input; format = format_const; }
    
    size_t pos = format_const.find(placeholder);
    
    if (!std::filesystem::exists(inputfile)) { backToMain("No " + inputfile + " exist"); return; }
    if (!inputtext.is_open()) { backToMain("Unable to open " + inputfile); return; }
    if (!outputtext.is_open()) { backToMain("Unable to open " + outputfile); return; }
    
    system("cls");

    cout << "Format: " << format_const << endl << endl;
    
    while (std::getline(inputtext, line)) {
        if (pos != std::string::npos) format.replace(pos, placeholder.length(), line);
        outputtext << format + "\n";
        output = output + format + "\n";
        format = format_const;
    }

    inputtext.close();
    outputtext.close();

    cout << output;

    backToMain("\nOutput has been printed to " + outputfile);
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    
    if (!std::filesystem::exists(inputfile)) { std::ofstream text(inputfile); }
    
    system("cls");
        
    std::string response;

    cout
    << "Have you put your text inside " + inputfile << "?"
    << "\n\nDone? (y/exit) ";

    std::getline(cin, response);

    if (response == "exit") { exit(0); return 0; }
    if (response != "y" ) { main(); return 0; }
    
    asciiFlowToPrints();
    return 0;
}


#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

void inputCountLine(int& sizeFilesByLines) {
    std::cout << "Specify the number of lines: ";
    
    int lines = 0;
    std::cin >> lines;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Seriously? This is not a number, but some kind of nonsense.\n";
        inputCountLine(sizeFilesByLines);
    }

    if (lines > 0) sizeFilesByLines = lines;
    else {
        std::cout << "Seriously? This is not a number, but some kind of nonsense.\n";
        return;
    }

    system("cls");
}
void chooseFile(int& sizeFilesByLines, bool& saveFirstNLastLines, const int countLines);

void menu(int& sizeFilesByLines, bool& saveFirstNLastLines) {
    std::cout << "raz-b ver: 0.2\n";
    std::cout << "0. Start\n";
    std::cout << "1. Specify the number of lines for splitting. Currently set to: " << sizeFilesByLines << std::endl;
    std::cout << "2. Keep original header & footer? Currently set to: " << std::boolalpha << saveFirstNLastLines << std::endl;

    int answer = 0;
    std::cin >> answer;
    switch (answer){
    case 0: 
        chooseFile(sizeFilesByLines, saveFirstNLastLines, sizeFilesByLines);
        break;
    case 1:
        inputCountLine(sizeFilesByLines);
        menu(sizeFilesByLines, saveFirstNLastLines);
        break;
    case 2:
        saveFirstNLastLines = !saveFirstNLastLines;
        system("cls");
        menu(sizeFilesByLines,saveFirstNLastLines);
        break;
     
    default:
        menu(sizeFilesByLines, saveFirstNLastLines);
        break;
    }

}

std::vector<fs::path> getListOfFiles() {
    
    std::vector<fs::path> outListPath;

    for (const auto& entry : fs::directory_iterator(".")) {
        if (entry.is_regular_file()) {
            outListPath.push_back(entry);
        }
    }

    return outListPath;

}

std::vector<std::string> readFile(fs::path file) {
    
    std::vector<std::string> fileByLine;
    std::ifstream inputFile(file);
    std::string line;
    if(inputFile){

        while (std::getline(inputFile, line)) {
            fileByLine.push_back(line);
        }

    }
    else {
        std::cout << "File said: 'Nope, not today!'\n";
    }
    return fileByLine;
}

void writeFile(std::vector<std::string> outFileByLine, std::string nameFile) {

    std::ofstream outFile(nameFile);

    for (const auto& i : outFileByLine) {
        outFile << i << "\n";
    }
    std::cout << "file " << nameFile << " writing succes\n";
}

void writeFileWithFirstNLast(std::vector<std::string> fileByLine, int countLines, std::string nameFile) {
    
    int countFiles = 0;
    countFiles = (fileByLine.size() + countLines - 1) / countLines; 
    
    
    std::vector<std::string> separetedFileByLines;
    separetedFileByLines.reserve(2 + countLines);

    std::string newFileName;
    
    for (int i = 0; i < countFiles; i++) {
        separetedFileByLines.clear();
        separetedFileByLines.push_back(fileByLine[0]);
        separetedFileByLines.insert(separetedFileByLines.end(), fileByLine.data() + 1 + i * countLines, fileByLine.data() + 1 + i * countLines + countLines);
        if (i + 1 != countFiles) separetedFileByLines.push_back(fileByLine.back());
        newFileName = nameFile;
        writeFile(separetedFileByLines, newFileName.insert(nameFile.find("."),( "_copy_" + std::to_string(i + 1 ))));
    }

    
}

void writeFileWithoutFirstNLast(std::vector<std::string> fileByLine, int countLines, std::string nameFile) { //дописать
    
    int countFiles = 0;
    countFiles = (fileByLine.size() + countLines - 1) / countLines;

    std::vector<std::string> separetedFileByLines;
    separetedFileByLines.reserve(countLines);

    std::string newFileName;

    for (int i = 0; i < countFiles; i++) {
        separetedFileByLines.clear();
        separetedFileByLines.insert(separetedFileByLines.end(), fileByLine.data() + i * countLines, fileByLine.data() + i * countLines + countLines);
        newFileName = nameFile;
        if (separetedFileByLines.empty()) break;
        writeFile(separetedFileByLines, newFileName.insert(nameFile.find("."), ("_copy_" + std::to_string(i + 1))));
    }
}

void chooseFile(int& sizeFilesByLines, bool& saveFirstNLastLines, const int countLines) {
    std::vector<fs::path> paths = getListOfFiles();

    int iterator = 0;

    for (const auto& i : paths) {
        iterator++;
        std::cout << iterator << ':' << i.string().erase(0,2) << std::endl;
    }
    std::cout << "Select file to split: ";
    
    int choosenFile = -1;
    std::cin >> choosenFile;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Seriously? This is not a number, but some kind of nonsense.\n";
        chooseFile(sizeFilesByLines, saveFirstNLastLines, countLines);
    }
    if (choosenFile > 0 && choosenFile <= paths.size()) {
        std::cout << "Choosen file: " << paths[choosenFile - 1].string().erase(0, 2) << std::endl;
    }
    else{
        std::cout << "Out of range...\n";
        chooseFile(sizeFilesByLines, saveFirstNLastLines, countLines);
    }

    std::vector<std::string> separetedFile = readFile(paths[choosenFile - 1]);

    if (separetedFile.empty()) {
        std::cout << "file empty :)\n";
        chooseFile(sizeFilesByLines, saveFirstNLastLines, countLines);
    }

    if (saveFirstNLastLines)
        writeFileWithFirstNLast(separetedFile, countLines, paths[choosenFile-1].string().erase(0,2));
    else
        writeFileWithoutFirstNLast(separetedFile, countLines, paths[choosenFile - 1].string().erase(0, 2));



}

int main() {

    //main menu

    int sizeFilesByLines = 10;
    bool saveFirstNLastLines = false;

    menu(sizeFilesByLines, saveFirstNLastLines);


	return 0;
}
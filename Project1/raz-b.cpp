#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

void filesSheeesh(std::vector<std::string> filesList,int i) {
    int numfile = 0;
    std::cout << "choose file: ";
    std::cin >> numfile;
    std::cout << "its " << filesList[numfile] << "\nin progress . . .\n";

    std::ifstream file(filesList[numfile]);

    if (!file.is_open()) {
        std::cerr << "file HYETA\n";
        return;
    }

    std::vector<std::string> fileByLines;
    std::string line;
    while (std::getline(file, line)) {
        fileByLines.push_back(line);
    }

    file.close();

    int targetNumFiles = (fileByLines.size() - 2) / i;
    std::cout << "files will be created:" << targetNumFiles << std::endl;

    std::string fileNameOut;

    for (int j = 0; j < targetNumFiles; j++) {
        fileNameOut = "copy" + std::to_string(j + 1) + '_' + filesList[numfile];
        std::cout << fileNameOut << std::endl;
        std::ofstream outfile(fileNameOut);
        if (!outfile) {
            std::cerr << "lox xuli))" << std::endl;
            return;
        }

        outfile << fileByLines[0] << std::endl;
        for (int y = 1 + (i * j); y <= i * j + i; y++) {
            outfile << fileByLines[y] << std::endl;
        }
        outfile << fileByLines[fileByLines.size() - 1];
        outfile.close();
    }
}

int main() {

    std::cout<<"enter the size of the final file in the lines\n";
    int i = 0;
    std::cin>>i;
    std::cout << "well, files well be split into " << i << " lines\n";

    std::string path =".";
    std::vector<std::string> filesList;
    try{
        std::cout<<"list of"<<path<<":\n";

        int counter = 0;

        for(const auto& entry:fs::directory_iterator(path)){
            std::cout<<counter<<": " << entry.path().filename().string() << std::endl;
            filesList.push_back(entry.path().filename().string());
            counter++;
        }
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "pshol naxui: " << e.what() << '\n';
    }

    while (true) {
        filesSheeesh(filesList, i);
    }
    

	return 0;
}

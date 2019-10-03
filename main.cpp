#include <iostream>
#include <fstream>
#include <vector>

// Main functionalities:
void printUsage();
void listTasks();
void addTask(std::string taskToAdd);
void removeTask(int taskNum);
void checkTask(int taskNum);

// Auxiliary functions:
int countLines(std::string fileName);
std::vector<std::string> getRemainingLines(const std::string& fileName, int taskNum);
void removeLine(const std::string& fileName, int taskNum);
void writeLinesToFile(std::vector<std::string> lines, std::string fileName);


int main(int argc, char* argv[]) {

    std::string firstArgument = std::string(argv[1]);

    if (argc == 1) {
        printUsage();
    } else {
        if (firstArgument == "-l" ) {
            listTasks();
        } else if (firstArgument == "-a") {
            if (argc != 3) {
                std::cout << "Unable to add: provide ONE task." << std::endl;
            } else {
                addTask(std::string(argv[2]));
            }
        } else if (firstArgument == "-r") {
            if (argc != 3) {
                std::cout << "Unable to remove: no index provided" << std::endl;
            } else {
                removeTask(std::stoi(argv[2]));
            }
        } else if (firstArgument == "-c") {
            if (argc != 3) {
                std::cout << "Unable to check: no index provided" << std::endl;
            } else {
                checkTask(std::stoi(argv[2]));
            }
        } else {
            std::cout << "Unsupported argument" << std::endl;
        }
    }
    return 0;
}

void printUsage() {
    std::cout << std::endl;
    std::cout << "Command Line Todo application" << std::endl;
    std::cout << "=============================" << std::endl;
    std::cout << std::endl;
    std::cout << "Command line arguments:" << std::endl;
    std::cout << "-l \t Lists all the tasks" << std::endl;
    std::cout << "-a \t Adds a new task" << std::endl;
    std::cout << "-r \t Removes a task" << std::endl;
    std::cout << "-c \t Completes a task" << std::endl;
    std::cout << std::endl;
}

void listTasks() {

    std::ifstream inputFile("../tasks.txt");
    std::string line;
    int lineNumber = 1;

    while (getline(inputFile, line)) {
        std::cout << lineNumber << " - " << line << std::endl;
        lineNumber++;
    }

    if (lineNumber == 1) {
        std::cout << "No tasks for today! :)" << std::endl;
    }
}

void addTask(std::string taskToAdd) {
    std::ofstream outputFile("../tasks.txt", std::ios_base::app);
    outputFile << "[ ] " << taskToAdd << std::endl;
}

int countLines(std::string fileName) {
    std::ifstream inputFile(fileName);
    std::string line;
    int count = 0;
    while (getline(inputFile, line)) {
        count++;
    }
    inputFile.close();
    return count;
}

std::vector<std::string> getRemainingLines(const std::string& fileName, int taskNum) {
    std::vector<std::string> lines;
    std::ifstream inputFile(fileName);
    std::string line;
    int index = 1;
    while (getline(inputFile, line)) {
        if (taskNum == index) {
            index++;
        } else {
            lines.push_back(line);
            index++;
        }
    }
    inputFile.close();
    return lines;
}

void writeLinesToFile(std::vector<std::string> lines, std::string fileName) {
    std::ofstream outputFile(fileName);
    for (const std::string& l : lines) {
        outputFile << l << std::endl;
    }
    outputFile.close();
}

void removeLine(const std::string& fileName, int taskNum){
    std::vector<std::string> lines = getRemainingLines(fileName, taskNum);
    writeLinesToFile(lines, fileName);
}

void removeTask(int taskNum) {
    std::string fileName = "../tasks.txt";
    int lineCount = countLines(fileName);
    if (taskNum > lineCount || taskNum < 1) {
        std::cout << "Unable to remove: index is out of bounds" << std::endl;
    } else {
        removeLine(fileName, taskNum);
    }
}

void checkTask(int taskNum) {
    std::string fileName = "../tasks.txt";
    int lineCount = countLines(fileName);
    if (taskNum > lineCount) {
        std::cout << "Unable to check: index is out of bounds" << std::endl;
    } else {
        std::vector<std::string> lines;
        std::ifstream inputFile(fileName);
        std::string line;
        while (getline(inputFile, line)) {
            lines.push_back(line);
        }
        inputFile.close();
        lines[taskNum - 1].replace(1, 1, "x");

        writeLinesToFile(lines, fileName);
    }
}
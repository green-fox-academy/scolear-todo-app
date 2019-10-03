#include <iostream>
#include <fstream>
#include <vector>

void printUsage();
void listTasks();
void addTask(std::string taskToAdd);
int countLines(std::string fileName);
void removeTask(int taskNum);


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
    outputFile << taskToAdd << std::endl;
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

void removeTask(int taskNum) {
    std::string fileName = "../tasks.txt";
    int lineCount = countLines(fileName);
    if (taskNum > lineCount) {
        std::cout << "Unable to remove: index is out of bounds" << std::endl;
    } else {
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

        std::ofstream outputFile(fileName);
        for (const std::string& l : lines) {
            outputFile << l << std::endl;
        }
        outputFile.close();
    }
}
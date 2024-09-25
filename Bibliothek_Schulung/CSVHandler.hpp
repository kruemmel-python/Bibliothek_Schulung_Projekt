#ifndef CSVHANDLER_HPP
#define CSVHANDLER_HPP

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

class CSVHandler {
public:
    static std::vector<std::vector<std::string>> readCSV(const std::string& filename);
    static void writeCSV(const std::string& filename, const std::vector<std::vector<std::string>>& data);
    static void writeCSVAppend(const std::string& filename, const std::vector<std::vector<std::string>>& data); // Methode zum Anhängen
};

#endif // CSVHANDLER_HPP

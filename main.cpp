#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <string>
#include <sstream>
#include <matplotlibcpp.h>


using namespace std;
namespace plt = matplotlibcpp;

class ReadCsv{

protected:
  std::vector<double> plotPoints;

public:

  ReadCsv()
  {
    cout << "[CSV] Constructed !" << endl;
  }
  ~ReadCsv(){}

  std::vector<std::pair<std::string, std::vector<double>>> readFile (std::string filename, unsigned int MaxIndex){
    /** Reads a CSV file into a vector of <string, vector<int>> pairs where
     each pair represents <column name, column values>*/

    // Create a vector of <string, double vector> pairs to store the result
    std::vector<std::pair<std::string, std::vector<double>>> result;

    // Create an input filestream
    std::ifstream myFile(filename);

    if(!myFile.is_open()) throw std::runtime_error("[CSV] Could not open file");
    std::string line, colname;
    double val;

    if(myFile.good())
    {
      cout << "[CSV] Inside !" << endl;
      // Extract the first line in the file
      std::getline(myFile, line);

      // Create a stringstream from line
      std::stringstream ss(line);
      // Extract each column name

      while(std::getline(ss, colname, ',')){

        // Initialize and add <colname, double vector> pairs to result
        result.push_back({colname, std::vector<double> {}});
      }
    }

    // Read data, line by line
    while(std::getline(myFile, line))
    {
      // Create a stringstream of the current line
      std::stringstream ss(line);

      // Keep track of the current column index
      unsigned int colIdx = 0;

      // Extract each double value till colum index is 26
      while(ss >> val){

        // Add the current integer to the 'colIdx' column's values vector
        result.at(colIdx).second.push_back(val);

        // If the next token is a comma, ignore it and move on
        if(ss.peek() == ',') ss.ignore();

        // Increment the column index
        colIdx++;
      }
    }

    myFile.close();
    return result;
  }

  void plotData( std::vector<std::pair<std::string, std::vector<double>>> output ){

    for(const auto& it : output)
     {
         string colName = it.first; cout << "###### column Name: " << colName << endl;
         std::vector<double> dataVect = it.second;
         std::vector<double> points;

         for (const auto& entry : dataVect)
         {
           //cout << "Data [" << "" << "]:" << entry << endl;
           points.push_back(entry);
         }
         plt::named_plot(colName, points, "r"); plt::title("Trajectory");
         plt::legend(); plt::show();
     }
  }

};



int main()
{
  ReadCsv Obj;
  std::vector<std::pair<std::string, std::vector<double>>> output = Obj.readFile("/home/mujib/Desktop/experiment1.csv", 26);
  Obj.plotData(output);

  return 0;
}

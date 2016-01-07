#ifndef CSVROW
#define CSVROW




#include "heads.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

class CSVRow
{
public:
    double const& operator[](std::size_t index) const
    {
        return m_data[index];
    }
    std::size_t size() const
    {
        return m_data.size();
    }

    void readNextRow(std::istream& str)
    {
        std::string line;
        std::getline(str, line);

        std::stringstream lineStream(line);
        std::string cell;
        float fcell;
        m_data.clear();
        while(std::getline(lineStream, cell, ',')) //by ' '
        {
            fcell = atof(cell.c_str());
            m_data.push_back(fcell);
        }
    }
private:
    std::vector<double> m_data;

};

std::istream& operator>>(std::istream& str, CSVRow& data)
{
    data.readNextRow(str);
    return str;
}

/*
 * int main()
 * {
 *      std::ifstream file("fimename.csv");
 *      CSVRow row;
 *      while(file >> row)
 *      {
 *          std::cout << "4th Element(" << row[3] << ")/n";
 *      }
 * }
*/

#endif // CSVROW

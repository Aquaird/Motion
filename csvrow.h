#ifndef CSVROW
#define CSVROW

#endif // CSVROW


#include "heads.h"

class CSVRow
{
public:
    std::string const& operator[](std::size_t index) const
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

        m_data.clear();
        while(std::getline(lineStream, cell, ' ')) //by ' '
        {
            m_data.push_back(cell);
        }
    }
private:
    std::vector<int> m_data;

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

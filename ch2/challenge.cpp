#include <iostream>

#include <fstream>
#include <sstream>
#include <array>

#include <iomanip> // für Manip über Flux
#include <numeric> // für accumulate 

constexpr int numRows = 4;
constexpr int numCols = 4;

std::array< std::array<float, numCols>, numRows > matrix;

int main()
{
    std::ifstream file("numbers.csv");

	// TODO: Check wheter file can be opened
    if(!file){
        std::cerr << "Problem bein Oefnen!";
        return 1;
    }

    // TODO: Read the matrix from file
    for(int i{0}; i<numRows; i++){
        for(int j{0}; j<numCols; j++){
            file >> matrix.at(i).at(j);
        }
    }

    // Close the file
    file.close();

    // Print Matrix in consol
    for(int i{0}; i<numRows; i++){
        for(int j{0}; j<numCols; j++){
            std::cout << std::setw(6) << matrix.at(i).at(j) << " ";
            //std::cout << std::setw(6) << std::left << matrix.at(i).at(j) << " ";
        }
        std::cout << std::endl;
    }

    // TODO: Calculate the sums
    float sum{0};
    for(int i{0}; i<numRows; i++){
        sum = std::accumulate(matrix.at(i).begin(), matrix.at(i).end(), sum);
    }

    // TODO: Display the sums
    std::cout << "Matrix summe = " << sum << std::endl;

    return 0;
}

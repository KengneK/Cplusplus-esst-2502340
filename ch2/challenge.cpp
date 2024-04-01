#include <iostream>

#include <fstream>
#include <sstream>
#include <array>

#include <iomanip> // für Manip über Flux
#include <numeric> // für accumulate 
#include <algorithm> // für foreach

constexpr int numRows = 4;
constexpr int numCols = 4;

std::array< std::array<float, numCols>, numRows > matrix;

template<typename T, std::size_t SIZE>
auto print_my_array( std::array<T, SIZE> &ar, const char *name_array) -> void{

    int i{0};
    for(const T &val: ar){
        std::cout << name_array << "[" << i++ << "] = " << val << std::endl;
    }
}


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

    std::array<float, numRows> horSum{};
    std::array<float, numCols> verSum{};
    for(int i{0}; i<numRows; i++){
        for(int j{0}; j<numCols; j++){
            horSum.at(i) += matrix.at(i).at(j);
            verSum.at(j) += matrix.at(i).at(j);
        }
    }

    // TODO: Display the sums
    std::cout << "Matrix summe = " << sum << std::endl;
    print_my_array(horSum, "horSum");
    print_my_array(verSum, "verSum");

    return 0;
}

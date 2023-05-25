//  main.cpp
//  Radix_Sort
//
//  Created by Martin Gregory Sendrowicz on 5/23/23.

#include "IO.hpp"

#include <iostream>
#include <fstream>


//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
int main() {
    
    
    std::ifstream in ;
    IO io ;
    io.load_file( in ) ;
    
    std::ofstream out ;
    io.write_file( out ) ;

    
    
    
    return 0;
}
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

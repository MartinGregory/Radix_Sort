//  main.cpp
//  Radix_Sort
//
//  Created by Martin Gregory Sendrowicz on 5/23/23.

#include "IO.hpp"
#include "LinkedListQueue.hpp"
#include "RadixSort.hpp"

#include <iostream>
#include <fstream>


//....................................................................................................
template< typename T, int SIZE>
void sort(){
    
    std::ifstream in ;
    IO<T> io ;
    io.load_file( in ) ;
    
    RadixSort<T,SIZE> * rs = new RadixSort<T,SIZE>( io.data ) ;
    io.data = (*rs).radix_sort() ;
    
    std::ofstream out ;
    io.write_file( out ) ;
}
//....................................................................................................

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
int main() {
    
    // Integer Numeric Data
    sort<int,10>() ;
    
    // Floating Point Numeric Data -- NOT implemented yet...
    //sort<double,10>() ;
    
    // ASCII Data
    //sort<char,256>() ;

    return 0;
}
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

//
//  IO.hpp
//  Radix_Sort
//
//  Created by Martin Gregory Sendrowicz on 5/24/23.
//

#ifndef _IO_H_
#define _IO_H_

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
class IO {
    
    std::string input_file_name ;
    std::string output_file_name ;
    
    std::vector<double> data ;

public:
    
    IO() = default ;
    void load_file( std::ifstream & in ) ;
    void write_file( std::ofstream & out ) ;
    
} ;
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

#endif /* _IO_H_ */



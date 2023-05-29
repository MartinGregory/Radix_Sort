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
template< typename T>
class IO {
    
    std::string input_file_name ;
    std::string output_file_name ;
    
public:
    std::vector<T> data ;

public:
    
    IO() = default ;
    
    //................................................................................................
    template< typename S>
    void check_if_open( S & stream, std::string file_name ){
        if( !stream.is_open() ){
            std::cerr << "Could not open " << file_name << ", exiting..." << std::endl ;
            exit( EXIT_FAILURE ) ;
        }
    }
    //................................................................................................
    void load_file( std::ifstream & in ){
        
        std::cin.clear() ;
        //std::cin.ignore( std::numeric_limits<std::streamsize>::max(),'\n' ) ;
        
        std::cout << "Enter input file name (e.g. input.txt): " ;
        std::cin >> (*this).input_file_name ;
        std::cout << "thanks you entered: " << (*this).input_file_name << std::endl ;
        
        in.open( (*this).input_file_name )  ; check_if_open( in,(*this).input_file_name ) ;
        
        T token ; int size = 0 ;
        while( !in.eof() ){
            
            in >> token ;
            (*this).data.emplace_back( token ) ;
            size++ ;
        }
        in.close() ;
        (*this).data.resize( size ) ;
        
        std::cout << "Below is the extracted data:\n" ;
        std::for_each( data.begin() , data.end() , []( const T & el ){ std::cout << el <<" "; }) ;
        std::cout << std::endl ;
    }
    //................................................................................................
    void write_file( std::ofstream & out ){
        
        std::cin.clear() ;
        //std::cin.ignore( std::numeric_limits<std::streamsize>::max(),'\n' ) ;
        
        std::cout << "Enter output file name (e.g. output.txt): " ;
        std::cin >> (*this).output_file_name ;
        std::cout << "thanks you entered: " << (*this).output_file_name << std::endl ;
        
        out.open( (*this).output_file_name )  ; check_if_open( out,(*this).output_file_name ) ;
        
        std::for_each( data.begin() , data.end() , [ & out ]( const T & el ){ out << el <<" "; }) ;
        std::cout << std::endl ;
        
        out.close() ;
    }
    //................................................................................................
} ;
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


#endif /* _IO_H_ */



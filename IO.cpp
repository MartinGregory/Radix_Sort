//
//  IO.cpp
//  Radix_Sort
//
//  Created by Martin Gregory Sendrowicz on 5/24/23.
//

#include "IO.hpp"


//....................................................................................................
template< typename T>
void check_if_open( T & stream, std::string file_name ){
    if( !stream.is_open() ){
        std::cerr << "Could not open " << file_name << ", exiting..." << std::endl ;
        exit( EXIT_FAILURE ) ;
    }
}
//....................................................................................................
void IO::load_file( std::ifstream & in ){
    
    std::cin.clear() ;
    //std::cin.ignore( std::numeric_limits<std::streamsize>::max(),'\n' ) ;
    
    std::cout << "Enter input file name (e.g. input.txt): " ;
    std::cin >> (*this).input_file_name ;
    std::cout << "thanks you entered: " << (*this).input_file_name << std::endl ;
    
    in.open( (*this).input_file_name )  ; check_if_open( in,(*this).input_file_name ) ;
    
    double token ;
    while( !in.eof() ){
        
        in >> token ;
        (*this).data.emplace_back(token) ;
    }
    in.close() ;
    
    std::cout << "Below is the extracted data:\n" ;
    std::for_each( data.begin() , data.end() , []( double & el ){ std::cout << el <<" "; }) ;
    std::cout << std::endl ;
}
//....................................................................................................
void IO::write_file( std::ofstream & out ){
    
    std::cin.clear() ;
    //std::cin.ignore( std::numeric_limits<std::streamsize>::max(),'\n' ) ;
    
    std::cout << "Enter output file name (e.g. output.txt): " ;
    std::cin >> (*this).output_file_name ;
    std::cout << "thanks you entered: " << (*this).output_file_name << std::endl ;
    
    out.open( (*this).output_file_name )  ; check_if_open( out,(*this).output_file_name ) ;
    
    std::for_each( data.begin() , data.end() , [ & out ]( double & el ){ out << el <<" "; }) ;
    std::cout << std::endl ;
    
    out.close() ;
}
//....................................................................................................

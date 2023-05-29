//
//  RadixSort.hpp
//  Radix_Sort
//
//  Created by Martin Gregory Sendrowicz on 5/28/23.
//

#ifndef _RadixSort_H_
#define _RadixSort_H_

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
template< class T, int SIZE >
class RadixSort{
    
    /* The SIZE of the Radix Sort Hash Table depends on the type of data we are sorting. I.e. 10
    if sorting whole numbers and 256 if sorting characters (ASCII). */
    static const int ht_size = SIZE ;
    
    LinkedListQueue< T >** hashTables [2] [ SIZE ] ;   // e.g. for numbers 2x10 matrix of ints

    /* The ‘index_r’ is the index pointing to the right-most digit of the given number i.e. the
    least significant digit. During consecutive iterations ‘index_r’ is incremented, one by one,
    all the way until it reaches the left-most digit i.e. the most significant digit. */
    int index_r ;
    /* RadixSort uses two HashTables so ‘index_h’ keeps track which HashTable we are currently
    using */
    int index_h ;
    
    /* The number of iterations will depend on the number of digits (+1) of the largest (to be
    sorted) value. */
    int iterations ;
    
    /* The ‘bucket’ is the index of the Hash Table. The ‘bucket’ is determined by the Hash
    Function */
    int bucket ;

    /* The ‘dt_size’ is the size of the data, i.e. how many umbers/chars are to be sorted */
    std::size_t dt_size ;
    
    /* The largest value among ALL the data. This is needed to establish how many iteration will
    the algorithm run for. */
    T largest_value ;
    
    /* Vector that stores ALL the input (to be sorted) data */
    std::vector< T > data ;
    
public:
    //....................................................................................................
    RadixSort( std::vector<T> & data ): index_r{1}, index_h{0}, bucket{0}, data{data} {
        
        /*Show the received data:*/
        (*this).data.shrink_to_fit() ;
        //show_data() ;
        
        /* First build the HashTables structure. We are working with 2 HashTables so the structure is
        a 2D-array. The elements (buckets) of each HashTable contain pointers to LinkedListQueue<T>.
        Ergo:
           ( 1 ): in each bucket allocate space for a pointer to a LinkedListQueue<T> */
        for( int ht=0 ; ht<2 ; ht++ )
            for( int bucket=0 ; bucket<(*this).ht_size ; ++bucket )
                (*this).hashTables[ ht ][ bucket ] = new LinkedListQueue<T> * ;
        
        /* ( 2 ): for each bucket's pointer allocate a new LinkedListQueue<T> and store the address into
        the corresponding pointer*/
        for( int ht=0 ; ht<2 ; ht++ )  // Radix Sort has two tables
            for( int bucket=0 ; bucket<(*this).ht_size ; bucket++ ){
                (*(*this).hashTables[ ht ][ bucket ]) = new LinkedListQueue< T >() ;
            }
        //show_table( 0 ) ;
        
        /* RadixSort needs the largest value (among ALL data) to determine the number of iterations */
        (*this).largest_value = (*this).data.at(0) ;
        auto it = (*this).data.begin() ;
        while( it != (*this).data.end() ){
            if( (*this).largest_value < *it )
                (*this).largest_value = *it ;
            it++ ;
        }
        (*this).iterations = count_digs( (*this).largest_value , 0 ) + 1 ;
        (*this).dt_size = data.size() ;
    }
    //....................................................................................................
    std::vector<T>& radix_sort(){

        /* Step 1:  Extract data one by one from the data vector into HashTable-0 */
        std::for_each( (*this).data.begin() , (*this).data.end() , [ this ]( T & el ){
            
        /* Step 2:  Get the Hash-Table bucket into which store data-i. */
            (*this).bucket = _Hash_Function(  get_digit_r( el , (*this).index_r , 0 )) ;
            
        /* Step 3:  Store data-i into Hash-Table 0 at the derived bucket. Remember beach bucket contains
        a pointer, so dereference it to get to the corresponding queue. */
            (*(*this).hashTables[ 0 ][ (*this).bucket ])->enqueue( el );
        });
        /* Step 4:  Repeat step 1 to step 3 until no more data ( i=data_size ) */
        
        show_table( 0 ) ;
        
        /* Step 5:  Update the right most digit r . */
        (*this).index_r++ ;

        T elem ;
        int bucket=0 ;
        int i=0 ;
        while( (*this).index_r <= (*this).iterations ){
            
            bucket = 0 ; i = 0 ;
            while( i < (*this).dt_size ){

        /* Step 6:  Extract data one by one from Hash-Table h. */
                while( true ){
                    elem = (*(*this).hashTables[ (*this).index_h ][ bucket ])->dequeue() ;
                    
                    i++ ;
                    if( elem == -1 ){ //dequeue() returns -1 is queue is empty.
                        i-- ;
                        bucket++ ;
                        break ;
                    }
        /* Step 7:  Get the bucket (index) where to store data-i. */
                    (*this).bucket = _Hash_Function(  get_digit_r( elem , (*this).index_r , 0 )) ;
                    
        /* Step 8:  Store data-i into Hash-Table h at the derived bucket. */
                    (*this).index_h = (( (*this).index_h+1 ) % 2 ) ;
                    (*(*this).hashTables[ (*this).index_h ][ (*this).bucket ])->enqueue( elem ) ;
                    (*this).index_h = (( (*this).index_h+1 ) % 2 ) ;
                }
            }
        /* Step 9:  Repeat step 6 to step 8 until no more data in Hash-Table h. ( i=data_size ) */
            
        /* Step 10: switch to the other Hash-Table. */
            (*this).index_h = ( ((*this).index_h+1 ) % 2 ) ;
            
            show_table( (*this).index_h ) ;
            
            (*this).index_r++ ;
        }
        /* Step 11:  Repeat step 6 to step 10 until r = iterations */

        /* Step 12:  Return the sorted data. */
        (*this).data.clear() ;
        i=0 ;
        while( i < (*this).dt_size ) {
            elem = (*(*this).hashTables[ (*this).index_h ][ 0 ])->dequeue() ;
            if( elem > -1 )
                (*this).data.emplace_back( elem ) ;
            i++ ;
        }
        return (*this).data ;
    }
    //....................................................................................................
    /* In RadixSort the HashFunction is the identity function: 1 maps to 1, 2 maps to 2, etc… */
    int _Hash_Function( T val ){
        return val ;
    }
    //....................................................................................................
    /* Returns the digit at the given index 'r'. The counting of the digits starts from the right-most digit
    of the given numerical value 'num'. When index 'r' decrements to zero, the digit 'd' is returned. Note
    that RadixSort applies zero-padding to all the 'num's that have less digits then the largest 'num' in
    the data. Thus, if e.g. the largest digit is 369, the currently evaluated 'num' is 17 and r is 3, this
    function will account for that and it will return 0. I implemented this function using a very Stack
    friendly tail recursion — i.e. the consecutive recursive call get popped of the Stack as the new call
    begging. */
    int get_digit_r( T num , int r , int d ){
        if( r==0 ) return d ;
        d = num % 10 ;
        return get_digit_r( num/10 , --r , d ) ;
    }
    //....................................................................................................
    /* Returns the number of digits 'i' in the given number ‘val'. (again Stack friendly tail recursion).
    Call this method with i=0 . The parameter 'val' should be that largest value among the given data. */
    int count_digs( int val , int i ){
        if( val==0 ) return i ;
        i++ ;
        return count_digs( val/10 , i ) ;
    }
    //....................................................................................................
    void show_table( int index_h ){
        std::cout << " - - - - - - - - - - - - - - - - \n" ;
        std::cout << " H A S H - T A B L E - "<< index_h << "\n" ;
        
        for( int bucket=0 ; bucket<(*this).ht_size ; ++bucket )
            std::cout <<"bucket "<<bucket<<" : "<< (*(*this).hashTables[ index_h ][ bucket ])->show_queue() ;
    }
    //....................................................................................................
    void show_data(){
        std::cout << "Below is the received data:\n" ;
        std::for_each( (*this).data.begin(), (*this).data.end(), [this]( T& el){std::cout << el << " " ;}) ;
        std::cout << std::endl ;
    }
    //....................................................................................................
} ;
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


#endif /* _RadixSort_H_ */

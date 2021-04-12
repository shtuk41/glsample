/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   helpers.h
 * Author: aleksander
 *
 * Created on December 12, 2019, 11:07 PM
 */

#ifndef HELPERS_H
#define HELPERS_H

 template < typename T > 
 std::string to_string( const T& n )
 {
    std::ostringstream stm ;
    stm << n ;
    return stm.str() ;
 }

#endif /* HELPERS_H */


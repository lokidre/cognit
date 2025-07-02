#! /usr/bin/octave -qf

source ("../common/read_vector.m") ;

K = read_vector ;

K = [ 1 ; K ] ;

X = roots(K)

# printf(" %g",X) ;


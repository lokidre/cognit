#! /usr/bin/octave -qf

source ("../common/read_matrix.m") ;

A = read_matrix ;

puts(cov(A)) ;

# printf("%g",cov(A)) ;


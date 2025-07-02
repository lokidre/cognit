#! /usr/bin/octave -qf

source ("../common/read_matrix.m") ;

A = read_matrix ;

[U S V] = svd(A)

# printf("%.16g",det(A)) ;




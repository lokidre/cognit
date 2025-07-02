#! /usr/bin/octave -qf

source("../common/read_matrix.m");

A = read_matrix;

[v, e] = eig(A)



# printf("%.16g",det(A)) ;


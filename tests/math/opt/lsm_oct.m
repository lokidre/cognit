#! /usr/bin/octave -qf

source ("../common/read_matrix.m") ;

A = read_matrix ;


[p, yf] = polyfit(A(1,:)',A(2,:)',1) ;

printf("%g %g",p) ;


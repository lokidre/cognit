#! /usr/bin/octave -qf

source ("../common/read_matrix.m") ;

A = read_matrix ;


printf("%g ",cov(A)) ;


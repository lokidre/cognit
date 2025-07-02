#! /usr/bin/octave -qf

source ("../common/read_vector.m") ;

A = read_vector ;

printf("%g",var(A)) ;


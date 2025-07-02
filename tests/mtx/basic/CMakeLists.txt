cmake_minimum_required(VERSION 3.16)

project(cognit-mtx-basic)

include(../../../scripts/tests.cmake)

addTest(mtx_eye)
addTest(mtx_add)

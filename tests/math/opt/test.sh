#! /bin/bash


echo "Testing LSM..."

. ../common/test_vector.sh


DATA_MASK="lsm"
TEST_BIN="./lsm"
OCT_BIN="./lsm_oct.m"

test_vector 2

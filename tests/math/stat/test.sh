#! /bin/bash

echo "testing mean..." ;
./mean_test.sh || exit 1

echo "testing standard deviation..." ;
./sd_test.sh || exit 1

echo "testing variance..." ;
./var_test.sh || exit 1

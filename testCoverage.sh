#!/bin/bash

sourceDirectory=$1

find . -iname "*.gcda" -print0 | xargs -0 rm -rf
lcov --zerocounters --directory "${sourceDirectory}"
cd main/bin
./testrunner
cd ../..
lcov --capture --directory "${sourceDirectory}" --output-file coverage.info
lcov --remove coverage.info "physic/Box2D/*" -o coverage.info
lcov --remove coverage.info "/usr/*" -o coverage.info
genhtml coverage.info --output-directory html --no-branch-coverage

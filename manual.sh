#!/bin/bash
rm bin/exe

make

cd bin

./exe manual 10

cd ..
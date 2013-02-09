@echo off

cd misclib
mingw32-make 
cd ..

cd compiler
mingw32-make 
cd ..

cd lib
mingw32-make 
cd ..

cd cobrun
mingw32-make 
cd ..

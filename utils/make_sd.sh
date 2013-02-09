# Extract all the keywords (except Intrinsic) and reformat them
./xtr_rw ../compiler/reswords.c >tc.tok
# Convert the yacc grammar into EBNF with some optimisation.
./y2l -O2 -p -ttc.tok ../compiler/htcobol.y >tc.ebnf
# Output the file tc.ps (implicit from tc.ebnf and -singlefile).
#Diagrams -singlefile -Scale 0.8 0.8 tc.ebnf
Diagrams -singlefile tc.ebnf
# Update the files in info
cp -f tc.ebnf tc.ps ../info
rm -f tc.tok tc.ebnf tc.ps

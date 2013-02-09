The NIST CCVS85 Test Suite
------------------------------------------------------------------------
This directory contains the NIST test program suite auxiliary utilities.


IMPORTANT NOTE:
The NIST test programs source is not included, but can be downloaded from the
here (1).

How to run the tests:
------------------------------------------------------------------------
- Download and expand the NIST test programs source.
- Prepare the setup (make setup) which does the following:
   - Run nc_exec85.pl to create EXEC85.cob (perl nc_exec85.pl newcob.val).
   - Compile EXEC85.cob to create EXEC85.
     - If TC compiler is installed in bin directories (make EXEC85).
     - If TC compiler is installed in development directories (mak.sh EXEC85).
   - Run EXEC85.
   - Run nc_extr.pl to create test programs (perl nc_extr.pl XXXXX002).
- Compile and run NIST test program as required.
   - Run all the tests (make -k -i -f ../Makefile_NC) from each subdirectory (in this case NC).
     You can select only one of the tests with the target program_name.PRT (i.e. NC101A.PRT).


NIST test modules:
------------------------------------------------------------------------

Core tests:

  NC - COBOL core tests
  SM - COPY sentence tests
  IC - CALL sentence tests

File I-O tests:

  SQ - Sequential file I-O tests
  RL - Relative file I-O tests
  IX - Indexed file I-O tests
  ST - SORT sentence tests

Advanced features:

  RW - REPORT SECTION tests
  CM - COMMUNICATION SECTION tests
  IF - Intrinsic Function tests
  SG - Segment tests
  DB - Debugging feature tests
  OB - Obsolete feature tests

------------------------------------------------------------------------

1) NIST test programs source
http://www.itl.nist.gov/div897/ctg/cobol_form.htm

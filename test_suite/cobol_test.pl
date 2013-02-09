#!/usr/bin/perl 
#
#  Copyright (C) 1999-2002 Glen Colbert, Bernard Giroud, David Essex
#  
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2, or (at your option)
#  any later version.
#  
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#  
#  You should have received a copy of the GNU General Public License
#  along with this software; see the file COPYING.  If not, write to
#  the Free Software Foundation, Inc., 59 Temple Place, Suite 330,
#  Boston, MA 02111-1307 USA
#
#----------------------------------------------------------------------------------- 
# Name        : test_cobol.pl
# Description : Perl script for the TinyCOBOL regression test/validation process.
# Author      : Glen Colbert
# Modified    : Bernard Giroud, David Essex, Stephen Connolly
#----------------------------------------------------------------------------------- 

#use strict;
#use testcobol;

# ######################################################
# # DECLARATIONS                                       #
# ######################################################

# Check configuration settings
if (!require('coboltest.inc'))  {
    die "Unable to find configuration settings file 'coboltest.inc'";
}

my $PGMVERSION="v010712";
my $SOURCE;
my $rc;
my @progvak;
my %TEST_STATUS;
my $SOURCE_DIR;
my $INSTR;
my $LIBS = "$PGM_LIBS_PATHS"  . "  $PGM_LIBS";
my $GROUP_SUCCESS;

# ######################################################
# # Set the TCOB_OPTIONS_PATH environment variable.    #
# # This is used by htcobol to set compiler defaults.  # 
# # Set the TCOB_RTCONFIG_PATH environment variable.   #
# # This is used by the RTL to set run-time defaults.  # 
# ######################################################
$ENV{"TCOB_OPTIONS_PATH"}  = $PGM_OPTIONS_PATH;
$ENV{"TCOB_RTCONFIG_PATH"} = $PGM_RTCONFIG_PATH;

# ######################################################
# # SUBROUTINES START HERE                             #
# ######################################################

sub make_executable 
{
 $COBOL_CLASSIC="NO";
 # ######################################################
 # # Test for existence of file.  If .cbl, use cobpp.   #
 # ######################################################
 if (-r "$SOURCE.cbl")   {
   system("$COB -X -E $SOURCE.cbl -o $SOURCE.cob");
   $COBOL_CLASSIC="YES";
   wait;
 }
 else   {
   if (-r "$SOURCE.cob")  {
   }
   else   {
      printf(STDERR "Cobol source code not found for $SOURCE test\n");
      return 1;
   }
 }
 # ######################################################
 # # Compile cobol source to an assembler source file   #
 # ######################################################
 #printf(STDOUT "$COB -P -S $SOURCE.cob 2>&1 >$SOURCE.scan\n");
 printf(STDOUT "Compiling program $SOURCE ... ");
 #$rc=system("$COB -P -S $SOURCE.cob >$SOURCE.scan 2>&1");
 #$rc=system("$COB -P -S $SOURCE.cob 2>&1 >$SOURCE.scan ");
 $rc=system("$COB -S $SOURCE.cob 2>&1 >$SOURCE.scan ");
 $rc = ($rc >> 8);
 printf(STDOUT "Compile return code = %d\n",$rc);
 if ($rc >= 16)   {
   printf(STDERR "Program %s failed to properly compile\n",$SOURCE);
   return 2;
 }
 # Note: the gstabs option is only valid in later version of GAS thus has been removed
 #$rc=system("$ASM  -o $SOURCE.o -as=$SOURCE.listing.0.txt --gstabs $SOURCE.s");
 #$rc=system("$ASM  -o $SOURCE.o -as=$SOURCE.listing.0.txt $SOURCE.s");
 $rc=system("$ASM -D -o $SOURCE.o -as=$SOURCE.listing.0.txt $SOURCE.s");

 if ($rc != 0)  {
   printf(STDERR "Program %s failed in assembler generation\n",$SOURCE);
   return 3;
 }
 $rc=system("grep -v 'LISTING' $SOURCE.listing.0.txt | sed '/^$$/d' >$SOURCE.txt ");

 #printf(STDERR "link : $GCCLD $LDFLAGS -o $SOURCE $SOURCE.o  $LIBS\n");
 $rc=system("$GCCLD $LDFLAGS -o $SOURCE $SOURCE.o  $LIBS");

 if ($rc != 0)   {
   printf(STDERR "Program %s failed to link edit\n",$SOURCE);
   return 4;
 }

 if ($COBOL_CLASSIC eq "YES")   {
   unlink("$SOURCE.cob");
 }
 unlink("$SOURCE.o");
 unlink("$SOURCE.s");
 unlink("$SOURCE.scan");
 unlink("$SOURCE.lis");
 unlink("$SOURCE.txt");
 #unlink("$SOURCE.listing.0.txt");
 $rc=system("rm -f temp.*.$SOURCE.cob");

 return 0;
}

# ######################################################
# # Make sure we have access to the tools.             #
# ######################################################
sub validate_setup
{
 $SETUP_OK="YES";
 my $CCXPROG01 = "/* test program */\n" .
                 "#include <stdio.h>\n" .
                 "int main(int ac, char *av[])\n" .
                 "{\n int r=0;\n" .
                 " printf(\"Hi there\");" .
                 " return r;\n}\n";
 my $ASMPROG01 = "testx.:\n.text\n    .align 16\n" .
                 ".globl main\nmain:\n     ret\n\n";
 my $COBPROG01 = "000010 IDENTIFICATION DIVISION.\n" .
                 "000011 PROGRAM-ID. BASIC.             \n" .
                 "000012                                \n" .
                 "000013 ENVIRONMENT DIVISION.          \n" .
                 "000014 CONFIGURATION SECTION.         \n" .
                 "000015*INPUT-OUTPUT SECTION.          \n" .
                 "000016                                \n" .
                 "000017 DATA DIVISION.                 \n" .
                 "000017 FILE SECTION.                  \n" .
                 "000018 WORKING-STORAGE SECTION.       \n" .
                 "000019 01   WS-COUNTERS.              \n" .
                 "000020      05 WS-COUNT-1       PIC X.\n" .
                 "000021                                \n" .
                 "000022 PROCEDURE DIVISION.            \n" .
                 "000023 0000-PROGRAM-ENTRY.            \n" .
                 "000024      STOP RUN.                 \n";
 
 printf(STDOUT "\n\nChecking to see if your kit is complete\n");

 # ######################################################
 # # Make sure we can compile a 'C' program.            #
 # ######################################################
 open (CPROG,">foo_c.c") 
     || die "Unable to write to directory";
 printf(CPROG "%s", $CCXPROG01);
 close (CPROG);

 $rc=system("$CCX -c foo_c.c");
 if ($rc != 0)   {
   $SETUP_OK = "NO";
   printf(STDERR "C compiler not executing properly\n");
 }

 # ######################################################
 # # Make sure we can assemble an output file           #
 # ######################################################
 open (APROG,">foo_s.s") 
     || die "Unable to write to directory";
 printf(APROG "%s", $ASMPROG01);
 close (APROG);

 $rc=system("$ASM -D -o foo_s.o -aslh=foo_s.listing foo_s.s");
 if ($rc != 0)   {
   $SETUP_OK = "NO";
   printf(STDERR "assembler not executing properly %d\n",$rc);
 }

 # ######################################################
 # # Check pre-processor                                #
 # ######################################################
 open (CPROG,">basic.cbl") 
     || die "Unable to write to directory";
 printf(CPROG "%s", $COBPROG01);
 close (CPROG);

 $rc=system("$COB -F -E basic.cbl -o basic.cob");
 if ($rc != 0)   {
   $SETUP_OK = "NO";
   printf(STDERR "Cobol preprocessor not executing properly %d\n",$rc);
 }

 # ######################################################
 # # Make sure that we have htcobol in path             #
 # ######################################################
# $rc=system("$COB -P -S basic.cob >/dev/null 2>&1");
 $rc=system("$COB -S basic.cob >/dev/null 2>&1");
 if ($rc != 0)   {
   $SETUP_OK = "NO";
   printf(STDERR "Cobol compiler not executing properly %d\n",$rc);
 }

 # ######################################################
 if ($SETUP_OK ne "YES") {
   setup_error();
   exit -1;
 }
 $v_line = `grep 'version' basic.s`;
 chop($v_line);
 unlink("basic.cbl");
 unlink("basic.cob");
 unlink("basic.s");
 unlink("basic.lis");
 $rc=system("rm -f temp.*.basic.cob");
 unlink("foo_s.o");
 unlink("foo_s.s");
 unlink("foo_s.listing");
 unlink("foo_c.c");
 unlink("foo_c.o");

 printf(STDOUT "Your kit looks complete.\n+++++++++++++++++++++++++\n\n");
}

# ######################################################
sub setup_error
{
 printf(STDOUT "The tools needed to perform these tests are not configured\n");
 printf(STDOUT "in a way that the tests can be run.  Check to make sure\n");
 printf(STDOUT "that the following variables are set up and usable:\n");

 printf(STDOUT "\$CCX=$CCX;");
# printf(STDOUT "\$LD=$LD;");
 printf(STDOUT "\$GCCLD=$GCCLD;");
 printf(STDOUT "\$ASM=$ASM;");
 printf(STDOUT "\$COB=$COB;");
}

# ######################################################
# # Make sure that we have htcobol in path             #
# ######################################################
sub just_compile
{
 $COBOL_CLASSIC="NO";
 # #############################################################
 # # Test for existence of file.  If '.cbl' use pre-processor. #
 # #############################################################
 if (-r "$SOURCE.cbl")   {
   system("$COB -F -E $SOURCE.cbl -o $SOURCE.cob");
   $COBOL_CLASSIC="YES";
   wait;
 }
 else   {
   if (-r "$SOURCE.cob")  {
   }
   else  {
      printf(STDERR "Cobol source code not found for $SOURCE test\n");
      return 1;
   }
 }
 # ######################################################
 # # Compile cobol source to an assembler source file   #
 # ######################################################
 printf(STDOUT "Compiling program $SOURCE ... ");
 #$rc=system("$COB -P -S $SOURCE >$SOURCE.scan 2>&1");
 $rc=system("$COB -S $SOURCE >$SOURCE.scan 2>&1");
 $rc = ($rc >> 8);
 printf(STDOUT "Compile return code = %d\n",$rc);
 if ($rc != 0)   {
    printf(STDERR "Program %s failed to properly compile\n",$SOURCE);
 }

 if ($progvak[1] eq "A")  {
   if ($rc != 0) {
      printf(STDERR "Program %s/%s could not compile!!\n",$SOURCE_DIR,$SOURCE);
      printf(STDERR "If this test fails, all other tests are invalid\n");
      printf(STDERR "Aborting the test run.\n");
      exit -1;
   }
 }

 if ($progvak[1] eq "T" || $progvak[1] eq "A" )  {
   if ($rc == 0) {
      $TEST_STATUS{$progvak[2]} = "PASS";
   }
   else  {
      $TEST_STATUS{$progvak[2]} = "FAIL";
      $GROUP_SUCCESS = "FAILED";
   }
 }
 if ($progvak[1] eq "F") {
   if ($rc == 0)   {
      $TEST_STATUS{$progvak[2]} = "FAIL";
      $GROUP_SUCCESS = "FAILED";
   }
   else  {
      $TEST_STATUS{$progvak[2]} = "PASS";
   }
 }
 if ($progvak[1] eq "W")  {
   if ($rc <= 4)  {
      $TEST_STATUS{$progvak[2]} = "PASS";
   }
   else  {
      $TEST_STATUS{$progvak[2]} = "FAIL";
      $GROUP_SUCCESS = "FAILED";
   }
 }
 if ($COBOL_CLASSIC eq "YES") {
    unlink("$SOURCE.cob");
 }
 unlink("$SOURCE.lis");
 if ($SOURCE_DIR ne "call_tests")  {
    unlink("$SOURCE.s");
 }
 unlink("$SOURCE.scan");
}

# #############################################
sub get_results
{
 my $TEST_COUNTER = 0;
 my $len;
 while ($INSTR = <TEST>)  {
   @progvar = split(/:/,$INSTR);
   chomp(@progvar);
   $len = scalar(@progvar);
   if ( $len > 3 )  {
      $TEST_COUNTER = $TEST_COUNTER + 1;
      $CURRENT_TEST= $progvar[0];
      $TEST_NAME{$progvar[0]} = $progvar[0];
      $TEST_DESC{$progvar[0]} = $progvar[3] . " : Expecting " . $progvar[2] . " got " .$progvar[1];
      if ($progvar[1] eq $progvar[2])  {
         $TEST_STATUS{$progvar[0]} = "PASS";
         print_results();
      }
      else  {
         $TEST_STATUS{$progvar[0]} = "FAIL";
         $GROUP_SUCCESS = "FAILED";
         print_results();
      }
   }
 }
 if ($TEST_COUNTER == 0) {
   $GROUP_SUCCESS = "FAILED";
 }
}
# #############################################
sub print_results
{
 printf(TEST_LOG "%5s: %5s %s\n",$CURRENT_TEST,$TEST_STATUS{$CURRENT_TEST},$TEST_DESC{$CURRENT_TEST});
}

sub std_test()
{
# ######################################################
# #                                                    #
# ######################################################
 chdir($SOURCE_DIR);
 open (TEST_LIST,"test.script");
 while ($TEST_LINE = <TEST_LIST>)  {
   @progvak = split(/:/,$TEST_LINE);
   chomp(@progvak);
   if (substr($progvak[0],0,1) ne "#")  {
      $GROUP_SUCCESS = "PASSED";
      $SOURCE = $progvak[0];
      unlink("$SOURCE");
      $TEST_TYPE= $progvak[1];
      $TEST_TEXT = $progvak[2];
#      $TEST_REQUIREMENT = $progvak[3];
      make_executable();
      printf(TEST_LOG "########################################################################\n");
      printf(TEST_LOG "# %-67s  #\n",$TEST_TEXT);
      printf(TEST_LOG "# Test Directory: %-25s Test File %-15s  #\n",$SOURCE_DIR,$SOURCE);
      printf(TEST_LOG "########################################################################\n\n");
      if (-e $SOURCE)  {
         $rc=system("./$SOURCE >> $SOURCE.txt");
         $rc = ($rc >> 8);
         if ($rc != 0)   {
            printf(STDOUT "Program run return code = %d\n",$rc);
            printf(STDERR "Program %s returned an unexpected return code\n",$SOURCE);
            printf(TEST_LOG "Program %s returned an unexpected return code\n",$SOURCE);
         }
         if ($TEST_TYPE eq "S")  {
            open(TEST,"<$SOURCE.txt");
            get_results();
            close(TEST);
            printf(TEST_LOG "  %-67s: %s\n\n",$TEST_TEXT,$GROUP_SUCCESS);
            unlink("$SOURCE");
            unlink("$SOURCE.lis");
            unlink("$SOURCE.txt");
            wait;
         }
         else  {
            printf(STDERR "Unknown test validation %s - %s tests\n",$SOURCE,$TEST_TEXT);
            printf(TEST_LOG "Unknown test validation %s - %s tests\n",$SOURCE,$TEST_TEXT);
         }
      }
      else {
         printf(STDERR "Could not generate %s - %s tests\n",$SOURCE,$TEST_TEXT);
         printf(TEST_LOG "Could not generate %s - %s tests\n",$SOURCE,$TEST_TEXT);
      }
   }
 }
 close(TEST_LIST);
 chdir("..");
}

sub std_call_tests()
{
 $LIBS=$LIBS  . " -L. -lcalls";
 #$LIBS=$PGM_LIBS  . " -L. -lcalls";

# ######################################################
# # Calling tests                                      #
# ######################################################

 chdir($SOURCE_DIR);
 system("ls -1 st*.c st*.cob >t_sub.idx");

 open (TEST_LIST,"t_sub.idx");
 while ($TEST_LINE = <TEST_LIST>) {
   chomp($TEST_LINE);
   @subname = split(/\./,$TEST_LINE,2);
   if ($subname[1] eq "cob")  {
      $SOURCE=$subname[0];
      just_compile();
      $cmd="$ASM -o " . $SOURCE . ".o " . $SOURCE . ".s";
      $rc=system($cmd);
   }
   else  {
      printf(STDOUT "Compiling subroutine %s\n", $subname[0]);
      $cmd="$CCX -c " . $TEST_LINE;
      $rc=system($cmd);
   }
 }
 close(TEST_LIST);
 unlink("t_sub.idx");
 # Collect all subroutines into one library
 $rc=system("ar cr libcalls.a st*.o");
 $rc=system("rm -f st*.o st*.s");
 $rc=system("rm -f temp.*.*.cob");
 chdir("..");
 std_test();
 # Remove the library
 $libfn=$SOURCE_DIR ."/libcalls.a";
 unlink($libfn);
}

sub std_compile_tests()
{
 $GROUP_SUCCESS = "PASSED";

# ######################################################
# # Compile only tests.  results are not executed.     #
# ######################################################
 printf(TEST_LOG "########################################################################\n");
 printf(TEST_LOG "# COMPILER ONLY TESTS - DIRECTORY compile_tests.                       #\n");
 printf(TEST_LOG "########################################################################\n");

 chdir($SOURCE_DIR);
 open (TEST_LIST,"test.script");
 while ($TEST_LINE = <TEST_LIST>)  {
   chomp($TEST_LINE);
   @progvak = split(/:/,$TEST_LINE);
   if (substr($progvak[0],0,1) ne "#") {
      $TEST_NAME{$progvak[2]} = $progvak[2];
#      chop($progvak[3]);
      $CURRENT_TEST= $progvak[2];
      $TEST_DESC{$progvak[2]} = $progvak[3];
      $SOURCE=$progvak[0];
      just_compile();
      print_results();
   }
 }
 close(TEST_LIST);
 printf(TEST_LOG "\n    COMPILER ONLY TESTS: %s\n\n",$GROUP_SUCCESS);
 $rc=system("rm -f temp.*.*.cob");
 chdir("..");
}

# ######################################################
# # MAIN LOGIC                                         #
# ######################################################
$LOG_FILE_NAME="test$$.log";
open(TEST_LOG,">$LOG_FILE_NAME") 
    || die "Unable to write log file";

printf(STDOUT "\nCobol test suite version %s\n",$PGMVERSION);
#printf(STDOUT "\nCobol test suite version %s\n",$PGMVERSION);
printf(TEST_LOG "Cobol test suite version %s\n\n",$PGMVERSION);

validate_setup();

printf(TEST_LOG "#######################################################\n");
printf(TEST_LOG "# Cobol regression test suite                         #\n");
printf(TEST_LOG "# Testing compiler:                                   #\n");
printf(TEST_LOG "# %s                       #\n",$v_line);
printf(TEST_LOG "#######################################################\n");
printf(STDOUT "#######################################################\n");
printf(STDOUT "# Testing compiler:                                   #\n");
printf(STDOUT "# %s                       #\n",$v_line);
printf(STDOUT "#######################################################\n");

# ######################################################
# # Tests are performed in line                        #
# ######################################################

$SOURCE_DIR="compile_tests";
std_compile_tests();

$SOURCE_DIR="format_tests";
std_test();

$SOURCE_DIR="seqio_tests";
std_test();
#system("rm -f seqio_tests/*.dat");

$SOURCE_DIR="lseqio_tests";
std_test();

$SOURCE_DIR="idxio_tests";
std_test();
#system("rm -f idxio_tests/*.dat idxio_tests/*.dbx idxio_tests/*.idx");

$SOURCE_DIR="relio_tests";
std_test();

$SOURCE_DIR="sortio_tests";
std_test();

$SOURCE_DIR="perform_tests";
std_test();

$SOURCE_DIR="condition_tests";
std_test();

$SOURCE_DIR="search_tests";
std_test();

$SOURCE_DIR="call_tests";
std_call_tests();


# ######################################################
# # Print test results.                                #
# ######################################################
printf(STDOUT "\n\n");
foreach $test (keys(%TEST_NAME)) {
  if ($TEST_STATUS{$test} eq "FAIL") {
      printf(STDOUT "Test %6s: %6s %s\n",$test,$TEST_STATUS{$test},$TEST_DESC{$test});
  }
}
printf(STDOUT "\n\n");

close (TEST_LOG);
printf(STDOUT "\n\nTest results are in %s\n\n",$LOG_FILE_NAME);
printf(STDOUT "Changes from baseline results:\n");
$rc=system("diff test.baseline $LOG_FILE_NAME | grep -a '^>'");
printf(STDOUT "\n\nTest results are in %s\n\n",$LOG_FILE_NAME);
printf(STDOUT "\n");

exit 0;


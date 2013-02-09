#!/usr/local/bin/perl -w
#
#  Copyright (C) 2001 David Essex
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

###########################################################################
#                                                                         #
# Perl script to extract EXEC85 COBOL program from NIST test file         #
#      and change SELECT clause file names                                #
#                                                                         #
###########################################################################


############### Globals ################

my $SW_start;
# Set to true to output program files
my $SW_output = "true";
#my $SW_output = "";
#
my $SW_nistfile = "true";
my $InString;
my $OutString;
my @InStringArray;
my @InStringArray1;
my $FileNameOut;
#my $FileNameLog = "logfile.txt";
#my $FileNameLog = $ARGV[1];
my $FileNameLog;
my @FileNameLogArray;
my $FileNameNIST = $ARGV[0];
my @SubPrmArray;
my $SubPrmItem;
my $PrgmInCntr = 0;
my $SubDirDel = "/";
my $SubDir    = "e85/";
# program name extention
my $PrgmNameExtention =  ".cob";
#
my $PrgmSubIn =   "SELECT  OPTIONAL POPULATION-FILE";
my $PrgmSubOut =  "SELECT POPULATION-FILE          ";
#
#------------------ File names begin ------------------# 
#
#\*     "XXXXX001." "../newcob.val"                                                   
my $PrgmFileIn01  = "XXXXX001.   ";
my $PrgmFileOut01 = "\"newcob.val\"";
#
#     "XXXXX002".                                                    
my $PrgmFileIn02  = "XXXXX002  ";
my $PrgmFileOut02 = "\"XXXXX002\"";
#
#     "XXXXX003".                                                    
my $PrgmFileIn03  = "XXXXX003";
my $PrgmFileOut03 = "\"XXXXX003\"";
#
#     "XXXXX055".                                                    
my $PrgmFileIn55  = "XXXXX055";
my $PrgmFileOut55 = "\"XXXXX055\"";
#
#     "XXXXX058" "make_pop_linux.txt"                                                   
my $PrgmFileIn58  = "XXXXX058";
my $PrgmFileOut58 = "\"make_pop_linux.txt\"";
#
#------------------ End globals ------------------# 

sub initialize_rtn ()
{

 @FileNameLogArray = <logfile*txt>;
 $FileNameLog = "logfile." . ($#FileNameLogArray + 2) . ".txt";

 if (-f $FileNameLog) {
   print "ERROR: file FileNameLog \"$FileNameLog\" exists\n";
   die;
 }
# print "FileNameLog = $FileNameLog;\n";

 open (NISTFILE, "< $FileNameNIST")
     or die "unable to open file \"$FileNameNIST\"";

 open (LOGFILE, "> $FileNameLog ")
     or die "unable to run \"$FileNameLog\"";

}

sub process_header ()
{

   print LOGFILE "* ---------------------------------------- *\n";
   print LOGFILE "head :" .  $_  . ":\n";
   $SW_start = 'True';
   $InString = $_;
   $InString =~ s/^\*HEADER,//g;
   $InString =~ s/ /:/;
   $InString =~ s/ //g;
   print LOGFILE "InString :" .  $InString  . ":\n";
   @InStringArray1 = split(/:/,  $InString);
   @InStringArray = split(/,/,  $InStringArray1[0]);
   for ($i=0; $i<=$#InStringArray; $i++) {
       print LOGFILE "InStringArray[$i] :" .  "$InStringArray[$i]"  . ":\n";
   }
}

sub determine_FileNameOut ()
{
#   $FileNameOut = $SubDir . 
   $FileNameOut = $InStringArray[$#InStringArray] . 
                  $PrgmNameExtention;
   
   print LOGFILE "FileNameOut :" . "$FileNameOut" . ":\n";
}

sub output_PgmFile ()
{
   print PGMFILE $InString . "\n";
}

#
#000600*INSTALLATION
sub process_line_06 ()
{
   $SubtStringIn1  = "000600 INSTALLATION";
   $SubtStringOut1 = "000600*INSTALLATION";

   $InString = $_;
   $InString =~ s/$SubtStringIn1/$SubtStringOut1/;
   output_PgmFile;
}

#000700*    "ON-SITE VALIDATION,
sub process_line_07 ()
{
   $SubtStringIn1  = "000700     \"ON-SITE VALIDATION,";
   $SubtStringOut1 = "000700*    \"ON-SITE VALIDATION,";

   $InString = $_;
   $InString =~ s/$SubtStringIn1/$SubtStringOut1/;
   output_PgmFile;
}

#000800*    "COBOL 85 VERSION
sub process_line_08 ()
{
   $SubtStringIn1  = "000800     \"COBOL 85 VERSION";
   $SubtStringOut1 = "000800*    \"COBOL 85 VERSION";

   $InString = $_;
   $InString =~ s/$SubtStringIn1/$SubtStringOut1/;
   output_PgmFile;
}

#my $PrgmFile55 =  "\"XXXXX055\"";
#my $PrgmFile58 =  "\"make_pop_linux.txt\"";

#002500     SELECT  OPTIONAL POPULATION-FILE                             EXEC84.2
#002600     ASSIGN TO                                                    EXEC84.2
#002700     XXXXX001.                                                    EXEC84.2
#
#\*     SELECT  OPTIONAL POPULATION-FILE                            
#     SELECT  POPULATION-FILE                                      
#     ASSIGN TO                                                    
#*     "XXXXX001"
#      "newcob.val"                                                   
#     ORGANIZATION LINE SEQUENTIAL                                     
#     ACCESS SEQUENTIAL.                                     
#
sub process_file01_24 ()
{
   $SubtStringIn1  = "002500     SELECT";
   $SubtStringOut1 = "002500*    SELECT";
   $SubtStringIn2  = "SELECT  OPTIONAL POPULATION-FILE";
   $SubtStringOut2 = "SELECT POPULATION-FILE          ";

   $InString = $_;
   $InString =~ s/$SubtStringIn1/$SubtStringOut1/;
   output_PgmFile;
   $InString = $_;
   $InString =~ s/$SubtStringIn2/$SubtStringOut2/;
   output_PgmFile;
}
    
sub process_file01_26 ()
{
   $SubtStringIn1  = "002700     XXXXX001.                   ";
   $SubtStringOut1 = "002700*    XXXXX001.                   ";
   $SubtStringOut2 = "002701     ORGANIZATION LINE SEQUENTIAL";
   $SubtStringOut3 = "002702     ACCESS SEQUENTIAL.          ";
#  $SubtStringIn2  = "XXXXX001.   ";
#  $PrgmFile01     = "newcob.val";

   $InString = $_;
   $InString =~ s/$SubtStringIn1/$SubtStringOut1/;
   output_PgmFile;
   $InString = $_;
   $InString =~ s/$PrgmFileIn01/$PrgmFileOut01/;
   output_PgmFile;
   $InString = $_;
   $InString =~ s/$SubtStringIn1/$SubtStringOut2/;
   output_PgmFile;
   $InString = $_;
   $InString =~ s/$SubtStringIn1/$SubtStringOut3/;
   output_PgmFile;
}

#002800     SELECT  SOURCE-COBOL-PROGRAMS                                EXEC84.2
#002900     ASSIGN TO                                                    EXEC84.2
#003000     XXXXX002                                                     EXEC84.2
#003100     ORGANIZATION SEQUENTIAL.                                     EXEC84.2
#
#     SELECT  SOURCE-COBOL-PROGRAMS                                
#     ASSIGN TO                                                    
#     "XXXXX002"                                                     
#     ORGANIZATION LINE SEQUENTIAL                                     
#*     ORGANIZATION SEQUENTIAL                                     
#     ACCESS SEQUENTIAL.                                     
#*     ORGANIZATION SEQUENTIAL.                                     
#
sub process_file02_29 ()
{
   $SubtStringIn1  = "003000     XXXXX002";
   $SubtStringOut1 = "003000*    XXXXX002";

   $InString = $_;
   $InString =~ s/$SubtStringIn1/$SubtStringOut1/;
   output_PgmFile;
   $InString = $_;
   $InString =~ s/$PrgmFileIn02/$PrgmFileOut02/;
   output_PgmFile;
}

sub process_file02_30 ()
{
   $SubtStringIn   = "003100     ORGANIZATION SEQUENTIAL.    ";
   $SubtStringOut1 = "003100*    ORGANIZATION SEQUENTIAL.    ";
   $SubtStringOut2 = "003100     ORGANIZATION LINE SEQUENTIAL";
   $SubtStringOut3 = "003101     ACCESS SEQUENTIAL.          ";

   $InString = $_;
   $InString =~ s/$SubtStringIn/$SubtStringOut1/;
   output_PgmFile;
   $InString = $_;
   $InString =~ s/$SubtStringIn/$SubtStringOut2/;
   output_PgmFile;
   $InString = $_;
   $InString =~ s/$SubtStringIn/$SubtStringOut3/;
   output_PgmFile;
}

#003200     SELECT  UPDATED-POPULATION-FILE                              EXEC84.2
#003300     ASSIGN TO                                                    EXEC84.2
#003400     XXXXX003.                                                    EXEC84.2
#
#     SELECT  UPDATED-POPULATION-FILE                              
#     ASSIGN TO                                                    
#     "XXXXX003".                                                    
#
sub process_file03_33 ()
{
   $SubtStringIn1  = "003400     XXXXX003.";
   $SubtStringOut1 = "003400*    XXXXX003.";
#  "XXXXX003".                                                    
#  $PrgmFileIn03  = "XXXXX003";
#  $PrgmFileOut03 = ""XXXXX003"";

   $InString = $_;
   $InString =~ s/$SubtStringIn1/$SubtStringOut1/;
   output_PgmFile;
   $InString = $_;
   $InString =~ s/$PrgmFileIn03.  /$PrgmFileOut03./;
   output_PgmFile;
}

#
#003500     SELECT  PRINT-FILE                                           EXEC84.2
#003600     ASSIGN TO                                                    EXEC84.2
#003700     XXXXX055.                                                    EXEC84.2
#
#     SELECT  PRINT-FILE                                           
#     ASSIGN TO                                                    
#     "XXXXX055".                                                    
sub process_file55_36 ()
{
   $SubtStringIn1  = "003700     XXXXX055.";
   $SubtStringOut1 = "003700*    XXXXX055.";
#  "XXXXX055".                                                    
#  $PrgmFileIn55  = "XXXXX055";
#  $PrgmFileOut55 = ""XXXXX055"";

   $InString = $_;
   $InString =~ s/$SubtStringIn1/$SubtStringOut1/;
   output_PgmFile;
   $InString = $_;
   $InString =~ s/$PrgmFileIn55.  /$PrgmFileOut55./;
   output_PgmFile;
}

#
#003800     SELECT  CONTROL-CARD-FILE                                    EXEC84.2
#003900     ASSIGN TO                                                    EXEC84.2
#004000     XXXXX058.                                                    EXEC84.2
#
#     SELECT  CONTROL-CARD-FILE                                    
#     ASSIGN TO                                                    
#*     "XXXXX058"                                                   
#     "make_pop_linux.txt"                                                   
#     ORGANIZATION LINE SEQUENTIAL                                     
#     ACCESS SEQUENTIAL.                                     
sub process_file58_39 ()
{
   $SubtStringIn1  = "004000     XXXXX058.";
   $SubtStringOut1 = "004000*    XXXXX058.";
   $SubtStringIn2  = "004000     XXXXX058.                   ";
   $SubtStringOut2 = "004001     ORGANIZATION LINE SEQUENTIAL";
   $SubtStringOut3 = "004002     ACCESS SEQUENTIAL.          ";
#     "XXXXX058" "make_pop_linux.txt"                                                   
# $PrgmFileIn58  = "XXXXX058";
# $PrgmFileOut58 = ""make_pop_linux.txt"";

   $InString = $_;
   $InString =~ s/$SubtStringIn1/$SubtStringOut1/;
   output_PgmFile;
   $InString = $_;
   $InString =~ s/$PrgmFileIn58\.           /$PrgmFileOut58/;
   output_PgmFile;
   $InString = $_;
   $InString =~ s/$SubtStringIn2/$SubtStringOut2/;
   output_PgmFile;
   $InString = $_;
   $InString =~ s/$SubtStringIn2/$SubtStringOut3/;
   output_PgmFile;
}

# -------------------- main begins here -------------------- # 

if ($#ARGV != 0) {
   print "ERROR: invalid number of arguments " . ($#ARGV + 1) . " != 1\n";
   die;
}

initialize_rtn;

#while ($SW_nistfile)
#read(NISTFILE, $inbuf, 81);
read(NISTFILE, $_, 81);
while ($SW_nistfile)
#while (<NISTFILE>)
#while ((<NISTFILE>) && ($SW_nistfile))
{
# $_ = $inbuf;
 chop;
 if ($SW_start) {
    if (/^\*END-OF,/) {
        print LOGFILE "tail :" . $_ . ":\n";
        $SW_start = '';
        if ($SW_output) {
           close(PGMFILE);
        }
        $SW_nistfile = '';
        close(NISTFILE);
    }
    else {
#        $PrgmInCntr++;
        if ($SW_output) {
           $PrgmInCntr++;
#           if (($PrgmInCntr > 23) && ($PrgmInCntr < 40)) {
           if (($PrgmInCntr ==  5) ||
               ($PrgmInCntr ==  6) ||
               ($PrgmInCntr ==  7) ||
               ($PrgmInCntr == 24) ||
               ($PrgmInCntr == 26) ||
               ($PrgmInCntr == 29) ||
               ($PrgmInCntr == 30) ||
               ($PrgmInCntr == 33) ||
               ($PrgmInCntr == 36) ||
               ($PrgmInCntr == 39)
                ) {
              if ($PrgmInCntr == 24) {
                 process_file01_24;
#              $InString = $_;
#              process_line25($_);
#              print PGMFILE $InString . "\n";
              }

              if ($PrgmInCntr ==  5) {
                 process_line_06;
              }
              if ($PrgmInCntr ==  6) {
                 process_line_07;
              }
              if ($PrgmInCntr ==  7) {
                 process_line_08;
              }
              if ($PrgmInCntr == 26) {
                 process_file01_26;
              }
              if ($PrgmInCntr == 29) {
                 process_file02_29;
              }
              if ($PrgmInCntr == 30) {
                 process_file02_30;
              }
              if ($PrgmInCntr == 33) {
                 process_file03_33;
              }
              if ($PrgmInCntr == 36) {
                 process_file55_36;
              }
              if ($PrgmInCntr == 39) {
                 process_file58_39;
              }
           }
           else {
              print PGMFILE $_ . "\n";
           }
        }
#        $PrgmInCntr++;
    }
 }
 else {
    if (/^\*HEADER,/) {
        process_header;
        determine_FileNameOut;
        if ($SW_output) {
            open (PGMFILE, "> $FileNameOut")
                  or die "unable to open output file \"$FileNameOut\"";
        }
    }
    else {
        print LOGFILE "* ---------------------------------------- *\n";
    	print LOGFILE "ignoring :" .  $_  . ":\n";
    }
 }
# read(NISTFILE, $inbuf, 81);
 read(NISTFILE, $_, 81);
}

print LOGFILE "* ---------------------------------------- *\n";
print LOGFILE "PrgmInCntr =" . $PrgmInCntr;

close(NISTFILE);
close(LOGFILE);

__END__

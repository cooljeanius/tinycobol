#!/bin/bash - 
#
#  Copyright (C) 2001 Bernard Giroud
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
gawk -v module=$1 ' 
BEGIN {FS=" ";
         print "Module : ",module
         print " Filename  "," Tot","  OK"," Fai"," Del"," Man"
         tot_tot = 0
         tot_ok = 0
         tot_failed = 0
         tot_deleted = 0
         tot_inspect = 0
         tot_pgm = 0
         tot_pgm_ok = 0
}
{
   if ($5 == "WERE" && $6 == "EXECUTED") {
      nr_ok = $1 + 0
      nr_tot = $3 + 0
      tot_tot = tot_tot + nr_tot
      tot_ok = tot_ok + nr_ok
      tot_pgm = tot_pgm + 1
   }
   if ($2 == "TEST(S)") {
      if ($3 == "FAILED") {
         nr_failed = $1 + 0
	 if ($1 == "NO") nr_failed = 0
         tot_failed = tot_failed + nr_failed
      }
      if ($3 == "DELETED") {
         nr_deleted = $1 + 0
	 if ($1 == "NO") nr_deleted = 0
         tot_deleted = tot_deleted + nr_deleted
      }
      if ($3 == "REQUIRE") {
         nr_inspect = $1 + 0
	 if ($1 == "NO") nr_inspect = 0
         tot_inspect = tot_inspect + nr_inspect
         stat = "  "
         if (nr_failed == 0) {
            stat = "OK"
            tot_pgm_ok = tot_pgm_ok + 1
            }
         printf "%11s %4d %4d %4d %4d %4d %s\n", FILENAME, nr_tot, nr_ok, nr_failed, nr_deleted, nr_inspect, stat
      }
   }
}
END {
   pc_success = (100 * tot_ok) / tot_tot
   printf "%11s %4d %4d %4d %4d %4d %4d %4d OK\n", "Total:    ", tot_tot, tot_ok, tot_failed, tot_deleted, tot_inspect, tot_pgm, tot_pgm_ok
   pc_pgms_ok = (100 * tot_pgm_ok) / tot_pgm
   print "    Percentages: pgms ok:", pc_pgms_ok, "%  Tests ok:", pc_success, "%"
}
' *.PRT >../$1.rpt

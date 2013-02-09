* 
*  Copyright (C) 2004 Rildo Pragana, Jose Vilmar Estacio de Souza, David Essex.
* 
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2, or (at your option)
*  any later version.
*  
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*  
*  You should have received a copy of the GNU General Public License
*  along with this software; see the file COPYING.  If not, write to
*  the Free Software Foundation, Inc., 59 Temple Place, Suite 330,
*  Boston, MA 02111-1307 USA
*
 identification division.
 program-id. subp01.
 environment division.
 input-output section.
 file-control.
   select f1 assign to "f1.txt"
      organization is line sequential.
   select fsort assign to "sort.bdb".
   select f2 assign to "f2.txt"
      organization is line sequential.
 data division.
 file section.
  fd f1.
  01 rec-f1.
    03  key-f1 pic 99.
    03 val-literal pic x(10).
  sd fsort.
  01 rec-fsort.
    03 key-fsort pic 99.
    03 filler pic x(10).
  fd f2.
  01 rec-f2 pic x(12).

 linkage section.
 01 var           pic x(256).

 procedure division using var.
 A100.
    open output f1.
    move 3 to key-f1
    move "t3" to val-literal
    write rec-f1
    move 2 to key-f1
    move "t2" to val-literal
    write rec-f1
    move 1 to key-f1
    move "t1" to val-literal
    write rec-f1
    close f1
    sort fsort ascending key  key-fsort  using f1 giving f2
    move 22 to return-code
*    display "var=" var ";"
    exit program.
*
  end program subp01.


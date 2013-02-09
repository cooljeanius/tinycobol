Test COBOL programs for re-directed and piped reads and 
writes using the ACCEPT/DISPLAY and READ/WRITE statements.

NOTE:
Use the 'ACCEPT ... ON EXCEPTION' clause to detect EOF on standard-input.
See 'test03a.cob' for details.

Usage:
#test03 < test03.input.txt

#test03a < test03a.input.txt
OR
#cat test03a.input.txt | test03a
OR
#cat test03a.input.txt | test03a | more

#test03b < test03a.input.txt
OR
#cat test03a.input.txt | test03b
OR
#cat test03a.input.txt | test03b | more

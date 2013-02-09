#
# Makefile to create binary form COBOL sources
#

prefix=/usr/local/
comp_prefix=/home/user/tc/development
exec_prefix=${comp_prefix}/compiler
g_includes=-I/usr/local/include
g_libraries=-L/usr/lib

CCX=gcc
#COB=${exec_prefix}/htcobol
COB=htcobol
ASM=as
RM=rm -f

COPYBOOKS= -I../copybooks -I.
INCLUDES=-I./ ${g_includes} 
#LIBS=${g_libraries} -L${comp_prefix}/lib -lhtcobol -ldb1 -lm -ldl
LIBS=${g_libraries} -L${comp_prefix}/lib -lhtcobol -ldb1 -lvbisam -lncurses -ldl -lm 
LDFLAGS=
COBFLAGS=-P ${COPYBOOKS} -F -T8 -t -D 
COBFLAGS1=-P ${COPYBOOKS} -F -T8 -t -D -m
ASMFLAGS=-D
CCXFLAGS=-g ${INCLUDES}

#%.cob : %.CBL
#%.s : %.cob
#	${COB} -T8 -S -P -D $*.cob

%.so : %.SUBPRG
	${COB} -o $@ $(COBFLAGS1) $*.SUBPRG $(LIBS)
	grep "error" $*.lis

%.EXE : %.CBL
	${COB} -o $@ $(COBFLAGS) $*.CBL $(LIBS)
	grep "error" $*.lis

%.PRT : %.EXE
	./$*.EXE 2>nl
	mv -f nl $*.RTE
	mv prt $*.PRT
#	${RM} $*.cob $*.lis* $*.o $*.s $*.scan $*.EXE

%.PRT : %.so
	${comp_prefix}/cobrun/htcobrun.sh $* 2>nl
	mv -f nl $*.RTE
	mv prt $*.PRT
#	${RM} $*.cob $*.lis* $*.o $*.s $*.scan $*.EXE

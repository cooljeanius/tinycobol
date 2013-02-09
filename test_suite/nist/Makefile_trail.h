#
# Makefile to create binary form COBOL sources
#

all: ${TARGETS}

report:
	../xtr_rpt.sh ${MODULE}
	diff ../${MODULE}.rpt ../${MODULE}_prev.rpt
	cat ../??.rpt >../nist.rpt
clean:
	@${RM} core *.cob *.lis* *.s* *.i *.EXE *.o *.so
#

cleanall: clean cleandat
	@${RM} *.PRT *.RTE

cleandat:
	@${RM} *.DAT* XXXXX001 XXXXX014 nl rpt

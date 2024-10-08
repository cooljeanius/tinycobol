ACLOCAL_AMFLAGS = -I m4 --install
DISTCLEANFILES = *~ autoscan.log build-aux/*~

SHELL=/bin/sh

@SET_MAKE@

prefix=@prefix@
exec_prefix=@exec_prefix@
bindir = ${exec_prefix}/bin
datadir = ${datarootdir}
datarootdir = ${prefix}/share
pkgdatadir = ${datarootdir}/htcobol
mandir = $(prefix)/man/man1
lib_dir=${exec_prefix}/lib
tcob_docdir=@tcob_docdir@
tcob_docdir1=${prefix}/doc/@tcob_docdir@

INSTTEXT1=${tcob_docdir}

RM=rm -fr
MKDIR = mkdir -p

INSTALL=@INSTALL@
INSTALL_DATA=@INSTALL_DATA@
INSTALL_DIR=$(INSTALL) -d -m 755
INSTALLdir=${INSTALL_DIR}
INSTALL_PROGRAM=$(INSTALL) -s -m 755

TEXTFILE01=README
TEXTFILE02=AUTHORS
TEXTFILE03=COPYING
TEXTFILE04=COPYING.LIB
TEXTFILE05=COPYRIGHT
TEXTFILE06=INSTALL
TEXTFILE07=STATUS
TEXTFILE08=HISTORY
TEXTFILE09=Readme.mingw32.txt
TEXTFILE10=Readme.cygwin.txt

subdirs=compiler lib libltdl cobrun info utils 
subdirs1=compiler lib libltdl cobrun info utils @tcob_cobf2f_dir1@ \
  test_suite test_suite/nist test.code

all: all-subdirs
all-subdirs:
	@for i in ${subdirs}; do \
		echo "Making all in $$i"; \
		(cd $$i; ${MAKE} all); \
	done
.PHONY: all-subdirs

install-data-local: all
	${INSTALL_DIR} $(DESTDIR)$(bindir)
	${INSTALL_DIR} $(DESTDIR)$(lib_dir)
	${INSTALL_DIR} $(DESTDIR)$(mandir)
	${INSTALL_DIR} $(DESTDIR)$(pkgdatadir)
	${INSTALL_DIR} $(DESTDIR)$(tcob_docdir)
	@for i in ${subdirs}; do \
		echo "Installing in $$i"; \
		(cd $$i; ${MAKE} install); \
	done
	${INSTALL_DATA} $(TEXTFILE01) $(DESTDIR)${tcob_docdir}/$(TEXTFILE01)
	${INSTALL_DATA} $(TEXTFILE02) $(DESTDIR)${tcob_docdir}/$(TEXTFILE02)
	${INSTALL_DATA} $(TEXTFILE03) $(DESTDIR)${tcob_docdir}/$(TEXTFILE03)
	${INSTALL_DATA} $(TEXTFILE04) $(DESTDIR)${tcob_docdir}/$(TEXTFILE04)
	${INSTALL_DATA} $(TEXTFILE05) $(DESTDIR)${tcob_docdir}/$(TEXTFILE05)
	${INSTALL_DATA} $(TEXTFILE06) $(DESTDIR)${tcob_docdir}/$(TEXTFILE06)
	${INSTALL_DATA} $(TEXTFILE07) $(DESTDIR)${tcob_docdir}/$(TEXTFILE07)
	${INSTALL_DATA} $(TEXTFILE08) $(DESTDIR)${tcob_docdir}/$(TEXTFILE08)
	${INSTALL_DATA} $(TEXTFILE09) $(DESTDIR)${tcob_docdir}/$(TEXTFILE09)
	${INSTALL_DATA} $(TEXTFILE10) $(DESTDIR)${tcob_docdir}/$(TEXTFILE10)

uninstall-local:
	@for i in ${subdirs}; do \
		echo "Un-Installing in $$i"; \
		(cd $$i; ${MAKE} uninstall); \
	done
	${RM} $(DESTDIR)$(pkgdatadir)
	${RM} $(DESTDIR)$(tcob_docdir)

clean-local:
	@for i in ${subdirs}; do \
		echo "Cleaning in $$i"; \
		(cd $$i; ${MAKE} clean); \
	done
	@${RM} autom4te.cache || rmdir autom4te.cache || find . -name '*.cache' -delete

distclean-local cleandist: 
	@for i in ${subdirs}; do \
		echo "Despite this being the $@ target, we are just cleaning in $$i"; \
		(cd $$i; ${MAKE} clean; ${RM} Makefile); \
	done
	@${RM} autom4te.cache || rmdir autom4te.cache || find . -name '*.cache' -delete
	@${RM} config.cache config.status config.log htconfig.h Makefile \
	compiler/htversion.h compiler/htcobolrc cobrun/tcrunversion.h \
	utils/cobf2f/Makefile info/slackware/SlackBuild \
	test.code/Makefile test.code/mconfig.inc \
	test_suite/Makefile test_suite/coboltest.inc \
	test_suite/nist/Makefile test_suite/nist/makeConfig.inc \
	lib/htcobolrt.rc libltdl/config.h
	
cleanall allclean: 
	@for i in ${subdirs1}; do \
		echo "Cleaning all in $$i"; \
		(cd $$i; ${MAKE} cleanall); \
	done
	@${RM} autom4te.cache || rmdir autom4te.cache || find . -name '*.cache' -delete
	@${RM} config.cache config.status config.log

# These are not actual targets, just workarounds for a bug:
.PHONY: -c -m 644

#
# Makefile.in for the TinyCOBOL compiler
#
SHELL=/bin/sh


RM=rm -f
MKDIR=mkdir -p

prefix=/usr/local
exec_prefix=${prefix}
bindir = ${exec_prefix}/bin
#datadir = ${datarootdir}
datarootdir = ${prefix}/share
pkgdatadir = ${datarootdir}/htcobol
tcob_docdir=${prefix}/doc/htcobol-0.66

INSTALL=/usr/bin/ginstall -c
INSTALL_DATA=${INSTALL} -m 644
INSTALL_DIR=$(INSTALL) -d -m 755 
INSTALL_PROGRAM=$(INSTALL) -s -m 755

#INSTCOPY=/usr/local/share/htcobol/copybooks
#INSTCOPY=/usr/local/share/htcobol/copybooks
INSTCOPY=${pkgdatadir}/copybooks

CPYBKS01=screen.cpy
CPYBKS02=SQLCA.cpy

all:

clean:

install: install-dir
#	${INSTALL_DATA} $(CPYBKS01) $(INSTCOPY)/$(CPYBKS01)
#	${INSTALL_DATA} $(CPYBKS01) $(DESTDIR)$(INSTCOPY)/$(CPYBKS01)
#	${INSTALL_DATA} $(CPYBKS02) $(DESTDIR)$(INSTCOPY)/$(CPYBKS02)

install-dir: 
#	$(MKDIR) $(INSTCOPY)
	${INSTALL_DIR} $(DESTDIR)$(INSTCOPY)

uninstall:
#	${RM} $(INSTCOPY)/$(CPYBKS01)
	${RM} $(DESTDIR)$(INSTCOPY)/$(CPYBKS01)
	${RM} $(DESTDIR)$(INSTCOPY)/$(CPYBKS02)

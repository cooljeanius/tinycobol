Summary: The Tiny COBOL compiler
Name: tinycobol
Version: 0.4
Release: 1
Copyright: GPL
Group: Development/Languages
Source: ftp://tiny-cobol.sourceforge.net/pub/tiny-cobol/tinycobol-0.4.tar.gz

%description
TinyCOBOL, htcobol, is a COBOL 85 compliant compiler for the 
i386 architecture.

%prep

%setup

%build
./configure --prefix=/usr/local
make

%install
make install

%files
/usr/local/bin/htcobol
/usr/local/bin/htcobpp
/usr/local/lib/libhtcobol.a
/usr/local/share/htcobol/cobopt
/usr/local/share/htcobol/htcobolpp
/usr/local/share/htcobol/copybooks/CMDLine.cpy 
/usr/local/share/htcobol/copybooks/CMDLine1.cpy
/usr/local/share/htcobol/copybooks/ENVAR1.cpy 
%doc AUTHORS
%doc BUGS
%doc CHANGES
%doc COPYING
%doc COPYING.LIB
%doc COPYRIGHT
%doc ChangeLog
%doc HISTORY
%doc INSTALL
%doc INSTALL.bin
%doc README
%doc TODO
%doc info
%doc test.code
%doc test_suite
%doc tinycobol.lsm
%doc utils/Readme.txt
%doc utils/cobpp/AUTHORS
%doc utils/cobpp/COPYING
%doc utils/cobpp/COPYRIGHT
%doc utils/cobpp/Readme.txt
%doc info

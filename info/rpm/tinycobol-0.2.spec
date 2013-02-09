Summary: The Tiny COBOL compiler
Name: tinycobol
Version: 0.2
Release: 1
Copyright: GPL
Group: Development/Languages
Source: ftp://tiny-cobol.sourceforge.net/pub/tiny-cobol/tinycobol-0.2.tar.gz

%description
TinyCOBOL, htcobol, is a COBOL ANSI/ISO 85 compliant compiler for the 
i386 architecture.

%prep
%setup -n tinycobol

%build
./configure --prefix=/usr/local
make
cd utils/cobpp
make

%install
make install
cd utils/cobpp
make install

%files
/usr/local/bin/htcobol
/usr/local/bin/htcobpp
/usr/local/lib/libhtcobol.a
/usr/local/share/htcobol/cobopt
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


Summary: COBOL compiler.
Name: tinycobol
Version: 0.63
Release: 1
Source: http://prdownloads.sourceforge.net/tiny-cobol/tinycobol-0.63.tar.gz
Group: Development/Languages
Copyright: GPL/LGPL
Packager: Bernard Giroud <bgiroud@nospam.free.fr.nospam>

%description
TinyCOBOL, htcobol, is a COBOL 85 compliant compiler for the IA32 (i386) architecture.

%prep

%setup

%build
./configure --prefix=/usr/local
make

%install
make install

%files
%doc ANNOUNCE AUTHORS COPYING COPYING.LIB COPYRIGHT 
%doc INSTALL INSTALL.bin INSTALL.Win32 README STATUS
%doc info/htcobf2f_man.html info/htcobol_man.html
/usr/local/bin/htcobol
/usr/local/bin/htcobrun
/usr/local/lib/libhtcobol.a
/usr/local/lib/libhtcobol.so.0.63.0
/usr/local/lib/libhtcobol.so.0
/usr/local/lib/libhtcobol.so
/usr/local/share/htcobol/htcobolrc
/usr/local/share/htcobol/htrtconf
/usr/local/share/htcobol/copybooks/screen.cpy
/usr/local/man/man1/htcobol.1
/usr/local/man/man1/htcobf2f.1

%changelog

* Wed  July 20 2005 David Essex
* Thur Sept 10 2003 David Essex
* Sun  Feb  03 2003 Bernard Giroud
* Tue  Jan  29 2002 David Essex
* Wed  July 11 2001 David Essex

- Updated previous version.

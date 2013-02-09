Summary: The Tiny COBOL compiler
Name: htcobol
Version: 0.0
Release: 19991230
Copyright: GPL
Group: Development/Languages
Source: ftp://tiny-cobol.sourceforge.net/pub/tiny-cobol/tinycobol-0.19991230.tar.gz

%description
Tiny COBOL, htcobol, is a ANSI 74 compliant COBOL compiler for the 
i386 architecture.

%prep
%setup

%build
configure --prefix=/usr/local
make

%install
make install

%files
/usr/local/bin/htcobol
/usr/local/lib/libhtcobol.a
/usr/local/share/htcobol/cobopt

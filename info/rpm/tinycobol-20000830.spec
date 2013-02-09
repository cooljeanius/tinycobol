Summary: The Tiny COBOL compiler
Name: tinycobol
Version: 0.1.5.3
Release: 1cl
Copyright: GPL
Group: Development/Languages
Source: ftp://tiny-cobol.sourceforge.net/pub/tiny-cobol/tinycobol-0.1.5.3.tar.gz

%description
TinyCOBOL, htcobol, is a COBOL ANSI/ISO 85 compliant compiler for the 
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
/usr/local/lib/libhtcobol.a
/usr/local/share/htcobol/cobopt

%changelog

* 
- Creating a rpm package

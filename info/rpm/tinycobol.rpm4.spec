Name: tinycobol
Version: 0.57
Release: 1
Copyright: GPL
Source: tinycobol-0.57.tar.gz
URL: http://prdownloads.sourceforge.net/tiny-cobol/tinycobol-0.57.tar.gz
Summary: tinycobol-0.57
Group: Development/Languages/Applications

%define ver	0.57
%define rel	1
%define prefix	/usr/local

%description
TinyCOBOL, htcobol, is a COBOL 85 compliant compiler for the IA32 (i386) architecture.

Home page:
http://tiny-cobol.sourceforge.net/

Download:
http://tiny-cobol.sourceforge.net/snapshots/
http://download.sourceforge.net/tiny-cobol/
http://www.ibiblio.org/pub/Linux/devel/lang/cobol/

Mailing list:
http://lists.sourceforge.net/mailman/listinfo/tiny-cobol-users

Mailing list archives:
http://www.geocrawler.com/redir-sf.php3?list=tiny-cobol-users

See INSTALL for build, install instructions. 
See INSTALL.bin for binary install instructions. 
See INSTALL.Win32 for Win32 systems install instructions. 

%prep
%setup
%build
* ./configure --prefix=%prefix --with-libdb=3
./configure --prefix=%prefix
make

%install
rm -rf $RPM_BUILD_ROOT

make install

%clean
rm -rf $RPM_BUILD_ROOT

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%defattr(-, root, root)
%doc ANNOUNCE AUTHORS BUGS COPYING COPYING.LIB COPYRIGHT ChangeLog
%doc HISTORY INSTALL INSTALL.bin INSTALL.Win32 README tinycobol.lsm
/usr/local/bin/htcobol
/usr/local/lib/libhtcobol.a
/usr/local/share/htcobol/cobopt
/usr/local/share/htcobol/htcobolpp
/usr/local/share/htcobol/copybooks/CMDLine.cpy 
/usr/local/man/man1/htcobol.1
/usr/local/man/man1/htcobf2f.1
/usr/local/man/man1/htcobolpp.1

%changelog

* Tue Jan 29 2002 David Essex
* Sun Jul 15 2001 David Essex
* Fri Jul 13 2001 David Billsbrough

This directory contains info on how to build a rpm file.
a sample RPM spec file for Tiny COBOL and info. 

Note:
Status is not functional. Rpm spec file is a prototype and requires configure.

To build:
rpm -ba tinycobol.spec

This will look for filename in spec file under Source. 
For example:

Source: ftp://tiny-cobol.sourceforge.net/pub/tiny-cobol/tinycobol-0.19991230.tar.gz

The program rpm will look for tinycobol-0.19991230.tar.gz in the $D1/SOURCES directory,
where D1 usually defaults to /usr/src/redhat. 

More info can found in rpm-KickStart-HOWTO-13.txt. 


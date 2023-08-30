%define _build_id_links none
%define _topdir /root/rpmbuild

%define name fano
%define release 1%{?dist}
%define version 2.0
%define buildroot %{_topdir}/BUILD/

BuildRoot: %{buildroot}
Summary: fano
Name: %{name}
Version: %{version}
Release: %{release}
Group: System
License: GPL
Packager: quentin.bouyer@atos.net

%description
fano will replace all valid IP adress and all strings from /etc/dic in file given as argument

%build
cd %{_sourcedir};
make

%install
rm -rf $RPM_BUILD_ROOT;
mkdir -p $RPM_BUILD_ROOT/usr/bin;
mkdir -p $RPM_BUILD_ROOT/etc;
cd %{_sourcedir};
cp fano $RPM_BUILD_ROOT/usr/bin;
cp dic $RPM_BUILD_ROOT/etc;
cp dic.wl $RPM_BUILD_ROOT/etc;

%clean
rm -rf RPM_BUILD_ROOT/

%files
%attr(755,root,root) /usr/bin/fano
%attr(644,root,root) /etc/dic
%attr(644,root,root) /etc/dic.wl

%changelog
* Fri Jun 16 2023 Quentin Bouyer <quentin.bouyer@atos.net> - 2.0-1
- add /etc/dic.wl to the rpm
- change permission for /etc/dic and /etc/dic.wl

* Fri Jun 16 2023 Quentin Bouyer <quentin.bouyer@atos.net> - 2.0
- add -h for print help
- add -v for print version
- add -n to not mask any IP Adress
- add -d to specify dic file
- add -f to specify file to anonymize
- dic.wl is a white list dictionaries

* Fri Jun 9 2023 Quentin Bouyer <quentin.bouyer@atos.net> - 1.0
- initial version

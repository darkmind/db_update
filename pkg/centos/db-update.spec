Name:    db-update
Version: 0.1
Release: 1%{?dist}
Summary: Tool to check and update MySQL db schema
License: GPLv3+
URL: https://github.com/darkmind/db_update
BuildRoot: ~/rpmbuild/
BuildRequires: boost-devel
BuildRequires: cmake
BuildRequires: extra-cmake-modules
BuildRequires: groff-base
BuildRequires: mysql-connector-c++-devel
Requires: boost-program-options
Requires: mysql-connector-c++

%description
Tool to check schema consistency according to schema in json file and upgrade it
with SQL statements from json file.

%build
cmake ./ -DMYSQLCONNECTORCPP_INCLUDE_DIR=/usr/include/mysql-cppconn/jdbc -DDB_UPDATE_SRC=../SOURCES
make
strip db_update
groff -man -Tascii ../SOURCES/doc/db_update.1 | gzip -c > db_update.1.gz
ls -la

%install
mkdir -p %{buildroot}/%{_bindir} %{buildroot}/%{_mandir}/man1
install -m 755 db_update %{buildroot}/%{_bindir}/db_update
cp db_update.1.gz %{buildroot}/%{_mandir}/man1/

%files
%{_bindir}/db_update
%{_mandir}/man1/db_update.1.gz

%changelog
* Wed Aug 14 2019 Mykola Malkov <nickolay.malkov@gmail.com>  0.1-1
- Initial revision

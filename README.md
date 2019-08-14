# db_update

db_update is a tool to check schema consistency according to schema in json file and upgrade it with
SQL statements from json file.

## Compiling and Installing

### Debian/Ubuntu

Required 'debian' files can be found in pkg/debian directory.

Install 'build-essential' and 'dpkg-dev' packages:

```
# apt install build-essential dpkg-dev
```

The script dpkg-checkbuilddeps can be used to check dependencies.

You can use travis_helper/build_deb_package.sh to build the package or do it manually as described below.

Copy pkg/debian directory and doc/db_update.1 into root of repo and run dpkg-buildpackage:

```
$ cp -r pkg/debian .
$ cp doc/db_update.1 .
$ dpkg-buildpackage -rfakeroot -us -uc
```

### RHEL/CentOS/OEL/Fedora

Required spec file can be found in pkg/centos directory.

Install 'rpm-build' package:

```
# yum install rpm-build
```

The required mysql-connector packages can be found in official MySQL repo.

You can use travis_helper/build_rpm_package.sh to build the package or do it manually as described below.

Create ~/rpmbuild directory with appropriate structure.

Copy the required files into this sctructure and run rpmbuild.

```
$ mkdir -p ~/rpmbuild/BUILD ~/rpmbuild/SOURCES ~/rpmbuild/SPEC
$ cp -r cmake CMakeLists.txt ~/rpmbuild/BUILD/
$ cp -r src/* ~/rpmbuild/SOURCES/
$ cp -r doc ~/rpmbuild/SOURCES/
$ cp pkg/centos/db-update.spec ~/rpmbuild/SPEC/
$ cd ~/rpmbuild/
$ rpmbuild -ba SPEC/db-update.spec
```

### Manual

The requirements:

cmake

Clang 4.0+ / Gcc 6.1+ - compiler

[Mysql-Connector-C++] (https://github.com/mysql/mysql-connector-cpp)

Boost

```
$ mkdir build && cd build
$ cmake ..
$ make
```

## Example

Initially you may want to create schema.json file of your schema:

```
$ db_update --host <IP> --user <User> --pass <Password> --db <DB name> --source_file schema.json --dump
Schema was dumped to schema.json
```

Before the update of database schema you can run check to be sure that current schema is equal to
the initial one in schema.json file.

```
$ db_update --host <IP> --user <User> --pass <Password> --db <DB name> --source_file schema.json --check
```

#!/bin/bash

set -euo pipefail

mkdir -p ~/rpmbuild/BUILD ~/rpmbuild/SOURCES ~/rpmbuild/SPEC
cp -r cmake CMakeLists.txt ~/rpmbuild/BUILD/
cp -r src/* ~/rpmbuild/SOURCES/
cp -r doc ~/rpmbuild/SOURCES/
cp pkg/centos/db-update.spec ~/rpmbuild/SPEC/

cd ~/rpmbuild/
rpmbuild -ba SPEC/db-update.spec

rpmlint ~/rpmbuild/RPMS/x86_64/db-update*.rpm

#!/bin/bash

set -euo pipefail

cp -r pkg/debian .
cp doc/db_update.1 .
dpkg-buildpackage -rfakeroot -us -uc
lintian ../db-update*.deb

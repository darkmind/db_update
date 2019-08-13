#!/bin/bash

set -euo pipefail
set -x

pwd
cp -r pkg/debian .
dpkg-buildpackage -rfakeroot -us -uc

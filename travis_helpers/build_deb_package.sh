#!/bin/bash

set -euo pipefail

cp -r pkg/debian .
dpkg-buildpackage -rfakeroot -us -uc

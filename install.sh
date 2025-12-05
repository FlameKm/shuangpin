#!/bin/bash

set -e

cmake -B build -DCMAKE_BUILD_TYPE=Release
sudo cmake --build build --target install

echo "You should restart Plasma or log out and log back in to apply the changes."
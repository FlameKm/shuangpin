#!/bin/bash

plasmoid_file="/usr/lib/x86_64-linux-gnu/qt5/plugins/kf5/krunner/plasma_krunner_shuangpin.so"

[ -f "$plasmoid_file" ] && sudo rm "$plasmoid_file" && echo "Removed $plasmoid_file"

echo "Uninstallation complete."
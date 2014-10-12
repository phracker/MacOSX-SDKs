#!/bin/bash

# Make MacOSX-SDKs release tarballs

TARGET="$(pwd)";
LOGFILE="$(mktemp)";

log() {
  dialog --infobox "$@" 4 80;
}

echo "Directory: $TARGET";
echo "Log: $LOGFILE";

if [[ -f "$(which dialog)" ]]; then
  echo "Dialog installed at $(which dialog).";
else
  echo "Dialog not installed. Please install and try again.";
  exit;
fi

if [[ $# -eq 0 ]]; then
  echo "Building MacOSX-SDKs release tarballs.";
else
  echo "This script does not take arguments.";
  exit;
fi

if [[ ! -d "$TARGET/release/" ]]; then
  echo "Making release directory at $TARGET/release/";
  mkdir "$TARGET/release/";
else
  dialog --title "Releases Directory" --yesno "An old release directory was found. Would you like to delete it before proceeding?" 10 60;
  echo "\$?: $?";
  if [[ "$?" -eq "0" ]]; then
    echo "Removing old release directory at $TARGET/release/";
    rm -rf "$TARGET/release/";
    echo "Making release directory at $TARGET/release/";
    mkdir "$TARGET/release/";
  fi
fi

for sdk_directory in *.sdk; do
  log "Compressing $sdk_directory to $sdk_directory.tar.xz...";
  tar -cpJf "release/$sdk_directory.tar.xz" "$sdk_directory";
done

du -h "$TARGET/release/"* | sed s/release\\\///g;
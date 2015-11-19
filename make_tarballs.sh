#!/bin/bash

# Make MacOSX-SDKs release tarballs

TARGET="$(pwd)";
LOGFILE="$(mktemp)";
SDKS="";

log() {
  echo "$@" 2>&1 | tee "$LOGFILE";
}

log "Current Directory: $TARGET";
log "Log: $LOGFILE";

if [[ $# -eq 0 ]]; then
  log "Building release tarballs.";
else
  log "This script does not take arguments.";
  exit;
fi

if [[ ! -d "$TARGET/release/" ]]; then
  log "Making release directory at $TARGET/release/";
  mkdir "$TARGET/release/";
else
  echo -n "An old release directory was found. Would you like to delete it before proceeding? [Y/n]: ";
  read DELETE_RELEASES;
  echo "";
  if [[ ! "$DELETE_RELEASES" -eq "n" ]]; then
    log "Removing old release directory at $TARGET/release/";
    rm -rf "$TARGET/release/";
    log "Making release directory at $TARGET/release/";
    mkdir "$TARGET/release/";
  else
    log "Moving old release directory to $TARGET/release_backup/";
    mv "$TARGET/release/" "$TARGET/release_backup/";
    log "Making release directory at $TARGET/release/";
    mkdir "$TARGET/release/";
  fi
fi
SDKS="";
for sdk_directory in *.sdk; do
  log "Compressing $sdk_directory to $sdk_directory.tar.xz...";
  tar -cpJf "release/$sdk_directory.tar.xz" "$sdk_directory";
  SDKS="${SDKS} $sdk_directory"
done

log "Done. Contents of $TARGET/release/:";
du -h "$TARGET/release/"* | sed s/release\\\///g 2>&1 | tee "$LOGFILE";
#!/usr/bin/env sh
SRC_DIR="`pwd`"
cd "`dirname "$0"`"
cd "../drush/drush"
BIN_TARGET="`pwd`/drush.php"
cd "$SRC_DIR"
"$BIN_TARGET" "$@"

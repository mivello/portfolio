@ECHO OFF
SET BIN_TARGET=%~dp0/../drush/drush/drush.complete.sh
php "%BIN_TARGET%" %*

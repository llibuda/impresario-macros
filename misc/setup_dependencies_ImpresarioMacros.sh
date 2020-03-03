#!/bin/bash

checkCommand()
{
  hash $* 2>/dev/null || { echo >&2 "Setup requires command '$*' but it is not available. Aborting."; exit 1; }
  echo "Checked availability of command '$*'. Ok."
}

echo "Setting up dependencies for Impresario Macros..."
echo ""

checkCommand tar
checkCommand ldd
checkCommand grep
checkCommand sed
checkCommand sort

cd bin 2>/dev/null

# setup LD_LIBRARY_PATH
LD_LIBRARY_PATH=./qtlib:../lib/ltilib-2:../lib/opencv-3:../lib/common
export LD_LIBRARY_PATH

path_pattern="../lib/*.so.*"
deps_archive="../lib/common/common.tar.gz"
deps_path="../lib/common"

continue_run=1
failed=0
pass=0

while [  $continue_run -eq 1 ]; do
  continue_run=0
  failed=0
  pass=$[pass+1]
  # get missing dependencies
  missing_deps=`ldd $path_pattern | grep "not found" | sed 's/=> not found/\n/' | sort -u`

  if [ ${#missing_deps} -gt 0 ]; then
    count=`wc -l <<< "$missing_deps"`
    count=$[count-1]
    echo ""
    echo "Pass $pass: Found $count missing dependencies."
    for dep in $missing_deps
    do
      tar --directory=$deps_path -xzf $deps_archive $dep 2>/dev/null
      if [ $? -eq 0 ]; then
        echo "$dep was successfully added from archive."
        continue_run=1
      else
        echo "$dep could not be found in archive!"
        failed=$[failed+1]
      fi
    done
  else
    echo ""
    echo "All dependencies available."
  fi
done

if [ $failed -gt 0 ]; then
  echo ""
  echo "$failed missing dependencies could not be found. Unfortunately some macros won't work in Impresario."
fi

#! /bin/bash

checkCommand()
{
  hash $* 2>/dev/null || { echo >&2 "Script requires command '$*' but it is not available. Aborting."; exit 1; }
  echo "Checked availability of command '$*'. Ok."
}

scriptPath=`which "$0"`
scriptFileName="${scriptPath##*/}"
scriptDirectory="${scriptPath%/*}"

echo "Collect depencies for Impresario macros"

checkCommand tar
checkCommand ldd
checkCommand awk
checkCommand sed
checkCommand sort

# setup LD_LIBRARY_PATH
LD_LIBRARY_PATH=./qtlib:../lib/ltilib-2:../lib/opencv-3.4.1
export LD_LIBRARY_PATH

# find all depencies and copy them to ../lib/common
path_pattern="../lib/*.so.*"
deps_archive="../lib/common/common.tar.gz"
deps_path="../lib/common"

targetDeps=$(ldd $path_pattern | awk 'BEGIN{ORS=" "}$1~/^\//{print $1}$3~/^\//{print $3}' | sed 's/,$/\n/' | sort -u )
for dep in $targetDeps
do
  if [[ "$dep" != *Qt* ]]; then
    cp "$dep" "$deps_path"
    echo "Copying $dep ..."
  fi
done

# compress all files
tar -czf $deps_path/common.tar.gz $deps_path/*.so.*

# clean up
rm $deps_path/*.so.*



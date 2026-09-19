#!/bin/sh
set -eu

here=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
flag_path=${FLAG_PATH:-"$here/flag.local"}

if [ ! -r "$flag_path" ]; then
    echo "Create a fake local flag at $flag_path or set FLAG_PATH." >&2
    exit 2
fi

export FLAG_PATH="$flag_path"
exec "$here/ld-linux-x86-64.so.2" \
    --library-path "$here/lib" \
    "$here/riftcapd" "$@"



#!/bin/bash
#
# Recursively rename *.[ch] files to *_bonus.[ch]
#
find . -name '*.c' -print0 \
  | xargs -0 -n1 bash -c 'mv -v "$0" "${0%%.c}"_bonus.c'
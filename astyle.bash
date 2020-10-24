#!/usr/bin/env bash

# files to check
if [ $# -eq 0 ]; then
    # No arguments provided
    FILES=`git diff --name-only --diff-filter=ACMR`
else
    FILES="$@"
fi
echo "running astyle for $FILES"

OPTIONS=$(cat <<-END
--style=ansi
--indent=spaces=4
--convert-tabs
--lineend=linux
--suffix=none
--unpad-paren
--indent-switches
--indent-cases
--indent-labels
--pad-header
END
)

RETURN=0
ASTYLE=$(which astyle)
if [ $? -ne 0 ]; then
	echo "[!] astyle not installed." >&2
	exit 1
fi

$ASTYLE --version

for FILE in $FILES; do
    if [[ $FILE =~ \.(c|cpp|h|hpp)$ ]]; then
        $ASTYLE $OPTIONS < $FILE > $FILE.astyle 
        cmp -s $FILE $FILE.astyle
        if [ $? -ne 0 ]; then
            echo "Changed $FILE" >&2
            RETURN=1
            diff $FILE $FILE.astyle >&2
	        mv $FILE.astyle $FILE
        else
            rm $FILE.astyle
            echo "Unchanged $FILE" >&2
        fi
    else
       echo "Skipping $FILE" >&2
    fi
done

exit $RETURN
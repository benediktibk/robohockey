#!/bin/bash

headerFiles=$(find . -path ./physic/Box2D -prune -o -path ./build -prune -o -iname "*.h")

for headerFileWithPath in ${headerFiles}
do
	if	[ $headerFileWithPath != "./physic/Box2D" ] &&
		[ $headerFileWithPath != "./build" ]; then
		headerFileWithoutPath=${headerFileWithPath##*/}
		headerFile=${headerFileWithoutPath%.h}
		path=${headerFileWithPath%/*}
		subProjectPath=${path##*./}
		echo "checking include guard of ${subProjectPath}/${headerFile}.h"

		firstLine=$(head --lines 1 ${headerFileWithPath})
		secondLine=$(head --lines 2 ${headerFileWithPath} | tail --lines 1)
		ifndef=${firstLine:0:7}
		define=${secondLine:0:7}

		if [ "${ifndef}" != "#ifndef" ]; then
		echo "missing include guard in file ${headerFileWithPath}:1:0:" 1>&2
		echo "${headerFileWithPath}:1:0: error: no #ifndef statement in the second line" 1>&2
		exit 1
		fi

		if [ $define != "#define" ]; then
		echo "missing include guard in file ${headerFileWithPath}:1:0:" 1>&2
		echo "${headerFileWithPath}:1:0: error: no #define statement in the second line" 1>&2
		exit 1
		fi

		includeGuardOne=${firstLine:8:${#firstLine}}
		includeGuardTwo=${secondLine:8:${#secondLine}}

		if [ $includeGuardOne != $includeGuardTwo ]; then
			echo "the include guards do not match in file ${headerFileWithPath}:1:0:" 1>&2
			echo "${headerFileWithPath}:1:0: error: '$includeGuardOne' does not match '$includeGuardTwo'" 1>&2
			exit 1
		fi

		includeGuardReal=$includeGuardOne;
		subProject=$(echo "$subProjectPath" | tr / _)
		subProjectUpperCase=$(echo $subProject | tr  "[:lower:]" "[:upper:]")
		fileNameUpperCase=$(echo $headerFile | tr  "[:lower:]" "[:upper:]")
		includeGuardShouldBe="ROBOHOCKEY_${subProjectUpperCase}_${fileNameUpperCase}_H"

		if [ $includeGuardReal != $includeGuardShouldBe ]; then
		echo "the include guards do not match the specified pattern in file ${headerFileWithPath}:1:0:" 1>&2
		echo "${headerFileWithPath}:1:0: error: '$includeGuardOne' does not match the specified pattern <DIRECTORY>_<CLASS>_H" 1>&2
		echo "the include guard should be $includeGuardShouldBe" 1>&2
		exit 1
		fi
	fi
done
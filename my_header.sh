#!/bin/bash

LOGIN=${1}

if [ "${LOGIN}" == "" ]
then
	printf "%s\n" "Error: specify a login"
	exit 1
fi

run_create_readme()
{
	local INDEX="${1}"
	local TEST="${2}"
	local TEST_NAME="${TEST##*/}"
	local TEST_FULLNAME="${TEST##*spec/}"
	local PARENT_DIR_NAME="${TEST%/*}"
	local README="${TEST}/README.md"

}

run_browse_directory()
{
	local -i INDEX=${1}
	local DIR="${2}"
	local DIR_NAME="${DIR##*/}"
	local DIR_FULLNAME="${DIR##*spec/}"
	local PARENT_DIR_NAME="${DIR%/*}"
	local README="${DIR}/README.md"
	local SUBDIR
	local IMGS=""


	for SUBDIR in $(ls -1 "${DIR}")
	do
		if [ -d "${DIR}/${SUBDIR}" ]
		then
			run_browse_directory "$(( INDEX + 1 ))" "${DIR}/${SUBDIR}"
		else
			if [[ "${SUBDIR}" =~ *[ch]\$ ]]
			then
				echo ${SUBDIR}
			fi
		fi
	done
}

run_browse_directory -1 "."

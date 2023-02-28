#!/bin/bash -x

if [ -z $1 ]; then
    echo "commit message required"
    exit
fi

function pcommit {
    git status 


}

commit_message=$1


git submodule foreach pcommit

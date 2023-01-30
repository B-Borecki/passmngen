#!/bin/bash
Help() {
    echo "Create or generate password for the given LOGIN/E-MAIL and WEBSITE or find this password in manager."
    echo "Usage:                passmngen LOGIN/E-MAIL WEBSITE"
    echo "   or:                passmngen [-c|h]"
    echo
    echo "Options:"
    echo "      c - Create password file"
    echo "      h - Print this Help"
    echo
}
Install() {
    mv setup.sh ~/.local/bin/passmngen
}

while getopts ":chi" option; do
    case $option in
        c)
            gcc -o passmngen passmngen.c
            ./passmngen create
            rm passmngen
            exit;;
        h)
            Help
            exit;;
        i)
            Install
            exit;;
        \?)
            echo "Error: Invalid option"
            exit;;
    esac
done

gcc -o passmngen passmngen.c
if(("$#" != "2")); then
    echo "Error: invalid number of arguments. Type \"passmngen -h\" if you need help "
else
    ./passmngen "$1" "$2"
fi
rm passmngen

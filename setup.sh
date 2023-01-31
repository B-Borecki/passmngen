#!/bin/bash
Help() {
    echo "Create or generate password for the given LOGIN/E-MAIL and WEBSITE or find this password in manager."
    echo "Usage:                passmngen LOGIN/E-MAIL WEBSITE"
    echo "   or:                passmngen [-c|h]"
    echo "   or:                passmngen [-g] LOGIN/E-MAIL WEBSITE"
    echo
    echo "Options:"
    echo "      c - Create password file"
    echo "      g - Generate password"
    echo "      h - Print this Help"
    echo
    echo "For first use you need to create password file so you have to select -c option"
    echo "If you want the program to print your password from manager, or you want to add new password to manager, select standard usage"
    echo "If you want the program to generate a random secure password for you, select the -g option"
}
Install() {
    mv setup.sh /usr/local/bin/passmngen
}

while getopts ":cghi" option; do
    case $option in
        c)
            gcc -o passmngen passmngen.c
            ./passmngen create
            rm passmngen
            exit;;
        g)
            gcc -o passmngen passmngen.c
            if(("$#" != "3")); then
                echo "Error: invalid number of arguments. Type \"passmngen -h\" if you need help "
            else
                ./passmngen "$2" "$3" generate
            fi
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

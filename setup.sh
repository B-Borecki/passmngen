#!/bin/bash
Help() {
    echo "Create or generate password for the given LOGIN/E-MAIL and WEBSITE or find this password in database."
    echo "Usage:                passmngen LOGIN/E-MAIL WEBSITE"
    echo "   or:                passmngen [-f|h]"
    echo "   or:                passmngen [-c|d|g] LOGIN/E-MAIL WEBSITE"
    echo
    echo "Options:"
    echo "      f - For first use. Create password database "
    echo "      h - Print this Help"
    echo "      c - Change the password in database for given LOGIN/E-MAIL and WEBSITE"
    echo "      d - Remove the password from database for given LOGIN/E-MAIL and WEBSITE"
    echo "      g - Generate the password for given LOGIN/E-MAIL and WEBSITE and save it in the database"
    echo
    echo "Guide:"
    echo "For first use you need to create password file so you have to run \"passmngen -f\""
    echo "If you want the program to print your password from database, or you want to add new password to database, select standard usage without any options"
    echo "If you want the program to generate a random secure password for given LOGIN/E-MAIL and WEBSITE and save it in the database, run program with -g option"
    echo "If you want to change the saved password to a new password created by you, run program with -c option"
    echo "If you want to change the saved password to a securely generated one, first you need to remove the password from database by running the program with -d option and then you can run the program with -g option"
}

Install() {
    echo -n "cd " >> passmngen.sh
    echo $PWD >> passmngen.sh
    echo -n "./setup.sh" >> passmngen.sh
    echo " \$1 \$2 \$3" >> passmngen.sh
    chmod 700 passmngen.sh
    mv passmngen.sh ~/.local/bin/passmngen
}

while getopts ":cdfghi" option; do
    case $option in
        c)
            gcc -o passmngen passmngen.c
            if(("$#" != "3")); then
                echo "Error: invalid number of arguments. Type \"passmngen -h\" if you need help "
            else
                ./passmngen "$2" "$3" change
            fi
            rm passmngen
            exit;;
        d)
            gcc -o passmngen passmngen.c
            if(("$#" != "3")); then
                echo "Error: invalid number of arguments. Type \"passmngen -h\" if you need help"
            else
                ./passmngen "$2" "$3" delete
            fi
            rm passmngen
            exit;;
        f)
            gcc -o passmngen passmngen.c
            ./passmngen create
            rm passmngen
            exit;;
        g)
            gcc -o passmngen passmngen.c
            if(("$#" != "3")); then
                echo "Error: invalid number of arguments. Type \"passmngen -h\" if you need help"
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

#!/bin/bash
Help() {
    echo "Create or generate password for the given LOGIN/E-MAIL and WEBSITE or find this password in database."
    echo "Usage:                passmngen LOGIN/E-MAIL WEBSITE"
    echo "   or:                passmngen [-f|h|u]"
    echo "   or:                passmngen [-c|d|g] LOGIN/E-MAIL WEBSITE"
    echo
    echo "Options:"
    echo "      f - For first use. Create password database "
    echo "      h - Print this Help"
    echo "      c - Change the password in database for given LOGIN/E-MAIL and WEBSITE"
    echo "      d - Remove the password from database for given LOGIN/E-MAIL and WEBSITE"
    echo "      g - Generate the password for given LOGIN/E-MAIL and WEBSITE and save it in the database"
    echo "      u - Unistall"
    echo
    echo "Guide:"
    echo "For first use you need to create password file so you have to run \"passmngen -f\""
    echo "To print your password from database, or to add new password to database, select standard usage without any options"
    echo "To generate a random secure password for given LOGIN/E-MAIL and WEBSITE and save it in the database, run program with -g option"
    echo "To change the saved password to a new password created by you, run program with -c option"
    echo "To change the saved password to a securely generated one, first you need to remove the password from database by running the program with -d option and then you can run the program with -g option"
    echo "To unistall Passmngen run program with -u option and then delete repository"
    echo "If you have uninstalled Passmngen but not deleted the files, you can still reinstall the program without losing your saved data"

}

Install() {
    echo -n "cd " >> passmngen.sh
    echo $PWD >> passmngen.sh
    echo -n "./setup.sh" >> passmngen.sh
    echo " \$1 \$2 \$3" >> passmngen.sh
    chmod 700 passmngen.sh
    if [ -d "~/.local/bin" ];
    then
        mv passmngen.sh ~/.local/bin/passmngen
    else
        mkdir -p ~/.local/bin
        export PATH="$HOME/.local/bin:$PATH"
        mv passmngen.sh ~/.local/bin/passmngen
    fi
}

Unistall() {
    rm ~/.local/bin/passmngen
}

while getopts ":cdfghiu" option; do
    case $option in
        c)
            gcc -o passmngen passmngen.c
            if(("$#" != "3")); then
                echo "Error: invalid number of arguments. Type \"passmngen -h\" if you need help "
            else
                sudo ./passmngen "$2" "$3" change
            fi
            rm passmngen
            exit;;
        d)
            gcc -o passmngen passmngen.c
            if(("$#" != "3")); then
                echo "Error: invalid number of arguments. Type \"passmngen -h\" if you need help"
            else
                sudo ./passmngen "$2" "$3" delete
            fi
            rm passmngen
            exit;;
        f)
            gcc -o passmngen passmngen.c
            sudo ./passmngen create
            rm passmngen
            exit;;
        g)
            gcc -o passmngen passmngen.c
            if(("$#" != "3")); then
                echo "Error: invalid number of arguments. Type \"passmngen -h\" if you need help"
            else
                sudo ./passmngen "$2" "$3" generate
            fi
            rm passmngen
            exit;;
        h)
            Help
            exit;;
        i)
            Install
            exit;;
        u)
            Uninstall
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
    sudo ./passmngen "$1" "$2"
fi
rm passmngen

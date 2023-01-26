#!/bin/bash
Help() {
    echo "pokaż dupcię"
}
Install() {
    cp setup.sh ~/.local/bin/passmngen
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
./passmngen
rm passmngen

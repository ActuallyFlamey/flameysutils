#!/usr/bin/bash

if [[ $EUID -ne 0 ]]; then
   echo "Please run this script as root." 1>&2
   exit 1
fi

LANG=0

echo -e "Please select the language you want to install \033[1;34mflameysutils\033[0m for:"
echo -e "0. \033[0;34mC\033[0m (\033[1;34mflameysutils.h\033[0m to \033[0;32m/usr/include\033[0m)"

printf "\n"

read -p "Input the number corresponding to your selection: " LANG

printf "\n"

case $LANG in
    0)
        if cp "./c/flameysutils.h" "/usr/include/flameysutils.h"; then
            echo -e "Successfully installed \033[1;34mflameysutils.h\033[0m to \033[0;32m/usr/include\033[0m."
        else
            echo -e "Failed to install \033[1;34mflameysutils.h\033[0m. Reason is unknown."
            exit 1
        fi
        ;;
    *)
        echo "Invalid selection."
        exit 1
        ;;
esac
#!/bin/bash

remUsername=""
remUserfile=""
#Functions for Remember.r Accounts

createAccount()
{
    bash final_project_sql.sh create
}

deleteAccount()
{
    bash final_project_sql.sh delete "$remUsername"
}

changeAccountName()
{
    bash final_project_sql.sh name "$remUsername"
}

changeAccountPassword()
{
    bash final_project_sql.sh pass "$remUsername"
}

#Functions for User Accounts

readAllData()
{
    perl final_project_perl.pl $remUsername
}

searchData()
{
    read -p "Please enter your case-sensitive search query: " query
    echo
    grep "$query" "$remUserfile"
}

createData()
{
    loop() {
        echo "Please enter the name of the website you are adding."
        read websiteData
        echo
        echo "Please enter the username you have on this website."
        read usernameData
        echo
        echo "Please enter the password you have on this website."
        read passwordData
        echo
        echo "You entered website: $websiteData, username: $usernameData, password: $passwordData. Is this correct? Y/N"
        read bool
        echo    
    }
    loop

    while [ "$bool" != "Y" ]; do
        loop
    done

    echo "$websiteData;$usernameData;$passwordData" >> "$remUserfile"
}

modifyData()
{
    deleteData
    createData
}

deleteData()
{
    loopdeloop()
    {
        echo "What website do you want to delete?"
        read websiteData
    }

    loopdeloop
    while ! grep $websiteData $remUserfile; do
        echo "That website is not in our database."
        loopdeloop
    done

    echo "Are you sure you want to delete the data on $websiteData? Y/N"   
    read bool
    echo

    if [ "$bool" == "Y" ]; then
        awk -F ';' -v site="$websiteData" '$1 != site' "$remUserfile" > temp && mv temp "$remUserfile"
    fi

}

log_in()
{

    read -p "Enter username: " username
    read -s -p "Enter password: " password
    echo
    # hash
    hashed_pass=$(echo -n "$password" | sha256sum | awk '{print $1}')
    # search(username)->password
    s_password=$(bash final_project_sql.sh search "$username")
    # match passwords
    if [[ "$hashed_pass" == "$s_password" ]]; then
        echo "Login successful"
	echo ""
        remUsername="$username"
        remUserfile="data/usrAccounts/$username.csv"
        logged_in
    else
        echo "Invalid username or password"
    fi
}

logged_in()
{
    while true; do
        user_choice=$(python3 final_project_python.py)
        if [[ "$user_choice" == "q" ]]; then
            echo "Logging out..."
            echo
            remUsername=""
            break
        elif [[ "$user_choice" == "r" ]]; then
            echo "Reading data..."
            echo
            readAllData
        elif [[ "$user_choice" == "w" ]]; then
            echo "Writing data..."
            echo
            createData
        elif [[ "$user_choice" == "d" ]]; then
            echo "Deleting data..."
            echo
            deleteData
        elif [[ "$user_choice" == "m" ]]; then
            echo "Modifying data..."
            echo
            modifyData
        elif [[ "$user_choice" == "DELETE" ]]; then 
            echo "Deleting account..."
            echo
            deleteAccount
            break
        fi
    done
}
set_up()
{
    bash final_project_sql.sh setup
}

#main, in BASH
set_up
while true; do
    printf "
██████╗ ███████╗███╗   ███╗███████╗███╗   ███╗██████╗ ███████╗██████╗    ██████╗ 
██╔══██╗██╔════╝████╗ ████║██╔════╝████╗ ████║██╔══██╗██╔════╝██╔══██╗   ██╔══██╗
██████╔╝█████╗  ██╔████╔██║█████╗  ██╔████╔██║██████╔╝█████╗  ██████╔╝   ██████╔╝
██╔══██╗██╔══╝  ██║╚██╔╝██║██╔══╝  ██║╚██╔╝██║██╔══██╗██╔══╝  ██╔══██╗   ██╔══██╗
██║  ██║███████╗██║ ╚═╝ ██║███████╗██║ ╚═╝ ██║██████╔╝███████╗██║  ██║██╗██║  ██║
╚═╝  ╚═╝╚══════╝╚═╝     ╚═╝╚══════╝╚═╝     ╚═╝╚═════╝ ╚══════╝╚═╝  ╚═╝╚═╝╚═╝  ╚═╝
                                                                                 \n"
    echo "Welcome to Remember.r Services!"
    echo "Press 1 to log in account, press 2 to create account, or type 'q' to quit."
    read num
    echo
    if [[ "$num" == "1" ]]; then
        log_in
    elif [[ "$num" == "2" ]]; then
        createAccount
    elif [[ "$num" == "q" ]]; then
        break
    fi
done

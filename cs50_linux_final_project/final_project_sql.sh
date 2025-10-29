#!/bin/bash

nameRegEx=".{4,}"
passRegEx="^(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])[A-Za-z0-9]{6,}$"
dbfile="data/remAccounts/remAccounts.db"


if [ "$1" == create ]; then
    echo "Please enter your desired username. It must include more than 4 characters and can't already be in our database."
    read remUsername
    echo
    if [[ ! $remUsername =~ $nameRegEx ]]; then
        echo "invalid username" >&2
        exit 1
    fi

    query="select count(*) from users where username='$remUsername'"
    result=$(sqlite3 "$dbfile" "$query")
    
    if [ "$result" -gt 0 ]; then
        echo "username already exist" >&2
        exit 1
    fi

    echo "Please enter your password, password must include more than 6 character and at least one upper and lower case letter and one number"
    read -s rempassword
    echo

    if [[ ${#rempassword} -lt 6 ]] ||
    ! [[ "$rempassword" =~ [A-Z] ]] ||
    ! [[ "$rempassword" =~ [a-z] ]] ||
    ! [[ "$rempassword" =~ [0-9] ]]; then
        echo "invalid username" >&2
        exit 1
    fi

    # hash
    hashed_pass=$(echo -n "$rempassword" | sha256sum | awk '{print $1}')

    # create account
    query="insert into users (username, password) VALUES ('$remUsername', '$hashed_pass');"
    sqlite3 "$dbfile" "$query"
    mkdir -p "data/usrAccounts"
    touch "data/usrAccounts/$remUsername.csv"
    chmod 600 "data/usrAccounts/$remUsername.csv"
    echo "account created"

# $2=username
elif [ "$1" == delete ]; then
    query="DELETE FROM users WHERE username='$2'"
    sqlite3 "$dbfile" "$query"
    rm "data/usrAccounts/$2.csv"

# $2=username
elif [ "$1" == name ]; then
    read -p "Enter new username: " new_username
    if [[ ! $new_username =~ $nameRegEx ]]; then
        echo "invalid username" >&2
        exit 1
    fi

    query="select count(*) from users where username='$new_username'"
    result=$(sqlite3 "$dbfile" "$query")
    if [ "$result" -gt 0 ]; then
        echo "username already exist" >&2
        exit 1
    fi

    query="update users set username='$new_username' where username='$2'"
    sqlite3 "$dbfile" "$query"
    echo "username changed from $2 to $new_username" >&2

#$2=username
elif [ "$1" == pass ]; then
    read -s -p "Enter new password: " new_pass
    echo
    if [[ ! $new_pass =~ $passRegEx ]]; then
        echo "invalid password" >&2
        exit 1
    fi
    hashed_pass=$(echo -n "$new_pass" | sha256sum | awk '{print $1}')
    query="update users set password = '$hashed_pass' where username = '$2'"
    sqlite3 "$dbfile" "$query"
    echo "password updated" >&2
    

elif [ "$1" == setup ]; then

    # set up database
    query="create table if not exists users (username text primary key, password text not null)"
    sqlite3 "$dbfile" "$query"


# for logging in $2=username
elif [ "$1" == search ]; then
    query="select password from users where username='$2'"
    result=$(sqlite3 "$dbfile" "$query")
    echo "$result"

fi

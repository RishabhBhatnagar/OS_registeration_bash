u_register () {
    read -p "Enter username: " username
    echo enter your Password: 
    read -s password
    echo re enter your password:
    read -s re_password

    if [ "$password" == "$re_password" ]; then
        echo password correct

        concatenated=$username$password
        current_hash_value=$((0x$(sha1sum <<<$concatenated)0))
        echo current hash value : $current_hash_value

        echo $username $password $current_hash_value >> db.txt

        file='db.txt'
        while IFS='' read -r line || [[ -n "$line" ]]; do
            i=1
            for word in $line; do
                echo $i
                if [ "$i" -eq "1" ]; then
                    if [ "$word" == "$username" ]; then
                        echo r found..........
                    fi
                fi
                echo ":" $word ":"
                i=$((i+1))
            done
            i=1
        done < $file

    else
        echo password incorrect
    fi
}

login () {
    l="#########LOGIN#########"
    echo
    echo $l
    echo
    file='db.txt'
    while IFS='' read -r line || [[ -n "$line" ]]; do
        i=1
        for word in $line; do
            echo $i
            if [ "$i" -eq "1" ]; then
                if [ "$word" == "$username" ]; then
                    echo r found..........
                fi
            fi
            echo ":" $word ":"
            i=$((i+1))
        done
        i=1
    done < $file

}


read -p "Are you registered??[y/n] " -n 1 -r
echo    # (optional) move to a new line
if [[ $REPLY =~ ^[Yy]$ ]]
    then
        login
    else
        u_register
fi

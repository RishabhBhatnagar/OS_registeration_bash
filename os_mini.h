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

        echo $username $current_hash_value >> db.txt

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
    read -p "Enter username: " username
    echo enter your Password: 
    read -s password

    concatenated=$username$password
    current_hash_value=$((0x$(sha1sum <<<$concatenated)0))
    echo current hash value : $current_hash_value

    file='db.txt'

    username_found=false
    while IFS='' read -r line || [[ -n "$line" ]]; do
        i=1
        for word in $line; do
            if [ "$i" -eq "1" ]; then
                if [ "$word" == "$username" ]; then
                    username_found=true
                    break
                fi
            fi
            i=$((i+1))
        done
        if [ "$username_found" = true ]; then
            break
        fi
        i=1
    done < $file
    i=1
    for word in $line; do
        if [ "$i" -eq "2" ]; then
            if [ "$word" == "$current_hash_value" ]; then
                echo user authenticated
            else
                echo wrong password
                break
            fi
        fi
        i=$((i+1))
    done
}
read -p "Are you registered??[y/n] " -n 1 -r
echo    # (optional) move to a new line
if [[ $REPLY =~ ^[Yy]$ ]]
    then
        login
    else
        u_register
fi

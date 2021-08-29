
#########################################################
#                                                       #
#                        MD-5                           #
#                                                       #
#########################################################

test_md5 () {
    
    if ( diff <(./ft_ssl md5 $1) <(md5 $1) )
    then
        echo -e "\033[0;32m[OK]\033[0m md5 $1"
    else
        echo -e "\033[0;31m[ERROR]\033[0m md5 $1"
    fi
}

test_md5_stdin () {
    
    if ( diff <(echo $1 | ./ft_ssl md5 $2) <(echo $1 | md5 $2) )
    then
        echo -e "\033[0;32m[OK]\033[0m echo $1 | md5 $2"
    else
        echo -e "\033[0;31m[ERROR]\033[0m echo $1 | md5 $2"
    fi
}

if [[ $1 == '' || $1 == 'md5' ]]
then
    test_md5 '-s hello Makefile'
    test_md5 '-s 1234567890123456789012345678901234567890123456789012345'
    test_md5 '-s 12345678901234567890123456789012345678901234567890123456'
    test_md5 '-s 1234567890123456789012345678901234567890123456789012345678901234'
    test_md5 '-s 12345678901234567890123456789012345678901234567890123456789012345'
    test_md5 '-s ""'
    test_md5 '-q -s hello'
    test_md5 '-r -s hello'
    test_md5 '-qr -s hello'

    test_md5_stdin 'hello Makefile'
    test_md5_stdin 'hello' '-p'
    test_md5_stdin 'hello' '-p Makefile'
    test_md5_stdin 'hello' '-q'
    test_md5_stdin 'hello' '-r'
    test_md5_stdin 'hello' '-qr'
    test_md5_stdin 'hello' '-p -s hello'
    test_md5_stdin 'hello' '-pq -s hello'
    test_md5_stdin 'hello' '-pr -s hello'
    test_md5_stdin 'hello' '-pqr -s hello'
    test_md5_stdin 'hello' '-pqr -s hello Makefile'
fi

#########################################################
#                                                       #
#                       SHA-256                         #
#                                                       #
#########################################################

test_sha256 () {
    
    if ( diff <(./ft_ssl sha256 $1) <(openssl sha256 $1) )
    then
        echo -e "\033[0;32m[OK]\033[0m sha256 $1"
    else
        echo -e "\033[0;31m[ERROR]\033[0m sha256 $1"
    fi
}

test_sha256_stdin () {
    
    if ( diff <(echo $1 | ./ft_ssl sha256 $2) <(echo $1 | openssl sha256 $2) )
    then
        echo -e "\033[0;32m[OK]\033[0m echo $1 | sha256 $2"
    else
        echo -e "\033[0;31m[ERROR]\033[0m echo $1 | sha256 $2"
    fi
}

# if [[ $1 == '' || $1 == 'sha256' ]]
# then
#     test_sha256_stdin 'hello Makefile'
#     test_sha256_stdin '1234567890123456789012345678901234567890123456789012345'
#     test_sha256_stdin '12345678901234567890123456789012345678901234567890123456'
#     test_sha256_stdin '1234567890123456789012345678901234567890123456789012345678901234'
#     test_sha256_stdin '12345678901234567890123456789012345678901234567890123456789012345'

#     test_sha256 '**/*.c Makefile'
# fi

#########################################################
#                                                       #
#                       BASE-64                         #
#                                                       #
#########################################################

test_base64 () {
    
    if ( diff <(./ft_ssl base64 $1) <(base64 $1) )
    then
        echo -e "\033[0;32m[OK]\033[0m base64 $1"
    else
        echo -e "\033[0;31m[ERROR]\033[0m base64 $1"
    fi
}

test_base64_stdin () {
    
    if ( diff <(echo $1 | ./ft_ssl base64 $2) <(echo $1 | base64 $2) )
    then
        echo -e "\033[0;32m[OK]\033[0m echo $1 | base64 $2"
    else
        echo -e "\033[0;31m[ERROR]\033[0m echo $1 | base64 $2"
    fi
}

test_base64_file_output () {
    
    if ( diff <(./ft_ssl base64 -o $1.mine $2) <(base64 -o $1.true $2) )
    then
        if ( diff $1.mine $1.true )
        then
            echo -e "\033[0;32m[OK]\033[0m base64 -o $1 $2"
        else
            echo -e "\033[0;31m[ERROR]\033[0m base64 -o $1 $2"
        fi
    else
        echo -e "\033[0;31m[ERROR]\033[0m base64 -o $1 $2"
    fi
}

test_base64_stdin_file_output () {
    
    if ( diff <(echo $1 | ./ft_ssl base64 -o $2.mine $3) <(echo $1 | base64 -o $2.true $3) )
    then
        if ( diff $2.mine $2.true )
        then
            echo -e "\033[0;32m[OK]\033[0m echo $1 | base64 -o $2 $3"
        else
            echo -e "\033[0;31m[ERROR]\033[0m echo $1 | base64 -o $2 $3"
        fi
    else
        echo -e "\033[0;31m[ERROR]\033[0m echo $1 | base64 -o $2 $3"
    fi
}

if [[ $1 == '' || $1 == 'base64' ]]
then
    test_base64_stdin ''
    test_base64_stdin '0'
    test_base64_stdin '01'
    test_base64_stdin '012'
    test_base64_stdin '0123'
    test_base64_stdin '01234'
    test_base64_stdin 'foobar'
    test_base64_stdin 'Zm9vYmFyCg==' '-d'
    test_base64_stdin 'Zm9vYmFy' '-d'
    # test_base64_stdin '' '-d'

    test_base64 '-i Makefile'
    test_base64 '-i README.md'

    test_base64_file_output 'output' '-i Makefile'
    test_base64_file_output 'output2' '-i output.true -d'

    rm -f output.mine output.true output2.mine output2.true
    test_base64_stdin_file_output 'Zm9vYmFyCg==' 'output' '-d'

    rm -f output.mine output.true
    test_base64_stdin_file_output 'Zm9vYmFy' 'output' '-d'

    rm -f output.mine output.true
    test_base64_stdin_file_output 'foobar' 'output'

    rm -f output.mine output.true output2.mine output2.true
fi

#########################################################
#                                                       #
#                        DES                            #
#                                                       #
#########################################################

test_des () {
    
    if ( diff <($1) <($2) )
    then
        echo -e "\033[0;32m[OK]\033[0m $2"
    else
        echo -e "\033[0;31m[ERROR]\033[0m $2"
    fi
}

test_des_ecb_decrypt () {

    ./ft_ssl des-ecb -k $2 -i $1 -o output
    
    if ( diff <(cat $1) <(./ft_ssl des-ecb -d -k $2 -i output) )
    then
        echo -e "\033[0;32m[OK]\033[0m des-ecb decrypt file <$1> key <$2>"
    else
        echo -e "\033[0;31m[ERROR]\033[0m des-ecb decrypt file <$1> key <$2>"
    fi
    rm -f output
}

test_des_cbc_decrypt () {

    ./ft_ssl $4 -k $2 -v $3 -i $1 -o output
    
    if ( diff <(cat $1) <(./ft_ssl $4 -d -k $2 -v $3 -i output) )
    then
        echo -e "\033[0;32m[OK]\033[0m $4 decrypt file <$1> key <$2> vector <$3>"
    else
        echo -e "\033[0;31m[ERROR]\033[0m $4 decrypt file <$1> key <$2> vector <$3>"
    fi
    rm -f output
}

test_des_ecb_decrypt_a () {

    ./ft_ssl des-ecb -k $2 -i $1 -o output -a
    
    if ( diff <(cat $1) <(./ft_ssl des-ecb -d -k $2 -i output -a) )
    then
        echo -e "\033[0;32m[OK]\033[0m des-ecb decrypt -a file <$1> key <$2>"
    else
        echo -e "\033[0;31m[ERROR]\033[0m des-ecb decrypt -a file <$1> key <$2>"
    fi
    rm -f output
}

test_des_cbc_decrypt_a () {

    ./ft_ssl $4 -k $2 -v $3 -i $1 -o output -a
    
    if ( diff <(cat $1) <(./ft_ssl $4 -d -k $2 -v $3 -i output -a) )
    then
        echo -e "\033[0;32m[OK]\033[0m $4 decrypt -a file <$1> key <$2> vector <$3>"
    else
        echo -e "\033[0;31m[ERROR]\033[0m $4 decrypt -a file <$1> key <$2> vector <$3>"
    fi
    rm -f output
}

if [[ $1 == '' || $1 == 'des' ]]
then
    # Simple encryption tests on files with size from 0 -> 8
    test_des './ft_ssl des -k ffffffffffffffff -v 0123456789abcdef -i ./tests/file_size_0' 'openssl des -K ffffffffffffffff -iv 0123456789abcdef -in ./tests/file_size_0'
    test_des './ft_ssl des -k ffffffffffffffff -v 0123456789abcdef -i ./tests/file_size_1' 'openssl des -K ffffffffffffffff -iv 0123456789abcdef -in ./tests/file_size_1'
    test_des './ft_ssl des -k ffffffffffffffff -v 0123456789abcdef -i ./tests/file_size_2' 'openssl des -K ffffffffffffffff -iv 0123456789abcdef -in ./tests/file_size_2'
    test_des './ft_ssl des -k ffffffffffffffff -v 0123456789abcdef -i ./tests/file_size_3' 'openssl des -K ffffffffffffffff -iv 0123456789abcdef -in ./tests/file_size_3'
    test_des './ft_ssl des -k ffffffffffffffff -v 0123456789abcdef -i ./tests/file_size_4' 'openssl des -K ffffffffffffffff -iv 0123456789abcdef -in ./tests/file_size_4'
    test_des './ft_ssl des -k ffffffffffffffff -v 0123456789abcdef -i ./tests/file_size_5' 'openssl des -K ffffffffffffffff -iv 0123456789abcdef -in ./tests/file_size_5'
    test_des './ft_ssl des -k ffffffffffffffff -v 0123456789abcdef -i ./tests/file_size_6' 'openssl des -K ffffffffffffffff -iv 0123456789abcdef -in ./tests/file_size_6'
    test_des './ft_ssl des -k ffffffffffffffff -v 0123456789abcdef -i ./tests/file_size_7' 'openssl des -K ffffffffffffffff -iv 0123456789abcdef -in ./tests/file_size_7'
    test_des './ft_ssl des -k ffffffffffffffff -v 0123456789abcdef -i ./tests/file_size_8' 'openssl des -K ffffffffffffffff -iv 0123456789abcdef -in ./tests/file_size_8'

    test_des './ft_ssl des-ecb -k ffffffffffffffff -i ./tests/file_size_0' 'openssl des-ecb -K ffffffffffffffff -in ./tests/file_size_0'
    test_des './ft_ssl des-ecb -k ffffffffffffffff -i ./tests/file_size_1' 'openssl des-ecb -K ffffffffffffffff -in ./tests/file_size_1'
    test_des './ft_ssl des-ecb -k ffffffffffffffff -i ./tests/file_size_2' 'openssl des-ecb -K ffffffffffffffff -in ./tests/file_size_2'
    test_des './ft_ssl des-ecb -k ffffffffffffffff -i ./tests/file_size_3' 'openssl des-ecb -K ffffffffffffffff -in ./tests/file_size_3'
    test_des './ft_ssl des-ecb -k ffffffffffffffff -i ./tests/file_size_4' 'openssl des-ecb -K ffffffffffffffff -in ./tests/file_size_4'
    test_des './ft_ssl des-ecb -k ffffffffffffffff -i ./tests/file_size_5' 'openssl des-ecb -K ffffffffffffffff -in ./tests/file_size_5'
    test_des './ft_ssl des-ecb -k ffffffffffffffff -i ./tests/file_size_6' 'openssl des-ecb -K ffffffffffffffff -in ./tests/file_size_6'
    test_des './ft_ssl des-ecb -k ffffffffffffffff -i ./tests/file_size_7' 'openssl des-ecb -K ffffffffffffffff -in ./tests/file_size_7'
    test_des './ft_ssl des-ecb -k ffffffffffffffff -i ./tests/file_size_8' 'openssl des-ecb -K ffffffffffffffff -in ./tests/file_size_8'

    test_des './ft_ssl des-cbc -k f1f2fadf589cf403 -v 0123456789abcdef -i ./tests/file_size_0' 'openssl des-cbc -K f1f2fadf589cf403 -iv 0123456789abcdef -in ./tests/file_size_0'
    test_des './ft_ssl des-cbc -k f1f2fadf589cf403 -v 0123456789abcdef -i ./tests/file_size_1' 'openssl des-cbc -K f1f2fadf589cf403 -iv 0123456789abcdef -in ./tests/file_size_1'
    test_des './ft_ssl des-cbc -k f1f2fadf589cf403 -v 0123456789abcdef -i ./tests/file_size_2' 'openssl des-cbc -K f1f2fadf589cf403 -iv 0123456789abcdef -in ./tests/file_size_2'
    test_des './ft_ssl des-cbc -k f1f2fadf589cf403 -v 0123456789abcdef -i ./tests/file_size_3' 'openssl des-cbc -K f1f2fadf589cf403 -iv 0123456789abcdef -in ./tests/file_size_3'
    test_des './ft_ssl des-cbc -k f1f2fadf589cf403 -v 0123456789abcdef -i ./tests/file_size_4' 'openssl des-cbc -K f1f2fadf589cf403 -iv 0123456789abcdef -in ./tests/file_size_4'
    test_des './ft_ssl des-cbc -k f1f2fadf589cf403 -v 0123456789abcdef -i ./tests/file_size_5' 'openssl des-cbc -K f1f2fadf589cf403 -iv 0123456789abcdef -in ./tests/file_size_5'
    test_des './ft_ssl des-cbc -k f1f2fadf589cf403 -v 0123456789abcdef -i ./tests/file_size_6' 'openssl des-cbc -K f1f2fadf589cf403 -iv 0123456789abcdef -in ./tests/file_size_6'
    test_des './ft_ssl des-cbc -k f1f2fadf589cf403 -v 0123456789abcdef -i ./tests/file_size_7' 'openssl des-cbc -K f1f2fadf589cf403 -iv 0123456789abcdef -in ./tests/file_size_7'
    test_des './ft_ssl des-cbc -k f1f2fadf589cf403 -v 0123456789abcdef -i ./tests/file_size_8' 'openssl des-cbc -K f1f2fadf589cf403 -iv 0123456789abcdef -in ./tests/file_size_8'

    # Simple encryption tests on big files
    test_des './ft_ssl des -k ffffffffffffffff -v 0123456789abcdef -i Makefile' 'openssl des -K ffffffffffffffff -iv 0123456789abcdef -in Makefile'
    test_des './ft_ssl des -k ffffffffffffffff -v 0123456789abcdef -i README.md' 'openssl des -K ffffffffffffffff -iv 0123456789abcdef -in README.md'
    test_des './ft_ssl des -k 0123456789abcdef -v 0123456789abcdef -i Makefile' 'openssl des -K 0123456789abcdef -iv 0123456789abcdef -in Makefile'
    test_des './ft_ssl des -k 0123456789abcdef -v 0123456789abcdef -i README.md' 'openssl des -K 0123456789abcdef -iv 0123456789abcdef -in README.md'
    test_des './ft_ssl des -k fedcba9876543210 -v 0123456789abcdef -i Makefile' 'openssl des -K fedcba9876543210 -iv 0123456789abcdef -in Makefile'
    test_des './ft_ssl des -k fedcba9876543210 -v 0123456789abcdef -i README.md' 'openssl des -K fedcba9876543210 -iv 0123456789abcdef -in README.md'

    test_des './ft_ssl des-ecb -k ffffffffffffffff -i Makefile' 'openssl des-ecb -K ffffffffffffffff -in Makefile'
    test_des './ft_ssl des-ecb -k ffffffffffffffff -i README.md' 'openssl des-ecb -K ffffffffffffffff -in README.md'
    test_des './ft_ssl des-ecb -k 0123456789abcdef -i Makefile' 'openssl des-ecb -K 0123456789abcdef -in Makefile'
    test_des './ft_ssl des-ecb -k 0123456789abcdef -i README.md' 'openssl des-ecb -K 0123456789abcdef -in README.md'
    test_des './ft_ssl des-ecb -k fedcba9876543210 -i Makefile' 'openssl des-ecb -K fedcba9876543210 -in Makefile'
    test_des './ft_ssl des-ecb -k fedcba9876543210 -i README.md' 'openssl des-ecb -K fedcba9876543210 -in README.md'

    test_des './ft_ssl des-cbc -k ffffffffffffffff -v 0123456789abcdef -i Makefile' 'openssl des-cbc -K ffffffffffffffff -iv 0123456789abcdef -in Makefile'
    test_des './ft_ssl des-cbc -k ffffffffffffffff -v 0123456789abcdef -i README.md' 'openssl des-cbc -K ffffffffffffffff -iv 0123456789abcdef -in README.md'
    test_des './ft_ssl des-cbc -k 0123456789abcdef -v 0123456789abcdef -i Makefile' 'openssl des-cbc -K 0123456789abcdef -iv 0123456789abcdef -in Makefile'
    test_des './ft_ssl des-cbc -k 0123456789abcdef -v 0123456789abcdef -i README.md' 'openssl des-cbc -K 0123456789abcdef -iv 0123456789abcdef -in README.md'
    test_des './ft_ssl des-cbc -k fedcba9876543210 -v 0123456789abcdef -i Makefile' 'openssl des-cbc -K fedcba9876543210 -iv 0123456789abcdef -in Makefile'
    test_des './ft_ssl des-cbc -k fedcba9876543210 -v 0123456789abcdef -i README.md' 'openssl des-cbc -K fedcba9876543210 -iv 0123456789abcdef -in README.md'

    # Simple encryption tests on files with size from 0 -> 8 with -a option
    test_des './ft_ssl des -k 5874693201547864 -v a58e69dfc4c9a8ff -i ./tests/file_size_0 -a' 'openssl des -K 5874693201547864 -iv a58e69dfc4c9a8ff -in ./tests/file_size_0 -a'
    test_des './ft_ssl des -k 5874693201547864 -v a58e69dfc4c9a8ff -i ./tests/file_size_1 -a' 'openssl des -K 5874693201547864 -iv a58e69dfc4c9a8ff -in ./tests/file_size_1 -a'
    test_des './ft_ssl des -k 5874693201547864 -v a58e69dfc4c9a8ff -i ./tests/file_size_2 -a' 'openssl des -K 5874693201547864 -iv a58e69dfc4c9a8ff -in ./tests/file_size_2 -a'
    test_des './ft_ssl des -k 5874693201547864 -v a58e69dfc4c9a8ff -i ./tests/file_size_3 -a' 'openssl des -K 5874693201547864 -iv a58e69dfc4c9a8ff -in ./tests/file_size_3 -a'
    test_des './ft_ssl des -k 5874693201547864 -v a58e69dfc4c9a8ff -i ./tests/file_size_4 -a' 'openssl des -K 5874693201547864 -iv a58e69dfc4c9a8ff -in ./tests/file_size_4 -a'
    test_des './ft_ssl des -k 5874693201547864 -v a58e69dfc4c9a8ff -i ./tests/file_size_5 -a' 'openssl des -K 5874693201547864 -iv a58e69dfc4c9a8ff -in ./tests/file_size_5 -a'
    test_des './ft_ssl des -k 5874693201547864 -v a58e69dfc4c9a8ff -i ./tests/file_size_6 -a' 'openssl des -K 5874693201547864 -iv a58e69dfc4c9a8ff -in ./tests/file_size_6 -a'
    test_des './ft_ssl des -k 5874693201547864 -v a58e69dfc4c9a8ff -i ./tests/file_size_7 -a' 'openssl des -K 5874693201547864 -iv a58e69dfc4c9a8ff -in ./tests/file_size_7 -a'
    test_des './ft_ssl des -k 5874693201547864 -v a58e69dfc4c9a8ff -i ./tests/file_size_8 -a' 'openssl des -K 5874693201547864 -iv a58e69dfc4c9a8ff -in ./tests/file_size_8 -a'

    test_des './ft_ssl des-ecb -a -k 5874693201547864 -i ./tests/file_size_0' 'openssl des-ecb -K 5874693201547864 -a -in ./tests/file_size_0'
    test_des './ft_ssl des-ecb -a -k 5874693201547864 -i ./tests/file_size_1' 'openssl des-ecb -K 5874693201547864 -a -in ./tests/file_size_1'
    test_des './ft_ssl des-ecb -a -k 5874693201547864 -i ./tests/file_size_2' 'openssl des-ecb -K 5874693201547864 -a -in ./tests/file_size_2'
    test_des './ft_ssl des-ecb -a -k 5874693201547864 -i ./tests/file_size_3' 'openssl des-ecb -K 5874693201547864 -a -in ./tests/file_size_3'
    test_des './ft_ssl des-ecb -a -k 5874693201547864 -i ./tests/file_size_4' 'openssl des-ecb -K 5874693201547864 -a -in ./tests/file_size_4'
    test_des './ft_ssl des-ecb -a -k 5874693201547864 -i ./tests/file_size_5' 'openssl des-ecb -K 5874693201547864 -a -in ./tests/file_size_5'
    test_des './ft_ssl des-ecb -a -k 5874693201547864 -i ./tests/file_size_6' 'openssl des-ecb -K 5874693201547864 -a -in ./tests/file_size_6'
    test_des './ft_ssl des-ecb -a -k 5874693201547864 -i ./tests/file_size_7' 'openssl des-ecb -K 5874693201547864 -a -in ./tests/file_size_7'
    test_des './ft_ssl des-ecb -a -k 5874693201547864 -i ./tests/file_size_8' 'openssl des-ecb -K 5874693201547864 -a -in ./tests/file_size_8'

    test_des './ft_ssl des-cbc -a -k f1f2fadf589cf403 -v 5874693201547864 -i ./tests/file_size_0' 'openssl des-cbc -a -K f1f2fadf589cf403 -iv 5874693201547864 -in ./tests/file_size_0'
    test_des './ft_ssl des-cbc -a -k f1f2fadf589cf403 -v 5874693201547864 -i ./tests/file_size_1' 'openssl des-cbc -a -K f1f2fadf589cf403 -iv 5874693201547864 -in ./tests/file_size_1'
    test_des './ft_ssl des-cbc -a -k f1f2fadf589cf403 -v 5874693201547864 -i ./tests/file_size_2' 'openssl des-cbc -a -K f1f2fadf589cf403 -iv 5874693201547864 -in ./tests/file_size_2'
    test_des './ft_ssl des-cbc -a -k f1f2fadf589cf403 -v 5874693201547864 -i ./tests/file_size_3' 'openssl des-cbc -a -K f1f2fadf589cf403 -iv 5874693201547864 -in ./tests/file_size_3'
    test_des './ft_ssl des-cbc -a -k f1f2fadf589cf403 -v 5874693201547864 -i ./tests/file_size_4' 'openssl des-cbc -a -K f1f2fadf589cf403 -iv 5874693201547864 -in ./tests/file_size_4'
    test_des './ft_ssl des-cbc -a -k f1f2fadf589cf403 -v 5874693201547864 -i ./tests/file_size_5' 'openssl des-cbc -a -K f1f2fadf589cf403 -iv 5874693201547864 -in ./tests/file_size_5'
    test_des './ft_ssl des-cbc -a -k f1f2fadf589cf403 -v 5874693201547864 -i ./tests/file_size_6' 'openssl des-cbc -a -K f1f2fadf589cf403 -iv 5874693201547864 -in ./tests/file_size_6'
    test_des './ft_ssl des-cbc -a -k f1f2fadf589cf403 -v 5874693201547864 -i ./tests/file_size_7' 'openssl des-cbc -a -K f1f2fadf589cf403 -iv 5874693201547864 -in ./tests/file_size_7'
    test_des './ft_ssl des-cbc -a -k f1f2fadf589cf403 -v 5874693201547864 -i ./tests/file_size_8' 'openssl des-cbc -a -K f1f2fadf589cf403 -iv 5874693201547864 -in ./tests/file_size_8'

    # Simple encryption tests on big files with -a option
    test_des './ft_ssl des -a -k ffffffffffffffff -v 0123456789abcdef -i Makefile' 'openssl des -a -K ffffffffffffffff -iv 0123456789abcdef -in Makefile'
    test_des './ft_ssl des -a -k ffffffffffffffff -v 0123456789abcdef -i README.md' 'openssl des -a -K ffffffffffffffff -iv 0123456789abcdef -in README.md'
    test_des './ft_ssl des -a -k 0123456789abcdef -v 0123456789abcdef -i Makefile' 'openssl des -a -K 0123456789abcdef -iv 0123456789abcdef -in Makefile'
    test_des './ft_ssl des -a -k 0123456789abcdef -v 0123456789abcdef -i README.md' 'openssl des -a -K 0123456789abcdef -iv 0123456789abcdef -in README.md'
    test_des './ft_ssl des -a -k fedcba9876543210 -v 0123456789abcdef -i Makefile' 'openssl des -a -K fedcba9876543210 -iv 0123456789abcdef -in Makefile'
    test_des './ft_ssl des -a -k fedcba9876543210 -v 0123456789abcdef -i README.md' 'openssl des -a -K fedcba9876543210 -iv 0123456789abcdef -in README.md'

    test_des './ft_ssl des-ecb -a -k ffffffffffffffff -i Makefile' 'openssl des-ecb -a -K ffffffffffffffff -in Makefile'
    test_des './ft_ssl des-ecb -a -k ffffffffffffffff -i README.md' 'openssl des-ecb -a -K ffffffffffffffff -in README.md'
    test_des './ft_ssl des-ecb -a -k 0123456789abcdef -i Makefile' 'openssl des-ecb -a -K 0123456789abcdef -in Makefile'
    test_des './ft_ssl des-ecb -a -k 0123456789abcdef -i README.md' 'openssl des-ecb -a -K 0123456789abcdef -in README.md'
    test_des './ft_ssl des-ecb -a -k fedcba9876543210 -i Makefile' 'openssl des-ecb -a -K fedcba9876543210 -in Makefile'
    test_des './ft_ssl des-ecb -a -k fedcba9876543210 -i README.md' 'openssl des-ecb -a -K fedcba9876543210 -in README.md'

    test_des './ft_ssl des-cbc -a -k ffffffffffffffff -v 0123456789abcdef -i Makefile' 'openssl des-cbc -a -K ffffffffffffffff -iv 0123456789abcdef -in Makefile'
    test_des './ft_ssl des-cbc -a -k ffffffffffffffff -v 0123456789abcdef -i README.md' 'openssl des-cbc -a -K ffffffffffffffff -iv 0123456789abcdef -in README.md'
    test_des './ft_ssl des-cbc -a -k 0123456789abcdef -v 0123456789abcdef -i Makefile' 'openssl des-cbc -a -K 0123456789abcdef -iv 0123456789abcdef -in Makefile'
    test_des './ft_ssl des-cbc -a -k 0123456789abcdef -v 0123456789abcdef -i README.md' 'openssl des-cbc -a -K 0123456789abcdef -iv 0123456789abcdef -in README.md'
    test_des './ft_ssl des-cbc -a -k fedcba9876543210 -v 0123456789abcdef -i Makefile' 'openssl des-cbc -a -K fedcba9876543210 -iv 0123456789abcdef -in Makefile'
    test_des './ft_ssl des-cbc -a -k fedcba9876543210 -v 0123456789abcdef -i README.md' 'openssl des-cbc -a -K fedcba9876543210 -iv 0123456789abcdef -in README.md'

    # Simple decryption tests on files with size from 0 -> 8
    test_des_ecb_decrypt ./tests/file_size_0 ffffffffffffffff
    test_des_ecb_decrypt ./tests/file_size_0 0123456789abcdef
    test_des_ecb_decrypt ./tests/file_size_0 fedcba9876543210
    test_des_ecb_decrypt ./tests/file_size_0 5874693201547864
    test_des_ecb_decrypt ./tests/file_size_0 a58e69dfc4c9a8ff
    test_des_ecb_decrypt ./tests/file_size_0 f1f2fadf589cf403

    test_des_ecb_decrypt ./tests/file_size_1 ffffffffffffffff
    test_des_ecb_decrypt ./tests/file_size_1 0123456789abcdef
    test_des_ecb_decrypt ./tests/file_size_1 fedcba9876543210
    test_des_ecb_decrypt ./tests/file_size_1 5874693201547864
    test_des_ecb_decrypt ./tests/file_size_1 a58e69dfc4c9a8ff
    test_des_ecb_decrypt ./tests/file_size_1 f1f2fadf589cf403

    test_des_ecb_decrypt ./tests/file_size_2 ffffffffffffffff
    test_des_ecb_decrypt ./tests/file_size_2 0123456789abcdef
    test_des_ecb_decrypt ./tests/file_size_2 fedcba9876543210
    test_des_ecb_decrypt ./tests/file_size_2 5874693201547864
    test_des_ecb_decrypt ./tests/file_size_2 a58e69dfc4c9a8ff
    test_des_ecb_decrypt ./tests/file_size_2 f1f2fadf589cf403

    test_des_ecb_decrypt ./tests/file_size_3 ffffffffffffffff
    test_des_ecb_decrypt ./tests/file_size_3 0123456789abcdef
    test_des_ecb_decrypt ./tests/file_size_3 fedcba9876543210
    test_des_ecb_decrypt ./tests/file_size_3 5874693201547864
    test_des_ecb_decrypt ./tests/file_size_3 a58e69dfc4c9a8ff
    test_des_ecb_decrypt ./tests/file_size_3 f1f2fadf589cf403

    test_des_ecb_decrypt ./tests/file_size_4 ffffffffffffffff
    test_des_ecb_decrypt ./tests/file_size_4 0123456789abcdef
    test_des_ecb_decrypt ./tests/file_size_4 fedcba9876543210
    test_des_ecb_decrypt ./tests/file_size_4 5874693201547864
    test_des_ecb_decrypt ./tests/file_size_4 a58e69dfc4c9a8ff
    test_des_ecb_decrypt ./tests/file_size_4 f1f2fadf589cf403

    test_des_ecb_decrypt ./tests/file_size_5 ffffffffffffffff
    test_des_ecb_decrypt ./tests/file_size_5 0123456789abcdef
    test_des_ecb_decrypt ./tests/file_size_5 fedcba9876543210
    test_des_ecb_decrypt ./tests/file_size_5 5874693201547864
    test_des_ecb_decrypt ./tests/file_size_5 a58e69dfc4c9a8ff
    test_des_ecb_decrypt ./tests/file_size_5 f1f2fadf589cf403

    test_des_ecb_decrypt ./tests/file_size_6 ffffffffffffffff
    test_des_ecb_decrypt ./tests/file_size_6 0123456789abcdef
    test_des_ecb_decrypt ./tests/file_size_6 fedcba9876543210
    test_des_ecb_decrypt ./tests/file_size_6 5874693201547864
    test_des_ecb_decrypt ./tests/file_size_6 a58e69dfc4c9a8ff
    test_des_ecb_decrypt ./tests/file_size_6 f1f2fadf589cf403

    test_des_ecb_decrypt ./tests/file_size_7 ffffffffffffffff
    test_des_ecb_decrypt ./tests/file_size_7 0123456789abcdef
    test_des_ecb_decrypt ./tests/file_size_7 fedcba9876543210
    test_des_ecb_decrypt ./tests/file_size_7 5874693201547864
    test_des_ecb_decrypt ./tests/file_size_7 a58e69dfc4c9a8ff
    test_des_ecb_decrypt ./tests/file_size_7 f1f2fadf589cf403

    test_des_ecb_decrypt ./tests/file_size_8 ffffffffffffffff
    test_des_ecb_decrypt ./tests/file_size_8 0123456789abcdef
    test_des_ecb_decrypt ./tests/file_size_8 fedcba9876543210
    test_des_ecb_decrypt ./tests/file_size_8 5874693201547864
    test_des_ecb_decrypt ./tests/file_size_8 a58e69dfc4c9a8ff
    test_des_ecb_decrypt ./tests/file_size_8 f1f2fadf589cf403

    test_des_cbc_decrypt ./tests/file_size_0 ffffffffffffffff ffffffffffffffff des
    test_des_cbc_decrypt ./tests/file_size_0 0123456789abcdef 0123456789abcdef des
    test_des_cbc_decrypt ./tests/file_size_0 fedcba9876543210 fedcba9876543210 des
    test_des_cbc_decrypt ./tests/file_size_0 5874693201547864 5874693201547864 des
    test_des_cbc_decrypt ./tests/file_size_0 a58e69dfc4c9a8ff a58e69dfc4c9a8ff des
    test_des_cbc_decrypt ./tests/file_size_0 f1f2fadf589cf403 f1f2fadf589cf403 des

    test_des_cbc_decrypt ./tests/file_size_1 ffffffffffffffff ffffffffffffffff des
    test_des_cbc_decrypt ./tests/file_size_1 0123456789abcdef 0123456789abcdef des
    test_des_cbc_decrypt ./tests/file_size_1 fedcba9876543210 fedcba9876543210 des
    test_des_cbc_decrypt ./tests/file_size_1 5874693201547864 5874693201547864 des
    test_des_cbc_decrypt ./tests/file_size_1 a58e69dfc4c9a8ff a58e69dfc4c9a8ff des
    test_des_cbc_decrypt ./tests/file_size_1 f1f2fadf589cf403 f1f2fadf589cf403 des

    test_des_cbc_decrypt ./tests/file_size_2 ffffffffffffffff ffffffffffffffff des
    test_des_cbc_decrypt ./tests/file_size_2 0123456789abcdef 0123456789abcdef des
    test_des_cbc_decrypt ./tests/file_size_2 fedcba9876543210 fedcba9876543210 des
    test_des_cbc_decrypt ./tests/file_size_2 5874693201547864 5874693201547864 des
    test_des_cbc_decrypt ./tests/file_size_2 a58e69dfc4c9a8ff a58e69dfc4c9a8ff des
    test_des_cbc_decrypt ./tests/file_size_2 f1f2fadf589cf403 f1f2fadf589cf403 des

    test_des_cbc_decrypt ./tests/file_size_3 ffffffffffffffff ffffffffffffffff des
    test_des_cbc_decrypt ./tests/file_size_3 0123456789abcdef 0123456789abcdef des
    test_des_cbc_decrypt ./tests/file_size_3 fedcba9876543210 fedcba9876543210 des
    test_des_cbc_decrypt ./tests/file_size_3 5874693201547864 5874693201547864 des
    test_des_cbc_decrypt ./tests/file_size_3 a58e69dfc4c9a8ff a58e69dfc4c9a8ff des
    test_des_cbc_decrypt ./tests/file_size_3 f1f2fadf589cf403 f1f2fadf589cf403 des

    test_des_cbc_decrypt ./tests/file_size_4 ffffffffffffffff ffffffffffffffff des
    test_des_cbc_decrypt ./tests/file_size_4 0123456789abcdef 0123456789abcdef des
    test_des_cbc_decrypt ./tests/file_size_4 fedcba9876543210 fedcba9876543210 des
    test_des_cbc_decrypt ./tests/file_size_4 5874693201547864 5874693201547864 des
    test_des_cbc_decrypt ./tests/file_size_4 a58e69dfc4c9a8ff a58e69dfc4c9a8ff des
    test_des_cbc_decrypt ./tests/file_size_4 f1f2fadf589cf403 f1f2fadf589cf403 des

    test_des_cbc_decrypt ./tests/file_size_5 ffffffffffffffff ffffffffffffffff des
    test_des_cbc_decrypt ./tests/file_size_5 0123456789abcdef 0123456789abcdef des
    test_des_cbc_decrypt ./tests/file_size_5 fedcba9876543210 fedcba9876543210 des
    test_des_cbc_decrypt ./tests/file_size_5 5874693201547864 5874693201547864 des
    test_des_cbc_decrypt ./tests/file_size_5 a58e69dfc4c9a8ff a58e69dfc4c9a8ff des
    test_des_cbc_decrypt ./tests/file_size_5 f1f2fadf589cf403 f1f2fadf589cf403 des

    test_des_cbc_decrypt ./tests/file_size_6 ffffffffffffffff ffffffffffffffff des
    test_des_cbc_decrypt ./tests/file_size_6 0123456789abcdef 0123456789abcdef des
    test_des_cbc_decrypt ./tests/file_size_6 fedcba9876543210 fedcba9876543210 des
    test_des_cbc_decrypt ./tests/file_size_6 5874693201547864 5874693201547864 des
    test_des_cbc_decrypt ./tests/file_size_6 a58e69dfc4c9a8ff a58e69dfc4c9a8ff des
    test_des_cbc_decrypt ./tests/file_size_6 f1f2fadf589cf403 f1f2fadf589cf403 des

    test_des_cbc_decrypt ./tests/file_size_7 ffffffffffffffff ffffffffffffffff des
    test_des_cbc_decrypt ./tests/file_size_7 0123456789abcdef 0123456789abcdef des
    test_des_cbc_decrypt ./tests/file_size_7 fedcba9876543210 fedcba9876543210 des
    test_des_cbc_decrypt ./tests/file_size_7 5874693201547864 5874693201547864 des
    test_des_cbc_decrypt ./tests/file_size_7 a58e69dfc4c9a8ff a58e69dfc4c9a8ff des
    test_des_cbc_decrypt ./tests/file_size_7 f1f2fadf589cf403 f1f2fadf589cf403 des

    test_des_cbc_decrypt ./tests/file_size_8 ffffffffffffffff ffffffffffffffff des
    test_des_cbc_decrypt ./tests/file_size_8 0123456789abcdef 0123456789abcdef des
    test_des_cbc_decrypt ./tests/file_size_8 fedcba9876543210 fedcba9876543210 des
    test_des_cbc_decrypt ./tests/file_size_8 5874693201547864 5874693201547864 des
    test_des_cbc_decrypt ./tests/file_size_8 a58e69dfc4c9a8ff a58e69dfc4c9a8ff des
    test_des_cbc_decrypt ./tests/file_size_8 f1f2fadf589cf403 f1f2fadf589cf403 des

    # Simple decryption tests on big files
    test_des_ecb_decrypt Makefile ffffffffffffffff
    test_des_ecb_decrypt README.md ffffffffffffffff
    test_des_ecb_decrypt Makefile 0123456789abcdef
    test_des_ecb_decrypt README.md 0123456789abcdef
    test_des_ecb_decrypt Makefile fedcba9876543210
    test_des_ecb_decrypt README.md fedcba9876543210

    test_des_cbc_decrypt Makefile ffffffffffffffff ffffffffffffffff des
    test_des_cbc_decrypt README.md ffffffffffffffff ffffffffffffffff des
    test_des_cbc_decrypt Makefile 0123456789abcdef 0123456789abcdef des
    test_des_cbc_decrypt README.md 0123456789abcdef 0123456789abcdef des
    test_des_cbc_decrypt Makefile fedcba9876543210 fedcba9876543210 des
    test_des_cbc_decrypt README.md fedcba9876543210 fedcba9876543210 des

    test_des_cbc_decrypt Makefile ffffffffffffffff ffffffffffffffff des-cbc
    test_des_cbc_decrypt README.md ffffffffffffffff ffffffffffffffff des-cbc
    test_des_cbc_decrypt Makefile 0123456789abcdef 0123456789abcdef des-cbc
    test_des_cbc_decrypt README.md 0123456789abcdef 0123456789abcdef des-cbc
    test_des_cbc_decrypt Makefile fedcba9876543210 fedcba9876543210 des-cbc
    test_des_cbc_decrypt README.md fedcba9876543210 fedcba9876543210 des-cbc

    # Simple decryption tests on files with size from 0 -> 8 with -a option
    test_des_ecb_decrypt_a ./tests/file_size_0 ffffffffffffffff
    test_des_ecb_decrypt_a ./tests/file_size_0 0123456789abcdef
    test_des_ecb_decrypt_a ./tests/file_size_0 fedcba9876543210
    test_des_ecb_decrypt_a ./tests/file_size_0 5874693201547864
    test_des_ecb_decrypt_a ./tests/file_size_0 a58e69dfc4c9a8ff
    test_des_ecb_decrypt_a ./tests/file_size_0 f1f2fadf589cf403

    test_des_ecb_decrypt_a ./tests/file_size_1 ffffffffffffffff
    test_des_ecb_decrypt_a ./tests/file_size_1 0123456789abcdef
    test_des_ecb_decrypt_a ./tests/file_size_1 fedcba9876543210
    test_des_ecb_decrypt_a ./tests/file_size_1 5874693201547864
    test_des_ecb_decrypt_a ./tests/file_size_1 a58e69dfc4c9a8ff
    test_des_ecb_decrypt_a ./tests/file_size_1 f1f2fadf589cf403

    test_des_ecb_decrypt_a ./tests/file_size_2 ffffffffffffffff
    test_des_ecb_decrypt_a ./tests/file_size_2 0123456789abcdef
    test_des_ecb_decrypt_a ./tests/file_size_2 fedcba9876543210
    test_des_ecb_decrypt_a ./tests/file_size_2 5874693201547864
    test_des_ecb_decrypt_a ./tests/file_size_2 a58e69dfc4c9a8ff
    test_des_ecb_decrypt_a ./tests/file_size_2 f1f2fadf589cf403

    test_des_ecb_decrypt_a ./tests/file_size_3 ffffffffffffffff
    test_des_ecb_decrypt_a ./tests/file_size_3 0123456789abcdef
    test_des_ecb_decrypt_a ./tests/file_size_3 fedcba9876543210
    test_des_ecb_decrypt_a ./tests/file_size_3 5874693201547864
    test_des_ecb_decrypt_a ./tests/file_size_3 a58e69dfc4c9a8ff
    test_des_ecb_decrypt_a ./tests/file_size_3 f1f2fadf589cf403

    test_des_ecb_decrypt_a ./tests/file_size_4 ffffffffffffffff
    test_des_ecb_decrypt_a ./tests/file_size_4 0123456789abcdef
    test_des_ecb_decrypt_a ./tests/file_size_4 fedcba9876543210
    test_des_ecb_decrypt_a ./tests/file_size_4 5874693201547864
    test_des_ecb_decrypt_a ./tests/file_size_4 a58e69dfc4c9a8ff
    test_des_ecb_decrypt_a ./tests/file_size_4 f1f2fadf589cf403

    test_des_ecb_decrypt_a ./tests/file_size_5 ffffffffffffffff
    test_des_ecb_decrypt_a ./tests/file_size_5 0123456789abcdef
    test_des_ecb_decrypt_a ./tests/file_size_5 fedcba9876543210
    test_des_ecb_decrypt_a ./tests/file_size_5 5874693201547864
    test_des_ecb_decrypt_a ./tests/file_size_5 a58e69dfc4c9a8ff
    test_des_ecb_decrypt_a ./tests/file_size_5 f1f2fadf589cf403

    test_des_ecb_decrypt_a ./tests/file_size_6 ffffffffffffffff
    test_des_ecb_decrypt_a ./tests/file_size_6 0123456789abcdef
    test_des_ecb_decrypt_a ./tests/file_size_6 fedcba9876543210
    test_des_ecb_decrypt_a ./tests/file_size_6 5874693201547864
    test_des_ecb_decrypt_a ./tests/file_size_6 a58e69dfc4c9a8ff
    test_des_ecb_decrypt_a ./tests/file_size_6 f1f2fadf589cf403

    test_des_ecb_decrypt_a ./tests/file_size_7 ffffffffffffffff
    test_des_ecb_decrypt_a ./tests/file_size_7 0123456789abcdef
    test_des_ecb_decrypt_a ./tests/file_size_7 fedcba9876543210
    test_des_ecb_decrypt_a ./tests/file_size_7 5874693201547864
    test_des_ecb_decrypt_a ./tests/file_size_7 a58e69dfc4c9a8ff
    test_des_ecb_decrypt_a ./tests/file_size_7 f1f2fadf589cf403

    test_des_ecb_decrypt_a ./tests/file_size_8 ffffffffffffffff
    test_des_ecb_decrypt_a ./tests/file_size_8 0123456789abcdef
    test_des_ecb_decrypt_a ./tests/file_size_8 fedcba9876543210
    test_des_ecb_decrypt_a ./tests/file_size_8 5874693201547864
    test_des_ecb_decrypt_a ./tests/file_size_8 a58e69dfc4c9a8ff
    test_des_ecb_decrypt_a ./tests/file_size_8 f1f2fadf589cf403

    test_des_cbc_decrypt_a ./tests/file_size_0 ffffffffffffffff ffffffffffffffff des
    test_des_cbc_decrypt_a ./tests/file_size_0 0123456789abcdef 0123456789abcdef des
    test_des_cbc_decrypt_a ./tests/file_size_0 fedcba9876543210 fedcba9876543210 des
    test_des_cbc_decrypt_a ./tests/file_size_0 5874693201547864 5874693201547864 des
    test_des_cbc_decrypt_a ./tests/file_size_0 a58e69dfc4c9a8ff a58e69dfc4c9a8ff des
    test_des_cbc_decrypt_a ./tests/file_size_0 f1f2fadf589cf403 f1f2fadf589cf403 des

    test_des_cbc_decrypt_a ./tests/file_size_1 ffffffffffffffff ffffffffffffffff des
    test_des_cbc_decrypt_a ./tests/file_size_1 0123456789abcdef 0123456789abcdef des
    test_des_cbc_decrypt_a ./tests/file_size_1 fedcba9876543210 fedcba9876543210 des
    test_des_cbc_decrypt_a ./tests/file_size_1 5874693201547864 5874693201547864 des
    test_des_cbc_decrypt_a ./tests/file_size_1 a58e69dfc4c9a8ff a58e69dfc4c9a8ff des
    test_des_cbc_decrypt_a ./tests/file_size_1 f1f2fadf589cf403 f1f2fadf589cf403 des

    test_des_cbc_decrypt_a ./tests/file_size_2 ffffffffffffffff ffffffffffffffff des
    test_des_cbc_decrypt_a ./tests/file_size_2 0123456789abcdef 0123456789abcdef des
    test_des_cbc_decrypt_a ./tests/file_size_2 fedcba9876543210 fedcba9876543210 des
    test_des_cbc_decrypt_a ./tests/file_size_2 5874693201547864 5874693201547864 des
    test_des_cbc_decrypt_a ./tests/file_size_2 a58e69dfc4c9a8ff a58e69dfc4c9a8ff des
    test_des_cbc_decrypt_a ./tests/file_size_2 f1f2fadf589cf403 f1f2fadf589cf403 des

    test_des_cbc_decrypt_a ./tests/file_size_3 ffffffffffffffff ffffffffffffffff des
    test_des_cbc_decrypt_a ./tests/file_size_3 0123456789abcdef 0123456789abcdef des
    test_des_cbc_decrypt_a ./tests/file_size_3 fedcba9876543210 fedcba9876543210 des
    test_des_cbc_decrypt_a ./tests/file_size_3 5874693201547864 5874693201547864 des
    test_des_cbc_decrypt_a ./tests/file_size_3 a58e69dfc4c9a8ff a58e69dfc4c9a8ff des
    test_des_cbc_decrypt_a ./tests/file_size_3 f1f2fadf589cf403 f1f2fadf589cf403 des

    test_des_cbc_decrypt_a ./tests/file_size_4 ffffffffffffffff ffffffffffffffff des
    test_des_cbc_decrypt_a ./tests/file_size_4 0123456789abcdef 0123456789abcdef des
    test_des_cbc_decrypt_a ./tests/file_size_4 fedcba9876543210 fedcba9876543210 des
    test_des_cbc_decrypt_a ./tests/file_size_4 5874693201547864 5874693201547864 des
    test_des_cbc_decrypt_a ./tests/file_size_4 a58e69dfc4c9a8ff a58e69dfc4c9a8ff des
    test_des_cbc_decrypt_a ./tests/file_size_4 f1f2fadf589cf403 f1f2fadf589cf403 des

    test_des_cbc_decrypt_a ./tests/file_size_5 ffffffffffffffff ffffffffffffffff des
    test_des_cbc_decrypt_a ./tests/file_size_5 0123456789abcdef 0123456789abcdef des
    test_des_cbc_decrypt_a ./tests/file_size_5 fedcba9876543210 fedcba9876543210 des
    test_des_cbc_decrypt_a ./tests/file_size_5 5874693201547864 5874693201547864 des
    test_des_cbc_decrypt_a ./tests/file_size_5 a58e69dfc4c9a8ff a58e69dfc4c9a8ff des
    test_des_cbc_decrypt_a ./tests/file_size_5 f1f2fadf589cf403 f1f2fadf589cf403 des

    test_des_cbc_decrypt_a ./tests/file_size_6 ffffffffffffffff ffffffffffffffff des
    test_des_cbc_decrypt_a ./tests/file_size_6 0123456789abcdef 0123456789abcdef des
    test_des_cbc_decrypt_a ./tests/file_size_6 fedcba9876543210 fedcba9876543210 des
    test_des_cbc_decrypt_a ./tests/file_size_6 5874693201547864 5874693201547864 des
    test_des_cbc_decrypt_a ./tests/file_size_6 a58e69dfc4c9a8ff a58e69dfc4c9a8ff des
    test_des_cbc_decrypt_a ./tests/file_size_6 f1f2fadf589cf403 f1f2fadf589cf403 des

    test_des_cbc_decrypt_a ./tests/file_size_7 ffffffffffffffff ffffffffffffffff des
    test_des_cbc_decrypt_a ./tests/file_size_7 0123456789abcdef 0123456789abcdef des
    test_des_cbc_decrypt_a ./tests/file_size_7 fedcba9876543210 fedcba9876543210 des
    test_des_cbc_decrypt_a ./tests/file_size_7 5874693201547864 5874693201547864 des
    test_des_cbc_decrypt_a ./tests/file_size_7 a58e69dfc4c9a8ff a58e69dfc4c9a8ff des
    test_des_cbc_decrypt_a ./tests/file_size_7 f1f2fadf589cf403 f1f2fadf589cf403 des

    test_des_cbc_decrypt_a ./tests/file_size_8 ffffffffffffffff ffffffffffffffff des
    test_des_cbc_decrypt_a ./tests/file_size_8 0123456789abcdef 0123456789abcdef des
    test_des_cbc_decrypt_a ./tests/file_size_8 fedcba9876543210 fedcba9876543210 des
    test_des_cbc_decrypt_a ./tests/file_size_8 5874693201547864 5874693201547864 des
    test_des_cbc_decrypt_a ./tests/file_size_8 a58e69dfc4c9a8ff a58e69dfc4c9a8ff des
    test_des_cbc_decrypt_a ./tests/file_size_8 f1f2fadf589cf403 f1f2fadf589cf403 des

    # Simple decryption tests on big files with -a option
    test_des_ecb_decrypt_a Makefile ffffffffffffffff
    test_des_ecb_decrypt_a README.md ffffffffffffffff
    test_des_ecb_decrypt_a Makefile 0123456789abcdef
    test_des_ecb_decrypt_a README.md 0123456789abcdef
    test_des_ecb_decrypt_a Makefile fedcba9876543210
    test_des_ecb_decrypt_a README.md fedcba9876543210

    test_des_cbc_decrypt_a Makefile ffffffffffffffff ffffffffffffffff des
    test_des_cbc_decrypt_a README.md ffffffffffffffff ffffffffffffffff des
    test_des_cbc_decrypt_a Makefile 0123456789abcdef 0123456789abcdef des
    test_des_cbc_decrypt_a README.md 0123456789abcdef 0123456789abcdef des
    test_des_cbc_decrypt_a Makefile fedcba9876543210 fedcba9876543210 des
    test_des_cbc_decrypt_a README.md fedcba9876543210 fedcba9876543210 des

    test_des_cbc_decrypt_a Makefile ffffffffffffffff ffffffffffffffff des-cbc
    test_des_cbc_decrypt_a README.md ffffffffffffffff ffffffffffffffff des-cbc
    test_des_cbc_decrypt_a Makefile 0123456789abcdef 0123456789abcdef des-cbc
    test_des_cbc_decrypt_a README.md 0123456789abcdef 0123456789abcdef des-cbc
    test_des_cbc_decrypt_a Makefile fedcba9876543210 fedcba9876543210 des-cbc
    test_des_cbc_decrypt_a README.md fedcba9876543210 fedcba9876543210 des-cbc
fi
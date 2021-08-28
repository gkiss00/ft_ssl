
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
    test_md5_stdin 'hello' '-pq'
    test_md5_stdin 'hello' '-pr'
    test_md5_stdin 'hello' '-qr'
    test_md5_stdin 'hello' '-pqr'
    test_md5_stdin 'hello' '-p -s hello'
    test_md5_stdin 'hello' '-pq -s hello'
    test_md5_stdin 'hello' '-pr -s hello'
    test_md5_stdin 'hello' '-pqr -s hello'
    test_md5_stdin 'hello' '-pqr -s hello Makefile'

    test_md5 '**/*.c Makefile'
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

if [[ $1 == '' || $1 == 'sha256' ]]
then
    test_sha256_stdin 'hello Makefile'
    test_sha256_stdin '1234567890123456789012345678901234567890123456789012345'
    test_sha256_stdin '12345678901234567890123456789012345678901234567890123456'
    test_sha256_stdin '1234567890123456789012345678901234567890123456789012345678901234'
    test_sha256_stdin '12345678901234567890123456789012345678901234567890123456789012345'

    test_sha256 '**/*.c Makefile'
fi

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
    test_base64_stdin '' '-d'

    test_base64 '-i Makefile'
    test_base64 '-i README.md'
    test_base64 '-i main.c'

    test_base64_file_output 'output' '-i Makefile'
    test_base64_file_output 'output2' '-i output.true -d'
    test_base64_stdin_file_output 'Zm9vYmFyCg==' 'output' '-d'
    test_base64_stdin_file_output 'Zm9vYmFy' 'output' '-d'
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
        echo -e "\033[0;32m[OK]\033[0m test_des-ecb_decrypt $1"
    else
        echo -e "\033[0;31m[ERROR]\033[0m test_des-ecb_decrypt $1"
    fi
    rm -f output
}

test_des_cbc_decrypt () {

    ./ft_ssl $4 -k $2 -v $3 -i $1 -o output
    
    if ( diff <(cat $1) <(./ft_ssl $4 -d -k $2 -v $3 -i output) )
    then
        echo -e "\033[0;32m[OK]\033[0m test_$4_decrypt $1"
    else
        echo -e "\033[0;31m[ERROR]\033[0m test_$4_file_output $1"
    fi
    rm -f output
}

if [[ $1 == '' || $1 == 'des' ]]
then
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

    # test_des './ft_ssl des-ecb -a -k ffffffffffffffff -i Makefile' 'openssl des-ecb -a -K ffffffffffffffff -in Makefile'
    # test_des './ft_ssl des-ecb -a -k ffffffffffffffff -i README.md' 'openssl des-ecb -a -K ffffffffffffffff -in README.md'
    # test_des './ft_ssl des-ecb -a -k ffffffffffffffff -i main.c' 'openssl des-ecb -a -K ffffffffffffffff -in main.c'
    # test_des './ft_ssl des-ecb -a -k ffffffffffffffff -i ft_ssl.h' 'openssl des-ecb -a -K ffffffffffffffff -in ft_ssl.h'

    # test_des './ft_ssl des-ecb -a -k 0123456789abcdef -i Makefile' 'openssl des-ecb -a -K 0123456789abcdef -in Makefile'
    # test_des './ft_ssl des-ecb -a -k 0123456789abcdef -i README.md' 'openssl des-ecb -a -K 0123456789abcdef -in README.md'
    # test_des './ft_ssl des-ecb -a -k 0123456789abcdef -i main.c' 'openssl des-ecb -a -K 0123456789abcdef -in main.c'
    # test_des './ft_ssl des-ecb -a -k 0123456789abcdef -i ft_ssl.h' 'openssl des-ecb -a -K 0123456789abcdef -in ft_ssl.h'

    test_des_ecb_decrypt Makefile ffffffffffffffff
    test_des_ecb_decrypt README.md ffffffffffffffff
    test_des_ecb_decrypt Makefile 0123456789abcdef
    test_des_ecb_decrypt README.md 0123456789abcdef
    test_des_ecb_decrypt Makefile fedcba9876543210
    test_des_ecb_decrypt README.md fedcba9876543210

    # test_des_cbc_decrypt Makefile ffffffffffffffff ffffffffffffffff des
    # test_des_cbc_decrypt README.md ffffffffffffffff ffffffffffffffff des
    # test_des_cbc_decrypt Makefile 0123456789abcdef 0123456789abcdef des
    # test_des_cbc_decrypt README.md 0123456789abcdef 0123456789abcdef des
    # test_des_cbc_decrypt Makefile fedcba9876543210 fedcba9876543210 des
    # test_des_cbc_decrypt README.md fedcba9876543210 fedcba9876543210 des

    # test_des_cbc_decrypt Makefile ffffffffffffffff ffffffffffffffff des-cbc
    # test_des_cbc_decrypt README.md ffffffffffffffff ffffffffffffffff des-cbc
    # test_des_cbc_decrypt Makefile 0123456789abcdef 0123456789abcdef des-cbc
    # test_des_cbc_decrypt README.md 0123456789abcdef 0123456789abcdef des-cbc
    # test_des_cbc_decrypt Makefile fedcba9876543210 fedcba9876543210 des-cbc
    # test_des_cbc_decrypt README.md fedcba9876543210 fedcba9876543210 des-cbc
fi
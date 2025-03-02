#!/bin/bash

COUTNER_SUCCESS=0
COUNTER_FAIL=0
COUNTER=0
DIFF_RES=""

declare -a tests=(
"VAR tests/test_case_cat.txt"
)

declare -a extra=(
"-s tests/test_1_cat.txt"
"-b -e -n -s -t tests/test_1_cat.txt"
"-t tests/test_3_cat.txt"
"-n tests/test_2_cat.txt"
"-n -b tests/test_1_cat.txt"
"-s -n -e tests/test_4_cat.txt"
"-n tests/test_1_cat.txt"
"-n tests/test_1_cat.txt"
"-n tests/test_1_cat.txt tests/test_2_cat.txt"
)

testing()
{
    t=$(echo $@ | sed "s/VAR/$var/")
    ./s21_cat $t > test_s21_cat.txt
    cat $t > test_sys_cat.txt
    DIFF_RES="$(diff -s test_s21_cat.txt test_sys_cat.txt)"
    (( COUNTER++ ))
    if [ "$DIFF_RES" == "Files test_s21_cat.txt and test_sys_cat.txt are identical" ]
    then
      (( COUNTER_SUCCESS++ ))
        echo "$COUNTER ./s21_cat $t \033[32mSUCCESS\033[0m"
    else
      (( COUNTER_FAIL++ ))
        echo "$COUNTER ./s21_cat $t \033[31mFAIL\033[0m"
    fi
    rm test_s21_cat.txt test_sys_cat.txt
}

for i in "${extra[@]}"
do
    var="-"
    testing $i
done

# 1 opt
for var1 in b e n s t
do
    for i in "${tests[@]}"
    do
        var="-$var1"
        testing $i
    done
done

# 2 opts
for var1 in b e n s t
do
    for var2 in b e n s t
    do
        if [ $var1 != $var2 ]
        then
            for i in "${tests[@]}"
            do
                var="-$var1 -$var2"
                testing $i
            done
        fi
    done
done

# 3 opts
for var1 in b e n s t
do
    for var2 in b e n s t
    do
        for var3 in b e n s t
        do
            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
            then
                for i in "${tests[@]}"
                do
                    var="-$var1 -$var2 -$var3"
                    testing $i
                done
            fi
        done
    done
done

# 4 opts
for var1 in b e n s t
do
    for var2 in b e n s t
    do
        for var3 in b e n s t
        do
            for var4 in b e n s t
            do
                if [ $var1 != $var2 ] && [ $var2 != $var3 ] \
                && [ $var1 != $var3 ] && [ $var1 != $var4 ] \
                && [ $var2 != $var4 ] && [ $var3 != $var4 ]
                then
                    for i in "${tests[@]}"
                    do
                        var="-$var1 -$var2 -$var3 -$var4"
                        testing $i
                    done
                fi
            done
        done
    done
done

echo "\033[31mFAIL: $COUNTER_FAIL\033[0m"
echo "\033[32mSUCCESS: $COUNTER_SUCCESS\033[0m"
echo "ALL: $COUNTER"

COUNTER=0
COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
TEST_FILE1="tests/test1.txt"
TEST_FILE2="tests/test2.txt"
PATTERN_FILE="tests/reg_exmpl.txt"
GREP_FILE="./s21_grep"
arguments=(i c n h s o)

declare -a tests=(
  "-f tests/pat.txt tests/test1.txt"
  "-f tests/pat.txt tests/test1.txt tests/test2.txt"
  "-f tests/empty_pat.txt tests/test1.txt"
  "-e ROW tests/test1.txt"
  "-e ROW tests/test1.txt tests/test2.txt"
  "-i row tests/test1.txt tests/test2.txt"
  "-e \"\" tests/test1.txt"
  "-e ro -f tests/pat.txt tests/test1.txt"
  "-v anoth tests/test1.txt tests/test2.txt"
  "-c anoth tests/test1.txt tests/test2.txt"
  "-h anoth tests/test1.txt tests/test2.txt"
  "-s anoth tests/test1.txt tests/test3.txt"
  "-o anoth tests/test1.txt tests/test2.txt"
  "-iv anoth tests/test1.txt tests/test2.txt"
  "-in anoth tests/test1.txt tests/test2.txt"
  "-ie anoth tests/test1.txt tests/test2.txt"
  "-ince anoth tests/test1.txt tests/test2.txt"
  "-lh anoth tests/test1.txt tests/test2.txt"
  "-hc anoth tests/test1.txt tests/test2.txt"
  "-oi anoth tests/test1.txt tests/test2.txt"
  "-ohf pat.txt tests/test1.txt"
  "-oinc anoth tests/test1.txt"
  "-oihlnc -e anoth -e id -f pat.txt tests/test1.txt"
  "an tests/test3.txt"
  #  "-q anoth tests/test1.txt tests/test2.txt"
)

testing()
{
  t=$@
  ./s21_grep $t > tests/s21_grep.txt
  grep $t > tests/grep.txt
  DIFF_RES="$(diff -s tests/s21_grep.txt tests/grep.txt)"
  (( COUNTER++ ))
    if [ "$DIFF_RES" == "Files tests/s21_grep.txt and tests/grep.txt are identical" ]
      then
      echo "$COUNTER ./s21_grep $t - \033[32mSUCCESS\033[0m"
        (( COUNTER_SUCCESS++ ))
      else
      echo "$COUNTER ./s21_grep $t - \033[31mFAIL\033[0m"
        (( COUNTER_FAIL++ ))
    fi
}


for i in "${tests[@]}"
do
    var="-"
    testing $i
done

echo "TEST 1"

for var in ${arguments[@]}
do
  for var2 in ${arguments[@]}
  do
        if [ $var != $var2 ]
        then
          TEST1="-$var$var2 cat $TEST_FILE1"
          $GREP_FILE $TEST1 > tests/s21_grep.txt
          grep $TEST1 > tests/grep.txt
          DIFF_RES="$(diff -s tests/s21_grep.txt tests/grep.txt)"
          (( COUNTER++ ))
          if [ "$DIFF_RES" == "Files tests/s21_grep.txt and tests/grep.txt are identical" ]
            then
            echo "$COUNTER ./s21_grep $TEST1 - \033[32mSUCCESS\033[0m"
              (( COUNTER_SUCCESS++ ))
            else
            echo "$COUNTER ./s21_grep $TEST1 - \033[31mFAIL\033[0m"
              (( COUNTER_FAIL++ ))
          fi
        fi
  done
done

echo "TEST 2"
for var in ${arguments[@]}
do
  for var2 in ${arguments[@]}
  do
        if [ $var != $var2 ]
        then
          TEST2="-$var$var2 cat $TEST_FILE1 $TEST_FILE2"
          $GREP_FILE $TEST2 > tests/s21_grep.txt
          grep $TEST2 > tests/grep.txt
          DIFF_RES="$(diff -s tests/s21_grep.txt tests/grep.txt)"
          (( COUNTER++ ))
          if [ "$DIFF_RES" == "Files tests/s21_grep.txt and tests/grep.txt are identical" ]
            then
            echo "$COUNTER ./s21_grep $TEST2 - \033[32mSUCCESS\033[0m"
              (( COUNTER_SUCCESS++ ))
            else
            echo "$COUNTER ./s21_grep $TEST2 - \033[31mFAIL\033[0m"
              (( COUNTER_FAIL++ ))
          fi
        fi
  done
done

echo "TEST 3:"
for var in ${arguments[@]}
do
  for var2 in ${arguments[@]}
  do
      for var3 in ${arguments[@]}
      do
        if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ]
        then
          TEST3="-$var$var2$var3 cat $TEST_FILE1 $TEST_FILE2"
          $GREP_FILE $TEST3 > tests/s21_grep.txt
          grep $TEST3 > tests/grep.txt
          DIFF_RES="$(diff -s tests/s21_grep.txt tests/grep.txt)"
          (( COUNTER++ ))
          if [ "$DIFF_RES" == "Files tests/s21_grep.txt and tests/grep.txt are identical" ]
            then
            echo "$COUNTER ./s21_grep $TEST3 - \033[32mSUCCESS\033[0m"
              (( COUNTER_SUCCESS++ ))
            else
            echo "$COUNTER ./s21_grep $TEST3 - \033[31mFAIL\033[0m"
              (( COUNTER_FAIL++ ))
          fi
        fi
      done
  done
done

echo "TEST 4:"
for var in ${arguments[@]}
do
  for var2 in ${arguments[@]}
  do
      for var3 in ${arguments[@]}
      do
        if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ]
        then
          TEST4="-$var$var2$var3 -f tests/pat.txt  $TEST_FILE1"
          $GREP_FILE $TEST4 > tests/s21_grep.txt
          grep $TEST4 > tests/grep.txt
          DIFF_RES="$(diff -s tests/s21_grep.txt tests/grep.txt)"
          (( COUNTER++ ))
          if [ "$DIFF_RES" == "Files tests/s21_grep.txt and tests/grep.txt are identical" ]
            then
            echo "$COUNTER ./s21_grep $TEST4 - \033[32mSUCCESS\033[0m"
              (( COUNTER_SUCCESS++ ))
            else
            echo "$COUNTER ./s21_grep $TEST4 - \033[31mFAIL\033[0m"
              (( COUNTER_FAIL++ ))
          fi
        fi
      done
  done
done

rm tests/s21_grep.txt tests/grep.txt
echo "\033[32mSUCCESS\033[0m: $COUNTER_SUCCESS"
echo "\033[31mFAIL\033[0m: $COUNTER_FAIL"

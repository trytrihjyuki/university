#!/bin/bash

printf "Compilation logs: \n"

# if g++ -o brut_solution brut_solution.cpp > ./err_log 2>&1; then
# 	printf "\n[+] brut_solution compiled successfully \n"
# else
# 	printf "\n[-] brut_solution compilation error \nShow error messages? [Y/n]"
# 	read input_err_msg
# 	if [ "$input_err_msg" = "Y" ]; then
# 		printf "Error messages: \n\n\n"
# 		cat err_log
# 		printf "\n"
# 	fi
# 	printf "\nTerminating script! \n"
# 	exit 1
# fi

if g++ -o solution solution.cpp > ./err_log 2>&1; then
	printf "\n[+] solution compiled successfully \n"
else
	printf "\n[-] solution compilation error \nShow error messages? [Y/n]"
	read input_err_msg
	if [ "$input_err_msg" = "Y" ]; then
		printf "Error messages: \n\n\n"
		cat err_log
		printf "\n"
	fi
	printf "\nTerminating script! \n"
	exit 1
fi

if g++ -o generator generator.cpp > ./err_log 2>&1; then
	printf "\n[+] generator compiled successfully \n"
else
	printf "\n[-] generator compilation error \nShow error messages? [Y/n]"
	read input_err_msg
	if [ "$input_err_msg" = "Y" ]; then
		printf "Error messages: \n\n\n"
		cat err_log
		printf "\n"
	fi
	printf "\nTerminating script! \n"
	exit 1
fi


printf "\nInput number of tests\n"

read number_tests

for((i = 1; i<=number_tests; i++)); do
	seed=$((RANDOM % 30000))
	printf "Test %d: " $i
	./generator $seed > test_in
	./zadFilip < test_in > b_out
	#sort -n b_out > b_out
	./solution < test_in > s_out
	#sort -n s_out > s_out
	if !(diff -r b_out b_out > /dev/null); then
		printf "\e[91mWrong answer! \e[39m \n"
		break
	else
		printf "\e[92mOK \e[39m \n"
	fi
done
 
#!/bin/bash

printf "Compilation logs: \n"

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

for input in aisd21c_testy/aisd21c*.inp ; do
    ./solution < $input > s_out
	printf "\n${input%.inp}.out\n"
	if !(diff -r s_out "${input%.inp}.out" > /dev/null); then
		printf "\e[91mWrong answer! \e[39m \n"
		break
	else
		printf "\e[92mOK \e[39m \n"
	fi
done

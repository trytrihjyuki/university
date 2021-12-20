# add
python3 main.py Book -a Stephen King It 1994
python3 main.py Book -a George Orwell 1984 1984
python3 main.py Book -a Agatha Chrisite Murder 1990
python3 main.py Book -a Adam Mickiewicz Pan_Tadeusz 1229
python3 main.py Book -a Hugo Boss lala 1229
python3 main.py Book -a Michael Mitzenmacher Propability 2137
python3 main.py Book -a Hans Kloss Stawka 1978
python3 main.py Book -a Jesus Christ Bible 0
python3 main.py Book -a Lil Pump Esketit 2018

print_tables () {
    echo '#####Books#####':
    python3 main.py Book -p 10
    echo '######Friends#####':
    python3 main.py Friend -p 10
    echo '######Borrowings#####':
    python3 main.py Borrowing -p 10
    echo -e '\n'
}

print_tables

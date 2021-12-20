# add
python3 main.py Friend -a Jan Kowalski 123456789 Janek@wp.pl
python3 main.py Friend -a Kuba Nowak 12342222 Kuba@wp.pl
python3 main.py Friend -a Michał Kozak 2145456789 michu420@wp.pl
python3 main.py Friend -a Tomasz Napet 21456789 tomson22@gmail.pl
python3 main.py Book -a Stephen King It 1994
python3 main.py Book -a George Orwell 1984 1984
python3 main.py Book -a Agatha Chrisite Murder 1990
python3 main.py Book -a Henryk Sienkiewicz Pan_Tadeusz 1229

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
# deleting
python3 main.py Friend -d Tomasz Napet 21456789 tomson22@gmail.pl
python3 main.py Book -d Stephen King It 1994
print_tables

# borrow / donate
echo 'Borrowing/Donating process'
print_tables
python3 main.py Friend -l 2 1 
print_tables
python3 main.py Friend -o 2 1
print_tables


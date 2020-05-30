dd if=/dev/zero of=zera.txt \
bs=$((($(wc -c a.out | awk '{print $1}'))*10+5)) count=1 2> /dev/null
chmod +x zera.txt
./a.out zera.txt
echo "0.mL" > wynik.txt
./zera.txt wynik.txt
cat wynik.txt
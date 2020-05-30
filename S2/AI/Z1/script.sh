runtime=1
counter=4

while [ $runtime -le 5 ]
do
    echo "queens: $counter"
    start=`date +%s`
    python3 hetmany.py $counter
    end=`date +%s`
    runtime=$((end-start))
    counter=$(($counter + 1))
done
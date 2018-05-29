total=0
for language in $(ls languages); do
    lcount=$(wc -l languages/$language/* | tail -1 | awk '{print $1}')
    echo "$language: $lcount"
    total=$((total+lcount))
done
echo "Total: $total"

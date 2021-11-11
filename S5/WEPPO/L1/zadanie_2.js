function is_good(x)
{
        function get_digits(x)
        {
            digits = [];
            while(x)
            {
                last_d = x % 10;
                digits.push(last_d);
                x = Math.floor(x/10);
            }
            return digits;
         }

        digits = get_digits(x);

        sum = 0
        for (let i = 0; i < digits.length; i++)
            sum += digits[i];

        if(x % sum != 0)
                return false;
        for (let i = 0; i < digits.length; i++)
        {
            if(!digits[i] || x % digits[i] != 0) // 0 exclude goodness of number
                return false;
        }

        return true;
}

good_numbers = [];
for (let i = 1; i <= 100000 ; i++)
        if(is_good(i)) good_numbers.push(i);

for (let i = 0; i <= 10; i++)
        console.log(good_numbers[i]);

console.log(good_numbers.length);

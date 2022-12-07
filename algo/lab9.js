n = input("Введіть n(натуральне): ");
x = input("Введіть x(дійсне): ");

if (Math.abs(x) > 1) {
    error("Введіть x від -1 до 1");
    return;
}

function dfact(n) {
    //коли 1 - вихід з рекурсії
    if (n == 1 || n == 0) {
        return 1;
    }
    return n * dfact(n - 2); // n!! = n * (n-2)!!     n-2 - аргумент рекурсивного виклику
}

//output("Факторіал: " + dfact(5)); //15

//на async/await не звертайте уваги, це для того, щоб виводити інформацію по ходу роботи
async function S(x, n, i, sum) {
    sum += dfact(2 * i - 1) * Math.pow(x, 2 * i + 1) / // (2i-1)!! * x^(2i+1)
        (2 * i + 1) * dfact(2 * i); //знаменник, (2i+1)(2i)!!
    if (i >= n) {
        return sum; //вихід з рекурсії
    }
    await output("Ітерація " + i +
        ",   Сума: " + sum.toFixed(8) +
        ",   arcsin(x): " + Math.asin(x).toFixed(8) +
        ",   Різниця: " + Math.abs(Math.asin(x) - sum).toFixed(8));
    return await S(x, n, i + 1, sum); //x та n залишаються не змінними, i збільшується на 1, sum - сума
}
відповідь = await S(x, n, 1, 0);
output("Сума: " + відповідь);
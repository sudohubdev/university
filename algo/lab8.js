/*
    Роботу виконав Вітязь Денис (116-1)
    Варіант 3
*/

/*
Заповнити матрицю, від лівого верхнього кута по спіралі: вправо -
вниз - вліво - вгору.
*/
розмірність = input("Введіть розмірність матриці: ", "число");

//2d масив розмірність*розмірність
матриця = Array.from(Array(розмірність), () => new Array(розмірність));

//заповнюємо матрицю
//починаємо з лівого верхнього кута
//проходимо по спіралі
//вправо - вниз - вліво - вгору

ліво = 0;
право = розмірність - 1;
верх = 0;
низ = розмірність - 1;

значення = 1;

while (ліво <= право && верх <= низ) {
    //вправо
    for (i = ліво; i <= право; i++) {
        матриця[верх][i] = значення;
        значення++;
    }
    верх++;

    //вниз
    for (i = верх; i <= низ; i++) {
        матриця[i][право] = значення;
        значення++;
    }
    право--;

    //вліво
    for (i = право; i >= ліво; i--) {
        матриця[низ][i] = значення;
        значення++;
    }
    низ--;

    //вгору
    for (i = низ; i >= верх; i--) {
        матриця[i][ліво] = значення;
        значення++;
    }
    ліво++;
}

//виводимо матрицю
output("Матриця:");
for (i = 0; i < розмірність; i++) {
    output(матриця[i]);
}
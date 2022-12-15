//найти булеви степеней матриці

let A = [
    [0, 1, 0, 1, 1],
    [0, 1, 1, 1, 1],
    [0, 0, 0, 0, 1],
    [0, 0, 1, 1, 1],
    [0, 0, 0, 0, 0]
];

function matrixPow(A, n) {
    let result = A;
    for (let i = 0; i < n - 1; i++) {
        result = matrixMultiply(result, A);
    }
    return result;
}

function matrixMultiply(A, B) {
    let result = [];
    for (let i = 0; i < A.length; i++) {
        result[i] = [];
        for (let j = 0; j < B[0].length; j++) {
            result[i][j] = 0;
            for (let k = 0; k < A[0].length; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

console.log(A);
console.log(matrixPow(A, 2));
console.log(matrixPow(A, 3));
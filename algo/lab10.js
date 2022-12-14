//задали вершини графу
var points = [1, 2, 3, 4, 5, 6];

//це орієнтований граф, має початок кінець і вагу
var graph = [
    //початок, кінець, вага
    [1, 3, 31],
    [1, 4, 54],
    [1, 2, 10],
    [2, 1, 10],
    [2, 5, 41],
    [3, 4, 40],
    [3, 6, 19],
    [4, 6, 73],
    [5, 3, 72],
    [6, 5, 26]
]

//алгоритм Дейкстри
async function dijkstra(graph, points, start) {
    var dist = []; //відстань від початку до кожної вершини
    var prev = []; //попередня вершина
    var visited = []; //відвідані вершини
    var path = []; //шлях

    var mindist, next;

    //встановлюємо стартову умову
    for (var i = 0; i < points.length; i++) {
        dist[points[i]] = Infinity; //d(x) = ∞
        prev[points[i]] = -1;
        visited[points[i]] = false;
    }
    dist[start] = 0; //d(1) = 0

    //шукаємо шлях
    for (var i = 0; i < points.length; i++) { //повторюємо для кожної вершини
        mindist = Infinity;
        //шукаємо найменшу відстань
        for (var j = 0; j < points.length; j++) {
            //якщо вершина не відвідана і відстань менша за мінімальну
            if (!visited[points[j]] && dist[points[j]] < mindist) {
                mindist = dist[points[j]]; //запам'ятовуємо відстань
                next = points[j]; //запам'ятовуємо вершину
            }
        }
        visited[next] = true; //викреслюємо вершину

        //обновляємо відстань
        for (var j = 0; j < graph.length; j++) {
            //якщо вершина знаходиться в графі
            if (graph[j][0] == next) {
                //якщо відстань до вершини більша за відстань до попередньої вершини + вага
                // виконує min(d(x), d(y) + a(y, x))
                if (dist[graph[j][1]] > dist[graph[j][0]] + graph[j][2]) {
                    dist[graph[j][1]] = dist[graph[j][0]] + graph[j][2];
                    prev[graph[j][1]] = next;
                }
            }
        }
        /*debug (виводить проміжні результати)
        output("Проміжний результат для i = " + i);
        output("шляхи");
        for (var j = 0; j < points.length; j++) {
            output("d(" + points[j] + ") = " + dist[points[j]]);
        }
        output("попередні вершини");
        for (var j = 0; j < points.length; j++) {
            if (prev[points[j]] != -1)
                output("p(" + points[j] + ") = " + prev[points[j]]);
        }
        output("відвідані вершини");
        for (var j = 0; j < points.length; j++) {
            if (visited[points[j]])
                output("v(" + points[j] + ") = " + visited[points[j]]);
        }
        */
    }
    //шукаємо шлях
    for (var i = 0; i < points.length; i++) {
        path[i] = []; //шлях це масив масивів (шлях до кожної вершини)
        var j = 0;
        var k = points[i];
        while (k != -1) { //поки не досягнемо початку
            path[i][j] = k; //записуємо вершину
            k = prev[k]; //переходимо до попередньої вершини
            j++; //збільшуємо індекс
        }
        path[i].reverse();
    }
    return path;
}

//виводимо результат
var pathes = await dijkstra(graph, points, 1);

for (var i = 0; i < pathes.length; i++) {
    output("d(" + points[i] + ") = " + pathes[i]);
}
#include <iostream>
#include <fstream>

using namespace std;

const int N = 6;

void fill_graph(int g[N][N], ifstream& in)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) in >> g[i][j];
}
void  dozap(int g[N][N])
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) if (g[i][j] == 0) g[i][j] = INT_MAX;
}
void print(int mtx[N][N], int n)
{ //¬ывести матрицу
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << mtx[i][j] << "\t";
        cout << "\n";
    }
}

int *deixtra(int minD[N], int graph[N][N], int start)
{
    bool visited[N];
    for (int i = 1; i < N; i++)
    {
        minD[i] = graph[start][i];
        visited[i] = false;
    } // задаЄм начальные значени€
    minD[start] = 0;
    int index = 0;
    for (int i = 1; i < N; i++)
    {
        int min = INT_MAX;
        for (int j = 1; j < N; j++)
        {
            if (!visited[j] && minD[j] < min)
            {
                min = minD[j];
                index = j;
            }//Ќаходим индекс ближайшей к данной вершины
        }
        visited[index] = true;
        for (int j = 1; j < N; j++)
        {
            if (!visited[j] && graph[index][j] != INT_MAX && minD[index] != INT_MAX && (minD[index] + graph[index][j] < minD[j]))
            {// если эта вершина не пройденна€ и она смежна с выбранной и если сумма веса выбранной вершины и ребра к текущей будет меньше, чем
             // вес текущей на данный момент, то  - мен€ем значение веса текущей вершины.
                minD[j] = minD[index] + graph[index][j];
            }
        }
    }
    return minD;
}
//weightsMtx-сама матрица
//*dist - массив миинимальных рассто€ний
// N - размер массивов
//pathLength-длина пути
int* path_Back(int graph[N][N], int* dist, int N, int& pathLength, int from, int to)
{ //Ќахождение пути обратно
    pathLength = 0; 
    //ѕринимаем что количество вершин, которое надо пройти 0(¬ дальнейшем это длина пути)
    int* path = new int[N]; //ћассив пути, пока что с длиной n

    int cur = to; //»ндекс нынешней вершины

    while (cur != from) 
    { //ѕока мы не дошли куда нужно
        for (int i = 0; i < N; i++)
        {

            if (graph[cur][i] !=INT_MAX && graph[cur][i] + dist[i] == dist[cur])
            { //»щем тот город, который подходит по длине ребра
                path[pathLength] = cur; //«аписываем нынешний город в массив пути
                pathLength++; //”величиваем длину пути
                cur = i; //ѕереходим на следующий подход€щий
                break; //ѕрерываем цикл
            }
        }
    }

    path[pathLength] = cur; //«аписываем последний город
    pathLength++;

    int* res = new int[pathLength]; //—оздаЄм другой массив, но уже нужного размера
    for (int i = 0; i < pathLength; i++)
        res[pathLength - 1 - i] = path[i]; // опируем прошлый, перевернув его

    delete path; //ќчищаем прошлый

    return res; //¬озвращаем новый
}
void main()
{
    setlocale(LC_ALL, "Rus");
    int minD[N]; //минимальное рассто€ние
    char str[N][50];
	ifstream in;
	in.open("cities.txt");
	int graph[N][N];
	fill_graph(graph, in);
    print(graph, N);
    dozap(graph);
	int start;
	cout<< "¬ведите номер вершины старта: ";
	cin >> start;
    
    int* minDD = deixtra(minD, graph, start);
    cout << "—амый короткий путь из указанной вершины до остальных:" << endl;
    for (int i = 1; i < N; i++)
    {
        if (minDD[i] != INT_MAX)
            cout << start << " -> " << i << " = " << minDD[i] << endl;
        else
            cout << start << " -> " << i << " = " << "ƒороги нет! :(" << endl;
    }
    int to;
    cout << "¬ведите город, в который хотите узнать путь: " << endl; cin >> to;
    int pathLength = 0;
    int* path = path_Back(graph, minDD, N, pathLength, start, to);
    if (pathLength <= 0)
    {
          cout << "нет такого пути";
          cout << "pathLength =" << pathLength;
    }
    else
        for (int i = 0; i < pathLength; i++)
        {   
              cout << i + 1 << "й посещенный город " << path[i] << endl;
        }
}
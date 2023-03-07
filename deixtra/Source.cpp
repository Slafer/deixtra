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
{ //������� �������
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
    } // ����� ��������� ��������
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
            }//������� ������ ��������� � ������ �������
        }
        visited[index] = true;
        for (int j = 1; j < N; j++)
        {
            if (!visited[j] && graph[index][j] != INT_MAX && minD[index] != INT_MAX && (minD[index] + graph[index][j] < minD[j]))
            {// ���� ��� ������� �� ���������� � ��� ������ � ��������� � ���� ����� ���� ��������� ������� � ����� � ������� ����� ������, ���
             // ��� ������� �� ������ ������, ��  - ������ �������� ���� ������� �������.
                minD[j] = minD[index] + graph[index][j];
            }
        }
    }
    return minD;
}
//weightsMtx-���� �������
//*dist - ������ ������������ ����������
// N - ������ ��������
//pathLength-����� ����
int* path_Back(int graph[N][N], int* dist, int N, int& pathLength, int from, int to)
{ //���������� ���� �������
    pathLength = 0; 
    //��������� ��� ���������� ������, ������� ���� ������ 0(� ���������� ��� ����� ����)
    int* path = new int[N]; //������ ����, ���� ��� � ������ n

    int cur = to; //������ �������� �������

    while (cur != from) 
    { //���� �� �� ����� ���� �����
        for (int i = 0; i < N; i++)
        {

            if (graph[cur][i] !=INT_MAX && graph[cur][i] + dist[i] == dist[cur])
            { //���� ��� �����, ������� �������� �� ����� �����
                path[pathLength] = cur; //���������� �������� ����� � ������ ����
                pathLength++; //����������� ����� ����
                cur = i; //��������� �� ��������� ����������
                break; //��������� ����
            }
        }
    }

    path[pathLength] = cur; //���������� ��������� �����
    pathLength++;

    int* res = new int[pathLength]; //������ ������ ������, �� ��� ������� �������
    for (int i = 0; i < pathLength; i++)
        res[pathLength - 1 - i] = path[i]; //�������� �������, ���������� ���

    delete path; //������� �������

    return res; //���������� �����
}
void main()
{
    setlocale(LC_ALL, "Rus");
    int minD[N]; //����������� ����������
    char str[N][50];
	ifstream in;
	in.open("cities.txt");
	int graph[N][N];
	fill_graph(graph, in);
    print(graph, N);
    dozap(graph);
	int start;
	cout<< "������� ����� ������� ������: ";
	cin >> start;
    
    int* minDD = deixtra(minD, graph, start);
    cout << "����� �������� ���� �� ��������� ������� �� ���������:" << endl;
    for (int i = 1; i < N; i++)
    {
        if (minDD[i] != INT_MAX)
            cout << start << " -> " << i << " = " << minDD[i] << endl;
        else
            cout << start << " -> " << i << " = " << "������ ���! :(" << endl;
    }
    int to;
    cout << "������� �����, � ������� ������ ������ ����: " << endl; cin >> to;
    int pathLength = 0;
    int* path = path_Back(graph, minDD, N, pathLength, start, to);
    if (pathLength <= 0)
    {
          cout << "��� ������ ����";
          cout << "pathLength =" << pathLength;
    }
    else
        for (int i = 0; i < pathLength; i++)
        {   
              cout << i + 1 << "� ���������� ����� " << path[i] << endl;
        }
}
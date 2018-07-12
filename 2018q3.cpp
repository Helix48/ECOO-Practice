#include <iostream>
#include <climits>
#include <exception>
#define WALL 'W'
#define AIR '.'
#define UP 'U'
#define DOWN 'D'
#define LEFT 'L'
#define RIGHT 'R'
#define CAM 'C'
#define START 'S'

using namespace std;

char grid[100][100];
char gridcpy[100][100];
int dis[100][100];

bool cam = false;

int width, height;
int startx, starty;

void propagate(int x, int y, int nx, int ny);
void start(int x, int y);
void output(bool cheese);
void markCam(int x, int y);

int main()
{

	cin >> height >> width;
	cin.ignore();

	for (int i = 0; i < height; i++)
	{
		string line;
		getline(cin, line);

		for (int j = 0; j < width; j++)
		{
			grid[i][j] = line[j];
			gridcpy[i][j] = line[j];

			if (line[j] == START)
			{
				startx = i;
				starty = j;
				dis[i][j] = 0;
			}
			else
			{
				dis[i][j] = -1;
			}
		}
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (grid[i][j] == CAM)
			{
				grid[i][j] = CAM;
				markCam(i, j);
			}
		}
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			cout << grid[i][j];
		}
		cout << endl;
	}

	// start(startx, starty);
	// output(cam);

	return 0;
}

void start(int x, int y)
{
	propagate(x, y, x + 1, y);
	propagate(x, y, x - 1, y);
	propagate(x, y, x, y + 1);
	propagate(x, y, x, y - 1);
}

void propagate(int x, int y, int nx, int ny)
{
	try
	{
		if (grid[nx][ny] != WALL && dis[x][y] != -1)
		{
			if (dis[nx][ny] > dis[x][y] + 1 || dis[nx][ny] == -1)
			{
				dis[nx][ny] = dis[x][y] + 1;
				start(nx, ny);
			}
		}
	}
	catch (const std::exception &e)
	{
	}
}

void markCam(int x, int y)
{
	for (int i = x + 1;; i++)
	{
		if (grid[i][y] == WALL)
		{
			break;
		}
		else if (grid[i][y] == AIR)
		{
			grid[i][y] = WALL;
		}
		else if (grid[i][y] == START)
		{
			cam = true;
		}
		else
		{
			continue;
		}
	}

	for (int i = x - 1;; i--)
	{
		if (grid[i][y] == WALL)
		{
			break;
		}
		else if (grid[i][y] == AIR)
		{
			grid[i][y] = WALL;
		}
		else if (grid[i][y] == START)
		{
			cam = true;
		}
		else
		{
			continue;
		}
	}
	for (int i = y + 1;; i++)
	{
		if (grid[x][i] == WALL)
		{
			break;
		}
		else if (grid[x][i] == AIR)
		{
			grid[x][i] = WALL;
		}
		else if (grid[x][i] == START)
		{
			cam = true;
		}
		else
		{
			continue;
		}
	}
	for (int i = y - 1;; i--)
	{
		if (grid[x][i] == WALL)
		{
			break;
		}
		else if (grid[x][i] == AIR)
		{
			grid[x][i] = WALL;
		}
		else if (grid[x][i] == START)
		{
			cam = true;
		}
		else
		{
			continue;
		}
	}
}

void output(bool cheese)
{

	for (int i = 0; i < height; i++)
	{

		for (int k = 0; k < width; k++)
		{

			if (gridcpy[i][k] == AIR)
			{
				if (cheese)
				{
					cout << -1 << endl;
				}
				else
				{
					cout << dis[i][k] << endl;
				}
			}
		}
	}
}
#include<iostream>
#include <stdlib.h>
#include<math.h>
#include <ctime>
#include <stdio.h>

#define INFINITY 1000000

class Point {
public :
	long x;
	long y;	
	Point() {
	}
	Point(int _x, int _y) {
		x = _x;
		y = _y;
	}
};

void printPoint(Point p) {
	std::cout << "x : " << p.x << "\ty : " << p.y << std::endl;
}

int compareX(const void* a, const void* b) {
	
	return (((Point *)a)->x - ((Point *)b)->x);
}

int compareY(const void* a, const void* b) {

	return (((Point *)a)->y - ((Point *)b)->y);
}

float distance(Point a, Point b) {
	float dist = sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
	return dist;
}

float bruteForce(Point p[],int start,int end) {
	float min = INFINITY;
	for (int i = start; i <= end; i++) {
		for (int j = i + 1; j <= end; j++) {
			float dist = distance(p[i], p[j]);
			if (dist < min) {
				min = dist;
			}
		}
	}

	return min;
}

float min(float a,float b) {
	return (a < b) ? a : b;
}

float stripClostest(Point p[], const int start, int end,float d) {
	float min = d;
	int n = end - start + 1;
	if (n <= 1) return INFINITY;
	Point *strips = new Point[n];
	for (int i = 0; i < n; i++) {
		strips[i] = p[start + i];
	}
	qsort(strips, n, sizeof(Point), compareY);
	for (int i = 0; i < n ; i++) {
		for (int j = i + 1; j < n && ((strips[j].y - strips[i].y) < min); j++) {
			float dist = distance(strips[i], strips[j]);
			if (dist < min) {
				min = dist;
			}
		}
	}
	return min;
}

float colsest(Point p[],const int start,int end) {
	
	int n = end - start + 1;
	if (n <= 1) {
		return INFINITY;
	}
	else if (n <= 3) {
		return bruteForce(p, start, end);
	}

	int mid = (end + start) / 2;
	float mL = colsest(p, start, mid - 1);
	float mR = colsest(p, mid, end);

	float d = min(mL, mR);

	//vertical line
	int startVer = mid;
	int endVer = mid + 1;
	for (int i = startVer; i >= start; i--) {
		if (abs(p[i].x-p[mid].x) > d) break;
		startVer = i;
	}
	for (int i = endVer; i <= end; i++) {
		if (abs(p[i].x-p[mid].x) > d) break;
		endVer = i;
	}
	float minVer = stripClostest(p, startVer, endVer,d);
	return min(d,minVer);
}

float closestPairOfPoints(Point p[],int n) {
	qsort(p, n, sizeof(Point), compareX);
	return colsest(p, 0, n - 1);;
	//return bruteForce(p, 0, n - 1);
}


//#define BF

const long nPoint = 50000;
const long max = 100000;
Point p[nPoint];
void main() {
	FILE *fpNdata;
	FILE *fpTime;

#ifdef BF
	FILE *fpTimeBF;
#endif 


	fpNdata = fopen("Ndata.txt", "w");
	fpTime = fopen("Timedata.txt", "w");

#ifdef BF
	fpTimeBF = fopen("fpTimeBF.txt", "w");
#endif 

	for (int a = 1000; a <= nPoint; a += 100) {
		srand(time(0));
		int lowest = 1, highest = max;
		int range = (highest - lowest) + 1;
		for (int index = 0; index < a; index++) {
			int xRnd = lowest + int(range*rand() / (RAND_MAX + 1.0));
			int yRnd = lowest + int(range*rand() / (RAND_MAX + 1.0));
			p[index] = Point(xRnd, yRnd);
		}
		int n = a;
		std::cout << n << std::endl;

		long tStart = clock();
		float min = closestPairOfPoints(p, n);
		float rtime = (clock() - tStart) / 1000.0;
		std::cout << "Time closestPairOfPoints : " << (clock() - tStart) / 1000.0 << " sec" << std::endl;
		
		fprintf(fpNdata,"%d\n",a);
		fprintf(fpTime,"%f\n", rtime);

#ifdef BF
		tStart = clock();
		float minB = bruteForce(p, 0, n - 1);
		rtime = (clock() - tStart) / 1000.0;
		std::cout << "Time bruteForce : " << (clock() - tStart) / 1000.0 << " sec" << std::endl;
		fprintf(fpTimeBF, "%f\n", rtime);
		std::cout << "min : " << min << " ,minB : " << minB << std::endl;
#endif 
		std::cout << std::endl;
		
	}
	fclose(fpNdata);
	fclose(fpTime);

#ifdef BF
	fclose(fpTimeBF);
#endif

}


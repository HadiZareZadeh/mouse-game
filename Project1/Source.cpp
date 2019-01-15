#include <iostream>
#include <string>

using namespace std;

// 1 = divar
// 0 = mekan azad
// 2 = masir tey shode tavasot moosh
// 3 = panir

int n = 12;
int m = 12;

int maze[12][12];

int harakat(int, int);
int check(int, int);
void print();
void prepare();

class Stack {
private:
	int top;
	int maxsize;
	int *stack;

public:
	Stack(int max) {
		maxsize = max;
		stack = new int[maxsize];
		top = -1;
	}
	bool isFull() {
		if (top == maxsize - 1)
			return true;
		return false;
	}

	bool isEmpty() {
		if (top == -1)
			return true;
		return false;
	}

	void push(int x) {
		if (isFull())
			return;
		top = top + 1;
		stack[top] = x;
	}

	int* pop(int &x) {
		if (isEmpty())
			return 0;
		x = stack[top];
		top = top - 1;
		return &x;
	}
};
Stack stack = Stack(1000);

void print() 
{ // چاپ ماتریس
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cout << maze[i][j] << "  " ; // چاپ تک تک خانه ها
		}
	    cout << endl; // رفتن به سطر بعد، پس از چاپ هر سطر
	}
}

void prepare() 
{ 
	// آماده سازی ماتریس، از جمله جاگذاری دیوار در چهار طرف ماتریس
	for (int i = 0; i < m; i++) 
		for (int j = 0; j < n; j++) 
		{
			if (i == 0 || j == 0 || i == m - 1 || j == n - 1)  
				maze[i][j] = 1;
			else
				maze[i][j] = 0;
		}

	
	/**************************/
	// جاگذاری دیوار ها توسط کاربر
	int walls;
	cout << "Enter number of walls: ";
	cin >> walls;
	cout << "Note) walls(2 >= satr <= 11 , 2 >= sotun <= 11)" << endl;
	cout << "      walls can't be satr=1 , sotun=1  AND  satr=12 , sotun=12" << endl << endl;
	for (int c = 0; c < walls; c++) {
		cout << "Enter satr sotun for wall " << c+1 << ": ";
		
		int i, j;
		cin >> i >> j;
		while( (( i >= 2 && i <= 11) && (j >= 2 && j <= 11)) == false )
		{
			cout << "You need enter satr sotun, Again: ";
			cin >> i >> j;
		}
		maze[i - 1][j - 1] = 1;
	}

	maze[1][1] = 2; ///جاگذاری محل موش
	maze[10][10] = 3; // جاگذاری محل پنیر
}

int check(int i , int j) {
	maze[i][j] = 2;
	int result = harakat(i, j);
	return result;
}

int harakat(int i, int j) 
{
	cout << "i=" << i << " j=" << j << endl;

	// بررسی رسیدن به پنیر
	if ((i == m - 3 && j == n - 3) || (i == m - 2 && j == n - 3) || (i == m - 3 && j == n - 2)) {
		return 0;
	}
	
	/*************************************************/
	// بررسی برای حرکت بعدی
	if (i == 1 && j == 1) { // بررسی نقطه شروع
		
		// سمت راست
		if (maze[i][j + 1] == 0) { 
			stack.push(1);
			stack.push(1);
			i = 1;
			j = 2;
			return check(i, j);
		}
		// سمت راست پایین
		if (maze[i + 1][j + 1] == 0) { 
			stack.push(1);
			stack.push(1);
			i = 2;
			j = 2;
			return check(i, j);
		}
		// سمت پایین
		if (maze[i + 1][j] == 0) { 
			stack.push(1);
			stack.push(1);
			i = 2;
			j = 1;
			return check(i, j);
		}
		// راهی وجود ندارد
		return -1;
	}
	/*************************************************/
	// نقطه شروع نباشد
	else { 
		// بررسی در دو گوشه ماتریس
		// دو گوش دیگر را درنظر نمیگیریم، چون یکی نقطه شروع موش است و دیگری نقطه پایان
		//گوشه راست بالا
		if (i == 1 && j == n - 2) {
			// سمت پایین
			if (maze[i + 1][j] == 0) {
				stack.push(i);
				stack.push(j);
				i = i + 1;
				j = j;
				return check(i, j);
			}
			// سمت چپ پایین
			if (maze[i + 1][j - 1] == 0) {
				stack.push(i);
				stack.push(j);
				i = i + 1;
				j = j - 1;
				return check(i, j);
			}
			// سمت چپ
			if (maze[i][j - 1] == 0) {
				stack.push(i);
				stack.push(j);
				i = i;
				j = j - 1;
				return check(i, j);
			}
		}
		// گوشه چپ پایین
		else if(i == m-2 && j == 1) {
			// سمت راست بالا
			if (maze[i - 1][j + 1] == 0) {
				stack.push(i);
				stack.push(j);       // ارسال آدرس خانه قبلی به پشته
				i = i - 1;
				j = j + 1;
				return check(i, j);
			}
			// سمت راست
			if (maze[i][j + 1] == 0) {
				stack.push(i);
				stack.push(j);
				i = i;
				j = j + 1;
				return check(i, j);
			}
			// سمت بالا
			if (maze[i - 1][j] == 0) {
				stack.push(i);
				stack.push(j);
				i = i - 1;
				j = j;
				return check(i, j);
			}
		}
		/*************************************************/
		// بررسی در چهار خط ماتریس
		// بررسی در خط سمت بالا
		else if (i == 1) { 
		   // سمت راست
			if (maze[i][j + 1] == 0) {
				stack.push(i);
				stack.push(j);
				maze[i][j + 1] = 2;
				i = i;
				j = j + 1;
				return check(i, j);
			}
			// سمت راست پایین
			if (maze[i + 1][j + 1] == 0) {
				stack.push(i);
				stack.push(j);
				maze[i + 1][j + 1] = 2;
				i = i + 1;
				j = j + 1;
				return check(i, j);
			}
			// سمت پایین
			if (maze[i + 1][j] == 0) {
				stack.push(i);
				stack.push(j);
				maze[i + 1][j] = 2;
				i = i + 1;
				j = j;
				return check(i, j);
			}
			// سمت چپ پایین
			if (maze[i + 1][j - 1] == 0) {
				stack.push(i);
				stack.push(j);
				maze[i + 1][j - 1] = 2;
				i = i + 1;
				j = j - 1;
				return check(i, j);
			}
			// سمت چپ
			if (maze[i][j - 1] == 0) {
				stack.push(i);
				stack.push(j);
				maze[i][j - 1] = 2;
				i = i;
				j = j - 1;
				return check(i, j);
			}
		}
		// بررسی در خط سمت چپ
		else if (j == 1) {
			// سمت پایین
			if (maze[i + 1][j] == 0) {
				stack.push(i);
				stack.push(j);
				i = i + 1;
				j = j;
				return check(i, j);
			}
			// سمت چپ پایین
			if (maze[i + 1][j - 1] == 0) {
				stack.push(i);
				stack.push(j);
				i = i + 1;
				j = j - 1;
				return check(i, j);
			}
			// سمت چپ
			if (maze[i][j - 1] == 0) {
				stack.push(i);
				stack.push(j);
				i = i;
				j = j - 1;
				return check(i, j);
			}
			// سمت چپ بالا
			if (maze[i - 1][j - 1] == 0) {
				stack.push(i);
				stack.push(j);
				i = i - 1;
				j = j - 1;
				return check(i, j);
			}
			// سمت بالا
			if (maze[i - 1][j] == 0) {
				stack.push(i);
				stack.push(j);
				i = i - 1;
				j = j;
				return check(i, j);
			}
		}
		// بررسی در خط سمت راست
		else if (j == n - 2) { 
			// سمت پایین
			if (maze[i + 1][j] == 0) {
				stack.push(i);
				stack.push(j);
				i = i + 1;
				j = j;
				return check(i, j);
			}
			// سمت چپ پایین
			if (maze[i + 1][j - 1] == 0) {
				stack.push(i);
				stack.push(j);
				i = i + 1;
				j = j - 1;
				return check(i, j);
			}
			// سمت چپ
			if (maze[i][j - 1] == 0) {
				stack.push(i);
				stack.push(j);
				i = i;
				j = j - 1;
				return check(i, j);
			}
			// سمت چپ بالا
			if (maze[i - 1][j - 1] == 0) {
				stack.push(i);
				stack.push(j);
				i = i - 1;
				j = j - 1;
				return check(i, j);
			}
			// سمت بالا
			if (maze[i - 1][j] == 0) {
				stack.push(i);
				stack.push(j);
				i = i - 1;
				j = j;
				return check(i, j);
			}
		}
		// بررسی در خط سمت پایین
		else if (i == m - 2) { 
			// سمت راست بالا
			if (maze[i - 1][j + 1] == 0) {
				stack.push(i);
				stack.push(j);
				i = i - 1;
				j = j + 1;
				return check(i, j);
			}
			// سمت راست
			if (maze[i][j + 1] == 0) {
				stack.push(i);
				stack.push(j);
				i = i;
				j = j + 1;
				return check(i, j);
			}
			// سمت چپ
			if (maze[i][j - 1] == 0) {
				stack.push(i);
				stack.push(j);
				i = i;
				j = j - 1;
				return check(i, j);
			}
			// سمت چپ بالا
			if (maze[i - 1][j - 1] == 0) {
				stack.push(i);
				stack.push(j);
				i = i - 1;
				j = j - 1;
				return check(i, j);
			}
			// سمت بالا
			if (maze[i - 1][j] == 0) {
				stack.push(i);
				stack.push(j);
				i = i - 1;
				j = j;
				return check(i, j);
			}
		}
		/*************************************************/
		// بررسی وسط ماتریس
		else if (i > 1 && j > 1 && i < m - 2 && j < n - 2) 
		{
			// سمت راست بالا
			if (maze[i - 1][j + 1] == 0) {
				stack.push(i);
				stack.push(j);       // ارسال آدرس خانه قبلی به پشته
				i = i - 1;
				j = j + 1;
				return check(i, j);
			}
			// سمت راست
			if (maze[i][j + 1] == 0) {
				stack.push(i);
				stack.push(j);
				i = i;
				j = j + 1;
				return check(i, j);
			}
			// سمت راست پایین
			if (maze[i + 1][j + 1] == 0) {
				stack.push(i);
				stack.push(j);
				i = i + 1;
				j = j + 1;
				return check(i, j);
			}
			// سمت پایین
			if (maze[i + 1][j] == 0) {
				stack.push(i);
				stack.push(j);
				i = i + 1;
				j = j;
				return check(i, j);
			}
			// سمت چپ پایین
			if (maze[i + 1][j - 1] == 0) {
				stack.push(i);
				stack.push(j);
				i = i + 1;
				j = j - 1;
				return check(i, j);
			}
			// سمت چپ
			if (maze[i][j - 1] == 0) {
				stack.push(i);
				stack.push(j);
				i = i;
				j = j - 1;
				return check(i, j);
			}
			// سمت چپ بالا
			if (maze[i - 1][j - 1] == 0) {
				stack.push(i);
				stack.push(j);
				i = i - 1;
				j = j - 1;
				return check(i, j);
			}
			// سمت بالا
			if (maze[i - 1][j] == 0) {
				stack.push(i);
				stack.push(j);
				i = i - 1;
				j = j;
				return check(i, j);
			}
		}
		stack.pop(j);
		stack.pop(i);
		return check(i, j);
	}
	return -1;
}

void main() 
{
	prepare();
	cout << "marahel jabejaei: " << endl << endl;
	harakat(1, 1);
	cout << endl << endl;
	print();
	int a;
	cin >> a;
}
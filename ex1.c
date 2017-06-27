
void main(void){
	int a;
	int b;
	int c;
	int d;
	a = 1;
	b = 2;
	c = 3;
	d = 4;
	a = a + b + ((c + d) + 5 + 6) + 7 + 8 * 9; /* 100 */
	output(a);
	b = c * d - b; /* 10 */
	output(b);
	c = d / (c - 1); /* 2 */
	output(c);
	d = a / b - c * c; /* 6 */
	output(d);
}

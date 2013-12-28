#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

string str_input;
float pro[26] = {0.082, 0.015, 0.028, 0.043, 0.127, 0.022, 0.020, 0.061, 0.070, 0.002, 0.008, 0.040, 0.024, 0.067, 0.075, 0.019, 0.001, 0.060, 0.063, 0.091, 0.028, 0.010, 0.023, 0.001, 0.020, 0.001};	


int KeyLength (int length) {
	float p;
	int pass = 0;
	vector<int> PosM;
	vector<float> MY;
	for (int i = 1; i <= 20; i++) {
		int j;
		if ( length	% i == 0) {
			j = length / i;
		} else {
			j = length / i + 1;
		}
		int flag;
		flag = 1;
		float p3 = 0;
		for (int m = 1; (m <= i && flag == 1); m++) {
			int b[26] = {0};
			for (int k = 0; (k<j && (m-1 + k*m)<length); k++) {
				b[str_input[m-1 + k*m] - 65]++;
			}

			float p1,p2;
			int t1;
			p1 = 0;
			p2 = 0;
			t1 = 0;
			for (int a = 0; a < 26; a++) {
				p1 += b[a] * (b[a]-1);
				t1 += b[a];
				b[a] = 0;
			}
		
			p2 = p1/ (t1 * (t1-1)); 
			//if (p2 < 0.08 && p2 > 0.05) {
			//	cout << "[i:p2]" << i << ":" << p2 << endl;
				pass = 1;
				p3 += p2;
			//} else {
			//	flag = 0;
			//	pass = 0;
			//	p3 = 0;
			//}
		}
		if ( pass == 1) {
			PosM.push_back(i);
			MY.push_back(p3/i);
		}
		p3 = 0;
	}
//	cout << PosM.size() << endl;
//	cout << MY.size() << endl;
	int m = 0;
	for (int i = 0; i < PosM.size(); i++) {
//		cout << PosM[i]<< ":" << MY[i] << endl;
		if (fabs(MY[m] - 0.065) > fabs(MY[i] - 0.065)) {
			m = i;
		}
	}
//	cout << PosM[m]<< endl;;
	return PosM[m];
}


vector<int> shift_v;
void GetKey (int m, int length) {
	int n; 					//length of the string y
	
	if (length % m == 0) {
		n = length / m;		
	} else {
		n = length / m + 1;
	}
	
	for (int i  = 0; i < m; i++) {				//keylength
		int shift_now;
		float diff = 1;
		float b[26] = {0};
		for (int k = 0; (i + m*k) < length; k++) {
			b[str_input[i + m*k] -65]++;		//times
		}

		for (int j = 0; j < 26; j++) {			//each string y tries shift 0~25
			float p1,p2;						//p2 = Mg
			int t1;								//total
			p1 = p2 = 0;						//reset
			t1 = 0;
			for (int a = 0; a < 26; a++) {
				p1 += pro[a] * b[(a+j)%26];
				t1 += b[a];
			}
			p2 = p1 / t1;
			
			if (fabs(p2 - 0.065) < diff) {
				shift_now = j;
				diff = fabs(p2 -0.065);
			}

		}
		shift_v.push_back(shift_now);
	}
}

void DeCryption() {
	for (int i = 0; i < shift_v.size(); i++) { 		//print key
		char c;
		c = shift_v[i] + 65;
		cout << c ;
	}
	cout << endl;
	int a = 0;
	int add;
	for (int j = 0; j < str_input.length(); j++) {	//print context
		char c;
		add = a % shift_v.size();	
		a++;
		int ar;
		if (str_input[j] - shift_v[add] < 65) ar = str_input[j] - shift_v[add] + 26;
		else ar = str_input[j] - shift_v[add];
		c = ar;
		cout << c;
	}
	cout << endl;
}

int main() {
	getline(cin, str_input);
	
	int keyl;
	keyl = KeyLength(str_input.length());
	GetKey(keyl, str_input.length());
	DeCryption();
	return 0;
}

#include "NokaFunc.h"
bool HASP = false;

hasp_handle_t handle_dop = HASP_INVALID_HANDLE_VALUE;
std::vector<unsigned int> C = { 0 };

bool Noka(hasp_status_t status_dop, hasp_feature_t feature_dop, unsigned char* vendor_code_dop) {// проверка++
	status_dop = hasp_login(feature_dop, vendor_code_dop, &handle_dop);
	if (status_dop != HASP_STATUS_OK) {
		return false;
		HASP = false;
	}
	else {
		return true;
		HASP = true;
	}
}
std::vector<unsigned int> Count_HASH(std::vector<unsigned int> H, std::vector<unsigned int> W_clone) {
	if (!HASP)//! написать
		return C;
	else {

		unsigned int a, b, c, d, e, f, g, h;
		unsigned int E0, Ma, t2, E1, Ch, t1;
		a = H[0];
		b = H[1];
		c = H[2];
		d = H[3];
		e = H[4];
		f = H[5];
		g = H[6];
		h = H[7];

		for (int i = 0; i < 63; i++) {
			E0 = (My_rotr(a, 2)) ^ (My_rotr(a, 13)) ^ (My_rotr(a, 22));
			Ma = (a & b) ^ (a & c) ^ (b & c);
			t2 = E0 + Ma;
			E1 = (My_rotr(e, 6)) ^ (My_rotr(e, 11)) ^ (My_rotr(e, 25));
			Ch = (e & f) ^ ((~e) & g);
			t1 = h + E1 + Ch + k[i] + W_clone[i];


			h = g;
			g = f;
			f = e;
			e = d + t1;
			d = c;
			c = b;
			b = a;
			a = t1 + t2;

			H[0] += a;
			H[1] += b;
			H[2] += c;
			H[3] += d;
			H[4] += e;
			H[5] += f;
			H[6] += g;
			H[7] += h;
		}
		return H;
	}
}

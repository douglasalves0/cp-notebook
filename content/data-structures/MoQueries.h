/**
 * Author: Simon Lindholm
 * Date: 2019-12-28
 * License: CC0
 * Source: https://github.com/hoke-t/tamu-kactl/blob/master/content/data-structures/MoQueries.h
 * Time: O(N \sqrt Q)
 * Status: stress-tested
 */
#pragma once

void add(int ind) { ... } // add a[ind]
void del(int ind) { ... } // remove a[ind]
int calc() { ... } // compute current answer

vi mo(vector<pii> Q) {
	int L = 0, R = -1, blk = 350; // ~N/sqrt(Q)
	vi s(sz(Q)), res = s;
#define K(x) pii(x.first/blk, x.second ^ -(x.first/blk & 1))
	iota(all(s), 0);
	sort(all(s), [&](int s, int t){ return K(Q[s]) < K(Q[t]); });
	for(int qi : s){
		pii q = Q[qi];
		while(L > q.first) add(--L);
		while(R < q.second) add(++R);
		while(L < q.first) del(L++);
		while(R > q.second) del(R--);
		res[qi] = calc();
	}
	return res;
}

#include "testlib.h"
#include <queue>
#include <stack>

struct DFA {
	int N;
	int *F;
	int (*D)[2];
	DFA(int n) : N(n) {
		F = new int[n]();
		D = new int[n][2]();
	}
};

inline DFA *nextDFA(InStream &inf) {
	DFA *D = new DFA(inf.readInt(1, 10000));
	inf.readEoln();
	for (int i = 0; i < D->N; i++) {
		int j = inf.readInt(0, D->N - 1);
		ensure(D->F[j] == 0);
		inf.readSpace();
		D->F[j] = inf.readInt(0, 1) ? 1 : -1;
		inf.readSpace();
		D->D[j][0] = inf.readInt(0, D->N - 1);
		inf.readSpace();
		D->D[j][1] = inf.readInt(0, D->N - 1);
		inf.readEoln();
	}
	inf.readEof();

	return D;
}

std::stack<char> S;

int main(int argc, char *argv[]) {
	registerTestlibCmd(argc, argv);

	DFA *A = nextDFA(ouf);
	DFA *B = nextDFA(ans);

	std::queue<int> Q;
	int *V = new int[A->N * B->N];
	Q.push(0);
	V[0] = -1;

	while (!Q.empty()) {
		int i = Q.front() / B->N;
		int j = Q.front() % B->N;
		if (A->F[i] != B->F[j]) {
			int k = i * B->N + j;
			while (k) {
				S.push(V[k] & 1 | 48);
				k = (V[k] >> 1) - 1;
			}
			char *s = new char[S.size() + 1]();
			for (k = 0; !S.empty(); k++) {
				s[k] = S.top();
				S.pop();
			}
			quitf(_wa, "Incorrect. Your DFA %sts \"%s\".", A->F[i] > 0 ? "accep" : "rejec", s);
		}
		Q.pop();

		int k;
		k = A->D[i][0] * B->N + B->D[j][0];
		if (!V[k]) {
			Q.push(k);
			V[k] = i * B->N + j + 1 << 1;
		}
		k = A->D[i][1] * B->N + B->D[j][1];
		if (!V[k]) {
			Q.push(k);
			V[k] = i * B->N + j + 1 << 1 | 1;
		}
	}

	quit(_ok, "Correct");
}

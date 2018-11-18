#include "Node.h"

Node::Node(char M[N][N], int t, int a, int b, int pos_i, int pos_j):turn(t),alpha(a),beta(b){
	set_MAP(M);
	if (pos_i != -1) move(pos_i, pos_j);
	get_next_pos();
	H = calc_H();
	child = vector<Node*>(next_i.size(), NULL);
}

void Node::set_MAP(char M[N][N]){
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			this->MAP[i][j] = M[i][j] == '*'? ' ': M[i][j];
}

void Node::get_next_pos(){
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (this->MAP[i][j] - '0' == this->turn) get_next_pos_with_ij(i, j);
}

int Node::calc_H(){
	int white = 0, black = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (MAP[i][j] == '0') white++;
			else if (MAP[i][j] == '1') black++;
	if (next_i.size() == 0) 
		return (white > black? INT_MIN: INT_MAX);
	return black - white;
}

void Node::get_next_pos_with_ij(int i, int j){
	//ˮƽ����
	if (j < N - 1 && MAP[i][j+1] - '0' == 1 - turn){
		int k = j + 2;
		while (k < N && MAP[i][k] - '0' == 1 - turn) k++;
		if (k < N && MAP[i][k] == ' ')
			{MAP[i][k] = '*'; next_i.push_back(i); next_j.push_back(k);}
	}
	if (j > 1 && MAP[i][j-1] - '0' == 1 - turn){
		int k = j - 2;
		while (k >= 0 && MAP[i][k] - '0' == 1 - turn) k--;
		if (k >= 0 && MAP[i][k] == ' ')
			{MAP[i][k] = '*'; next_i.push_back(i); next_j.push_back(k);}
	}
	//��ֱ����
	if (i < N - 1 && MAP[i+1][j] - '0' == 1 - turn){
		int k = i + 2;
		while (k < N && MAP[k][j] - '0' == 1 - turn) k++;
		if (k < N && MAP[k][j] == ' ') 
			{MAP[k][j] = '*'; next_i.push_back(k); next_j.push_back(j);}
	}
	if (i > 1 && MAP[i-1][j] - '0' == 1 - turn){
		int k = i - 2;
		while (k >= 0 && MAP[k][j] - '0' == 1 - turn) k--;
		if (k >= 0 && MAP[k][j] == ' ') 
			{MAP[k][j] = '*'; next_i.push_back(k); next_j.push_back(j);}
	}
	//���¶Խ��߷���
	if (j < N - 1 && i < N - 1 && MAP[i+1][j+1] - '0' == 1 - turn){
		int k = 2;
		while (j + k < N && i + k < N && MAP[i+k][j+k] - '0' == 1 - turn) k++;
		if (j + k < N && i + k < N && MAP[i+k][j+k] == ' ')
			{MAP[i+k][j+k] = '*'; next_i.push_back(i+k); next_j.push_back(j+k);}
	}
	if (j > 1 && i > 1 && MAP[i-1][j-1] - '0' == 1 - turn){
		int k = 2;
		while (j - k >= 0 && i - k >= 0 && MAP[i-k][j-k] - '0' == 1 - turn) k++;
		if (j - k >= 0 && i - k >= 0 && MAP[i-k][j-k] == ' ')
			{MAP[i-k][j-k] = '*'; next_i.push_back(i-k); next_j.push_back(j-k);}
	}
	//���¶Խ��߷���
	if (i < N - 1 && j > 1 && MAP[i+1][j-1] - '0' == 1 - turn){
		int k = 2;
		while(i+k < N && j - k >= 0 && MAP[i+k][j-k] - '0' == 1 - turn) k++;
		if (i+k < N && j - k >= 0 && MAP[i+k][j-k] == ' ')
			{MAP[i+k][j-k] = '*'; next_i.push_back(i+k); next_j.push_back(j-k);}
	}
	if (j < N - 1 && i > 1 && MAP[i-1][j+1] - '0' == 1 - turn){
		int k = 2;
		while(j+k < N && i - k >= 0 && MAP[i-k][j+k] - '0' == 1 - turn) k++;
		if (j+k < N && i - k >= 0 && MAP[i-k][j+k] == ' ')
			{MAP[i-k][j+k] = '*'; next_i.push_back(i-k); next_j.push_back(j+k);}
	}
}

void Node::move(int i, int j){
	MAP[i][j] = '0' + 1 - turn;
	int k;
	//ˮƽ����
	k = j + 1;
	while(k < N && MAP[i][k] - '0' == turn) k++;
	if (k < N && MAP[i][k] - '0' == 1 - turn) 
		for (int w = j + 1; w < k; w++) MAP[i][w] = '0' + 1 - turn;
	k = j - 1;
	while(k >= 0 && MAP[i][k] - '0' == turn) k--;
	if (k >= 0 && MAP[i][k] - '0' == 1 - turn) 
		for (int w = j - 1; w > k; w--) MAP[i][w] = '0' + 1 - turn;
	//��ֱ����
	k = i + 1;
	while (k < N && MAP[k][j] - '0' == turn) k++;
	if (k < N && MAP[k][j] - '0' == 1 - turn)
		for (int w = i + 1; w < k; w++) MAP[w][j] = '0' + 1 - turn;
	k = i - 1;
	while (k >= 0 && MAP[k][j] - '0' == turn) k--;
	if (k >= 0 && MAP[k][j] - '0' == 1 - turn)
		for (int w = i - 1; w > k; w--) MAP[w][j] = '0' + 1 - turn;
	//���¶Խ��߷���
	k = 1;
	while (j + k < N && i + k < N && MAP[i+k][j+k] - '0' == turn) k++;
	if (j + k < N && i + k < N && MAP[i+k][j+k] - '0' == 1 - turn)
		for (int w = 1; w < k; w++) MAP[i+w][j+w] = '0' + 1 - turn;
	k = 1;
	while (j - k >= 0 && i - k >= 0 && MAP[i-k][j-k] - '0' == turn) k++;
	if (j - k < N && i - k < N && MAP[i-k][j-k] - '0' == 1 - turn)
		for (int w = 1; w < k; w++) MAP[i-w][j-w] = '0' + 1 - turn;
	//���¶Խ��߷���
	k = 1;
	while(i+k < N && j - k >= 0 && MAP[i+k][j-k] - '0' == turn) k++;
	if (i+k < N && j - k >= 0 && MAP[i+k][j-k] - '0' == 1 - turn)
		for (int w = 1; w < k; w++) MAP[i+w][j-w] = '0' + 1 - turn;
	k = 1;
	while(j+k < N && i - k >= 0 && MAP[i-k][j+k] - '0' == turn) k++;
	if (i-k < N && j + k >= 0 && MAP[i-k][j+k] - '0' == 1 - turn)
		for (int w = 1; w < k; w++) MAP[i-w][j+w] = '0' + 1 - turn;
}

void Node::show_map(){
	for (int i = 0; i < N; i++){
		cout << "           ";
		for (int k = 0; k < 4 * N; k++) cout << '-';
		cout << "\n           |";
		for (int j = 0; j < N; j++){
			cout << ' ' << this->MAP[i][j] << " |";
		}
		cout << endl;
	}
}

bool Node::isGameOver(){
	return next_i.empty();
}

void Node::get_chess_num(int & black, int & white){
	black = white = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (MAP[i][j] == '1') black++;
			else if (MAP[i][j] == '0') white++;
}
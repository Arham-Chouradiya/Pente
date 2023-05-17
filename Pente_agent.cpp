#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <utility>
#include <string>
#include <climits>
using namespace std;

struct board_white_black	{vector<string> updated_board; int updated_white_captures; int updated_black_captures;};
struct value_x_y {long long int updated_value; int index_x; int index_y;};

value_x_y play_move_white(vector<string> board, long long int alpha, long long int beta, int depth, string who_won, int white_captures, int black_captures, int original_depth, int min_i, int min_j, int max_i, int max_j);
value_x_y play_move_black(vector<string> board, long long int alpha, long long int beta, int depth, string who_won, int white_captures, int black_captures, int original_depth, int min_i, int min_j, int max_i, int max_j);


bool game_ended(vector<string> b, int i, int j)	{
	int same_right = 0, same_left = 0, same_down = 0, same_up = 0, same_right_up = 0, same_right_down = 0, same_left_up = 0, same_left_down = 0;

	//right
	if(i<18 && b[i][j]==b[i+1][j])
	{
		if(i<17 && b[i][j]==b[i+2][j])
		{
			if(i<16 && b[i][j]==b[i+3][j])
			{
				if(i<15 && b[i][j]==b[i+4][j])
					same_right = 4;
				else
					same_right = 3;
			}
			else	same_right = 2;
		}
		else	same_right = 1;
	}

	//left
	if(i>0 && b[i][j]==b[i-1][j])
	{
		if(i>1 && b[i][j]==b[i-2][j])
		{
			if(i>2 && b[i][j]==b[i-3][j])
			{
				if(i>3 && b[i][j]==b[i-4][j])
					same_left = 4;
				else
					same_left = 3;
			}
			else	same_left = 2;
		}
		else	same_left = 1;
	}

	if(same_right + same_left >= 4)
		return true;

	//down
	if(j<18 && b[i][j]==b[i][j+1])
	{
		if(j<17 && b[i][j]==b[i][j+2])
		{
			if(j<16 && b[i][j]==b[i][j+3])
			{
				if(j<15 && b[i][j]==b[i][j+4])
					same_down = 4;
				else
					same_down = 3;
			}
			else	same_down = 2;
		}
		else	same_down = 1;
	}

	//up
	if(j>0 && b[i][j]==b[i][j-1])
	{
		if(j>1 && b[i][j]==b[i][j-2])
		{
			if(j>2 && b[i][j]==b[i][j-3])
			{
				if(j>3 && b[i][j]==b[i][j-4])
					same_up = 4;
				else
					same_up = 3;
			}
			else	same_up = 2;
		}
		else	same_up = 1;
	}

	if(same_up + same_down >= 4)
			return true;

	//right-up
	if(i>0 && j<18 && b[i][j]==b[i-1][j+1])
	{
		if(i>1 && j<17 && b[i][j]==b[i-2][j+2])
		{
			if(i>2 && j<16 && b[i][j]==b[i-3][j+3])
			{
				if(i>3 && j<15 && b[i][j]==b[i-4][j+4])
					same_right_up = 4;
				else
					same_right_up = 3;
			}
			else	same_right_up = 2;
		}
		else	same_right_up = 1;
	}

	//left-down
	if(i<18 && j>0 && b[i][j]==b[i+1][j-1])
	{
		if(i<17 && j>1 && b[i][j]==b[i+2][j-2])
		{
			if(i<16 && j>2 && b[i][j]==b[i+3][j-3])
			{
				if(i<15 && j>3 && b[i][j]==b[i+4][j-4])
					same_left_down = 4;
				else
					same_left_down = 3;
			}
			else	same_left_down = 2;
		}
		else	same_left_down = 1;
	}

	if(same_right_up + same_left_down >= 4)
			return true;

	//right-down
	if(i<18 && j<18 && b[i][j]==b[i+1][j+1])
	{
		if(i<17 && j<17 && b[i][j]==b[i+2][j+2])
		{
			if(i<16 && j<16 && b[i][j]==b[i+3][j+3])
			{
				if(i<15 && j<15 && b[i][j]==b[i+4][j+4])
					same_right_down = 4;
				else
					same_right_down = 3;
			}
			else	same_right_down = 2;
		}
		else	same_right_down = 1;
	}

	//left_up
	if(i>0 && j>0 && b[i][j]==b[i-1][j-1])
	{
		if(i>1 && j>1 && b[i][j]==b[i-2][j-2])
		{
			if(i>2 && j>2 && b[i][j]==b[i-3][j-3])
			{
				if(i>3 && j>3 && b[i][j]==b[i-4][j-4])
					same_left_up = 4;
				else
					same_left_up = 3;
			}
			else	same_left_up = 2;
		}
		else	same_left_up = 1;
	}

	if(same_right_down + same_left_up >= 4)
			return true;

	return false;
}

board_white_black captures(vector<string> b, int i, int j, int white_captures, int black_captures)	{
	char you = b[i][j];
	char opp = b[i][j]=='w'?'b':'w';

	if(i+3<19 && b[i+1][j]==opp && b[i+2][j]==opp && b[i+3][j]==you)					{you=='w'?white_captures++:black_captures++; b[i+1][j]='.'; b[i+2][j]='.';}
	if(i-3>=0 && b[i-1][j]==opp && b[i-2][j]==opp && b[i-3][j]==you)					{you=='w'?white_captures++:black_captures++; b[i-1][j]='.'; b[i-2][j]='.';}
	if(j+3<19 && b[i][j+1]==opp && b[i][j+2]==opp && b[i][j+3]==you)					{you=='w'?white_captures++:black_captures++; b[i][j+1]='.'; b[i][j+2]='.';}
	if(j-3>=0 && b[i][j-1]==opp && b[i][j-2]==opp && b[i][j-3]==you)					{you=='w'?white_captures++:black_captures++; b[i][j-1]='.'; b[i][j-2]='.';}
	if(i+3<19 && j+3<19 && b[i+1][j+1]==opp && b[i+2][j+2]==opp && b[i+3][j+3]==you)	{you=='w'?white_captures++:black_captures++; b[i+1][j+1]='.'; b[i+2][j+2]='.';}
	if(i-3>=0 && j-3>=0 && b[i-1][j-1]==opp && b[i-2][j-2]==opp && b[i-3][j-3]==you)	{you=='w'?white_captures++:black_captures++; b[i-1][j-1]='.'; b[i-2][j-2]='.';}
	if(i-3>=0 && j+3<19 && b[i-1][j+1]==opp && b[i-2][j+2]==opp && b[i-3][j+3]==you)	{you=='w'?white_captures++:black_captures++; b[i-1][j+1]='.'; b[i-2][j+2]='.';}
	if(i+3<19 && j-3>=0 && b[i+1][j-1]==opp && b[i+2][j-2]==opp && b[i+3][j-3]==you)	{you=='w'?white_captures++:black_captures++; b[i+1][j-1]='.'; b[i+2][j-2]='.';}
	
	return board_white_black {b, white_captures, black_captures};
}

value_x_y evaluate(vector<string> b, int white_captures, int black_captures, bool color, int original_depth, string who_won, int min_i, int min_j, int max_i, int max_j)	{
	// cout<<min_i<<":"<<min_j<<" and "<<max_i<<":"<<max_j<<endl;

	value_x_y last_option = {-1,-1,-1};
	value_x_y white_create_5 = {-1000,-1,-1}, black_create_5 = {-1000,-1,-1};
	value_x_y white_create_4 = {-1000,-1,-1}, black_create_4 = {-1000,-1,-1};
	value_x_y white_create_3 = {-1000,-1,-1}, black_create_3 = {-1000,-1,-1};
	value_x_y new_white_captures = {-1000,-1,-1}, new_black_captures = {-1000,-1,-1};
	value_x_y white_create_5_from_3 = {-1000,-1,-1}, black_create_5_from_3 = {-1000,-1,-1};
	
	long long int white_create_5_count = 0, black_create_5_count = 0;
	long long int white_create_4_count = 0, black_create_4_count = 0;
	long long int white_create_3_count = 0, black_create_3_count = 0;
	long long int new_white_captures_count = 0, new_black_captures_count = 0;	
	long long int white_create_5_from_3_count = 0, black_create_5_from_3_count = 0;
	long long int evaluation = 0, far = 2, close = 3;
	long long int white_prevent_5_till_now = 0, white_prevent_4_till_now = 0, white_prevent_3_till_now = 0, white_prevent_2_till_now = 0;
	long long int black_prevent_5_till_now = 0, black_prevent_4_till_now = 0, black_prevent_3_till_now = 0, black_prevent_2_till_now = 0;
	pair<int,int> return_index = {-1,-1};

	//horizontal
	for(int i=min_i;i<=max_i;i++)
		for(int j=min_j;j<=max_j;j++)
		{
			//block of 5
			if(j<15)
			{
				int w_count = 0, b_count = 0;
				for(int k=0;k<5;k++)	{if(b[i][j+k]!='.')	b[i][j+k]=='w'?w_count+=1:b_count+=1;}

				//create 5
				if(w_count == 4 && b_count == 0)	for(int k=0;k<5;k++)	if(b[i][j+k]=='.')	
					{white_create_5 = {1000000000000000000, i, j+k};		white_create_5_count+=1;}
			
				//prevent 5
				if(w_count == 0 && b_count == 4)	for(int k=0;k<5;k++)	if(b[i][j+k]=='.')	
					{black_create_5 = {10000000000000000, i, j+k};	black_create_5_count+=1;}

				//create 5 from 3
				if(w_count == 3 && b_count == 0)	for(int k=0;k<5;k++)	if(b[i][j+k]=='.')	{
					int count=0;
					if(i-2>=0 && b[i-2][j+k]!='.') 					count+=((b[i-2][j+k]=='b'?2:1)*far);	
					if(j+k-2>=0 && b[i][j+k-2]!='.')				count+=((b[i][j+k-2]=='b'?2:1)*far);
					if(i-1>=0 && b[i-1][j+k]!='.')					count+=((b[i-1][j+k]=='b'?2:1)*close);	
					if(j+k-1>=0 && b[i][j+k-1]!='.')				count+=((b[i][j+k-1]=='b'?2:1)*close);
					if(i+2<19 && b[i+2][j+k]!='.')					count+=((b[i+2][j+k]=='b'?2:1)*far);	
					if(j+k+2<19 && b[i][j+k+2]!='.')				count+=((b[i][j+k+2]=='b'?2:1)*far);
					if(i+1<19 && b[i+1][j+k]!='.')					count+=((b[i+1][j+k]=='b'?2:1)*close);	
					if(j+k+1<19 && b[i][j+k+1]!='.')				count+=((b[i][j+k+1]=='b'?2:1)*close);
					if(i-2>=0 && j+k-2>=0 && b[i-2][j+k-2]!='.')	count+=((b[i-2][j+k-2]=='b'?2:1)*far);	
					if(i-1>=0 && j+k-1>=0 && b[i-1][j+k-1]!='.') 	count+=((b[i-1][j+k-1]=='b'?2:1)*close);
					if(i+2<19 && j+k+2<19 && b[i+2][j+k+2]!='.')	count+=((b[i+2][j+k+2]=='b'?2:1)*far);	
					if(i+1<19 && j+k+1<19 && b[i+1][j+k+1]!='.')	count+=((b[i+1][j+k+1]=='b'?2:1)*close);
					if(i-2>=0 && j+k+2<19 && b[i-2][j+k+2]!='.')	count+=((b[i-2][j+k+2]=='b'?2:1)*far);	
					if(i-1>=0 && j+k+1<19 && b[i-1][j+k+1]!='.')	count+=((b[i-1][j+k+1]=='b'?2:1)*close);
					if(i+2<19 && j+k-2>=0 && b[i+2][j+k-2]!='.')	count+=((b[i+2][j+k-2]=='b'?2:1)*far);	
					if(i+1<19 && j+k-1>=0 && b[i+1][j+k-1]!='.')	count+=((b[i+1][j+k-1]=='b'?2:1)*close);

					if(count > white_create_5_from_3.updated_value)	white_create_5_from_3 = {count, i, j+k};
					white_create_5_from_3_count += 1;
				}

				//prevent 5 from 3
				if(w_count == 0 && b_count == 3)	for(int k=0;k<5;k++)	if(b[i][j+k]=='.')	{
					int count=0;
					if(i-2>=0 && b[i-2][j+k]!='.') 					count+=((b[i-2][j+k]=='b'?2:1)*far);	
					if(j+k-2>=0 && b[i][j+k-2]!='.')				count+=((b[i][j+k-2]=='b'?2:1)*far);
					if(i-1>=0 && b[i-1][j+k]!='.')					count+=((b[i-1][j+k]=='b'?2:1)*close);	
					if(j+k-1>=0 && b[i][j+k-1]!='.')				count+=((b[i][j+k-1]=='b'?2:1)*close);
					if(i+2<19 && b[i+2][j+k]!='.')					count+=((b[i+2][j+k]=='b'?2:1)*far);	
					if(j+k+2<19 && b[i][j+k+2]!='.')				count+=((b[i][j+k+2]=='b'?2:1)*far);
					if(i+1<19 && b[i+1][j+k]!='.')					count+=((b[i+1][j+k]=='b'?2:1)*close);	
					if(j+k+1<19 && b[i][j+k+1]!='.')				count+=((b[i][j+k+1]=='b'?2:1)*close);
					if(i-2>=0 && j+k-2>=0 && b[i-2][j+k-2]!='.')	count+=((b[i-2][j+k-2]=='b'?2:1)*far);	
					if(i-1>=0 && j+k-1>=0 && b[i-1][j+k-1]!='.') 	count+=((b[i-1][j+k-1]=='b'?2:1)*close);
					if(i+2<19 && j+k+2<19 && b[i+2][j+k+2]!='.')	count+=((b[i+2][j+k+2]=='b'?2:1)*far);	
					if(i+1<19 && j+k+1<19 && b[i+1][j+k+1]!='.')	count+=((b[i+1][j+k+1]=='b'?2:1)*close);
					if(i-2>=0 && j+k+2<19 && b[i-2][j+k+2]!='.')	count+=((b[i-2][j+k+2]=='b'?2:1)*far);	
					if(i-1>=0 && j+k+1<19 && b[i-1][j+k+1]!='.')	count+=((b[i-1][j+k+1]=='b'?2:1)*close);
					if(i+2<19 && j+k-2>=0 && b[i+2][j+k-2]!='.')	count+=((b[i+2][j+k-2]=='b'?2:1)*far);	
					if(i+1<19 && j+k-1>=0 && b[i+1][j+k-1]!='.')	count+=((b[i+1][j+k-1]=='b'?2:1)*close);
					
					if(count > black_create_5_from_3.updated_value)	black_create_5_from_3 = {count, i, j+k};
					black_create_5_from_3_count += 1;
				}
			}

			//block of 4
			if(j<16)
			{
				int w_count = 0, b_count = 0;
				for(int k=0;k<4;k++)	{if(b[i][j+k]!='.')	b[i][j+k]=='w'?w_count+=1:b_count+=1;}

				//create 4
				if(w_count == 3 && b_count == 0)	for(int k=0;k<4;k++)	if(b[i][j+k]=='.')	{
					int count=0;
					if(i-2>=0 && b[i-2][j+k]!='.') 					count+=((b[i-2][j+k]=='b'?2:1)*far);	
					if(j+k-2>=0 && b[i][j+k-2]!='.')				count+=((b[i][j+k-2]=='b'?2:1)*far);
					if(i-1>=0 && b[i-1][j+k]!='.')					count+=((b[i-1][j+k]=='b'?2:1)*close);	
					if(j+k-1>=0 && b[i][j+k-1]!='.')				count+=((b[i][j+k-1]=='b'?2:1)*close);
					if(i+2<19 && b[i+2][j+k]!='.')					count+=((b[i+2][j+k]=='b'?2:1)*far);	
					if(j+k+2<19 && b[i][j+k+2]!='.')				count+=((b[i][j+k+2]=='b'?2:1)*far);
					if(i+1<19 && b[i+1][j+k]!='.')					count+=((b[i+1][j+k]=='b'?2:1)*close);	
					if(j+k+1<19 && b[i][j+k+1]!='.')				count+=((b[i][j+k+1]=='b'?2:1)*close);
					if(i-2>=0 && j+k-2>=0 && b[i-2][j+k-2]!='.')	count+=((b[i-2][j+k-2]=='b'?2:1)*far);	
					if(i-1>=0 && j+k-1>=0 && b[i-1][j+k-1]!='.') 	count+=((b[i-1][j+k-1]=='b'?2:1)*close);
					if(i+2<19 && j+k+2<19 && b[i+2][j+k+2]!='.')	count+=((b[i+2][j+k+2]=='b'?2:1)*far);	
					if(i+1<19 && j+k+1<19 && b[i+1][j+k+1]!='.')	count+=((b[i+1][j+k+1]=='b'?2:1)*close);
					if(i-2>=0 && j+k+2<19 && b[i-2][j+k+2]!='.')	count+=((b[i-2][j+k+2]=='b'?2:1)*far);	
					if(i-1>=0 && j+k+1<19 && b[i-1][j+k+1]!='.')	count+=((b[i-1][j+k+1]=='b'?2:1)*close);
					if(i+2<19 && j+k-2>=0 && b[i+2][j+k-2]!='.')	count+=((b[i+2][j+k-2]=='b'?2:1)*far);	
					if(i+1<19 && j+k-1>=0 && b[i+1][j+k-1]!='.')	count+=((b[i+1][j+k-1]=='b'?2:1)*close);
					
					if(count > white_create_4.updated_value)	white_create_4 = {count, i, j+k};
					white_create_4_count += 1;
				}

				//prevent 4
				if(w_count == 0 && b_count == 3)	for(int k=0;k<4;k++)	if(b[i][j+k]=='.')	{
					int count=0;
					if(i-2>=0 && b[i-2][j+k]!='.') 					count+=((b[i-2][j+k]=='b'?2:1)*far);	
					if(j+k-2>=0 && b[i][j+k-2]!='.')				count+=((b[i][j+k-2]=='b'?2:1)*far);
					if(i-1>=0 && b[i-1][j+k]!='.')					count+=((b[i-1][j+k]=='b'?2:1)*close);	
					if(j+k-1>=0 && b[i][j+k-1]!='.')				count+=((b[i][j+k-1]=='b'?2:1)*close);
					if(i+2<19 && b[i+2][j+k]!='.')					count+=((b[i+2][j+k]=='b'?2:1)*far);	
					if(j+k+2<19 && b[i][j+k+2]!='.')				count+=((b[i][j+k+2]=='b'?2:1)*far);
					if(i+1<19 && b[i+1][j+k]!='.')					count+=((b[i+1][j+k]=='b'?2:1)*close);	
					if(j+k+1<19 && b[i][j+k+1]!='.')				count+=((b[i][j+k+1]=='b'?2:1)*close);
					if(i-2>=0 && j+k-2>=0 && b[i-2][j+k-2]!='.')	count+=((b[i-2][j+k-2]=='b'?2:1)*far);	
					if(i-1>=0 && j+k-1>=0 && b[i-1][j+k-1]!='.') 	count+=((b[i-1][j+k-1]=='b'?2:1)*close);
					if(i+2<19 && j+k+2<19 && b[i+2][j+k+2]!='.')	count+=((b[i+2][j+k+2]=='b'?2:1)*far);	
					if(i+1<19 && j+k+1<19 && b[i+1][j+k+1]!='.')	count+=((b[i+1][j+k+1]=='b'?2:1)*close);
					if(i-2>=0 && j+k+2<19 && b[i-2][j+k+2]!='.')	count+=((b[i-2][j+k+2]=='b'?2:1)*far);	
					if(i-1>=0 && j+k+1<19 && b[i-1][j+k+1]!='.')	count+=((b[i-1][j+k+1]=='b'?2:1)*close);
					if(i+2<19 && j+k-2>=0 && b[i+2][j+k-2]!='.')	count+=((b[i+2][j+k-2]=='b'?2:1)*far);	
					if(i+1<19 && j+k-1>=0 && b[i+1][j+k-1]!='.')	count+=((b[i+1][j+k-1]=='b'?2:1)*close);
					
					if(count > black_create_4.updated_value)	black_create_4 = {count, i, j+k};
					black_create_4_count += 1;
				}

				//white capture
				if(b[i][j+1]=='b' && b[i][j+2]=='b' && (b[i][j]=='w' && b[i][j+3]=='.') || (b[i][j]=='.' && b[i][j+3]=='w'))
				{
					int k = b[i][j]=='.'?j:j+3, count = 0;
					if(i-2>=0 && b[i-2][k]!='.') 				count+=((b[i-2][k]=='b'?2:1)*far);		
					if(k-2>=0 && b[i][k-2]!='.')				count+=((b[i][k-2]=='b'?2:1)*far);
					if(i-1>=0 && b[i-1][k]!='.')				count+=((b[i-1][k]=='b'?2:1)*close);	
					if(k-1>=0 && b[i][k-1]!='.')				count+=((b[i][k-1]=='b'?2:1)*close);
					if(i+2<19 && b[i+2][k]!='.')				count+=((b[i+2][k]=='b'?2:1)*far);		
					if(k+2<19 && b[i][k+2]!='.')				count+=((b[i][k+2]=='b'?2:1)*far);
					if(i+1<19 && b[i+1][k]!='.')				count+=((b[i+1][k]=='b'?2:1)*close);	
					if(k+1<19 && b[i][k+1]!='.')				count+=((b[i][k+1]=='b'?2:1)*close);
					if(i-2>=0 && k-2>=0 && b[i-2][k-2]!='.')	count+=((b[i-2][k-2]=='b'?2:1)*far);	
					if(i-1>=0 && k-1>=0 && b[i-1][k-1]!='.') 	count+=((b[i-1][k-1]=='b'?2:1)*close);
					if(i+2<19 && k+2<19 && b[i+2][k+2]!='.')	count+=((b[i+2][k+2]=='b'?2:1)*far);	
					if(i+1<19 && k+1<19 && b[i+1][k+1]!='.')	count+=((b[i+1][k+1]=='b'?2:1)*close);
					if(i-2>=0 && k+2<19 && b[i-2][k+2]!='.')	count+=((b[i-2][k+2]=='b'?2:1)*far);	
					if(i-1>=0 && k+1<19 && b[i-1][k+1]!='.')	count+=((b[i-1][k+1]=='b'?2:1)*close);
					if(i+2<19 && k-2>=0 && b[i+2][k-2]!='.')	count+=((b[i+2][k-2]=='b'?2:1)*far);	
					if(i+1<19 && k-1>=0 && b[i+1][k-1]!='.')	count+=((b[i+1][k-1]=='b'?2:1)*close);
					
					if(count > new_white_captures.updated_value)	new_white_captures = {count, i, k};
					new_white_captures_count += 1;
				}

				//black capture
				if(b[i][j+1]=='w' && b[i][j+2]=='w' && (b[i][j]=='b' && b[i][j+3]=='.') || (b[i][j]=='.' && b[i][j+3]=='b'))
				{
					int k = b[i][j]=='.'?j:j+3, count = 0;
					if(i-2>=0 && b[i-2][k]!='.') 				count+=((b[i-2][k]=='b'?2:1)*far);		
					if(k-2>=0 && b[i][k-2]!='.')				count+=((b[i][k-2]=='b'?2:1)*far);
					if(i-1>=0 && b[i-1][k]!='.')				count+=((b[i-1][k]=='b'?2:1)*close);	
					if(k-1>=0 && b[i][k-1]!='.')				count+=((b[i][k-1]=='b'?2:1)*close);
					if(i+2<19 && b[i+2][k]!='.')				count+=((b[i+2][k]=='b'?2:1)*far);		
					if(k+2<19 && b[i][k+2]!='.')				count+=((b[i][k+2]=='b'?2:1)*far);
					if(i+1<19 && b[i+1][k]!='.')				count+=((b[i+1][k]=='b'?2:1)*close);	
					if(k+1<19 && b[i][k+1]!='.')				count+=((b[i][k+1]=='b'?2:1)*close);
					if(i-2>=0 && k-2>=0 && b[i-2][k-2]!='.')	count+=((b[i-2][k-2]=='b'?2:1)*far);	
					if(i-1>=0 && k-1>=0 && b[i-1][k-1]!='.') 	count+=((b[i-1][k-1]=='b'?2:1)*close);
					if(i+2<19 && k+2<19 && b[i+2][k+2]!='.')	count+=((b[i+2][k+2]=='b'?2:1)*far);	
					if(i+1<19 && k+1<19 && b[i+1][k+1]!='.')	count+=((b[i+1][k+1]=='b'?2:1)*close);
					if(i-2>=0 && k+2<19 && b[i-2][k+2]!='.')	count+=((b[i-2][k+2]=='b'?2:1)*far);	
					if(i-1>=0 && k+1<19 && b[i-1][k+1]!='.')	count+=((b[i-1][k+1]=='b'?2:1)*close);
					if(i+2<19 && k-2>=0 && b[i+2][k-2]!='.')	count+=((b[i+2][k-2]=='b'?2:1)*far);	
					if(i+1<19 && k-1>=0 && b[i+1][k-1]!='.')	count+=((b[i+1][k-1]=='b'?2:1)*close);
					
					if(count > new_black_captures.updated_value)	new_black_captures = {count, i, k};
					new_black_captures_count += 1;
				}
			}

			//block of 3
			if(j<17)
			{
				int w_count = 0, b_count = 0;
				for(int k=0;k<3;k++)	{if(b[i][j+k]!='.')	b[i][j+k]=='w'?w_count+=1:b_count+=1;}

				//create 3
				if(w_count == 2 && b_count == 0)	for(int k=0;k<3;k++)	if(b[i][j+k]=='.')	{
					int count=0;
					if(i-2>=0 && b[i-2][j+k]!='.') 					count+=((b[i-2][j+k]=='b'?2:1)*far);	
					if(j+k-2>=0 && b[i][j+k-2]!='.')				count+=((b[i][j+k-2]=='b'?2:1)*far);
					if(i-1>=0 && b[i-1][j+k]!='.')					count+=((b[i-1][j+k]=='b'?2:1)*close);	
					if(j+k-1>=0 && b[i][j+k-1]!='.')				count+=((b[i][j+k-1]=='b'?2:1)*close);
					if(i+2<19 && b[i+2][j+k]!='.')					count+=((b[i+2][j+k]=='b'?2:1)*far);	
					if(j+k+2<19 && b[i][j+k+2]!='.')				count+=((b[i][j+k+2]=='b'?2:1)*far);
					if(i+1<19 && b[i+1][j+k]!='.')					count+=((b[i+1][j+k]=='b'?2:1)*close);	
					if(j+k+1<19 && b[i][j+k+1]!='.')				count+=((b[i][j+k+1]=='b'?2:1)*close);
					if(i-2>=0 && j+k-2>=0 && b[i-2][j+k-2]!='.')	count+=((b[i-2][j+k-2]=='b'?2:1)*far);	
					if(i-1>=0 && j+k-1>=0 && b[i-1][j+k-1]!='.') 	count+=((b[i-1][j+k-1]=='b'?2:1)*close);
					if(i+2<19 && j+k+2<19 && b[i+2][j+k+2]!='.')	count+=((b[i+2][j+k+2]=='b'?2:1)*far);	
					if(i+1<19 && j+k+1<19 && b[i+1][j+k+1]!='.')	count+=((b[i+1][j+k+1]=='b'?2:1)*close);
					if(i-2>=0 && j+k+2<19 && b[i-2][j+k+2]!='.')	count+=((b[i-2][j+k+2]=='b'?2:1)*far);	
					if(i-1>=0 && j+k+1<19 && b[i-1][j+k+1]!='.')	count+=((b[i-1][j+k+1]=='b'?2:1)*close);
					if(i+2<19 && j+k-2>=0 && b[i+2][j+k-2]!='.')	count+=((b[i+2][j+k-2]=='b'?2:1)*far);	
					if(i+1<19 && j+k-1>=0 && b[i+1][j+k-1]!='.')	count+=((b[i+1][j+k-1]=='b'?2:1)*close);
					
					if(count > white_create_3.updated_value)	white_create_3 = {count, i, j+k};
					white_create_3_count += 1;
				}

				//prevent 3
				if(w_count == 0 && b_count == 2)	for(int k=0;k<3;k++)	if(b[i][j+k]=='.')	{
					int count=0;
					if(i-2>=0 && b[i-2][j+k]!='.') 					count+=((b[i-2][j+k]=='b'?2:1)*far);	
					if(j+k-2>=0 && b[i][j+k-2]!='.')				count+=((b[i][j+k-2]=='b'?2:1)*far);
					if(i-1>=0 && b[i-1][j+k]!='.')					count+=((b[i-1][j+k]=='b'?2:1)*close);	
					if(j+k-1>=0 && b[i][j+k-1]!='.')				count+=((b[i][j+k-1]=='b'?2:1)*close);
					if(i+2<19 && b[i+2][j+k]!='.')					count+=((b[i+2][j+k]=='b'?2:1)*far);	
					if(j+k+2<19 && b[i][j+k+2]!='.')				count+=((b[i][j+k+2]=='b'?2:1)*far);
					if(i+1<19 && b[i+1][j+k]!='.')					count+=((b[i+1][j+k]=='b'?2:1)*close);	
					if(j+k+1<19 && b[i][j+k+1]!='.')				count+=((b[i][j+k+1]=='b'?2:1)*close);
					if(i-2>=0 && j+k-2>=0 && b[i-2][j+k-2]!='.')	count+=((b[i-2][j+k-2]=='b'?2:1)*far);	
					if(i-1>=0 && j+k-1>=0 && b[i-1][j+k-1]!='.') 	count+=((b[i-1][j+k-1]=='b'?2:1)*close);
					if(i+2<19 && j+k+2<19 && b[i+2][j+k+2]!='.')	count+=((b[i+2][j+k+2]=='b'?2:1)*far);	
					if(i+1<19 && j+k+1<19 && b[i+1][j+k+1]!='.')	count+=((b[i+1][j+k+1]=='b'?2:1)*close);
					if(i-2>=0 && j+k+2<19 && b[i-2][j+k+2]!='.')	count+=((b[i-2][j+k+2]=='b'?2:1)*far);	
					if(i-1>=0 && j+k+1<19 && b[i-1][j+k+1]!='.')	count+=((b[i-1][j+k+1]=='b'?2:1)*close);
					if(i+2<19 && j+k-2>=0 && b[i+2][j+k-2]!='.')	count+=((b[i+2][j+k-2]=='b'?2:1)*far);	
					if(i+1<19 && j+k-1>=0 && b[i+1][j+k-1]!='.')	count+=((b[i+1][j+k-1]=='b'?2:1)*close);
					
					if(count > black_create_3.updated_value)	black_create_3 = {count, i, j+k};
					black_create_3_count += 1;
				}
			}
		}

	//vertical
	for(int i=min_i;i<=max_i;i++)
		for(int j=min_j;j<=max_j;j++)
		{
			//block of 5
			if(i<15)
			{
				int w_count = 0, b_count = 0;
				for(int k=0;k<5;k++)	{if(b[i+k][j]!='.')	b[i+k][j]=='w'?w_count+=1:b_count+=1;}

				//create 5
				if(w_count == 4 && b_count == 0)	for(int k=0;k<5;k++)	if(b[i+k][j]=='.')	
					{white_create_5 = {1000000000000000000, i+k, j};		white_create_5_count+=1;}
			
				//prevent 5
				if(w_count == 0 && b_count == 4)	for(int k=0;k<5;k++)	if(b[i+k][j]=='.')	
					{black_create_5 = {10000000000000000, i+k, j};	black_create_5_count+=1;}

				//create 5 from 3
				if(w_count == 3 && b_count == 0)	for(int k=0;k<5;k++)	if(b[i+k][j]=='.')	{
					int count=0;
					if(j-2>=0 && b[i+k][j-2]!='.') 					count+=((b[i+k][j-2]=='b'?2:1)*far);	
					if(i+k-2>=0 && b[i+k-2][j]!='.')				count+=((b[i+k-2][j]=='b'?2:1)*far);
					if(j-1>=0 && b[i+k][j-1]!='.')					count+=((b[i+k][j-1]=='b'?2:1)*close);	
					if(i+k-1>=0 && b[i+k-1][j]!='.')				count+=((b[i+k-1][j]=='b'?2:1)*close);
					if(j+2<19 && b[i+k][j+2]!='.')					count+=((b[i+k][j+2]=='b'?2:1)*far);	
					if(i+k+2<19 && b[i+k+2][j]!='.')				count+=((b[i+k+2][j]=='b'?2:1)*far);
					if(j+1<19 && b[i+k][j+1]!='.')					count+=((b[i+k][j+1]=='b'?2:1)*close);	
					if(i+k+1<19 && b[i+k+1][j]!='.')				count+=((b[i+k+1][j]=='b'?2:1)*close);
					if(j-2>=0 && i+k-2>=0 && b[i+k-2][j-2]!='.')	count+=((b[i+k-2][j-2]=='b'?2:1)*far);	
					if(j-1>=0 && i+k-1>=0 && b[i+k-1][j-1]!='.') 	count+=((b[i+k-1][j-1]=='b'?2:1)*close);
					if(j+2<19 && i+k+2<19 && b[i+k+2][j+2]!='.')	count+=((b[i+k+2][j+2]=='b'?2:1)*far);	
					if(j+1<19 && i+k+1<19 && b[i+k+1][j+1]!='.')	count+=((b[i+k+1][j+1]=='b'?2:1)*close);
					if(j-2>=0 && i+k+2<19 && b[i+k+2][j-2]!='.')	count+=((b[i+k+2][j-2]=='b'?2:1)*far);	
					if(j-1>=0 && i+k+1<19 && b[i+k+1][j-1]!='.')	count+=((b[i+k+1][j-1]=='b'?2:1)*close);
					if(j+2<19 && i+k-2>=0 && b[i+k-2][j+2]!='.')	count+=((b[i+k-2][j+2]=='b'?2:1)*far);	
					if(j+1<19 && i+k-1>=0 && b[i+k-1][j+1]!='.')	count+=((b[i+k-1][j+1]=='b'?2:1)*close);

					if(count > white_create_5_from_3.updated_value)	white_create_5_from_3 = {count, i+k, j};
					white_create_5_from_3_count += 1;
				}

				//prevent 5 from 3
				if(w_count == 0 && b_count == 3)	for(int k=0;k<5;k++)	if(b[i+k][j]=='.')	{
					int count=0;
					if(j-2>=0 && b[i+k][j-2]!='.') 					count+=((b[i+k][j-2]=='b'?2:1)*far);	
					if(i+k-2>=0 && b[i+k-2][j]!='.')				count+=((b[i+k-2][j]=='b'?2:1)*far);
					if(j-1>=0 && b[i+k][j-1]!='.')					count+=((b[i+k][j-1]=='b'?2:1)*close);	
					if(i+k-1>=0 && b[i+k-1][j]!='.')				count+=((b[i+k-1][j]=='b'?2:1)*close);
					if(j+2<19 && b[i+k][j+2]!='.')					count+=((b[i+k][j+2]=='b'?2:1)*far);	
					if(i+k+2<19 && b[i+k+2][j]!='.')				count+=((b[i+k+2][j]=='b'?2:1)*far);
					if(j+1<19 && b[i+k][j+1]!='.')					count+=((b[i+k][j+1]=='b'?2:1)*close);	
					if(i+k+1<19 && b[i+k+1][j]!='.')				count+=((b[i+k+1][j]=='b'?2:1)*close);
					if(j-2>=0 && i+k-2>=0 && b[i+k-2][j-2]!='.')	count+=((b[i+k-2][j-2]=='b'?2:1)*far);	
					if(j-1>=0 && i+k-1>=0 && b[i+k-1][j-1]!='.') 	count+=((b[i+k-1][j-1]=='b'?2:1)*close);
					if(j+2<19 && i+k+2<19 && b[i+k+2][j+2]!='.')	count+=((b[i+k+2][j+2]=='b'?2:1)*far);	
					if(j+1<19 && i+k+1<19 && b[i+k+1][j+1]!='.')	count+=((b[i+k+1][j+1]=='b'?2:1)*close);
					if(j-2>=0 && i+k+2<19 && b[i+k+2][j-2]!='.')	count+=((b[i+k+2][j-2]=='b'?2:1)*far);	
					if(j-1>=0 && i+k+1<19 && b[i+k+1][j-1]!='.')	count+=((b[i+k+1][j-1]=='b'?2:1)*close);
					if(j+2<19 && i+k-2>=0 && b[i+k-2][j+2]!='.')	count+=((b[i+k-2][j+2]=='b'?2:1)*far);	
					if(j+1<19 && i+k-1>=0 && b[i+k-1][j+1]!='.')	count+=((b[i+k-1][j+1]=='b'?2:1)*close);
					
					if(count > black_create_5_from_3.updated_value)	black_create_5_from_3 = {count, i+k, j};
					black_create_5_from_3_count += 1;
				}
			}

			//block of 4
			if(i<16)
			{
				int w_count = 0, b_count = 0;
				for(int k=0;k<4;k++)	{if(b[i+k][j]!='.')	b[i+k][j]=='w'?w_count+=1:b_count+=1;}

				//create 4
				if(w_count == 3 && b_count == 0)	for(int k=0;k<4;k++)	if(b[i+k][j]=='.')	{
					int count=0;
					if(j-2>=0 && b[i+k][j-2]!='.') 					count+=((b[i+k][j-2]=='b'?2:1)*far);	
					if(i+k-2>=0 && b[i+k-2][j]!='.')				count+=((b[i+k-2][j]=='b'?2:1)*far);
					if(j-1>=0 && b[i+k][j-1]!='.')					count+=((b[i+k][j-1]=='b'?2:1)*close);	
					if(i+k-1>=0 && b[i+k-1][j]!='.')				count+=((b[i+k-1][j]=='b'?2:1)*close);
					if(j+2<19 && b[i+k][j+2]!='.')					count+=((b[i+k][j+2]=='b'?2:1)*far);	
					if(i+k+2<19 && b[i+k+2][j]!='.')				count+=((b[i+k+2][j]=='b'?2:1)*far);
					if(j+1<19 && b[i+k][j+1]!='.')					count+=((b[i+k][j+1]=='b'?2:1)*close);	
					if(i+k+1<19 && b[i+k+1][j]!='.')				count+=((b[i+k+1][j]=='b'?2:1)*close);
					if(j-2>=0 && i+k-2>=0 && b[i+k-2][j-2]!='.')	count+=((b[i+k-2][j-2]=='b'?2:1)*far);	
					if(j-1>=0 && i+k-1>=0 && b[i+k-1][j-1]!='.') 	count+=((b[i+k-1][j-1]=='b'?2:1)*close);
					if(j+2<19 && i+k+2<19 && b[i+k+2][j+2]!='.')	count+=((b[i+k+2][j+2]=='b'?2:1)*far);	
					if(j+1<19 && i+k+1<19 && b[i+k+1][j+1]!='.')	count+=((b[i+k+1][j+1]=='b'?2:1)*close);
					if(j-2>=0 && i+k+2<19 && b[i+k+2][j-2]!='.')	count+=((b[i+k+2][j-2]=='b'?2:1)*far);	
					if(j-1>=0 && i+k+1<19 && b[i+k+1][j-1]!='.')	count+=((b[i+k+1][j-1]=='b'?2:1)*close);
					if(j+2<19 && i+k-2>=0 && b[i+k-2][j+2]!='.')	count+=((b[i+k-2][j+2]=='b'?2:1)*far);	
					if(j+1<19 && i+k-1>=0 && b[i+k-1][j+1]!='.')	count+=((b[i+k-1][j+1]=='b'?2:1)*close);
					
					if(count > white_create_4.updated_value)	white_create_4 = {count, i+k, j};
					white_create_4_count += 1;
				}

				//prevent 4
				if(w_count == 0 && b_count == 3)	for(int k=0;k<4;k++)	if(b[i+k][j]=='.')	{
					int count=0;
					if(j-2>=0 && b[i+k][j-2]!='.') 					count+=((b[i+k][j-2]=='b'?2:1)*far);	
					if(i+k-2>=0 && b[i+k-2][j]!='.')				count+=((b[i+k-2][j]=='b'?2:1)*far);
					if(j-1>=0 && b[i+k][j-1]!='.')					count+=((b[i+k][j-1]=='b'?2:1)*close);	
					if(i+k-1>=0 && b[i+k-1][j]!='.')				count+=((b[i+k-1][j]=='b'?2:1)*close);
					if(j+2<19 && b[i+k][j+2]!='.')					count+=((b[i+k][j+2]=='b'?2:1)*far);	
					if(i+k+2<19 && b[i+k+2][j]!='.')				count+=((b[i+k+2][j]=='b'?2:1)*far);
					if(j+1<19 && b[i+k][j+1]!='.')					count+=((b[i+k][j+1]=='b'?2:1)*close);	
					if(i+k+1<19 && b[i+k+1][j]!='.')				count+=((b[i+k+1][j]=='b'?2:1)*close);
					if(j-2>=0 && i+k-2>=0 && b[i+k-2][j-2]!='.')	count+=((b[i+k-2][j-2]=='b'?2:1)*far);	
					if(j-1>=0 && i+k-1>=0 && b[i+k-1][j-1]!='.') 	count+=((b[i+k-1][j-1]=='b'?2:1)*close);
					if(j+2<19 && i+k+2<19 && b[i+k+2][j+2]!='.')	count+=((b[i+k+2][j+2]=='b'?2:1)*far);	
					if(j+1<19 && i+k+1<19 && b[i+k+1][j+1]!='.')	count+=((b[i+k+1][j+1]=='b'?2:1)*close);
					if(j-2>=0 && i+k+2<19 && b[i+k+2][j-2]!='.')	count+=((b[i+k+2][j-2]=='b'?2:1)*far);	
					if(j-1>=0 && i+k+1<19 && b[i+k+1][j-1]!='.')	count+=((b[i+k+1][j-1]=='b'?2:1)*close);
					if(j+2<19 && i+k-2>=0 && b[i+k-2][j+2]!='.')	count+=((b[i+k-2][j+2]=='b'?2:1)*far);	
					if(j+1<19 && i+k-1>=0 && b[i+k-1][j+1]!='.')	count+=((b[i+k-1][j+1]=='b'?2:1)*close);
					
					if(count > black_create_4.updated_value)	black_create_4 = {count, i+k, j};
					black_create_4_count += 1;
				}

				//white capture
				if(b[i][j+1]=='b' && b[i][j+2]=='b' && (b[i][j]=='w' && b[i][j+3]=='.') || (b[i][j]=='.' && b[i][j+3]=='w'))
				{
					int k = b[i][j]=='.'?j:j+3, count = 0;
					if(k-2>=0 && b[k-2][j]!='.') 				count+=((b[k-2][j]=='b'?2:1)*far);		
					if(j-2>=0 && b[k][j-2]!='.')				count+=((b[k][j-2]=='b'?2:1)*far);
					if(k-1>=0 && b[k-1][j]!='.')				count+=((b[k-1][j]=='b'?2:1)*close);	
					if(j-1>=0 && b[k][j-1]!='.')				count+=((b[k][j-1]=='b'?2:1)*close);
					if(k+2<19 && b[k+2][j]!='.')				count+=((b[k+2][j]=='b'?2:1)*far);		
					if(j+2<19 && b[k][j+2]!='.')				count+=((b[k][j+2]=='b'?2:1)*far);
					if(k+1<19 && b[k+1][j]!='.')				count+=((b[k+1][j]=='b'?2:1)*close);	
					if(j+1<19 && b[k][j+1]!='.')				count+=((b[k][j+1]=='b'?2:1)*close);
					if(k-2>=0 && j-2>=0 && b[k-2][j-2]!='.')	count+=((b[k-2][j-2]=='b'?2:1)*far);	
					if(k-1>=0 && j-1>=0 && b[k-1][j-1]!='.') 	count+=((b[k-1][j-1]=='b'?2:1)*close);
					if(k+2<19 && j+2<19 && b[k+2][j+2]!='.')	count+=((b[k+2][j+2]=='b'?2:1)*far);	
					if(k+1<19 && j+1<19 && b[k+1][j+1]!='.')	count+=((b[k+1][j+1]=='b'?2:1)*close);
					if(k-2>=0 && j+2<19 && b[k-2][j+2]!='.')	count+=((b[k-2][j+2]=='b'?2:1)*far);	
					if(k-1>=0 && j+1<19 && b[k-1][j+1]!='.')	count+=((b[k-1][j+1]=='b'?2:1)*close);
					if(k+2<19 && j-2>=0 && b[k+2][j-2]!='.')	count+=((b[k+2][j-2]=='b'?2:1)*far);	
					if(k+1<19 && j-1>=0 && b[k+1][j-1]!='.')	count+=((b[k+1][j-1]=='b'?2:1)*close);
					
					if(count > new_white_captures.updated_value)	new_white_captures = {count, k, j};
					new_white_captures_count += 1;
				}

				//black capture
				if(b[i][j+1]=='w' && b[i][j+2]=='w' && (b[i][j]=='b' && b[i][j+3]=='.') || (b[i][j]=='.' && b[i][j+3]=='b'))
				{
					int k = b[i][j]=='.'?j:j+3, count = 0;
					if(k-2>=0 && b[k-2][j]!='.') 				count+=((b[k-2][j]=='b'?2:1)*far);		
					if(j-2>=0 && b[k][j-2]!='.')				count+=((b[k][j-2]=='b'?2:1)*far);
					if(k-1>=0 && b[k-1][j]!='.')				count+=((b[k-1][j]=='b'?2:1)*close);	
					if(j-1>=0 && b[k][j-1]!='.')				count+=((b[k][j-1]=='b'?2:1)*close);
					if(k+2<19 && b[k+2][j]!='.')				count+=((b[k+2][j]=='b'?2:1)*far);		
					if(j+2<19 && b[k][j+2]!='.')				count+=((b[k][j+2]=='b'?2:1)*far);
					if(k+1<19 && b[k+1][j]!='.')				count+=((b[k+1][j]=='b'?2:1)*close);	
					if(j+1<19 && b[k][j+1]!='.')				count+=((b[k][j+1]=='b'?2:1)*close);
					if(k-2>=0 && j-2>=0 && b[k-2][j-2]!='.')	count+=((b[k-2][j-2]=='b'?2:1)*far);	
					if(k-1>=0 && j-1>=0 && b[k-1][j-1]!='.') 	count+=((b[k-1][j-1]=='b'?2:1)*close);
					if(k+2<19 && j+2<19 && b[k+2][j+2]!='.')	count+=((b[k+2][j+2]=='b'?2:1)*far);	
					if(k+1<19 && j+1<19 && b[k+1][j+1]!='.')	count+=((b[k+1][j+1]=='b'?2:1)*close);
					if(k-2>=0 && j+2<19 && b[k-2][j+2]!='.')	count+=((b[k-2][j+2]=='b'?2:1)*far);	
					if(k-1>=0 && j+1<19 && b[k-1][j+1]!='.')	count+=((b[k-1][j+1]=='b'?2:1)*close);
					if(k+2<19 && j-2>=0 && b[k+2][j-2]!='.')	count+=((b[k+2][j-2]=='b'?2:1)*far);	
					if(k+1<19 && j-1>=0 && b[k+1][j-1]!='.')	count+=((b[k+1][j-1]=='b'?2:1)*close);
					
					if(count > new_black_captures.updated_value)	new_black_captures = {count, k, j};
					new_black_captures_count += 1;
				}
			}

			//block of 3
			if(i<17)
			{
				int w_count = 0, b_count = 0;
				for(int k=0;k<3;k++)	{if(b[i+k][j]!='.')	b[i+k][j]=='w'?w_count+=1:b_count+=1;}

				//create 3
				if(w_count == 2 && b_count == 0)	for(int k=0;k<3;k++)	if(b[i+k][j]=='.')	{
					int count=0;
					if(j-2>=0 && b[i+k][j-2]!='.') 					count+=((b[i+k][j-2]=='b'?2:1)*far);	
					if(i+k-2>=0 && b[i+k-2][j]!='.')				count+=((b[i+k-2][j]=='b'?2:1)*far);
					if(j-1>=0 && b[i+k][j-1]!='.')					count+=((b[i+k][j-1]=='b'?2:1)*close);	
					if(i+k-1>=0 && b[i+k-1][j]!='.')				count+=((b[i+k-1][j]=='b'?2:1)*close);
					if(j+2<19 && b[i+k][j+2]!='.')					count+=((b[i+k][j+2]=='b'?2:1)*far);	
					if(i+k+2<19 && b[i+k+2][j]!='.')				count+=((b[i+k+2][j]=='b'?2:1)*far);
					if(j+1<19 && b[i+k][j+1]!='.')					count+=((b[i+k][j+1]=='b'?2:1)*close);	
					if(i+k+1<19 && b[i+k+1][j]!='.')				count+=((b[i+k+1][j]=='b'?2:1)*close);
					if(j-2>=0 && i+k-2>=0 && b[i+k-2][j-2]!='.')	count+=((b[i+k-2][j-2]=='b'?2:1)*far);	
					if(j-1>=0 && i+k-1>=0 && b[i+k-1][j-1]!='.') 	count+=((b[i+k-1][j-1]=='b'?2:1)*close);
					if(j+2<19 && i+k+2<19 && b[i+k+2][j+2]!='.')	count+=((b[i+k+2][j+2]=='b'?2:1)*far);	
					if(j+1<19 && i+k+1<19 && b[i+k+1][j+1]!='.')	count+=((b[i+k+1][j+1]=='b'?2:1)*close);
					if(j-2>=0 && i+k+2<19 && b[i+k+2][j-2]!='.')	count+=((b[i+k+2][j-2]=='b'?2:1)*far);	
					if(j-1>=0 && i+k+1<19 && b[i+k+1][j-1]!='.')	count+=((b[i+k+1][j-1]=='b'?2:1)*close);
					if(j+2<19 && i+k-2>=0 && b[i+k-2][j+2]!='.')	count+=((b[i+k-2][j+2]=='b'?2:1)*far);	
					if(j+1<19 && i+k-1>=0 && b[i+k-1][j+1]!='.')	count+=((b[i+k-1][j+1]=='b'?2:1)*close);
					
					if(count > white_create_3.updated_value)	white_create_3 = {count, i+k, j};
					white_create_3_count += 1;
				}

				//prevent 3
				if(w_count == 0 && b_count == 2)	for(int k=0;k<3;k++)	if(b[i+k][j]=='.')	{
					int count=0;
					if(j-2>=0 && b[i+k][j-2]!='.') 					count+=((b[i+k][j-2]=='b'?2:1)*far);	
					if(i+k-2>=0 && b[i+k-2][j]!='.')				count+=((b[i+k-2][j]=='b'?2:1)*far);
					if(j-1>=0 && b[i+k][j-1]!='.')					count+=((b[i+k][j-1]=='b'?2:1)*close);	
					if(i+k-1>=0 && b[i+k-1][j]!='.')				count+=((b[i+k-1][j]=='b'?2:1)*close);
					if(j+2<19 && b[i+k][j+2]!='.')					count+=((b[i+k][j+2]=='b'?2:1)*far);	
					if(i+k+2<19 && b[i+k+2][j]!='.')				count+=((b[i+k+2][j]=='b'?2:1)*far);
					if(j+1<19 && b[i+k][j+1]!='.')					count+=((b[i+k][j+1]=='b'?2:1)*close);	
					if(i+k+1<19 && b[i+k+1][j]!='.')				count+=((b[i+k+1][j]=='b'?2:1)*close);
					if(j-2>=0 && i+k-2>=0 && b[i+k-2][j-2]!='.')	count+=((b[i+k-2][j-2]=='b'?2:1)*far);	
					if(j-1>=0 && i+k-1>=0 && b[i+k-1][j-1]!='.') 	count+=((b[i+k-1][j-1]=='b'?2:1)*close);
					if(j+2<19 && i+k+2<19 && b[i+k+2][j+2]!='.')	count+=((b[i+k+2][j+2]=='b'?2:1)*far);	
					if(j+1<19 && i+k+1<19 && b[i+k+1][j+1]!='.')	count+=((b[i+k+1][j+1]=='b'?2:1)*close);
					if(j-2>=0 && i+k+2<19 && b[i+k+2][j-2]!='.')	count+=((b[i+k+2][j-2]=='b'?2:1)*far);	
					if(j-1>=0 && i+k+1<19 && b[i+k+1][j-1]!='.')	count+=((b[i+k+1][j-1]=='b'?2:1)*close);
					if(j+2<19 && i+k-2>=0 && b[i+k-2][j+2]!='.')	count+=((b[i+k-2][j+2]=='b'?2:1)*far);	
					if(j+1<19 && i+k-1>=0 && b[i+k-1][j+1]!='.')	count+=((b[i+k-1][j+1]=='b'?2:1)*close);
					
					if(count > black_create_3.updated_value)	black_create_3 = {count, i+k, j};
					black_create_3_count += 1;
				}
			}
		}	

	//diagonal
	for(int i=min_i;i<=max_i;i++)
		for(int j=min_j;j<=max_j;j++)
		{
			//block of 5
			if(i<15 && j<15)
			{
				int w_count = 0, b_count = 0;
				for(int k=0;k<5;k++)	{if(b[i+k][j+k]!='.')	b[i+k][j+k]=='w'?w_count+=1:b_count+=1;}

				//create 5
				if(w_count == 4 && b_count == 0)	for(int k=0;k<5;k++)	if(b[i+k][j+k]=='.')	
					{white_create_5 = {1000000000000000000, i+k, j+k};		white_create_5_count+=1;}
			
				//prevent 5
				if(w_count == 0 && b_count == 4)	for(int k=0;k<5;k++)	if(b[i+k][j+k]=='.')	
					{black_create_5 = {10000000000000000, i+k, j+k};	black_create_5_count+=1;}

				//create 5 from 3
				if(w_count == 3 && b_count == 0)	for(int k=0;k<5;k++)	if(b[i+k][j+k]=='.')	{
					int count=0;
					if(i+k-2>=0 && b[i+k-2][j+k]!='.') 				count+=((b[i+k-2][j+k]=='b'?2:1)*far);	
					if(j+k-2>=0 && b[i+k][j+k-2]!='.')				count+=((b[i+k][j+k-2]=='b'?2:1)*far);
					if(i+k-1>=0 && b[i+k-1][j+k]!='.')				count+=((b[i+k-1][j+k]=='b'?2:1)*close);	
					if(j+k-1>=0 && b[i+k][j+k-1]!='.')				count+=((b[i+k][j+k-1]=='b'?2:1)*close);
					if(i+k+2<19 && b[i+k+2][j+k]!='.')				count+=((b[i+k+2][j+k]=='b'?2:1)*far);	
					if(j+k+2<19 && b[i+k][j+k+2]!='.')				count+=((b[i+k][j+k+2]=='b'?2:1)*far);
					if(i+k+1<19 && b[i+k+1][j+k]!='.')				count+=((b[i+k+1][j+k]=='b'?2:1)*close);	
					if(j+k+1<19 && b[i+k][j+k+1]!='.')				count+=((b[i+k][j+k+1]=='b'?2:1)*close);
					if(i+k-2>=0 && j+k-2>=0 && b[i+k-2][j+k-2]!='.')	count+=((b[i+k-2][j+k-2]=='b'?2:1)*far);	
					if(i+k-1>=0 && j+k-1>=0 && b[i+k-1][j+k-1]!='.') 	count+=((b[i+k-1][j+k-1]=='b'?2:1)*close);
					if(i+k+2<19 && j+k+2<19 && b[i+k+2][j+k+2]!='.')	count+=((b[i+k+2][j+k+2]=='b'?2:1)*far);	
					if(i+k+1<19 && j+k+1<19 && b[i+k+1][j+k+1]!='.')	count+=((b[i+k+1][j+k+1]=='b'?2:1)*close);
					if(i+k-2>=0 && j+k+2<19 && b[i+k-2][j+k+2]!='.')	count+=((b[i+k-2][j+k+2]=='b'?2:1)*far);	
					if(i+k-1>=0 && j+k+1<19 && b[i+k-1][j+k+1]!='.')	count+=((b[i+k-1][j+k+1]=='b'?2:1)*close);
					if(i+k+2<19 && j+k-2>=0 && b[i+k+2][j+k-2]!='.')	count+=((b[i+k+2][j+k-2]=='b'?2:1)*far);	
					if(i+k+1<19 && j+k-1>=0 && b[i+k+1][j+k-1]!='.')	count+=((b[i+k+1][j+k-1]=='b'?2:1)*close);

					if(count > white_create_5_from_3.updated_value)	white_create_5_from_3 = {count, i+k, j+k};
					white_create_5_from_3_count += 1;
				}

				//prevent 5 from 3
				if(w_count == 0 && b_count == 3)	for(int k=0;k<5;k++)	if(b[i+k][j+k]=='.')	{
					int count=0;
					if(i+k-2>=0 && b[i+k-2][j+k]!='.') 				count+=((b[i+k-2][j+k]=='b'?2:1)*far);	
					if(j+k-2>=0 && b[i+k][j+k-2]!='.')				count+=((b[i+k][j+k-2]=='b'?2:1)*far);
					if(i+k-1>=0 && b[i+k-1][j+k]!='.')				count+=((b[i+k-1][j+k]=='b'?2:1)*close);	
					if(j+k-1>=0 && b[i+k][j+k-1]!='.')				count+=((b[i+k][j+k-1]=='b'?2:1)*close);
					if(i+k+2<19 && b[i+k+2][j+k]!='.')				count+=((b[i+k+2][j+k]=='b'?2:1)*far);	
					if(j+k+2<19 && b[i+k][j+k+2]!='.')				count+=((b[i+k][j+k+2]=='b'?2:1)*far);
					if(i+k+1<19 && b[i+k+1][j+k]!='.')				count+=((b[i+k+1][j+k]=='b'?2:1)*close);	
					if(j+k+1<19 && b[i+k][j+k+1]!='.')				count+=((b[i+k][j+k+1]=='b'?2:1)*close);
					if(i+k-2>=0 && j+k-2>=0 && b[i+k-2][j+k-2]!='.')	count+=((b[i+k-2][j+k-2]=='b'?2:1)*far);	
					if(i+k-1>=0 && j+k-1>=0 && b[i+k-1][j+k-1]!='.') 	count+=((b[i+k-1][j+k-1]=='b'?2:1)*close);
					if(i+k+2<19 && j+k+2<19 && b[i+k+2][j+k+2]!='.')	count+=((b[i+k+2][j+k+2]=='b'?2:1)*far);	
					if(i+k+1<19 && j+k+1<19 && b[i+k+1][j+k+1]!='.')	count+=((b[i+k+1][j+k+1]=='b'?2:1)*close);
					if(i+k-2>=0 && j+k+2<19 && b[i+k-2][j+k+2]!='.')	count+=((b[i+k-2][j+k+2]=='b'?2:1)*far);	
					if(i+k-1>=0 && j+k+1<19 && b[i+k-1][j+k+1]!='.')	count+=((b[i+k-1][j+k+1]=='b'?2:1)*close);
					if(i+k+2<19 && j+k-2>=0 && b[i+k+2][j+k-2]!='.')	count+=((b[i+k+2][j+k-2]=='b'?2:1)*far);	
					if(i+k+1<19 && j+k-1>=0 && b[i+k+1][j+k-1]!='.')	count+=((b[i+k+1][j+k-1]=='b'?2:1)*close);
					
					if(count > black_create_5_from_3.updated_value)	black_create_5_from_3 = {count, i+k, j+k};
					black_create_5_from_3_count += 1;
				}
			}

			//block of 4
			if(i<16 && j<16)
			{
				int w_count = 0, b_count = 0;
				for(int k=0;k<4;k++)	{if(b[i+k][j+k]!='.')	b[i+k][j+k]=='w'?w_count+=1:b_count+=1;}

				//create 4
				if(w_count == 3 && b_count == 0)	for(int k=0;k<4;k++)	if(b[i+k][j+k]=='.')	{
					int count=0;
					if(i+k-2>=0 && b[i+k-2][j+k]!='.') 				count+=((b[i+k-2][j+k]=='b'?2:1)*far);	
					if(j+k-2>=0 && b[i+k][j+k-2]!='.')				count+=((b[i+k][j+k-2]=='b'?2:1)*far);
					if(i+k-1>=0 && b[i+k-1][j+k]!='.')				count+=((b[i+k-1][j+k]=='b'?2:1)*close);	
					if(j+k-1>=0 && b[i+k][j+k-1]!='.')				count+=((b[i+k][j+k-1]=='b'?2:1)*close);
					if(i+k+2<19 && b[i+k+2][j+k]!='.')				count+=((b[i+k+2][j+k]=='b'?2:1)*far);	
					if(j+k+2<19 && b[i+k][j+k+2]!='.')				count+=((b[i+k][j+k+2]=='b'?2:1)*far);
					if(i+k+1<19 && b[i+k+1][j+k]!='.')				count+=((b[i+k+1][j+k]=='b'?2:1)*close);	
					if(j+k+1<19 && b[i+k][j+k+1]!='.')				count+=((b[i+k][j+k+1]=='b'?2:1)*close);
					if(i+k-2>=0 && j+k-2>=0 && b[i+k-2][j+k-2]!='.')	count+=((b[i+k-2][j+k-2]=='b'?2:1)*far);	
					if(i+k-1>=0 && j+k-1>=0 && b[i+k-1][j+k-1]!='.') 	count+=((b[i+k-1][j+k-1]=='b'?2:1)*close);
					if(i+k+2<19 && j+k+2<19 && b[i+k+2][j+k+2]!='.')	count+=((b[i+k+2][j+k+2]=='b'?2:1)*far);	
					if(i+k+1<19 && j+k+1<19 && b[i+k+1][j+k+1]!='.')	count+=((b[i+k+1][j+k+1]=='b'?2:1)*close);
					if(i+k-2>=0 && j+k+2<19 && b[i+k-2][j+k+2]!='.')	count+=((b[i+k-2][j+k+2]=='b'?2:1)*far);	
					if(i+k-1>=0 && j+k+1<19 && b[i+k-1][j+k+1]!='.')	count+=((b[i+k-1][j+k+1]=='b'?2:1)*close);
					if(i+k+2<19 && j+k-2>=0 && b[i+k+2][j+k-2]!='.')	count+=((b[i+k+2][j+k-2]=='b'?2:1)*far);	
					if(i+k+1<19 && j+k-1>=0 && b[i+k+1][j+k-1]!='.')	count+=((b[i+k+1][j+k-1]=='b'?2:1)*close);
					
					if(count > white_create_4.updated_value)	white_create_4 = {count, i+k, j+k};
					white_create_4_count += 1;
				}

				//prevent 4
				if(w_count == 0 && b_count == 3)	for(int k=0;k<4;k++)	if(b[i+k][j+k]=='.')	{
					int count=0;
					if(i+k-2>=0 && b[i+k-2][j+k]!='.') 				count+=((b[i+k-2][j+k]=='b'?2:1)*far);	
					if(j+k-2>=0 && b[i+k][j+k-2]!='.')				count+=((b[i+k][j+k-2]=='b'?2:1)*far);
					if(i+k-1>=0 && b[i+k-1][j+k]!='.')				count+=((b[i+k-1][j+k]=='b'?2:1)*close);	
					if(j+k-1>=0 && b[i+k][j+k-1]!='.')				count+=((b[i+k][j+k-1]=='b'?2:1)*close);
					if(i+k+2<19 && b[i+k+2][j+k]!='.')				count+=((b[i+k+2][j+k]=='b'?2:1)*far);	
					if(j+k+2<19 && b[i+k][j+k+2]!='.')				count+=((b[i+k][j+k+2]=='b'?2:1)*far);
					if(i+k+1<19 && b[i+k+1][j+k]!='.')				count+=((b[i+k+1][j+k]=='b'?2:1)*close);	
					if(j+k+1<19 && b[i+k][j+k+1]!='.')				count+=((b[i+k][j+k+1]=='b'?2:1)*close);
					if(i+k-2>=0 && j+k-2>=0 && b[i+k-2][j+k-2]!='.')	count+=((b[i+k-2][j+k-2]=='b'?2:1)*far);	
					if(i+k-1>=0 && j+k-1>=0 && b[i+k-1][j+k-1]!='.') 	count+=((b[i+k-1][j+k-1]=='b'?2:1)*close);
					if(i+k+2<19 && j+k+2<19 && b[i+k+2][j+k+2]!='.')	count+=((b[i+k+2][j+k+2]=='b'?2:1)*far);	
					if(i+k+1<19 && j+k+1<19 && b[i+k+1][j+k+1]!='.')	count+=((b[i+k+1][j+k+1]=='b'?2:1)*close);
					if(i+k-2>=0 && j+k+2<19 && b[i+k-2][j+k+2]!='.')	count+=((b[i+k-2][j+k+2]=='b'?2:1)*far);	
					if(i+k-1>=0 && j+k+1<19 && b[i+k-1][j+k+1]!='.')	count+=((b[i+k-1][j+k+1]=='b'?2:1)*close);
					if(i+k+2<19 && j+k-2>=0 && b[i+k+2][j+k-2]!='.')	count+=((b[i+k+2][j+k-2]=='b'?2:1)*far);	
					if(i+k+1<19 && j+k-1>=0 && b[i+k+1][j+k-1]!='.')	count+=((b[i+k+1][j+k-1]=='b'?2:1)*close);
					
					if(count > black_create_4.updated_value)	black_create_4 = {count, i+k, j+k};
					black_create_4_count += 1;
				}

				//white capture
				if(b[i+1][j+1]=='b' && b[i+2][j+2]=='b' && (b[i][j]=='w' && b[i+3][j+3]=='.') || (b[i][j]=='.' && b[i+3][j+3]=='w'))
				{
					int k = (b[i][j]=='.'?j:j+3), l = (b[i][j]=='.'?i:i+3), count = 0;
					if(l-2>=0 && b[l-2][k]!='.') 				count+=((b[l-2][k]=='b'?2:1)*far);		
					if(k-2>=0 && b[l][k-2]!='.')				count+=((b[l][k-2]=='b'?2:1)*far);
					if(l-1>=0 && b[l-1][k]!='.')				count+=((b[l-1][k]=='b'?2:1)*close);	
					if(k-1>=0 && b[l][k-1]!='.')				count+=((b[l][k-1]=='b'?2:1)*close);
					if(l+2<19 && b[l+2][k]!='.')				count+=((b[l+2][k]=='b'?2:1)*far);		
					if(k+2<19 && b[l][k+2]!='.')				count+=((b[l][k+2]=='b'?2:1)*far);
					if(l+1<19 && b[l+1][k]!='.')				count+=((b[l+1][k]=='b'?2:1)*close);	
					if(k+1<19 && b[l][k+1]!='.')				count+=((b[l][k+1]=='b'?2:1)*close);
					if(l-2>=0 && k-2>=0 && b[l-2][k-2]!='.')	count+=((b[l-2][k-2]=='b'?2:1)*far);	
					if(l-1>=0 && k-1>=0 && b[l-1][k-1]!='.') 	count+=((b[l-1][k-1]=='b'?2:1)*close);
					if(l+2<19 && k+2<19 && b[l+2][k+2]!='.')	count+=((b[l+2][k+2]=='b'?2:1)*far);	
					if(l+1<19 && k+1<19 && b[l+1][k+1]!='.')	count+=((b[l+1][k+1]=='b'?2:1)*close);
					if(l-2>=0 && k+2<19 && b[l-2][k+2]!='.')	count+=((b[l-2][k+2]=='b'?2:1)*far);	
					if(l-1>=0 && k+1<19 && b[l-1][k+1]!='.')	count+=((b[l-1][k+1]=='b'?2:1)*close);
					if(l+2<19 && k-2>=0 && b[l+2][k-2]!='.')	count+=((b[l+2][k-2]=='b'?2:1)*far);	
					if(l+1<19 && k-1>=0 && b[l+1][k-1]!='.')	count+=((b[l+1][k-1]=='b'?2:1)*close);
					
					if(count > new_white_captures.updated_value)	new_white_captures = {count, l, k};
					new_white_captures_count += 1;
				}

				//black capture
				if(b[i+1][j+1]=='w' && b[i+2][j+2]=='w' && (b[i][j]=='b' && b[i+3][j+3]=='.') || (b[i][j]=='.' && b[i+3][j+3]=='b'))
				{
					int k = (b[i][j]=='.'?j:j+3), l = (b[i][j]=='.'?i:i+3), count = 0;
					if(l-2>=0 && b[l-2][k]!='.') 				count+=((b[l-2][k]=='b'?2:1)*far);		
					if(k-2>=0 && b[l][k-2]!='.')				count+=((b[l][k-2]=='b'?2:1)*far);
					if(l-1>=0 && b[l-1][k]!='.')				count+=((b[l-1][k]=='b'?2:1)*close);	
					if(k-1>=0 && b[l][k-1]!='.')				count+=((b[l][k-1]=='b'?2:1)*close);
					if(l+2<19 && b[l+2][k]!='.')				count+=((b[l+2][k]=='b'?2:1)*far);		
					if(k+2<19 && b[l][k+2]!='.')				count+=((b[l][k+2]=='b'?2:1)*far);
					if(l+1<19 && b[l+1][k]!='.')				count+=((b[l+1][k]=='b'?2:1)*close);	
					if(k+1<19 && b[l][k+1]!='.')				count+=((b[l][k+1]=='b'?2:1)*close);
					if(l-2>=0 && k-2>=0 && b[l-2][k-2]!='.')	count+=((b[l-2][k-2]=='b'?2:1)*far);	
					if(l-1>=0 && k-1>=0 && b[l-1][k-1]!='.') 	count+=((b[l-1][k-1]=='b'?2:1)*close);
					if(l+2<19 && k+2<19 && b[l+2][k+2]!='.')	count+=((b[l+2][k+2]=='b'?2:1)*far);	
					if(l+1<19 && k+1<19 && b[l+1][k+1]!='.')	count+=((b[l+1][k+1]=='b'?2:1)*close);
					if(l-2>=0 && k+2<19 && b[l-2][k+2]!='.')	count+=((b[l-2][k+2]=='b'?2:1)*far);	
					if(l-1>=0 && k+1<19 && b[l-1][k+1]!='.')	count+=((b[l-1][k+1]=='b'?2:1)*close);
					if(l+2<19 && k-2>=0 && b[l+2][k-2]!='.')	count+=((b[l+2][k-2]=='b'?2:1)*far);	
					if(l+1<19 && k-1>=0 && b[l+1][k-1]!='.')	count+=((b[l+1][k-1]=='b'?2:1)*close);
					
					if(count > new_black_captures.updated_value)	new_black_captures = {count, l, k};
					new_black_captures_count += 1;
				}
			}

			//block of 3
			if(i<17 && j<17)
			{
				int w_count = 0, b_count = 0;
				for(int k=0;k<3;k++)	{if(b[i+k][j+k]!='.')	b[i+k][j+k]=='w'?w_count+=1:b_count+=1;}

				//create 3
				if(w_count == 2 && b_count == 0)	for(int k=0;k<3;k++)	if(b[i+k][j+k]=='.')	{
					int count=0;
					if(i+k-2>=0 && b[i+k-2][j+k]!='.') 				count+=((b[i+k-2][j+k]=='b'?2:1)*far);	
					if(j+k-2>=0 && b[i+k][j+k-2]!='.')				count+=((b[i+k][j+k-2]=='b'?2:1)*far);
					if(i+k-1>=0 && b[i+k-1][j+k]!='.')				count+=((b[i+k-1][j+k]=='b'?2:1)*close);	
					if(j+k-1>=0 && b[i+k][j+k-1]!='.')				count+=((b[i+k][j+k-1]=='b'?2:1)*close);
					if(i+k+2<19 && b[i+k+2][j+k]!='.')				count+=((b[i+k+2][j+k]=='b'?2:1)*far);	
					if(j+k+2<19 && b[i+k][j+k+2]!='.')				count+=((b[i+k][j+k+2]=='b'?2:1)*far);
					if(i+k+1<19 && b[i+k+1][j+k]!='.')				count+=((b[i+k+1][j+k]=='b'?2:1)*close);	
					if(j+k+1<19 && b[i+k][j+k+1]!='.')				count+=((b[i+k][j+k+1]=='b'?2:1)*close);
					if(i+k-2>=0 && j+k-2>=0 && b[i+k-2][j+k-2]!='.')	count+=((b[i+k-2][j+k-2]=='b'?2:1)*far);	
					if(i+k-1>=0 && j+k-1>=0 && b[i+k-1][j+k-1]!='.') 	count+=((b[i+k-1][j+k-1]=='b'?2:1)*close);
					if(i+k+2<19 && j+k+2<19 && b[i+k+2][j+k+2]!='.')	count+=((b[i+k+2][j+k+2]=='b'?2:1)*far);	
					if(i+k+1<19 && j+k+1<19 && b[i+k+1][j+k+1]!='.')	count+=((b[i+k+1][j+k+1]=='b'?2:1)*close);
					if(i+k-2>=0 && j+k+2<19 && b[i+k-2][j+k+2]!='.')	count+=((b[i+k-2][j+k+2]=='b'?2:1)*far);	
					if(i+k-1>=0 && j+k+1<19 && b[i+k-1][j+k+1]!='.')	count+=((b[i+k-1][j+k+1]=='b'?2:1)*close);
					if(i+k+2<19 && j+k-2>=0 && b[i+k+2][j+k-2]!='.')	count+=((b[i+k+2][j+k-2]=='b'?2:1)*far);	
					if(i+k+1<19 && j+k-1>=0 && b[i+k+1][j+k-1]!='.')	count+=((b[i+k+1][j+k-1]=='b'?2:1)*close);
					
					if(count > white_create_3.updated_value)	white_create_3 = {count, i+k, j+k};
					white_create_3_count += 1;
				}

				//prevent 3
				if(w_count == 0 && b_count == 2)	for(int k=0;k<3;k++)	if(b[i+k][j+k]=='.')	{
					int count=0;
					if(i+k-2>=0 && b[i+k-2][j+k]!='.') 				count+=((b[i+k-2][j+k]=='b'?2:1)*far);	
					if(j+k-2>=0 && b[i+k][j+k-2]!='.')				count+=((b[i+k][j+k-2]=='b'?2:1)*far);
					if(i+k-1>=0 && b[i+k-1][j+k]!='.')				count+=((b[i+k-1][j+k]=='b'?2:1)*close);	
					if(j+k-1>=0 && b[i+k][j+k-1]!='.')				count+=((b[i+k][j+k-1]=='b'?2:1)*close);
					if(i+k+2<19 && b[i+k+2][j+k]!='.')				count+=((b[i+k+2][j+k]=='b'?2:1)*far);	
					if(j+k+2<19 && b[i+k][j+k+2]!='.')				count+=((b[i+k][j+k+2]=='b'?2:1)*far);
					if(i+k+1<19 && b[i+k+1][j+k]!='.')				count+=((b[i+k+1][j+k]=='b'?2:1)*close);	
					if(j+k+1<19 && b[i+k][j+k+1]!='.')				count+=((b[i+k][j+k+1]=='b'?2:1)*close);
					if(i+k-2>=0 && j+k-2>=0 && b[i+k-2][j+k-2]!='.')	count+=((b[i+k-2][j+k-2]=='b'?2:1)*far);	
					if(i+k-1>=0 && j+k-1>=0 && b[i+k-1][j+k-1]!='.') 	count+=((b[i+k-1][j+k-1]=='b'?2:1)*close);
					if(i+k+2<19 && j+k+2<19 && b[i+k+2][j+k+2]!='.')	count+=((b[i+k+2][j+k+2]=='b'?2:1)*far);	
					if(i+k+1<19 && j+k+1<19 && b[i+k+1][j+k+1]!='.')	count+=((b[i+k+1][j+k+1]=='b'?2:1)*close);
					if(i+k-2>=0 && j+k+2<19 && b[i+k-2][j+k+2]!='.')	count+=((b[i+k-2][j+k+2]=='b'?2:1)*far);	
					if(i+k-1>=0 && j+k+1<19 && b[i+k-1][j+k+1]!='.')	count+=((b[i+k-1][j+k+1]=='b'?2:1)*close);
					if(i+k+2<19 && j+k-2>=0 && b[i+k+2][j+k-2]!='.')	count+=((b[i+k+2][j+k-2]=='b'?2:1)*far);	
					if(i+k+1<19 && j+k-1>=0 && b[i+k+1][j+k-1]!='.')	count+=((b[i+k+1][j+k-1]=='b'?2:1)*close);
					
					if(count > black_create_3.updated_value)	black_create_3 = {count, i+k, j+k};
					black_create_3_count += 1;
				}
			}
		}
	
	//anti-diagonal
	for(int i=min_i;i<=max_i;i++)
		for(int j=min_j;j<=max_j;j++)
		{
			//block of 5
			if(i>3 && j<15)
			{
				int w_count = 0, b_count = 0;
				for(int k=0;k<5;k++)	{if(b[i-k][j+k]!='.')	b[i-k][j+k]=='w'?w_count+=1:b_count+=1;}

				//create 5
				if(w_count == 4 && b_count == 0)	for(int k=0;k<5;k++)	if(b[i-k][j+k]=='.')	
					{white_create_5 = {1000000000000000000, i-k, j+k};		white_create_5_count+=1;}

			
				//prevent 5
				if(w_count == 0 && b_count == 4)	for(int k=0;k<5;k++)	if(b[i-k][j+k]=='.')	
					{black_create_5 = {10000000000000000, i-k, j+k};	black_create_5_count+=1;}

				//create 5 from 3
				if(w_count == 3 && b_count == 0)	for(int k=0;k<5;k++)	if(b[i-k][j+k]=='.')	{
					int count=0;
					if(i-k-2>=0 && b[i-k-2][j+k]!='.') 				count+=((b[i-k-2][j+k]=='b'?2:1)*far);	
					if(j+k-2>=0 && b[i-k][j+k-2]!='.')				count+=((b[i-k][j+k-2]=='b'?2:1)*far);
					if(i-k-1>=0 && b[i-k-1][j+k]!='.')				count+=((b[i-k-1][j+k]=='b'?2:1)*close);	
					if(j+k-1>=0 && b[i-k][j+k-1]!='.')				count+=((b[i-k][j+k-1]=='b'?2:1)*close);
					if(i-k+2<19 && b[i-k+2][j+k]!='.')				count+=((b[i-k+2][j+k]=='b'?2:1)*far);	
					if(j+k+2<19 && b[i-k][j+k+2]!='.')				count+=((b[i-k][j+k+2]=='b'?2:1)*far);
					if(i-k+1<19 && b[i-k+1][j+k]!='.')				count+=((b[i-k+1][j+k]=='b'?2:1)*close);	
					if(j+k+1<19 && b[i-k][j+k+1]!='.')				count+=((b[i-k][j+k+1]=='b'?2:1)*close);
					if(i-k-2>=0 && j+k-2>=0 && b[i-k-2][j+k-2]!='.')	count+=((b[i-k-2][j+k-2]=='b'?2:1)*far);	
					if(i-k-1>=0 && j+k-1>=0 && b[i-k-1][j+k-1]!='.') 	count+=((b[i-k-1][j+k-1]=='b'?2:1)*close);
					if(i-k+2<19 && j+k+2<19 && b[i-k+2][j+k+2]!='.')	count+=((b[i-k+2][j+k+2]=='b'?2:1)*far);	
					if(i-k+1<19 && j+k+1<19 && b[i-k+1][j+k+1]!='.')	count+=((b[i-k+1][j+k+1]=='b'?2:1)*close);
					if(i-k-2>=0 && j+k+2<19 && b[i-k-2][j+k+2]!='.')	count+=((b[i-k-2][j+k+2]=='b'?2:1)*far);	
					if(i-k-1>=0 && j+k+1<19 && b[i-k-1][j+k+1]!='.')	count+=((b[i-k-1][j+k+1]=='b'?2:1)*close);
					if(i-k+2<19 && j+k-2>=0 && b[i-k+2][j+k-2]!='.')	count+=((b[i-k+2][j+k-2]=='b'?2:1)*far);	
					if(i-k+1<19 && j+k-1>=0 && b[i-k+1][j+k-1]!='.')	count+=((b[i-k+1][j+k-1]=='b'?2:1)*close);

					if(count > white_create_5_from_3.updated_value)	white_create_5_from_3 = {count, i-k, j+k};
					white_create_5_from_3_count += 1;
				}

				//prevent 5 from 3
				if(w_count == 0 && b_count == 3)	for(int k=0;k<5;k++)	if(b[i-k][j+k]=='.')	{
					int count=0;
					if(i-k-2>=0 && b[i-k-2][j+k]!='.') 				count+=((b[i-k-2][j+k]=='b'?2:1)*far);	
					if(j+k-2>=0 && b[i-k][j+k-2]!='.')				count+=((b[i-k][j+k-2]=='b'?2:1)*far);
					if(i-k-1>=0 && b[i-k-1][j+k]!='.')				count+=((b[i-k-1][j+k]=='b'?2:1)*close);	
					if(j+k-1>=0 && b[i-k][j+k-1]!='.')				count+=((b[i-k][j+k-1]=='b'?2:1)*close);
					if(i-k+2<19 && b[i-k+2][j+k]!='.')				count+=((b[i-k+2][j+k]=='b'?2:1)*far);	
					if(j+k+2<19 && b[i-k][j+k+2]!='.')				count+=((b[i-k][j+k+2]=='b'?2:1)*far);
					if(i-k+1<19 && b[i-k+1][j+k]!='.')				count+=((b[i-k+1][j+k]=='b'?2:1)*close);	
					if(j+k+1<19 && b[i-k][j+k+1]!='.')				count+=((b[i-k][j+k+1]=='b'?2:1)*close);
					if(i-k-2>=0 && j+k-2>=0 && b[i-k-2][j+k-2]!='.')	count+=((b[i-k-2][j+k-2]=='b'?2:1)*far);	
					if(i-k-1>=0 && j+k-1>=0 && b[i-k-1][j+k-1]!='.') 	count+=((b[i-k-1][j+k-1]=='b'?2:1)*close);
					if(i-k+2<19 && j+k+2<19 && b[i-k+2][j+k+2]!='.')	count+=((b[i-k+2][j+k+2]=='b'?2:1)*far);	
					if(i-k+1<19 && j+k+1<19 && b[i-k+1][j+k+1]!='.')	count+=((b[i-k+1][j+k+1]=='b'?2:1)*close);
					if(i-k-2>=0 && j+k+2<19 && b[i-k-2][j+k+2]!='.')	count+=((b[i-k-2][j+k+2]=='b'?2:1)*far);	
					if(i-k-1>=0 && j+k+1<19 && b[i-k-1][j+k+1]!='.')	count+=((b[i-k-1][j+k+1]=='b'?2:1)*close);
					if(i-k+2<19 && j+k-2>=0 && b[i-k+2][j+k-2]!='.')	count+=((b[i-k+2][j+k-2]=='b'?2:1)*far);	
					if(i-k+1<19 && j+k-1>=0 && b[i-k+1][j+k-1]!='.')	count+=((b[i-k+1][j+k-1]=='b'?2:1)*close);
					
					if(count > black_create_5_from_3.updated_value)	black_create_5_from_3 = {count, i-k, j+k};
					black_create_5_from_3_count += 1;
				}
			}

			//block of 4
			if(i>2 && j<16)
			{
				int w_count = 0, b_count = 0;
				for(int k=0;k<4;k++)	{if(b[i-k][j+k]!='.')	b[i-k][j+k]=='w'?w_count+=1:b_count+=1;}

				//create 4
				if(w_count == 3 && b_count == 0)	for(int k=0;k<4;k++)	if(b[i-k][j+k]=='.')	{
					int count=0;
					if(i-k-2>=0 && b[i-k-2][j+k]!='.') 				count+=((b[i-k-2][j+k]=='b'?2:1)*far);	
					if(j+k-2>=0 && b[i-k][j+k-2]!='.')				count+=((b[i-k][j+k-2]=='b'?2:1)*far);
					if(i-k-1>=0 && b[i-k-1][j+k]!='.')				count+=((b[i-k-1][j+k]=='b'?2:1)*close);	
					if(j+k-1>=0 && b[i-k][j+k-1]!='.')				count+=((b[i-k][j+k-1]=='b'?2:1)*close);
					if(i-k+2<19 && b[i-k+2][j+k]!='.')				count+=((b[i-k+2][j+k]=='b'?2:1)*far);	
					if(j+k+2<19 && b[i-k][j+k+2]!='.')				count+=((b[i-k][j+k+2]=='b'?2:1)*far);
					if(i-k+1<19 && b[i-k+1][j+k]!='.')				count+=((b[i-k+1][j+k]=='b'?2:1)*close);	
					if(j+k+1<19 && b[i-k][j+k+1]!='.')				count+=((b[i-k][j+k+1]=='b'?2:1)*close);
					if(i-k-2>=0 && j+k-2>=0 && b[i-k-2][j+k-2]!='.')	count+=((b[i-k-2][j+k-2]=='b'?2:1)*far);	
					if(i-k-1>=0 && j+k-1>=0 && b[i-k-1][j+k-1]!='.') 	count+=((b[i-k-1][j+k-1]=='b'?2:1)*close);
					if(i-k+2<19 && j+k+2<19 && b[i-k+2][j+k+2]!='.')	count+=((b[i-k+2][j+k+2]=='b'?2:1)*far);	
					if(i-k+1<19 && j+k+1<19 && b[i-k+1][j+k+1]!='.')	count+=((b[i-k+1][j+k+1]=='b'?2:1)*close);
					if(i-k-2>=0 && j+k+2<19 && b[i-k-2][j+k+2]!='.')	count+=((b[i-k-2][j+k+2]=='b'?2:1)*far);	
					if(i-k-1>=0 && j+k+1<19 && b[i-k-1][j+k+1]!='.')	count+=((b[i-k-1][j+k+1]=='b'?2:1)*close);
					if(i-k+2<19 && j+k-2>=0 && b[i-k+2][j+k-2]!='.')	count+=((b[i-k+2][j+k-2]=='b'?2:1)*far);	
					if(i-k+1<19 && j+k-1>=0 && b[i-k+1][j+k-1]!='.')	count+=((b[i-k+1][j+k-1]=='b'?2:1)*close);
					
					if(count > white_create_4.updated_value)	white_create_4 = {count, i-k, j+k};
					white_create_4_count += 1;
				}

				//prevent 4
				if(w_count == 0 && b_count == 3)	for(int k=0;k<4;k++)	if(b[i-k][j+k]=='.')	{
					int count=0;
					if(i-k-2>=0 && b[i-k-2][j+k]!='.') 				count+=((b[i-k-2][j+k]=='b'?2:1)*far);	
					if(j+k-2>=0 && b[i-k][j+k-2]!='.')				count+=((b[i-k][j+k-2]=='b'?2:1)*far);
					if(i-k-1>=0 && b[i-k-1][j+k]!='.')				count+=((b[i-k-1][j+k]=='b'?2:1)*close);	
					if(j+k-1>=0 && b[i-k][j+k-1]!='.')				count+=((b[i-k][j+k-1]=='b'?2:1)*close);
					if(i-k+2<19 && b[i-k+2][j+k]!='.')				count+=((b[i-k+2][j+k]=='b'?2:1)*far);	
					if(j+k+2<19 && b[i-k][j+k+2]!='.')				count+=((b[i-k][j+k+2]=='b'?2:1)*far);
					if(i-k+1<19 && b[i-k+1][j+k]!='.')				count+=((b[i-k+1][j+k]=='b'?2:1)*close);	
					if(j+k+1<19 && b[i-k][j+k+1]!='.')				count+=((b[i-k][j+k+1]=='b'?2:1)*close);
					if(i-k-2>=0 && j+k-2>=0 && b[i-k-2][j+k-2]!='.')	count+=((b[i-k-2][j+k-2]=='b'?2:1)*far);	
					if(i-k-1>=0 && j+k-1>=0 && b[i-k-1][j+k-1]!='.') 	count+=((b[i-k-1][j+k-1]=='b'?2:1)*close);
					if(i-k+2<19 && j+k+2<19 && b[i-k+2][j+k+2]!='.')	count+=((b[i-k+2][j+k+2]=='b'?2:1)*far);	
					if(i-k+1<19 && j+k+1<19 && b[i-k+1][j+k+1]!='.')	count+=((b[i-k+1][j+k+1]=='b'?2:1)*close);
					if(i-k-2>=0 && j+k+2<19 && b[i-k-2][j+k+2]!='.')	count+=((b[i-k-2][j+k+2]=='b'?2:1)*far);	
					if(i-k-1>=0 && j+k+1<19 && b[i-k-1][j+k+1]!='.')	count+=((b[i-k-1][j+k+1]=='b'?2:1)*close);
					if(i-k+2<19 && j+k-2>=0 && b[i-k+2][j+k-2]!='.')	count+=((b[i-k+2][j+k-2]=='b'?2:1)*far);	
					if(i-k+1<19 && j+k-1>=0 && b[i-k+1][j+k-1]!='.')	count+=((b[i-k+1][j+k-1]=='b'?2:1)*close);
					
					if(count > black_create_4.updated_value)	black_create_4 = {count, i-k, j+k};
					black_create_4_count += 1;
				}

				//white capture
				if(b[i-1][j+1]=='b' && b[i-2][j+2]=='b' && (b[i][j]=='w' && b[i-3][j+3]=='.') || (b[i][j]=='.' && b[i-3][j+3]=='w'))
				{
					int k = (b[i][j]=='.'?j:j+3), l = (b[i][j]=='.'?i:i-3), count = 0;
					if(l-2>=0 && b[l-2][k]!='.') 				count+=((b[l-2][k]=='b'?2:1)*far);		
					if(k-2>=0 && b[l][k-2]!='.')				count+=((b[l][k-2]=='b'?2:1)*far);
					if(l-1>=0 && b[l-1][k]!='.')				count+=((b[l-1][k]=='b'?2:1)*close);	
					if(k-1>=0 && b[l][k-1]!='.')				count+=((b[l][k-1]=='b'?2:1)*close);
					if(l+2<19 && b[l+2][k]!='.')				count+=((b[l+2][k]=='b'?2:1)*far);		
					if(k+2<19 && b[l][k+2]!='.')				count+=((b[l][k+2]=='b'?2:1)*far);
					if(l+1<19 && b[l+1][k]!='.')				count+=((b[l+1][k]=='b'?2:1)*close);	
					if(k+1<19 && b[l][k+1]!='.')				count+=((b[l][k+1]=='b'?2:1)*close);
					if(l-2>=0 && k-2>=0 && b[l-2][k-2]!='.')	count+=((b[l-2][k-2]=='b'?2:1)*far);	
					if(l-1>=0 && k-1>=0 && b[l-1][k-1]!='.') 	count+=((b[l-1][k-1]=='b'?2:1)*close);
					if(l+2<19 && k+2<19 && b[l+2][k+2]!='.')	count+=((b[l+2][k+2]=='b'?2:1)*far);	
					if(l+1<19 && k+1<19 && b[l+1][k+1]!='.')	count+=((b[l+1][k+1]=='b'?2:1)*close);
					if(l-2>=0 && k+2<19 && b[l-2][k+2]!='.')	count+=((b[l-2][k+2]=='b'?2:1)*far);	
					if(l-1>=0 && k+1<19 && b[l-1][k+1]!='.')	count+=((b[l-1][k+1]=='b'?2:1)*close);
					if(l+2<19 && k-2>=0 && b[l+2][k-2]!='.')	count+=((b[l+2][k-2]=='b'?2:1)*far);	
					if(l+1<19 && k-1>=0 && b[l+1][k-1]!='.')	count+=((b[l+1][k-1]=='b'?2:1)*close);
					
					if(count > new_white_captures.updated_value)	new_white_captures = {count, l, k};
					new_white_captures_count += 1;
				}

				//black capture
				if(b[i-1][j+1]=='w' && b[i-2][j+2]=='w' && (b[i][j]=='b' && b[i-3][j+3]=='.') || (b[i][j]=='.' && b[i-3][j+3]=='b'))
				{
					int k = (b[i][j]=='.'?j:j+3), l = (b[i][j]=='.'?i:i-3), count = 0;
					if(l-2>=0 && b[l-2][k]!='.') 				count+=((b[l-2][k]=='b'?2:1)*far);		
					if(k-2>=0 && b[l][k-2]!='.')				count+=((b[l][k-2]=='b'?2:1)*far);
					if(l-1>=0 && b[l-1][k]!='.')				count+=((b[l-1][k]=='b'?2:1)*close);	
					if(k-1>=0 && b[l][k-1]!='.')				count+=((b[l][k-1]=='b'?2:1)*close);
					if(l+2<19 && b[l+2][k]!='.')				count+=((b[l+2][k]=='b'?2:1)*far);		
					if(k+2<19 && b[l][k+2]!='.')				count+=((b[l][k+2]=='b'?2:1)*far);
					if(l+1<19 && b[l+1][k]!='.')				count+=((b[l+1][k]=='b'?2:1)*close);	
					if(k+1<19 && b[l][k+1]!='.')				count+=((b[l][k+1]=='b'?2:1)*close);
					if(l-2>=0 && k-2>=0 && b[l-2][k-2]!='.')	count+=((b[l-2][k-2]=='b'?2:1)*far);	
					if(l-1>=0 && k-1>=0 && b[l-1][k-1]!='.') 	count+=((b[l-1][k-1]=='b'?2:1)*close);
					if(l+2<19 && k+2<19 && b[l+2][k+2]!='.')	count+=((b[l+2][k+2]=='b'?2:1)*far);	
					if(l+1<19 && k+1<19 && b[l+1][k+1]!='.')	count+=((b[l+1][k+1]=='b'?2:1)*close);
					if(l-2>=0 && k+2<19 && b[l-2][k+2]!='.')	count+=((b[l-2][k+2]=='b'?2:1)*far);	
					if(l-1>=0 && k+1<19 && b[l-1][k+1]!='.')	count+=((b[l-1][k+1]=='b'?2:1)*close);
					if(l+2<19 && k-2>=0 && b[l+2][k-2]!='.')	count+=((b[l+2][k-2]=='b'?2:1)*far);	
					if(l+1<19 && k-1>=0 && b[l+1][k-1]!='.')	count+=((b[l+1][k-1]=='b'?2:1)*close);
					
					if(count > new_black_captures.updated_value)	new_black_captures = {count, l, k};
					new_black_captures_count += 1;
				}
			}

			//block of 3
			if(i>1 && j<17)
			{
				int w_count = 0, b_count = 0;
				for(int k=0;k<3;k++)	{if(b[i-k][j+k]!='.')	b[i-k][j+k]=='w'?w_count+=1:b_count+=1;}

				//create 3
				if(w_count == 2 && b_count == 0)	for(int k=0;k<3;k++)	if(b[i-k][j+k]=='.')	{
					int count=0;
					if(i-k-2>=0 && b[i-k-2][j+k]!='.') 				count+=((b[i-k-2][j+k]=='b'?2:1)*far);	
					if(j+k-2>=0 && b[i-k][j+k-2]!='.')				count+=((b[i-k][j+k-2]=='b'?2:1)*far);
					if(i-k-1>=0 && b[i-k-1][j+k]!='.')				count+=((b[i-k-1][j+k]=='b'?2:1)*close);	
					if(j+k-1>=0 && b[i-k][j+k-1]!='.')				count+=((b[i-k][j+k-1]=='b'?2:1)*close);
					if(i-k+2<19 && b[i-k+2][j+k]!='.')				count+=((b[i-k+2][j+k]=='b'?2:1)*far);	
					if(j+k+2<19 && b[i-k][j+k+2]!='.')				count+=((b[i-k][j+k+2]=='b'?2:1)*far);
					if(i-k+1<19 && b[i-k+1][j+k]!='.')				count+=((b[i-k+1][j+k]=='b'?2:1)*close);	
					if(j+k+1<19 && b[i-k][j+k+1]!='.')				count+=((b[i-k][j+k+1]=='b'?2:1)*close);
					if(i-k-2>=0 && j+k-2>=0 && b[i-k-2][j+k-2]!='.')	count+=((b[i-k-2][j+k-2]=='b'?2:1)*far);	
					if(i-k-1>=0 && j+k-1>=0 && b[i-k-1][j+k-1]!='.') 	count+=((b[i-k-1][j+k-1]=='b'?2:1)*close);
					if(i-k+2<19 && j+k+2<19 && b[i-k+2][j+k+2]!='.')	count+=((b[i-k+2][j+k+2]=='b'?2:1)*far);	
					if(i-k+1<19 && j+k+1<19 && b[i-k+1][j+k+1]!='.')	count+=((b[i-k+1][j+k+1]=='b'?2:1)*close);
					if(i-k-2>=0 && j+k+2<19 && b[i-k-2][j+k+2]!='.')	count+=((b[i-k-2][j+k+2]=='b'?2:1)*far);	
					if(i-k-1>=0 && j+k+1<19 && b[i-k-1][j+k+1]!='.')	count+=((b[i-k-1][j+k+1]=='b'?2:1)*close);
					if(i-k+2<19 && j+k-2>=0 && b[i-k+2][j+k-2]!='.')	count+=((b[i-k+2][j+k-2]=='b'?2:1)*far);	
					if(i-k+1<19 && j+k-1>=0 && b[i-k+1][j+k-1]!='.')	count+=((b[i-k+1][j+k-1]=='b'?2:1)*close);
					
					if(count > white_create_3.updated_value)	white_create_3 = {count, i-k, j+k};
					white_create_3_count += 1;
				}

				//prevent 3
				if(w_count == 0 && b_count == 2)	for(int k=0;k<3;k++)	if(b[i-k][j+k]=='.')	{
					int count=0;
					if(i-k-2>=0 && b[i-k-2][j+k]!='.') 				count+=((b[i-k-2][j+k]=='b'?2:1)*far);	
					if(j+k-2>=0 && b[i-k][j+k-2]!='.')				count+=((b[i-k][j+k-2]=='b'?2:1)*far);
					if(i-k-1>=0 && b[i-k-1][j+k]!='.')				count+=((b[i-k-1][j+k]=='b'?2:1)*close);	
					if(j+k-1>=0 && b[i-k][j+k-1]!='.')				count+=((b[i-k][j+k-1]=='b'?2:1)*close);
					if(i-k+2<19 && b[i-k+2][j+k]!='.')				count+=((b[i-k+2][j+k]=='b'?2:1)*far);	
					if(j+k+2<19 && b[i-k][j+k+2]!='.')				count+=((b[i-k][j+k+2]=='b'?2:1)*far);
					if(i-k+1<19 && b[i-k+1][j+k]!='.')				count+=((b[i-k+1][j+k]=='b'?2:1)*close);	
					if(j+k+1<19 && b[i-k][j+k+1]!='.')				count+=((b[i-k][j+k+1]=='b'?2:1)*close);
					if(i-k-2>=0 && j+k-2>=0 && b[i-k-2][j+k-2]!='.')	count+=((b[i-k-2][j+k-2]=='b'?2:1)*far);	
					if(i-k-1>=0 && j+k-1>=0 && b[i-k-1][j+k-1]!='.') 	count+=((b[i-k-1][j+k-1]=='b'?2:1)*close);
					if(i-k+2<19 && j+k+2<19 && b[i-k+2][j+k+2]!='.')	count+=((b[i-k+2][j+k+2]=='b'?2:1)*far);	
					if(i-k+1<19 && j+k+1<19 && b[i-k+1][j+k+1]!='.')	count+=((b[i-k+1][j+k+1]=='b'?2:1)*close);
					if(i-k-2>=0 && j+k+2<19 && b[i-k-2][j+k+2]!='.')	count+=((b[i-k-2][j+k+2]=='b'?2:1)*far);	
					if(i-k-1>=0 && j+k+1<19 && b[i-k-1][j+k+1]!='.')	count+=((b[i-k-1][j+k+1]=='b'?2:1)*close);
					if(i-k+2<19 && j+k-2>=0 && b[i-k+2][j+k-2]!='.')	count+=((b[i-k+2][j+k-2]=='b'?2:1)*far);	
					if(i-k+1<19 && j+k-1>=0 && b[i-k+1][j+k-1]!='.')	count+=((b[i-k+1][j+k-1]=='b'?2:1)*close);
					
					if(count > black_create_3.updated_value)	black_create_3 = {count, i-k, j+k};
					black_create_3_count += 1;
				}
			}
		}
	
	//prevents till now
	for(int i=min_i;i<=max_i;i++)
		for(int j=min_j;j<=max_j;j++)
			if(b[i][j]!='.')
		{
			//horizontal
			if(i<16 && b[i+1][j]==b[i][j] && b[i+2][j]==b[i][j] && b[i+3][j]==b[i][j])
				b[i][j]=='w'?white_prevent_4_till_now++:black_prevent_4_till_now++;

			if(i<17 && b[i+1][j]==b[i][j] && b[i+2][j]==b[i][j])
				b[i][j]=='w'?white_prevent_3_till_now++:black_prevent_3_till_now++;

			if(i<18 && b[i+1][j]==b[i][j])
				b[i][j]=='w'?white_prevent_2_till_now++:black_prevent_2_till_now++;

			//vertical
			if(j<16 && b[i][j+1]==b[i][j] && b[i][j+2]==b[i][j] && b[i][j+3]==b[i][j])
				b[i][j]=='w'?white_prevent_4_till_now++:black_prevent_4_till_now++;

			if(j<17 && b[i][j+1]==b[i][j] && b[i][j+2]==b[i][j])
				b[i][j]=='w'?white_prevent_3_till_now++:black_prevent_3_till_now++;

			if(j<18 && b[i][j+1]==b[i][j])
				b[i][j]=='w'?white_prevent_2_till_now++:black_prevent_2_till_now++;

			//diagonal
			if(j<16 && i<16 && b[i+1][j+1]==b[i][j] && b[i+2][j+2]==b[i][j] && b[i+3][j+3]==b[i][j])
				b[i][j]=='w'?white_prevent_4_till_now++:black_prevent_4_till_now++;

			if(j<17 && i<17 && b[i+1][j+1]==b[i][j] && b[i+2][j+2]==b[i][j])
				b[i][j]=='w'?white_prevent_3_till_now++:black_prevent_3_till_now++;

			if(j<18 && i<18 && b[i+1][j+1]==b[i][j])
				b[i][j]=='w'?white_prevent_2_till_now++:black_prevent_2_till_now++;

			//anti-diagonal
			if(j<16 && i>2 && b[i-1][j+1]==b[i][j] && b[i-2][j+2]==b[i][j] && b[i-3][j+3]==b[i][j])
				b[i][j]=='w'?white_prevent_4_till_now++:black_prevent_4_till_now++;

			if(j<17 && i>1 && b[i-1][j+1]==b[i][j] && b[i-2][j+2]==b[i][j])
				b[i][j]=='w'?white_prevent_3_till_now++:black_prevent_3_till_now++;

			if(j<18 && i>0 && b[i-1][j+1]==b[i][j])
				b[i][j]=='w'?white_prevent_2_till_now++:black_prevent_2_till_now++;
		}

		white_prevent_3_till_now = white_prevent_3_till_now - 2*white_prevent_4_till_now;
		white_prevent_2_till_now = white_prevent_2_till_now - 2*white_prevent_3_till_now - 3*white_prevent_4_till_now;

		black_prevent_3_till_now = black_prevent_3_till_now - 2*black_prevent_4_till_now;
		black_prevent_2_till_now = black_prevent_2_till_now - 2*black_prevent_3_till_now - 3*black_prevent_4_till_now;

		long long int capture_difference = white_captures - black_captures;
		evaluation += 1000000000000000 * capture_difference;
		evaluation += (black_prevent_4_till_now - white_prevent_4_till_now) * 1000000000000;
		evaluation += (black_prevent_3_till_now - white_prevent_3_till_now) * 10000000000000;
		evaluation += (black_prevent_2_till_now - white_prevent_2_till_now) * 100000000000000;
		if(white_create_5_count)
		{
			evaluation += 1000000000000;
			if(return_index == make_pair(-1,-1))
				return_index = make_pair(white_create_5.index_x, white_create_5.index_y);
		}

		if(white_captures == 4 && new_white_captures_count > 0)
		{
			evaluation += 1000000000000;
			if(return_index == make_pair(-1, -1))
				return_index = make_pair(new_white_captures.index_x, new_white_captures.index_y);
		}

		if(black_create_5_count)
		{
			evaluation += 1000000000000;
			if(return_index == make_pair(-1, -1))
				return_index = make_pair(black_create_5.index_x, black_create_5.index_y);
		}
		if(black_create_5_count>1)
		{
			return {LONG_MIN, black_create_5.index_x, black_create_5.index_y};
		}

		if(black_captures == 4 && new_black_captures_count > 0)
		{
			evaluation += 1000000000000;
			if(return_index == make_pair(-1, -1))
				return_index = make_pair(new_black_captures.index_x, new_black_captures.index_y);
		}

		if(white_create_5_from_3_count)
		{
			evaluation += 10000000000 * white_create_5_from_3.updated_value;
			if(return_index == make_pair(-1, -1))
				return_index = make_pair(white_create_5_from_3.index_x, white_create_5_from_3.index_y);
		}

		if(black_create_5_from_3_count)
		{
			evaluation += 10000000000 * black_create_5_from_3.updated_value;
			if(return_index == make_pair(-1, -1))
				return_index = make_pair(black_create_5_from_3.index_x, black_create_5_from_3.index_y);
		}

		if(new_white_captures_count)
		{
			evaluation += 100000000 * new_white_captures.updated_value;
			if(return_index == make_pair(-1, -1))
				return_index = make_pair(new_white_captures.index_x, new_white_captures.index_y);
		}

		if(new_black_captures_count)
		{
			evaluation += 100000000 * new_black_captures.updated_value;
			if(return_index == make_pair(-1, -1))
				return_index = make_pair(new_black_captures.index_x, new_black_captures.index_y);
		}

		if(white_create_4_count)
		{
			evaluation += 1000000 * white_create_4.updated_value;
			if(return_index == make_pair(-1, -1))
				return_index = make_pair(white_create_4.index_x, white_create_4.index_y);
		}

		if(black_create_4_count)
		{
			evaluation += 10000 * black_create_4.updated_value;
			if(return_index == make_pair(-1, -1))
				return_index = make_pair(black_create_4.index_x, black_create_4.index_y);
		}

		if(white_create_3_count)
		{
			evaluation += 10000 * white_create_3.updated_value;
			if(return_index == make_pair(-1, -1))
				return_index = make_pair(white_create_3.index_x, white_create_3.index_y);
		}

		if(black_create_3_count)
		{
			evaluation += 100 * black_create_3.updated_value;
			if(return_index == make_pair(-1, -1))
				return_index = make_pair(black_create_3.index_x, black_create_3.index_y);
		}

	for(int i=min_i;i<=max_i;i++)
		for(int j=min_j;j<=max_j;j++)
			if(b[i][j]=='.')
			{
				if(i-1>=0 && i+2<19 && b[i+1][j]=='w' && ((b[i-1][j]=='b' && b[i+2][j]=='.') || (b[i-1][j]=='.' && b[i+2][j]=='b')))
					continue;
				if(i-2>=0 && i+1<19 && b[i-1][j]=='w' && ((b[i+1][j]=='b' && b[i-2][j]=='.') || (b[i+1][j]=='.' && b[i-2][j]=='b')))
					continue;
				
				int count=0;
				if(i-2>=0 && b[i-2][j]!='.') 				count+=((b[i-2][j]=='b'?2:1)*far);	
				if(j-2>=0 && b[i][j-2]!='.')				count+=((b[i][j-2]=='b'?2:1)*far);
				if(i-1>=0 && b[i-1][j]!='.')				count+=((b[i-1][j]=='b'?2:1)*close);	
				if(j-1>=0 && b[i][j-1]!='.')				count+=((b[i][j-1]=='b'?2:1)*close);
				if(i+2<19 && b[i+2][j]!='.')				count+=((b[i+2][j]=='b'?2:1)*far);	
				if(j+2<19 && b[i][j+2]!='.')				count+=((b[i][j+2]=='b'?2:1)*far);
				if(i+1<19 && b[i+1][j]!='.')				count+=((b[i+1][j]=='b'?2:1)*close);	
				if(j+1<19 && b[i][j+1]!='.')				count+=((b[i][j+1]=='b'?2:1)*close);
				if(i-2>=0 && j-2>=0 && b[i-2][j-2]!='.')	count+=((b[i-2][j-2]=='b'?2:1)*far);	
				if(i-1>=0 && j-1>=0 && b[i-1][j-1]!='.') 	count+=((b[i-1][j-1]=='b'?2:1)*close);
				if(i+2<19 && j+2<19 && b[i+2][j+2]!='.')	count+=((b[i+2][j+2]=='b'?2:1)*far);	
				if(i+1<19 && j+1<19 && b[i+1][j+1]!='.')	count+=((b[i+1][j+1]=='b'?2:1)*close);
				if(i-2>=0 && j+2<19 && b[i-2][j+2]!='.')	count+=((b[i-2][j+2]=='b'?2:1)*far);	
				if(i-1>=0 && j+1<19 && b[i-1][j+1]!='.')	count+=((b[i-1][j+1]=='b'?2:1)*close);
				if(i+2<19 && j-2>=0 && b[i+2][j-2]!='.')	count+=((b[i+2][j-2]=='b'?2:1)*far);	
				if(i+1<19 && j-1>=0 && b[i+1][j-1]!='.')	count+=((b[i+1][j-1]=='b'?2:1)*close);
				
				if(count > last_option.updated_value)	last_option = {count, i, j};
			}
		evaluation += 5 * last_option.updated_value;
		if(return_index == make_pair(-1, -1))
			return_index = make_pair(last_option.index_x, last_option.index_y);
		
	if(return_index.first!=-1 && return_index.second!=-1)
		return {evaluation, return_index.first, return_index.second};
	for(int i=min_i;i<=max_i;i++)
		for(int j=min_j;j<=max_j;j++)
			if(b[i][j]=='.')
				return {evaluation, i, j};
}

value_x_y play_move_black(vector<string> board, long long int alpha, long long int beta, int depth, string who_won, int white_captures, int black_captures, int original_depth, int min_i, int min_j, int max_i, int max_j)	{
	if (!depth)
	{
		return evaluate(board, white_captures, black_captures, false, original_depth, who_won, min_i, min_j, max_i, max_j); 
	}

	long long int best_value = LONG_MAX;
	int best_i = 0, best_j = 0;
	for(int i=min_i;i<=max_i;i++)
		for(int j=min_j;j<=max_j;j++)
			if(board[i][j] == '.')	{
				board[i][j] = 'b';
				if(who_won=="" && game_ended(board, i, j))
				{
					who_won = "b";
					return {LONG_MAX,i,j};
				}
				board_white_black captures_returned = captures(board, i, j, white_captures, black_captures);
				
				if(who_won=="" && captures_returned.updated_black_captures >= 5)
				{
					who_won = "b";
					return {LONG_MAX,i,j};
				}

				value_x_y value_returned = play_move_white(captures_returned.updated_board, alpha, beta, depth - 1, who_won, captures_returned.updated_white_captures, captures_returned.updated_black_captures, original_depth, max(0, min(min_i, i-2)), max(0, min(min_j, j-2)), min(18, max(max_i, i+2)), min(18, max(max_j,j+2)));


				if(value_returned.updated_value < best_value)	{
					best_value = min(best_value, value_returned.updated_value);
					best_i = i;
					best_j = j;
				}

				beta = min(beta, best_value);
				board[i][j] = '.';
			}
	return value_x_y {best_value, best_i, best_j};
}

value_x_y play_move_white(vector<string> board, long long int alpha, long long int beta, int depth, string who_won, int white_captures, int black_captures, int original_depth, int min_i, int min_j, int max_i, int max_j)	{
	if (!depth)
	{
		return evaluate(board, white_captures, black_captures, true, original_depth, who_won, min_i, min_j, max_i, max_j);
	}

	value_x_y return_value_index {-1,-1,-1};
	return_value_index.updated_value = LONG_MIN;
	long long int best_value = LONG_MIN;
	int best_i = 0, best_j = 0;
	for(int i=min_i;i<=max_i;i++)
		for(int j=min_j;j<=max_j;j++)
			if(board[i][j]=='.')	{
				board[i][j] = 'w';
				if(who_won=="" && game_ended(board, i, j))	
				{
					who_won = "w";
					return {LONG_MIN,i,j};
				}

				board_white_black captures_returned = captures(board, i, j, white_captures, black_captures);

				if(who_won=="" && captures_returned.updated_white_captures >= 5)
				{
					who_won = "w";
					return {LONG_MIN,i,j};
				}

				value_x_y value_returned = play_move_black(captures_returned.updated_board, alpha, beta, depth - 1, who_won, captures_returned.updated_white_captures, captures_returned.updated_black_captures, original_depth, max(0, min(min_i, i-2)), max(0, min(min_j, j-2)), min(18, max(max_i, i+2)), min(18, max(max_j,j+2)));

				if(value_returned.updated_value == LONG_MAX)
					return evaluate(board, white_captures, black_captures, true, original_depth, who_won, min_i, min_j, max_i, max_j);

				if(value_returned.updated_value > best_value)	{
					best_value = max(best_value, value_returned.updated_value);
					best_i = i;
					best_j = j;
				}

				if(return_value_index.updated_value < value_returned.updated_value)
				{
					return_value_index = {value_returned.updated_value, i, j};
				}

				alpha = max(alpha, best_value);
				board[i][j] = '.';
			}
	return return_value_index;
}

int main()	{
	ifstream file;
    file.open("input.txt");
    string our_color = "";
    float time = 0.0;
    string wb_captures = "";
    int white_captures = 0, black_captures = 0;
    string board_line = "";
    vector<string> board;

    if(file.is_open())	{
    	file >> our_color;
    	file >> time;
    	
    	file >> wb_captures;
    	white_captures = stoi(wb_captures.substr(0, wb_captures.find(',')));
    	black_captures = stoi(wb_captures.substr(wb_captures.find(',') + 1));

    	for(int i=0;i<19;i++)	{
    		file >> board_line;
    		board.push_back(board_line);
    	}
    }
    file.close();

    //black color
    if(our_color =="BLACK")
    {
    	for(int i=0;i<19;i++)
    		for(int j=0;j<19;j++)
    		{
    			if(board[i][j]=='b')
    				board[i][j]='w';
    			else if(board[i][j]=='w')
    				board[i][j]='b';
    		}
    	int temp = white_captures;
    	white_captures = black_captures;
    	black_captures = temp;
    }

    int max_i = 0, max_j = 0, min_i = 18, min_j = 18;
    int white_count = 0, black_count = 0;

    for(int i=0;i<19;i++)
    	for(int j=0;j<19;j++)
    		if(board[i][j]!='.')	{
    			max_i = max(max_i, i);
    			max_j = max(max_j, j);
    			min_i = min(min_i, i);
    			min_j = min(min_j, j);
    			board[i][j]=='w'?white_count++:black_count++;
    		}


	if(our_color == "WHITE")
	{
	    if(white_count == 0 && black_count == 0)
	    {
	    	ofstream output_file("output.txt");
			output_file << "10K" << endl;
			output_file.close();
	    	return 0;
	    }

	    if(white_count == 1 && black_count == 1)
	    {
	    	//second move
	    	if(board[6][6]=='.')
	    	{
	    		ofstream output_file("output.txt");
				output_file << "13G" << endl;
				output_file.close();
				return 0;
	    	}
	    	else
	    	{
	    		ofstream output_file("output.txt");
				output_file << "7N" << endl;
				output_file.close();
	    		return 0;
	    	}
	    }
	}   
	white_captures = white_captures / 2;
	black_captures = black_captures / 2;
	long long int alpha = LONG_MIN, beta = LONG_MAX;
	int depth = 0;
	if(time > 100)
		depth = 2;
	else if(time > 50)
		depth = 1;
	string who_won = "";
	value_x_y value = play_move_white(board, alpha, beta, depth, who_won, white_captures, black_captures, depth, max(min_i-2, 0), max(min_j-2,0),min(max_i+2,18), min(max_j+2, 18));
	
	vector<string> y_axis = {"A","B","C","D","E","F","G","H","J","K","L","M","N","O","P","Q","R","S","T"};
	vector<string> x_axis = {"19","18","17","16","15","14","13","12","11","10","9","8","7","6","5","4","3","2","1"};

	string output = x_axis[value.index_x] + y_axis[value.index_y];
	ofstream output_file("output.txt");
	output_file << output << endl;
	output_file.close();

	return 0;
}
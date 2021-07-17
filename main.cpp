/*
 * main.cpp
 *
 *  Created on: Jul 17, 2021
 *      Author: d-w-h
 */

#include <stdio.h>
#include <iostream>
#include <vector>

bool is_square_magic(int** s) {
    //Check for magic square
    int magic_number = 15;

    int nx = 3;
    int ny = 3;

    //Check rows
    bool is_magic_square = true;
    for(int j = 0; j < ny; ++j) {
        int num_check = 0;
        for(int i = 0; i < nx; ++i) {
            num_check += s[i][j];
        }
        if(num_check != magic_number) { is_magic_square = false; }
    }

    //Check columns
    for(int i = 0; i < nx; ++i) {
        int num_check = 0;
        for(int j = 0; j < ny; ++j) {
            num_check += s[i][j];
        }
        if(num_check != magic_number) { is_magic_square = false; }
    }

    //Check diagonal 1
    int num_check = 0;
    for(int i = 0; i < nx; ++i) {
        num_check += s[i][i];
    }
    if(num_check != magic_number) { is_magic_square = false; }

    //Check diagonal 2
    num_check = 0;
    int j = 2;
    for(int i = 0; i < nx; ++i) {
        num_check += s[i][j];
        --j;
    }
    if(num_check != magic_number) { is_magic_square = false; }

    return is_magic_square;
}

void print_magic_square (int** s) {
    int nx = 3;
    int ny = 3;

    for(int j = 0; j < ny; ++j) {
        for(int i = 0; i < nx; ++i) {
            std::cout << s[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int cost_conversion(std::vector<std::vector<int>> s_ref, int** s) {

    int nx = 3;
    int ny = 3;

    int cost_conversion = 0;

    for(int i = 0; i < nx; ++i) {
        for(int j = 0; j < ny; ++j) {
            if(s[i][j] != s_ref[i][j]) {
                cost_conversion += abs(s[i][j] - s_ref[i][j]);
            }
        }
    }

    return cost_conversion;
}

void determine_min_conv(std::vector<std::vector<int>>& s_ref, std::vector<int> track_indices, int& min_cost_conv, int n) {

	int size_vector = track_indices.size();
	int min_index = 1;
	int max_index = 9;
	int nx = 3;
	int ny = 3;

    int** s = new int*[nx];
    for(int i = 0; i < nx; ++i) {
        s[i] = new int[ny];
    }

	for(int i = min_index; i <= max_index; ++i) {
		bool index_not_used = true;
		if(size_vector > 0) {
			for(int j = 0; j < size_vector; ++j) {
				index_not_used = index_not_used && track_indices[j] != i;
			}
		}
		else { index_not_used = true; }
		if(index_not_used) {
			std::vector<int> tracker;
			int size_track = track_indices.size();
			for(int it2 = 0; it2 < size_track; ++it2) {
				tracker.push_back(track_indices[it2]);
			}
			tracker.push_back(i);
			int n2 = n + 1;

			if(n == 8) {
				for(int it = 0; it < 9; ++it) {
					int nn = it;
					int i_index = nn - (nn / nx) * nx;
					int j_index = nn / nx;
					s[i_index][j_index] = tracker[it];
				}

				bool is_magic_square = is_square_magic(s);
				int cost_of_conversion = cost_conversion(s_ref, s);
				if(is_magic_square) {
					if(cost_of_conversion < min_cost_conv) {
						min_cost_conv = cost_of_conversion;
					}
				}

			}
			else {
				determine_min_conv(s_ref, tracker, min_cost_conv, n2);
			}
		}
	}
}

int forming_magic_square(std::vector<std::vector<int>> s) {
    int min_cost_conversion = 3e+8;
    std::vector<int> track_indices;

    determine_min_conv(s, track_indices, min_cost_conversion, 0);

    return min_cost_conversion;
}

int main(int argc, char* argv[]) {

    std::vector<std::vector<int>> s;

    //Create magic square start
    s.push_back({4, 8, 2});
    s.push_back({4, 5, 7});
    s.push_back({6, 1, 6});

    //Compute minimum cost conversion
    int min_cost_conversion = forming_magic_square(s);

    //Print results
    std::cout << "min cost of conversion: " << min_cost_conversion << std::endl;
    std::cout << "done" << std::endl;

    return 0;
}



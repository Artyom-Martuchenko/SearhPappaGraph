#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <string>
#include <sstream>
#include <algorithm>
#include <list>
#include <map>

using namespace std;

typedef vector<pair<size_t, vector<size_t>>> VECTOR;

vector<pair<size_t, vector<size_t>>> return_container(string path)
{
	ifstream file_read;

	vector<pair<size_t, vector<size_t>>> container;

	file_read.open(path);
	if (!file_read.is_open())
	{
		cout << "Error opening a file!" << '\n';
	}
	else
	{
		while (!file_read.eof())
		{

			string temp;
			size_t temp_id, temp_int;
			vector<size_t> temp_vector;
			pair<size_t, vector<size_t>> temp_pair;
			stringstream ss;

			getline(file_read, temp);
			ss << temp;
			ss >> temp_id;
			ss >> temp;

			while (ss >> temp_int)
			{
				temp_vector.push_back(temp_int);
			}
			temp_pair.first = temp_id;
			temp_pair.second = temp_vector;

			container.push_back(temp_pair);
		}

		sort(container.begin(), container.end());
		for (auto& i : container)
		{
			sort(i.second.begin(), i.second.end());
		}

		cout << '\n';

		return container;
	}
}

void write_container(string path)
{
	for (auto& a : return_container(path)) {
		cout << a.first << " | ";
		for (auto& b : a.second)
			cout << b << ' ';
		cout << '\n';
	}
	cout << '\n';
}

void compare_grafs(vector<pair<size_t, vector<size_t>>> vector_1, vector<pair<size_t, vector<size_t>>> vector_2)
{

	if (vector_1.size() == vector_2.size()) {
		for (size_t i = 0; i < vector_1.size(); i++)
			for (size_t n = 0; n < vector_1[i].second.size(); n++)
				if (vector_1[i].second[n] != vector_2[i].second[n] || vector_1[i].second.size() != vector_2[i].second.size()) 
				{
					cout << "No coherence witha pappa pattern!" << '\n'; 
					exit(0); 
				}

		cout << "It is sure to assume that input corresponds to the pappa pattern!" << '\n';
	}
	else { cout << "No coherence with a pappa pattern!" << '\n'; exit(0); }
}

list<pair<size_t, list<pair<size_t, size_t>>>> return_adj_to_inc_list(string path = "test_adj.txt")
{
	list<pair<size_t, list<pair<size_t, size_t>>>> pair_list;
	list<pair<size_t, size_t>> temp_in_list;

	for (auto& a : return_container(path)) {
		for (auto& b : a.second)
			if (a.first < b)
				temp_in_list.push_back(make_pair(a.first, b));
			else if (a.first > b)
				temp_in_list.push_back(make_pair(b, a.first));

		pair_list.push_back(make_pair(a.first, temp_in_list));
		temp_in_list.clear();
	}

	return pair_list;
}

vector<pair<size_t, vector<size_t>>> return_inc_container(string path = "test_adj.txt")
{
	map<pair<size_t, size_t>, size_t> decoder_container;
	size_t id = 1;
	for (auto& a : return_adj_to_inc_list(path))
		for (auto& b : a.second) 
		{
			decoder_container[b] = 0;
		}

	for (auto& a : return_adj_to_inc_list(path))
		for (auto& b : a.second) {
			if (decoder_container[b] == 0) {
				decoder_container[b] = id;
				id++;
			}
		}

	vector<pair<size_t, vector<size_t>>> output_container;
	vector<size_t> temp_vect;
	for (auto& a : return_adj_to_inc_list(path)) {
		for (auto& b : a.second)
			temp_vect.push_back(decoder_container[b]);

		output_container.push_back(make_pair(a.first, temp_vect));
		temp_vect.clear();
	}

	return output_container;
}

void write_inc_container()
{
	cout << "Incidence list (edge represented as number): ";
	for (auto& a : return_inc_container()) {
		cout << a.first << " | ";
		for (auto& b : a.second)
			cout << b << ' ';

		cout << '\n';
	}
}

void write_adj_container()
{
	cout << "Adjacency container: " << '\n';
	for (auto& a : return_container("test_adj.txt")) {
		cout << a.first << " | ";
		for (auto& b : a.second)
			cout << b << ' ';

		cout << '\n';
	}
	cout << "\n\n";
}

void write_inc_in_file(string source, string target)
{
	ofstream write_file;
	write_file.open(target);
	if (!write_file.is_open()) {
		std::cout << "Error opening file! " << '\n'; exit(0);
	}
	else {
		for (auto& a : return_inc_container(source)) {
			write_file << a.first << " | ";
			for (auto& b : a.second)
				write_file << b << ' ';

			write_file << '\n';
		}
	}
}

int main()
{
	compare_grafs(return_container("graf_pappa_inc.txt"), return_container("graf_pappa_inc.txt"));
}
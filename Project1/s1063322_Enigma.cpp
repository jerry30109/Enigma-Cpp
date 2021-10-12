#include"Enigma.h"

Plugboard::Plugboard(std::string encode_file) {
	Read_table(encode_file);
}
size_t Plugboard::Forward(size_t const& i) {
	next_spin = true;
	return link_next->Forward(encode_table[i] - 65);
}
size_t Plugboard::Backward(size_t const& i) {
	return (encode_table[i]);
}
void Plugboard::Reset() {
	if (link_next) {
		link_next->Reset();
	}
}
Rotor::Rotor(std::string encode_file, char const& start_, char const& arrows_)
{
	Read_table(encode_file);
	for (int i = 0; i < 26; i++)
	{
		if (start_ + i <= 90)
			reverse_table.push_back(start_ + i);
		else
			reverse_table.push_back((start_ + i) - 26);
	}
	reset_table = reverse_table;
	reset_table2 = encode_table;
	for (int i = 0; i < 26; i++) {
		if (arrows_ == reverse_table[i]) {
			space = i;
			reset_space = i;
			break;
		}
	}
}
void Rotor::Reset() {
	reverse_table = reset_table;
	encode_table = reset_table2;
	space = reset_space;
	if (link_next) {
		link_next->Reset();
	}
}
size_t Rotor::Forward(size_t const& i) //Forward Encoding
{
	Spin();
	int temp = reverse_table[i] - 65;
	for (int j = 0; j < 26; j++)
	{
		if (encode_table[temp] == reverse_table[j])
			return link_next->Forward(j);
	}
}

size_t Rotor::Backward(size_t const& i)
{

	for (int j = 0; j < 26; j++)
	{
		if (encode_table[j] == reverse_table[i])
		{
			int vec = j + 65;
			for (int k = 0; k < 26; k++)
			{
				if (reverse_table[k] == vec) {
					return link_previous->Backward(k);
				}

			}
		}
	}
}
void Rotor::Spin() {

	if (link_previous->next_spin == true) {
		if (space == 0) {
			space = 25;
			next_spin = true;
		}
		else {
			space--;
		}
		link_previous->next_spin = false;
		buffer_table.clear();
		buffer_table = reverse_table;
		reverse_table.clear();
		for (int i = 1; i <= 25; i++) {
			reverse_table.push_back(buffer_table[i]);
		}
		reverse_table.push_back(buffer_table[0]);
		buffer_table2 = encode_table;
	}
	else {
		return;
	}
	

}
Reflector::Reflector(std::string encode_file)
{
	Read_table(encode_file);
}
void Reflector::Reset() {
	if (link_next) {
		link_next->Reset();
	}
}

size_t Reflector::Forward(size_t const& i) //Forward Encoding
{
	return link_previous->Backward((encode_table[i] - 65));
}

size_t Reflector::Backward(size_t const& i)
{
	return i;
}
Special_Rotor::Special_Rotor(std::string encode_file, char const& start_, char const& arrows_)
	:Rotor(encode_file, start_, arrows_)
{
	reset_table = reverse_table;
	reset_space = space;
}
size_t Special_Rotor::Forward(size_t const& i) //Forward Encoding
{
	Spin();
	int temp = reverse_table[i] - 65;
	for (int j = 0; j < 26; j++)
	{
		if (encode_table[temp] == reverse_table[j])
			return link_next->Forward(j);
	}
}
size_t Special_Rotor::Backward(size_t const& i)
{
	for (int j = 0; j < 26; j++)
	{
		if (encode_table[j] == reverse_table[i])
		{
			int vec = j + 65;
			for (int k = 0; k < 26; k++)
			{
				if (reverse_table[k] == vec) {
					return link_previous->Backward(k);
				}

			}
		}
	}
}
void Special_Rotor::Spin() {

	if (link_previous->next_spin == true) {
		if (space == 0) {
			space = 25;
			next_spin = true;
			ifnext = true;
		}
		else {
			space--;
		}
		link_previous->next_spin = false;
		buffer_table = reverse_table;
		reverse_table.clear();
		for (int i = 1; i <= 25; i++) {
			reverse_table.push_back(buffer_table[i]);
		}
		reverse_table.push_back(buffer_table[0]);
		buffer_table2 = encode_table;
	}
	if (ifnext == true) {
		space--;
		ifnext = false;
		buffer_table = reverse_table;
		reverse_table.clear();
		for (int i = 1; i <= 25; i++) {
			reverse_table.push_back(buffer_table[i]);
		}
		reverse_table.push_back(buffer_table[0]);
		return;
	}
	else {

	}
}
void Special_Rotor::Reset() {
	reverse_table = reset_table;
	space = reset_space;
	if(link_next)
		link_next->Reset();
}
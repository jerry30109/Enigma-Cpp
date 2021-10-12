#include"Enigma_Base.h"
struct str {
	int size = 0;
	string charArray;
};
void Enigma_Files::Read_file(std::string file) //Read text from file into string
{
	str filein;
	ifstream inFile(file, ios::in);
	while (inFile >> filein.charArray) {

	}
	filein.size = (filein.charArray.size());
	cout << filein.size;
	data = filein.charArray;

}
void Enigma_Files::Write_file(std::string file) //Write string from file into string
{
	ofstream outFile(file, ios::out);
	outFile << data;
}
void Enigma_Files::Push(char const& c) //Push a character on the end of data string
{
	string vec = data;
	vec.push_back(c);
	data = vec;
}
char const& Enigma_Files::operator [] (size_t const& i) // (const) subscript operator
{
	return data[i];
}
std::string Enigma_Files::Data() //get the data string
{
	return data;
}
size_t Enigma_Files::Length() //report # of character
{
	return data.size();
}
Enigma_Component::Enigma_Component() {

}
Enigma_Component::Enigma_Component(std::string file)
{
	Read_table(file);
}
char Enigma_Component::Input_signal(char c) //Input a character and start to encode it.
{
	return Forward(c - 65);
}
void Enigma_Component::Reset() {
	
}
void Enigma_Component::Link(Enigma_Component & next) //Link the NEXT ENCODER
{
	link_next = &next;
	next.link_previous = this;
}
void Enigma_Component::Read_table(std::string file) //Read the Ringstellung and generate encode_table & reverse_table
{
	str filein;
	ifstream inFile(file, ios::in);
	while (inFile >> filein.charArray) {

	}
	filein.size = (filein.charArray.size());
	for (int i = 0; i < filein.size; i++) {
		encode_table.push_back(filein.charArray[i]);
	}


}
void Enigma_Component::Spin() {

}
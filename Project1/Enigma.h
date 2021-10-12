#pragma once

#include "Enigma_Base.h"
class Plugboard : public Enigma_Component
{
public:
	Plugboard(std::string encode_file);
	size_t Forward(size_t const& i);
	size_t Backward(size_t const& i);
	void Reset();
};

class Rotor : public Enigma_Component
{
public:
	Rotor(std::string encode_file, char const& start_, char const& arrows_);
	size_t Forward(size_t const& i);
	size_t Backward(size_t const& i);
	void Spin();
	void Reset();
private:
	std::vector<size_t> buffer_table;
	std::vector<size_t> buffer_table2;


};

class Reflector : public Enigma_Component
{
public:
	void Reset();
	Reflector(std::string encode_file);
	size_t Forward(size_t const& i);
	size_t Backward(size_t const& i);

};
class Special_Rotor : public Rotor
{
public:
	Special_Rotor(std::string encode_file, char const& start_, char const& arrows_);
	size_t Forward(size_t const& i);
	size_t Backward(size_t const& i);
	void Spin();
	void Reset();
private:
	int space;
	bool ifnext = false;
	std::vector<size_t> buffer_table2;
	std::vector<size_t> buffer_table;
};

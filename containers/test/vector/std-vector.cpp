#include <vector>
#include <iostream>
#include <iterator>
#include "../../vector.hpp"

int main()
{
	std::vector<int> v(5,2);
	std::vector<int>::iterator it;
    ft::vector<int> ftv(5,2);
    ft::vector<int>::iterator ftit;


	// std::cout << std::endl << "#====== push back end =====#" << std::endl;
	for (int i = 0; i < 5; i++)
	{	
        v[i] = i;
        ftv[i] = i;
    }
    std::cout << "------ std     ||||    ft ------" << std::endl;
	std::cout << std::endl
			  << "#====== constructor, begin end =====#" << std::endl;
	std::cout << "stdstdstdstdstdstdstdstd" << std::endl;
    for (it = v.begin(); it != v.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

    std::cout << "ftftftftftftftftftftftft" << std::endl;
    for (ftit = ftv.begin(); ftit != ftv.end(); ftit++)
	    std::cout << *ftit << " ";
    std::cout << std::endl;

    std::cout << "------------------------------" << std::endl;
    std::cout << "stdstdstdstdstdstdstdstd" << std::endl;
	std::vector<int> v2(v.begin(), v.end());
	for (it = v2.begin(); it != v2.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
    std::cout << "ftftftftftftftftftftftft" << std::endl;
    ft::vector<int> ftv2(ftv.begin(), ftv.end());
	// int i =0;
    // std::cout << "begin : " << *ftv.begin()
    for (ftit = ftv2.begin(); ftit != ftv2.end(); ftit++)
    // {
    //     // std::cout << "index : " << i++;
		std::cout << *ftit << " ";
    // }
    // std::cout << "OUT---------" << std::endl;
	std::cout << std::endl;

	std::cout << "std" << std::endl;
	std::vector<int> v3(v2);
	for (it = v3.begin(); it != v3.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

	std::cout << "ft" << std::endl;
	ft::vector<int> ftv3(ftv2);
	for (ftit = ftv3.begin(); ftit != ftv3.end(); ftit++)
		std::cout << *ftit << " ";
	std::cout << std::endl;

	std::cout <<"std" << std::endl;
	std::vector<int> v4(7, 7);
	v4 = v2;
	for (it = v4.begin(); it != v4.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

	std::cout <<"ft" << std::endl;
	ft::vector<int> ftv4(7, 7);
	ftv4 = ftv2;
	for (ftit = ftv4.begin(); ftit != ftv4.end(); ftit++)
		std::cout << *ftit << " ";
	std::cout << std::endl;

	std::cout << std::endl
			  << "#===== reverse iterator =====#" << std::endl;
	std::vector<int>::reverse_iterator rit;
	for (rit = v4.rbegin(); rit != v4.rend(); rit++)
		std::cout << *rit << " ";
	std::cout << std::endl;

	std::cout << "ft "<< std::endl;
	ft::vector<int>::reverse_iterator ftrit;
	for (ftrit = ftv4.rbegin(); ftrit != ftv4.rend(); ftrit++)
		std::cout << *ftrit << " ";
	std::cout << std::endl;

	// // std::cout << std::endl << "#===== front back =====#" << std::endl;
	// // std::vector<int> vempty;
	// // std::cout << vempty.front() << std::endl;
	// // std::cout << vempty.back() << std::endl;

	// std::cout << std::endl
	// 		  << "#===== assign =====#" << std::endl;
	// v3.resize(30);
	// v4.assign(v3.begin(), v3.end());
	// for (rit = v4.rbegin(); rit != v4.rend(); rit++)
	// 	std::cout << *rit << " ";
	// std::cout << std::endl;

	std::cout << std::endl
			  << "#===== max_size =====#" << std::endl;
	std::vector<int> iv;
	std::vector<char> cv;
	std::cout << iv.max_size() << "\n"
			  << cv.max_size() << std::endl;
	std::cout << "ft" << std::endl;
	ft::vector<int> ftiv;
	ft::vector<char> ftcv;
	std::cout << ftiv.max_size() << "\n"
			  << ftcv.max_size() << std::endl;


	std::cout << std::endl << "#===== reserve =====#" << std::endl;
	std::vector<int> v5;
	// v5.reserve(v5.max_size() + 1);
	// std::cout << v5.size() << std::endl;
	// std::cout <<"ft" << std::endl;
	// ft::vector<int> ftv5;
	// ftv5.reserve(ftv5.max_size() + 1);
	// std::cout << ftv5.size() << std::endl;

	std::cout << std::endl
			  << "#===== resize =====#" << std::endl;
	std::cout << v.capacity() << std::endl;
	v.resize(5, 100);
	std::cout << v.capacity() << " " << v.size() << " " << v.at(4) << std::endl;
	v.resize(30, 100);
	std::cout << v.capacity() << " " << v.size() << " " << v.at(29) << std::endl;
	for (int i = 0; i < 5; i++)
	{
		v.resize(60 + i);
		std::cout << "capacity: " << v.capacity() << std::endl;
	}
	std::cout <<"ft" << std::endl;
	std::cout << ftv.capacity() << std::endl;
	ftv.resize(5, 100);
	std::cout << ftv.capacity() << " " << ftv.size() << " " << ftv.at(4) << std::endl;
	ftv.resize(30, 100);
	std::cout << ftv.capacity() << " " << ftv.size() << " " << ftv.at(29) << std::endl;
	for (int i = 0; i < 5; i++)
	{
		ftv.resize(60 + i);
		std::cout << "capacity: " << ftv.capacity() << std::endl;
	}

	// std::cout << std::endl
	// 		  << "#===== push_back =====#" << std::endl;
	// v.resize(0);
	// v.push_back(11);
	// v.push_back(22);
	// v.push_back(33);
	// for (int i = 0; i < v.size(); i++)
	// 	std::cout << v.at(i) << " ";
	// std::cout << std::endl;

	// std::cout << std::endl
	// 		  << "#===== pop_back =====#" << std::endl;
	// v.resize(1);
	// std::cout << v.size() << std::endl;
	// v.pop_back();
	// std::cout << v.size() << std::endl;
	// // v.pop_back();
}

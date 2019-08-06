#include <iostream>
#include "Image/image.h"
using namespace std;

int main()
{
	IPL::Array2D<int> ary1(5, 5);
	ary1[2][2] = 4;
	ary1[3][3] = 9;

	/*IPL::Array2D<int> ary2(5, 5);
	ary2[0][0] = 1;
	ary2[4][4] = 16;*/

	// ≤‚ ‘øΩ±¥ππ‘Ï
	/*while (1)
	{
		IPL::Array2D<int> ary2(ary);
	}*/
	
	// ≤‚ ‘“∆∂Øππ‘Ï
	IPL::Array2D<int> ary2(std::move(ary1));
	
	while (1)
	{
		IPL::Array2D<int> ary3(std::move(ary1));
	}

	// ≤‚ ‘øΩ±¥∏≥÷µ
	/*while (1)
	{
		ary1 = ary2;
	}*/

	// ≤‚ ‘“∆∂Ø∏≥÷µ
	//ary1 = std::move(ary2);
	//ary1 = std::move(ary2);
	

	ary1.Print();
	ary2.Print();
	
	system("pause");
	return 0;
}

#include <cryptoTools/Common/CLP.h>

#include "cryptoTools/Common/BitIterator.h"
#include "cryptoTools/Common/Timer.h"
#include "cryptoTools/Crypto/PRNG.h"
#include <cryptoTools/Network/IOService.h>
#include <atomic>
#include "aby3-DB/DBServer.h"
#include <unordered_set>
#include <typeinfo>
#include <stdlib.h>

using namespace oc;

void print_all_of_SharedTabel(SharedTable T, int i, DBServer server[]);

void print_all_of_SharedTabel(SharedTable T, int i, DBServer server[])
{
	for (u64 index = 0; index < T.mColumns.size(); ++index)
	{

		aby3::i64Matrix t(T.mColumns[index].rows(), T.mColumns[index].i64Cols());
		server[i].mEnc.revealAll(server[i].mRt.mComm, T.mColumns[index], t);
		if (i == 0)
		{
			std::cout << T.mColumns[index].mName << std::endl;
			std::cout << t << std::endl;
			std::cout << std::endl;
			std::cout << std::endl;
		}
	}
}
void print_all_of_Table(Table b)
{
	int index = 0;
	while (index < b.mColumns.size())
	{
		std::cout << "'''''''" << std::endl;
		std::cout << b.mColumns[index].mName << std::endl;
		std::cout << b.mColumns[index].mData << std::endl;
		index++;
	}
}

void use_case2(u32 rows = 10,  u32 intersect = 5)
{
	u32 cols = 2;
	using namespace aby3;
	IOService ios;
	Session s01(ios, "127.0.0.1:50000", SessionMode::Server, "01");
	Session s10(ios, "127.0.0.1:50000", SessionMode::Client, "01");
	Session s02(ios, "127.0.0.1:50000", SessionMode::Server, "02");
	Session s20(ios, "127.0.0.1:50000", SessionMode::Client, "02");
	Session s12(ios, "127.0.0.1:50000", SessionMode::Server, "12");
	Session s21(ios, "127.0.0.1:50000", SessionMode::Client, "12");

	PRNG prng(oc::ZeroBlock);
	DBServer srvs[3];
	srvs[0].init(0, s02, s01, prng);
	srvs[1].init(1, s10, s12, prng);
	srvs[2].init(2, s21, s20, prng);
	// s01.mBase.get()->mGroup.get()->mSockets.front().mSocket

	// 80 bits;
	u32 hashSize = 80;

	auto keyBitCount = srvs[0].mKeyBitCount;
	std::vector<ColumnInfo>
		aCols = {ColumnInfo{"key", TypeID::IntID, keyBitCount}},
		bCols = {ColumnInfo{"key", TypeID::IntID, keyBitCount}},
		a_zeroCols = {ColumnInfo{"key", TypeID::IntID, keyBitCount}},
		b_zeroCols = {ColumnInfo{"key", TypeID::IntID, keyBitCount}},
		a_oneCols  =  {ColumnInfo{"key", TypeID::IntID, keyBitCount}},
		b_oneCols  =  {ColumnInfo{"key", TypeID::IntID, keyBitCount}};
		

	for (u32 i = 1; i < cols; ++i)
	{
		// emplace_back adds element to end of container
		aCols.emplace_back("a" + std::to_string(i), TypeID::IntID,1 );
		bCols.emplace_back("b" + std::to_string(i), TypeID::IntID,1 );
		a_zeroCols.emplace_back("a" + std::to_string(i), TypeID::IntID,1 );
		b_zeroCols.emplace_back("b" + std::to_string(i), TypeID::IntID,1 );
		a_oneCols.emplace_back("a" + std::to_string(i), TypeID::IntID,1 );
		b_oneCols.emplace_back("b" + std::to_string(i), TypeID::IntID,1 );

		
	}
	
	Table a(rows, aCols), b(rows, bCols);

	for (u64 i = 0; i < rows; ++i)
	{
		auto out = (i >= intersect);
		for (u64 j = 0; j < 2; ++j)
		{
			a.mColumns[0].mData(i, j) = i + 1;
			b.mColumns[0].mData(i, j) = i + 1 + (rows * out);
			
		}
	}
	srandom(11132);
	for (u64 i = 1; i < cols; ++i)
	{
		for (u64 j = 0; j < rows; ++j)
		{
			int k = 1;
			a.mColumns[i].mData(j, 0) = rand() %2;
			b.mColumns[i].mData(j, 0) = rand() %2 ;
		}
	}
		int zeros = 0;
		int ones = 0;
		for (u64 j = 0; j < rows; ++j){
			if (a.mColumns[1].mData(j,0) == 0) zeros =  zeros +1;
			else
			{
				ones = ones+1;
			}	
		}
		Table a_with_ones(ones, a_oneCols) ;
		int ones_index =0;
		int zeros_index =0;
		Table a_with_zeros(zeros, a_zeroCols );
		for (u64 j = 0; j < rows; ++j){
			if(a.mColumns[1].mData(j,0) == 0) {
				a_with_zeros.mColumns[0].mData(zeros_index,0) = a.mColumns[0].mData(j,0);
				a_with_zeros.mColumns[0].mData(zeros_index,1) = a.mColumns[0].mData(j,1);
				a_with_zeros.mColumns[1].mData(zeros_index,0) = 0;
				zeros_index = zeros_index +1;
			} 
			else{
				a_with_ones .mColumns[0].mData(ones_index,0) = a.mColumns[0].mData(j,0);
				a_with_ones.mColumns[0].mData(ones_index,1) = a.mColumns[0].mData(j,1);
				a_with_ones.mColumns[1].mData(ones_index,0) = 1;
				ones_index = ones_index +1;
			}
		}
		zeros = 0;
		ones = 0;
		for (u64 j = 0; j < rows; ++j){
			if (b.mColumns[1].mData(j,0) == 0) zeros =  zeros +1;
			else
			{
				ones = ones+1;
			}	
		}
		Table b_with_ones(ones, b_oneCols) ;
		ones_index =0;
		zeros_index =0;
		Table b_with_zeros(zeros, b_zeroCols );
		for (u64 j = 0; j < rows; ++j){
			if(b.mColumns[1].mData(j,0) == 0) {
				b_with_zeros.mColumns[0].mData(zeros_index,0) = b.mColumns[0].mData(j,0);
				b_with_zeros.mColumns[0].mData(zeros_index,1) = b.mColumns[0].mData(j,1);
				b_with_zeros.mColumns[1].mData(zeros_index,0) = 0;
				zeros_index = zeros_index +1;
			} 
			else{
				b_with_ones .mColumns[0].mData(ones_index,0) = b.mColumns[0].mData(j,0);
				b_with_ones.mColumns[0].mData(ones_index,1) = b.mColumns[0].mData(j,1);
				b_with_ones.mColumns[1].mData(ones_index,0) = 1;
				ones_index = ones_index +1;
			}
		}
	
	Timer t;
	bool failed = false;
	print_all_of_Table(a);
	print_all_of_Table(b);
	auto getIntermediate =[&] (int i, int filter){
		SharedTable A;
		SharedTable B;
		if (filter == 1) {
			A = (i == 0) ? srvs[i].localInput(a_with_ones) : srvs[i].remoteInput(0);
			B = (i == 1) ? srvs[i].localInput(b_with_ones) : srvs[i].remoteInput(1);
			
		}else{
			B = (i == 1) ? srvs[i].localInput(b_with_zeros ) : srvs[i].remoteInput(1);
			A = (i == 0) ? srvs[i].localInput(a_with_zeros) : srvs[i].remoteInput(0);
		}
		std::vector<SharedTable::ColRef>  First_Select_collumns; 
		First_Select_collumns.emplace_back(SharedTable::ColRef(B , B.mColumns[0]) );
		First_Select_collumns.emplace_back(SharedTable::ColRef(B , B.mColumns[1]) );
		First_Select_collumns.emplace_back(SharedTable::ColRef(A , A.mColumns[1]) );
		return srvs[i].join( SharedTable::ColRef(  A , A.mColumns[0]) , SharedTable::ColRef( B, B.mColumns[0]  ), First_Select_collumns);

	};



	auto routine = [&](int i, int filter)
	{
		setThreadName("t0");
		t.setTimePoint("start");
		SharedTable intermediateOne = getIntermediate(i,0);
		t.setTimePoint("first_intermediate");
		SharedTable intermediateZero = getIntermediate(i,1);
		t.setTimePoint("second_intermediate");
		//print_all_of_SharedTabel(intermediateZero,i,srvs);
		//print_all_of_SharedTabel(intermediateOne,i,srvs);
		SharedTable UNION;
		std::vector<SharedTable::ColRef>  SelectOnes; 
		SelectOnes.emplace_back(SharedTable::ColRef( intermediateOne , intermediateOne.mColumns[0]) );
		SelectOnes.emplace_back(SharedTable::ColRef( intermediateOne , intermediateOne.mColumns[1]) );
		SelectOnes.emplace_back(SharedTable::ColRef( intermediateOne , intermediateOne.mColumns[2]) );
		std::vector<SharedTable::ColRef>  SelectZeros; 
		SelectZeros.emplace_back(SharedTable::ColRef( intermediateZero , intermediateZero.mColumns[0]) );
		SelectZeros.emplace_back(SharedTable::ColRef( intermediateZero , intermediateZero.mColumns[1]) );
		SelectZeros.emplace_back(SharedTable::ColRef( intermediateZero , intermediateZero.mColumns[2]) );
		UNION = srvs[i].rightUnion(SharedTable::ColRef( intermediateZero, intermediateZero.mColumns[0] ),
		SharedTable::ColRef( intermediateOne, intermediateOne.mColumns[0]),  SelectZeros,SelectOnes  );
		t.setTimePoint("UNION");
		
		//print_all_of_SharedTabel( UNION,i,srvs );
		
	};


	

	auto t0 = std::thread(routine, 0,1);
	auto t1 = std::thread(routine, 1,1);
	routine(2,1);
	t0.join();
	t1.join();
	auto comm0 = (srvs[0].mRt.mComm.mNext.getTotalDataSent() + srvs[0].mRt.mComm.mPrev.getTotalDataSent());
	auto comm1 = (srvs[1].mRt.mComm.mNext.getTotalDataSent() + srvs[1].mRt.mComm.mPrev.getTotalDataSent());
	auto comm2 = (srvs[2].mRt.mComm.mNext.getTotalDataSent() + srvs[2].mRt.mComm.mPrev.getTotalDataSent());
	std::cout << "n = " << rows << "   " << comm0 + comm1 + comm2 << "\n" << t << std::endl;


}

void compare_random(u32 rows = 20, u32 cols = 2, u32 intersect = 30)
{

	using namespace aby3;
	IOService ios;
	Session s01(ios, "127.0.0.1:50000", SessionMode::Server, "01");
	Session s10(ios, "127.0.0.1:50000", SessionMode::Client, "01");
	Session s02(ios, "127.0.0.1:50000", SessionMode::Server, "02");
	Session s20(ios, "127.0.0.1:50000", SessionMode::Client, "02");
	Session s12(ios, "127.0.0.1:50000", SessionMode::Server, "12");
	Session s21(ios, "127.0.0.1:50000", SessionMode::Client, "12");

	PRNG prng(oc::ZeroBlock);
	DBServer srvs[3];
	srvs[0].init(0, s02, s01, prng);
	srvs[1].init(1, s10, s12, prng);
	srvs[2].init(2, s21, s20, prng);
	// s01.mBase.get()->mGroup.get()->mSockets.front().mSocket

	// 80 bits;
	u32 hashSize = 80;

	auto keyBitCount = srvs[0].mKeyBitCount;
	std::vector<ColumnInfo>
		aCols = {ColumnInfo{"key", TypeID::IntID, keyBitCount}},
		bCols = {ColumnInfo{"key", TypeID::IntID, keyBitCount}},
		comCols = {ColumnInfo{"key", TypeID::IntID, keyBitCount}};

	for (u32 i = 1; i < cols; ++i)
	{
		// emplace_back adds element to end of container
		aCols.emplace_back("a" + std::to_string(i), TypeID::IntID,64 );
		bCols.emplace_back("b" + std::to_string(i), TypeID::IntID,64 );
		comCols.emplace_back("c" + std::to_string(i), TypeID::IntID,64 );
	}
	
	Table a(rows, aCols), b(rows, bCols), com(rows, comCols);

	for (u64 i = 0; i < rows; ++i)
	{
		auto out = (i >= intersect);
		for (u64 j = 0; j < 2; ++j)
		{
			a.mColumns[0].mData(i, j) = i + 1;
			b.mColumns[0].mData(i, j) = i + 1 + (rows * out);
			com.mColumns[0].mData(i, j) = i + 1 + (rows * out);
		}
	}
	srandom(11011);
	for (u64 i = 1; i < cols; ++i)
	{
		for (u64 j = 0; j < rows; ++j)
		{
			int k = 1;
			if(j %2 == 0) k = 1;
			a.mColumns[i].mData(j, 0) = ((rand() %1000)) *k;
			b.mColumns[i].mData(j, 0) = (rand() %1000 );
			com.mColumns[i].mData(j, 0) = (rand() %1000 );
		}
	}
	
	Timer t;
	bool failed = false;
	auto routine = [&](int i)
	{
		setThreadName("t0");
		t.setTimePoint("start");

		auto A = (i == 0) ? srvs[i].localInput(a) : srvs[i].remoteInput(0);
		auto B = (i == 0) ? srvs[i].localInput(b) : srvs[i].remoteInput(0);
		auto C = (i == 0) ? srvs[i].localInput(com) : srvs[i].remoteInput(0);
		print_all_of_SharedTabel(A, i, srvs);
		print_all_of_SharedTabel(B, i, srvs);
		print_all_of_SharedTabel(C, i, srvs);
		if (i == 0)
			t.setTimePoint("inputs");

		if (i == 0)
			srvs[i].setTimer(t);

		SelectQuery select;
		auto REQUIRED = select.joinOn(A["key"], C["key"]);
		auto a1 = select.addInput(A["a1"]);
		auto c1 = select.addInput(C["c1"]);
		auto larger = c1 < a1;
		select.addOutput("a1", a1);
		select.addOutput("c1", c1);
		select.addOutput("larger", larger);

		auto intersection = srvs[i].joinImpl(select);
		print_all_of_SharedTabel(intersection, i, srvs);
	};
	auto t0 = std::thread(routine, 0);
	auto t1 = std::thread(routine, 1);
	routine(2);
	t0.join();
	t1.join();
}
int main(int argc, char *argv[])
{
	if (argc == 3)
	{
		use_case2(atoi(argv[1]), atoi(argv[2]));
	}
	else
	{
		//DB_threat();
		//DB_test();
		use_case2();
		//eric(10);
	}
}

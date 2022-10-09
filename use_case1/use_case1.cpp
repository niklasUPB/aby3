
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

void print_all_of_tabel(SharedTable T, int i, DBServer server[]);
/*
void DB_Intersect(u32 rows = 100, u32 cols = 3, u32 intersectionsize = 30  )
{
	using namespace aby3;
	IOService ios;
	Session s01(ios, "127.0.0.1:50001", SessionMode::Server, "01");
	Session s10(ios, "127.0.0.1:50010", SessionMode::Client, "01");
	Session s02(ios, "127.0.0.1:5002", SessionMode::Server, "02");
	Session s20(ios, "127.0.0.1:5002", SessionMode::Client, "02");
	Session s12(ios, "127.0.0.1:5003", SessionMode::Server, "12");
	Session s21(ios, "127.0.0.1:5003", SessionMode::Client, "12");
	PRNG prng(oc::ZeroBlock);
	DBServer srvs[3];
	srvs[0].init(0, s02, s01, prng);
	srvs[1].init(1, s10, s12, prng);
	srvs[2].init(2, s21, s20, prng);
	auto keyBitCount = srvs[0].mKeyBitCount;
	std::vector<ColumnInfo>
		AliceCols = { ColumnInfo{ "key", TypeID::IntID, keyBitCount } },
		BobCols = { ColumnInfo{ "key", TypeID::IntID, keyBitCount } };

	for (u32 i = 1; i < cols; ++i)
	{
		AliceCols.emplace_back("Alice" + std::to_string(i), TypeID::IntID, 32);
		BobCols.emplace_back("Bob" + std::to_string(i), TypeID::IntID, 32);
	}

	Table AliceTable(rows, AliceCols) , BobTable(rows, BobCols);
		
	for (u64 i = 0; i < rows; ++i)
	{
		auto out = (i >= intersectionsize);
		for (u64 j = 0; j < 2; ++j)
		{
			AliceTable.mColumns[0].mData(i, j) = i + 1;
			BobTable.mColumns[0].mData(i, j) = i + 1 + (rows * out);
		}
	}

	for (u64 i = 1;  i < cols; ++i){
		for (u64 j =0; j < rows; ++j){
			AliceTable.mColumns[i].mData(j, 0) = rand() %100;
			BobTable.mColumns[i].mData(j, 0) = rand() %100;	
		}
	}
	Timer t;
	bool failed = false;
	auto routine = [&](int i) { setThreadName("t0");
		t.setTimePoint("start");

		auto A = (i == 0) ? srvs[i].localInput(a) : srvs[i].remoteInput(0);
		auto B = (i == 0) ? srvs[i].localInput(b) : srvs[i].remoteInput(0);

		if (i == 0)
			t.setTimePoint("inputs");

		if (i == 0)
			srvs[i].setTimer(t);


		std::vector<SharedTable::ColRef>  First_Select_collumns;		
		for (u64 i = 0;  i < cols; ++i){
			First_Select_collumns.emplace_back(SharedTable::ColRef(B,B.mColumns[i]) );
		}
		for (u64 i = 1;  i < cols; ++i){
			First_Select_collumns.emplace_back(SharedTable::ColRef(A,A.mColumns[i]) );
			
		}
		auto result =srvs[i].join( SharedTable::ColRef(A,A.mColumns[0]) , SharedTable::ColRef(B,B.mColumns[0]), First_Select_collumns);
		if (i == 0) t.setTimePoint("intersect");
		for (u64 index = 0; index < result.mColumns.size(); ++index)
		{
			aby3::i64Matrix reveal(result.mColumns[index].rows(),  result.mColumns[index].i64Cols());
			server[i].mEnc.revealAll(server[i].mRt.mComm, T.mColumns[index], reveal);
			if (i == 0) std:: cout << reveal << std::endl;	
		}

		
	};

	auto t0 = std::thread(routine, 0);
	auto t1 = std::thread(routine, 1);
	t0.join();
	t1.join();
}
*/
void print_all_of_tabel(SharedTable T, int i, DBServer server[]){
	for (u64 index = 0; index < T.mColumns.size(); ++index)
	 {
		aby3::i64Matrix t(T.mColumns[index].rows(), T.mColumns[index].i64Cols());
		server[i].mEnc.revealAll(server[i].mRt.mComm, T.mColumns[index], t);
		if (i == 0) {
		std:: cout << t << std::endl;
		std:: cout << std::endl;
		std:: cout << std::endl;
		}
		
	 }

}

void use_case1(u32 rows = 10, u32 cols = 3, u32 intersect = 3 )  {
	using namespace aby3;
	IOService ios;
	Session s01(ios, "127.0.0.1:5001", SessionMode::Server, "01");
	Session s10(ios, "127.0.0.1:5001", SessionMode::Client, "01");
	Session s02(ios, "127.0.0.1:5002", SessionMode::Server, "02");
	Session s20(ios, "127.0.0.1:5002", SessionMode::Client, "02");
	Session s12(ios, "127.0.0.1:5003", SessionMode::Server, "12");
	Session s21(ios, "127.0.0.1:5003", SessionMode::Client, "12");
		
	PRNG prng(oc::ZeroBlock);
	DBServer srvs[3];
	srvs[0].init(0, s02, s01, prng);
	srvs[1].init(1, s10, s12, prng);
	srvs[2].init(2, s21, s20, prng);
	//s01.mBase.get()->mGroup.get()->mSockets.front().mSocket
	


	// 80 bits;
	u32 hashSize = 80;

	auto keyBitCount = srvs[0].mKeyBitCount;
	std::vector<ColumnInfo>
		aCols = { ColumnInfo{ "key", TypeID::IntID, keyBitCount } },
		bCols = { ColumnInfo{ "key", TypeID::IntID, keyBitCount } };
		

	for (u32 i = 1; i < cols; ++i)
	{
		//emplace_back adds element to end of container
		aCols.emplace_back("a" + std::to_string(i), TypeID::IntID, 32);
		bCols.emplace_back("b" + std::to_string(i), TypeID::IntID, 32);
		
	}

	Table a(rows, aCols)
		, b(rows, bCols);
		

	for (u64 i = 0; i < rows; ++i)
	{
		auto out = (i >= intersect);
		for (u64 j = 0; j < 2; ++j)
		{
			a.mColumns[0].mData(i, j) = i + 1;
			b.mColumns[0].mData(i, j) = i + 1 + (rows * out);
			
		}
	}

	for (u64 i = 1;  i < cols; ++i){
		for (u64 j =0; j < rows; ++j){
			a.mColumns[i].mData(j, 0) = rand() %100;
			b.mColumns[i].mData(j, 0) = rand() %100;
		}

	}

	Timer t;
	bool failed = false;
	auto routine = [&](int i) { setThreadName("t0");
		t.setTimePoint("start");

		auto A = (i == 0) ? srvs[i].localInput(a) : srvs[i].remoteInput(0);
		auto B = (i == 0) ? srvs[i].localInput(b) : srvs[i].remoteInput(0);
		

		if (i == 0)
			t.setTimePoint("inputs");

		if (i == 0)
			srvs[i].setTimer(t);


		std::vector<SharedTable::ColRef>  First_Select_collumns;

		
		for (u64 i = 0;  i < cols; ++i){
			First_Select_collumns.emplace_back(SharedTable::ColRef(B,B.mColumns[i]) );
		}
		for (u64 i = 1;  i < cols; ++i){
			First_Select_collumns.emplace_back(SharedTable::ColRef(A,A.mColumns[i]) );
			
		}
		
		auto result =srvs[i].join( SharedTable::ColRef(A,A.mColumns[0]) , SharedTable::ColRef(B,B.mColumns[0]), First_Select_collumns);
		
		
		if (i == 0) t.setTimePoint("intersect");
		
		if (result.rows())
		{
			if(i==0) std:: cout << "A" << std::endl;
			print_all_of_tabel(A, i , srvs );
			if(i==0) std:: cout << "B" << std::endl;
			print_all_of_tabel(B, i , srvs );
			if(i==0) std:: cout << "result" << std::endl;
			print_all_of_tabel(result, i , srvs );
			if (i == 0)  {
  
				t.setTimePoint("reveal");
			}
		}
		else
		{
			failed = true;
		}
	};

	auto t0 = std::thread(routine, 0);
	auto t1 = std::thread(routine, 1);
	routine(2);
	t0.join();
	t1.join();

	auto comm0 = (srvs[0].mRt.mComm.mNext.getTotalDataSent() + srvs[0].mRt.mComm.mPrev.getTotalDataSent());
	auto comm1 = (srvs[1].mRt.mComm.mNext.getTotalDataSent() + srvs[1].mRt.mComm.mPrev.getTotalDataSent());
	auto comm2 = (srvs[2].mRt.mComm.mNext.getTotalDataSent() + srvs[2].mRt.mComm.mPrev.getTotalDataSent());
	std::cout << "n = " << rows << "   " << comm0 + comm1 + comm2 << "\n" << t << std::endl;
	
	if (failed)
	{
		std::cout << "bad intersection" << std::endl;
		throw std::runtime_error("");
	}
}

int main(int argc, char* argv[]){
	if(argc == 4){
		use_case1( atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
	}
	else{

		use_case1();
	}

}

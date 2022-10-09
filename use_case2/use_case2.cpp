
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
		cCols = {ColumnInfo{"key", TypeID::IntID, keyBitCount}},
		bCols = {ColumnInfo{"key", TypeID::IntID, keyBitCount}};
		

	for (u32 i = 1; i < cols; ++i)
	{
		// emplace_back adds element to end of container
		aCols.emplace_back("a" + std::to_string(i), TypeID::IntID,1 );
		bCols.emplace_back("b" + std::to_string(i), TypeID::IntID,1 );
		
	}
	
	Table a(rows, aCols), b(rows, bCols), c(intersect, cCols) ;

	for (u64 i = 0; i < rows; ++i)
	{
		auto out = (i >= intersect);
		for (u64 j = 0; j < 2; ++j)
		{
			a.mColumns[0].mData(i, j) = i + 1;
			b.mColumns[0].mData(i, j) = i + 1 + (rows * out);
			if( not out) c.mColumns[0].mData(i,j) = i+1;
		}
	}
	srandom(11032);
	for (u64 i = 1; i < cols; ++i)
	{
		for (u64 j = 0; j < rows; ++j)
		{
			a.mColumns[i].mData(j, 0) = ((rand() %2));
			b.mColumns[i].mData(j, 0) = (rand() %2 );
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
		auto C = (i == 0) ? srvs[i].localInput(c) : srvs[i].remoteInput(0);
		//print_all_of_SharedTabel(A, i, srvs);
		//print_all_of_SharedTabel(B, i, srvs);
		if (i == 0)
			t.setTimePoint("inputs");

		if (i == 0)
			srvs[i].setTimer(t);

		SelectQuery select;
		SelectBundle REQUIRED = select.joinOn(A["key"], B["key"]);
		SelectBundle primary = select.addInput(B["key"]); //muss B sein stürzt sonst ab
		SelectBundle a1 = select.addInput(A["a1"]);
		SelectBundle b1 = select.addInput(B["b1"]);
		SelectBundle AND = a1 & b1;
		SelectBundle nota1 = !a1;
		SelectBundle notb1 = !b1;
		SelectBundle NAND = nota1 & notb1;
		select.addOutput("primary", primary * (NAND + AND )  );
		select.addOutput("a1", a1);
		select.addOutput("b1", b1);
		//select.addOutput("test",( NAND + AND ) );
		//select.addOutput("NAND", NAND  );
		//select.addOutput("AND", AND  );
		SharedTable intersection = srvs[i].joinImpl(select);
		std::vector<SharedTable::ColRef>  First_Select_collumns; 
		First_Select_collumns.emplace_back(SharedTable::ColRef(intersection , intersection.mColumns[0]) );
		First_Select_collumns.emplace_back(SharedTable::ColRef(intersection , intersection.mColumns[1]) );
		First_Select_collumns.emplace_back(SharedTable::ColRef(intersection , intersection.mColumns[2]) );
		auto result =srvs[i].join( SharedTable::ColRef( intersection , intersection.mColumns[0]) , SharedTable::ColRef( C, C.mColumns[0]  ), First_Select_collumns);
		print_all_of_SharedTabel(result, i, srvs);
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
		std::cout << "2 parameters pls" << std::endl;
		//eric(10);
	}
}
